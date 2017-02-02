#include <iostream>
#include <queue>
#include <string>

#include <pthread.h>

#include "device_mgr.h"
#include "graph_mgr.h"
#include "../graph/node.h"
#include "rpc/protos/node_def.pb.h"
#include "rpc/worker_service.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using dml::NodeDef;

pthread_mutex_t waiting_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t waiting_cv = PTHREAD_COND_INITIALIZER;
std::queue<Node*> fwd_waiting;
std::queue<Node*> fwd_ready;
std::queue<Node*> bwd;

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
  if (pthread_create(&server_thread, NULL, RunServer, argv[2])) {
    // TODO(santhnm2): handle error
    std::cout << "Error creating pthread." << std::endl;
    return 1;
  }
  if (pthread_join(server_thread, NULL)) {
    // TODO(santhnm2): handle error
    std::cout << "Error joining pthread." << std::endl;
    return 1;
  }
  return 0;
}