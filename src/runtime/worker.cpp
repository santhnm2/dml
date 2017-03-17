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

// Wait cycle
// 1) Wake up
// 2) Move everything with dependencies == 0 to running queue
// 3) Run everything in running queue and remove dependencies
// 4) Move everything in running queue to backward queue

void* Waiting(void* arg) {
  bool fwd = true;

  int iterations = 0;
  while (iterations < 3001) {
    pthread_mutex_lock(&waiting_lock);
    // std::cout << "Waiting: Acquired waiting lock" << std::endl;
    while (fwd && fwd_waiting.empty()) {
      // std::cout << "Waiting: Going to sleep" << std::endl;
      // Wait for nodes to be inserted in to the waiting queue
      pthread_cond_wait(&waiting_cv, &waiting_lock);
      // std::cout << "Waiting: Woke up!" << std::endl;
    }
    
    if (fwd) {
      // Move any nodes with all dependencies met to the running queue
      auto it = fwd_waiting.begin();
      while (it != fwd_waiting.end()) {
        Node *n = it->second;
        if (n->getForwardDependencies() == 0) {
            // std::cout << "Moving node \"" << n->name() << "\" to the running queue." << std::endl; 
            fwd_ready.insert({n->name(), n});
            it = fwd_waiting.erase(it);
        } else {
          it++;
        }
      }

      // Run all nodes in the running queue
      it = fwd_ready.begin();
      while (it != fwd_ready.end()) { 
        Node *n = it->second;

        // std::cout << "Running node \"" << n->name() << "\"." << std::endl;

        //n->compute();
        Operation::compute(n, fwd);

        for (auto output_name : n->output_names()) {
          Node *n_output = fwd_waiting[output_name];
          // n_output->setInput(n->getOutput());
          int fwd_deps = n_output->getForwardDependencies();
          n_output->setForwardDependencies(fwd_deps-1);
          // std::cout << "Set node \"" << n_output->name() << "\"'s forward dependencies to " << fwd_deps-1 << std::endl;
        }

        // std::cout << "Set node \"" << n->name() << "\"'s backward dependencies to " << n->outputs().size() << std::endl;
        n->setBackwardDependencies(n->outputs().size());
        bwd.insert({n->name(), n});
        
        it = fwd_ready.erase(it);

        if (fwd_waiting.empty() && fwd_ready.empty()) {
          std::cout << "Iteration " << iterations + 1 << ": ";
          fwd = false;
        }
      } 
    } else {
      auto it = bwd.begin();
      while (it != bwd.end()) {
        Node *n = it->second;
        if (n->getBackwardDependencies() == 0) {
          // std::cout << "Running node \"" << n->name() << "\" in reverse." << std::endl;
          Operation::compute(n, fwd);

          for (auto input_name : n->input_names()) {
            Node *n_input = bwd[input_name];
            // n_output->setInput(n->getOutput());
            int bwd_deps = n_input->getBackwardDependencies();
            n_input->setBackwardDependencies(bwd_deps-1);
            // std::cout << "Set node \"" << n_input->name() << "\"'s dependencies to " << bwd_deps-1 << std::endl;
          }

          n->setForwardDependencies(n->inputs().size());
          fwd_waiting.insert({n->name(), n});
          it = bwd.erase(it);
        } else {
          it++;
        }

        if (bwd.size() == 0) {
          fwd = true;
          iterations++;
        }
      }
    }



    // it = bwd.begin();
    // while (it != bwd.end()) {
    //   Node *n = it->second;

    //   // n->computeBwd();

    // }

    pthread_mutex_unlock(&waiting_lock);
  }
}

int main(int argc, char* argv[]) {
  // TODO(santhnm2): implement check of ready queues and execution

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

  if (pthread_join(server_thread, NULL)) {
    // TODO(santhnm2): handle error
    std::cout << "Error joining pthread." << std::endl;
    return 1;
  }

  if (pthread_join(waiting_thread, NULL)) {
    // TODO(santhnm2): handle error
    std::cout << "Error joining pthread." << std::endl;
  }
  
  return 0;
}