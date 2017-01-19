#ifndef RUNTIME_SCHEDULER_H
#define RUNTIME_SCHEDULER_H

#include <vector>

#include "device_mgr.h"
#include "graph_mgr.h"

class Scheduler {
 public:
  int schedule(const DeviceManager& device_mgr, GraphManager& graph_mgr);
 private:
};

#endif // RUNTIME_SCHEDULER_H