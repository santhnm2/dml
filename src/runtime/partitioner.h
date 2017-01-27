#ifndef RUNTIME_PARTITIONER_H
#define RUNTIME_PARTITIONER_H

#include <map>
#include <vector>

#include "device.h"
#include "rpc/node_def.pb.h"
#include "device_mgr.h"
#include "graph_mgr.h"

using dml::NodeDef;

class Partitioner {
 public:
  std::map<Device, std::vector<NodeDef>> 
  	partition(DeviceManager& device_mgr, GraphManager& graph_mgr);
};

#endif // RUNTIME_PARTITIONER_H