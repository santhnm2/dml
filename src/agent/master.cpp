#include "runtime/device_mgr.h"
#include "runtime/graph_mgr.h"
#include "graph/node.h"
#include "agent/master_client.h"
#include "node_def.pb.h"

#include <iostream>
#include <map>
#include <vector>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using dml::InitRequest;
using dml::InitResponse;
using dml::NodeDef;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cout << "Usage: ./master [device list file] [graph spec file]"
    << std::endl;
    return 1;
  }

  std::string device_list_file(argv[1]);
  std::string graph_spec_file(argv[2]);

  DeviceManager device_mgr(device_list_file);

  GraphManager graph_mgr(graph_spec_file);

  std::vector<NodeDef> graphDef = graph_mgr.graphDef();
  int iterations = graph_mgr.iterations();

  std::cout << iterations << std::endl;
  std::cout << device_mgr.devices().size() << std::endl;

  for (auto it : device_mgr.devices()) {

    std::cout << it.name() << std::endl;

    MasterClient mc(grpc::CreateChannel(
      it.addr(), grpc::InsecureChannelCredentials()));
    std::string response = mc.Init(graphDef, iterations);

    std::cout << response << std::endl;

    graph_mgr.eraseGraph();
  }
}