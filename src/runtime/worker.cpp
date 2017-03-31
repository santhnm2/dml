#include <iostream>
#include <string>
#include <unordered_map>

#include <pthread.h>

#include "device_mgr.h"
#include "../graph/node.h"
#include "../ops/operation.h"
#include "rpc/protos/node_def.pb.h"
#include "rpc/worker_service.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using dml::NodeDef;

pthread_mutex_t waiting_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t waiting_cv = PTHREAD_COND_INITIALIZER;
pthread_mutex_t ready_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t ready_cv = PTHREAD_COND_INITIALIZER;
std::unordered_map<std::string, Node*> fwd_waiting;
std::unordered_map<std::string, Node*> fwd_ready;
std::unordered_map<std::string, Node*> bwd;

int iterations = 1000;

void* RunServer(void* arg) {
  std::string server_address((char*) arg);

  WorkerServiceImpl service;

  ServerBuilder builder;

  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

  builder.RegisterService(&service);

  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  server->Wait();
}

// TODO(santhnm2): Document this better
// Control flow:
// If forward:
//  Move every node in waiting queue with dependencies == 0 to ready queue
//  Run every node in ready queue and remove dependencies
//  Move every node in ready queue to backward queue
//  If every node is in backward queue:
//    forward = false
// Else:
//  Run every node in backward queue and remove dependencies
//  Move every node in backward queue to waiting queue
//  If every node is in waiting queue:
//    forward = true

void* Waiting(void* arg) {
  bool fwd = true;

  int cur_iter = 0;
  while (cur_iter < iterations) {
    pthread_mutex_lock(&waiting_lock);
    while (fwd && fwd_waiting.empty()) {
      // Wait for nodes to be inserted in to the waiting queue
      pthread_cond_wait(&waiting_cv, &waiting_lock);
    }
    
    if (fwd) {
      // Move any nodes with all dependencies met to the ready queue
      auto it = fwd_waiting.begin();
      while (it != fwd_waiting.end()) {
        Node *n = it->second;
        if (n->getForwardDependencies() == 0) {
            fwd_ready.insert({n->name(), n});
            it = fwd_waiting.erase(it);
        } else {
          it++;
        }
      }

      // Run all nodes in the ready queue
      it = fwd_ready.begin();
      while (it != fwd_ready.end()) {
        Node *n = it->second;

        Operation::compute(n, fwd);

        for (auto output_name : n->output_names()) {
          Node *n_output = fwd_waiting[output_name];
          int fwd_deps = n_output->getForwardDependencies();
          n_output->setForwardDependencies(fwd_deps-1);
        }

        n->setBackwardDependencies(n->outputs().size());
        bwd.insert({n->name(), n});
        
        it = fwd_ready.erase(it);

        if (fwd_waiting.empty() && fwd_ready.empty()) {
          std::cout << std::endl << "Iteration " << cur_iter + 1 << ": " << std::endl;
          fwd = false;
        }
      } 
    } else {
      auto it = bwd.begin();
      while (it != bwd.end()) {
        Node *n = it->second;
        if (n->getBackwardDependencies() == 0) {
          Operation::compute(n, fwd);

          for (auto input_name : n->input_names()) {
            Node *n_input = bwd[input_name];
            int bwd_deps = n_input->getBackwardDependencies();
            n_input->setBackwardDependencies(bwd_deps-1);
          }

          n->setForwardDependencies(n->inputs().size());
          fwd_waiting.insert({n->name(), n});
          it = bwd.erase(it);
        } else {
          it++;
        }

        if (bwd.size() == 0) {
          fwd = true;
          cur_iter++;
        }
      }
    }
    
    pthread_mutex_unlock(&waiting_lock);
  }
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cout << "Usage: ./worker [device_list_file] [server address]"
    << std::endl;
    return 1;
  }

  std::string device_list_file(argv[1]);

  DeviceManager device_mgr(device_list_file);

  pthread_t server_thread;
  pthread_t waiting_thread;

  if (pthread_create(&server_thread, NULL, RunServer, argv[2])) {
    // TODO(santhnm2): handle error
    std::cout << "Error creating pthread." << std::endl;
    return 1;
  }

  if (pthread_create(&waiting_thread, NULL, Waiting, NULL)) {
    // TODO(santhnm2): handle error
    std::cout << "Error creating pthread." << std::endl;
  }

  // if (pthread_join(server_thread, NULL)) {
  //   // TODO(santhnm2): handle error
  //   std::cout << "Error joining pthread." << std::endl;
  //   return 1;
  // }

  if (pthread_join(waiting_thread, NULL)) {
    // TODO(santhnm2): handle error
    std::cout << "Error joining pthread." << std::endl;
  }
  
  return 0;
}