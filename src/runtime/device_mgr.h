#ifndef RUNTIME_DEVICE_MANAGER_H
#define RUNTIME_DEVICE_MANAGER_H

#include <string>
#include <vector>

#include "device.h"

class DeviceManager {
 public:
  void parseDeviceList(const std::string filename);
  Device getDeviceAtIndex(int idx);

 private:
  std::vector<Device> device_list_;
};

#endif // RUNTIME_DEVICE_MANAGER_H