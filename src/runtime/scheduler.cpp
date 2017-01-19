#include "scheduler.h"

#include "device.h"
#include "../graph/node.h"

#include <iostream>
#include <queue>

int Scheduler::schedule(const DeviceManager& device_mgr, GraphManager& graph_mgr) {
  /*
    0) Verify number of devices >= number of nodes 
    1) Add devices to a queue
    2) Add nodes to a queue
    3) While node queue not empty:
    4)  dequeue node, dequeue device
    5)  assign node to device
  */

  if (device_mgr.size() < graph_mgr.size()) {
    return 1;
  }

  for (int i = 0; i < graph_mgr.size(); i++) {
    Node* node = graph_mgr.getNodeAtIndex(i);
    node->setDevice(device_mgr.getDeviceAtIndex(i));
  }

  /*std::queue<Device> devices;
  std::queue<Node> nodes;

  for (Device d : device_mgr.devices()) {
    devices.push(d);
  }

  for (Node n : *graph_mgr.graph()) {
    nodes.push(n);
  }

  while (!nodes.empty()) {
    Device d = devices.front();
    devices.pop();

    Node n = nodes.front();
    nodes.pop();

    std::cout << "Assigning device \"" << d.name() << "\" to node \"" 
    << n.name() << "\"" << std::endl;

    n->setDevice(d);
  }*/

  return 0;
}