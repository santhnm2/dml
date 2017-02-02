#include "partitioner.h"

#include <iostream>
#include <map>
#include <vector>

using dml::NodeDef;

std::map<Device, std::vector<NodeDef>> 
  Partitioner::partition(DeviceManager& device_mgr, GraphManager& graph_mgr) {
  std::map<Device, std::vector<NodeDef>> placement;

  for (Device d : device_mgr.devices()) {
    placement[d];
  }

  int device_idx = 0;
  for (Node n : graph_mgr.graph()) {
    Device d = device_mgr.devices()[device_idx];
    n.setDevice(d);
    placement[d].push_back(n.def());

    ++device_idx %= device_mgr.size();
  }

  return placement;
}