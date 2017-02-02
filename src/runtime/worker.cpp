#include "device_mgr.h"
#include "graph_mgr.h"
#include "../graph/node.h"
#include "rpc/protos/node_def.pb.h"
#include "rpc/worker_service.h"

#include <iostream>
#include <queue>
#include <string>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using dml::NodeDef;

std::queue<Node*> fwd_waiting;
std::queue<Node*> fwd_ready;
std::queue<Node*> bwd;

void RunServer(std::string server_address) {
  WorkerServiceImpl service;

  ServerBuilder builder;

  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

  builder.RegisterService(&service);

  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  server->Wait();
}

int main(int argc, char* argv[]) {
  // TODO(santhnm2): intialize mutex and condition variable
  // TODO(santhnm2): start worker service in new thread
  // TODO(santhnm2): implement check of ready queues and execution

  if (argc != 3) {
    std::cout << "Usage: ./worker [device_list_file] [server address]"
    << std::endl;
    return 1;
  }

  std::string device_list_file(argv[1]);
  std::string server_address(argv[2]);

  DeviceManager device_mgr(device_list_file);

  RunServer(server_address);

  return 0;
}