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

  // TODO(santhnm2): add baseline partitioner

  return placement;
}