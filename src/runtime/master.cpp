#include "device_mgr.h"
#include "graph_mgr.h"
#include "../graph/node.h"
#include "rpc/master_client.h"
#include "rpc/protos/node_def.pb.h"
#include "partitioner.h"

#include <iostream>
#include <map>
#include <vector>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using dml::InitNodeRequest;
using dml::InitNodeResponse;
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

  Partitioner partitioner;

  std::map<Device, std::vector<NodeDef>> placement = 
    partitioner.partition(device_mgr, graph_mgr);

  for (auto const& it : placement) {
    MasterClient mc(grpc::CreateChannel(
        it.first.addr(), grpc::InsecureChannelCredentials()));
    std::string response = mc.InitNode(it.second);

    std::cout << "Master received: " << response << std::endl;
  }

  // TODO(santhnm2): start computation
}