#include "device_mgr.h"
#include "graph_mgr.h"
#include "../graph/node.h"
#include "rpc/master_client.h"
#include "rpc/node_def.pb.h"
#include "scheduler.h"

#include <iostream>

using dml::NodeDef;

int main() {
	DeviceManager device_mgr;
  device_mgr.parseDeviceList("testdevicelist");

  GraphManager graph_mgr;
  graph_mgr.parseGraphSpec("testgraphspec");

  Scheduler sched;

  int status = sched.schedule(device_mgr, graph_mgr);
  if (status == 1) {
    std:: cout << "Failed to schedule, not enough devices" << std::endl;
    return 1;
  }

  /* 
    For each node, send NodeDef to the device where that node is located
  */

  for (int i = 0; i < graph_mgr.size(); i++) {    
    Node* node = graph_mgr.getNodeAtIndex(i);
    MasterClient master(grpc::CreateChannel(
        node->device().addr(), grpc::InsecureChannelCredentials()));
    std::string reply = master.InitNode(node->allocated_def());  // The actual RPC call!
    std::cout << "Master received: " << reply << std::endl;
  }
}