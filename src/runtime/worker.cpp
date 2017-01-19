#include "device_mgr.h"
#include "graph_mgr.h"
#include "../graph/node.h"
#include "rpc/node_def.pb.h"
#include "rpc/worker_service.h"
#include "scheduler.h"

#include <iostream>
#include <string>

using dml::NodeDef;

int main(int argc, char* argv[]) {
  /*
    1) Start worker service
    2) Instantiate node
  */

  // 0.0.0.0:50051

  if (argc != 2) {
    std::cout << "Usage: ./worker [server address]" << std::endl;
    return 1;
  }

  std::string addr(argv[1]);

  WorkerService server;
  server.Run(addr);

  return 0;
}