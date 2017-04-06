#ifndef RUNTIME_DEVICE_MANAGER_H
#define RUNTIME_DEVICE_MANAGER_H

#include <string>
#include <vector>

#include "runtime/device.h"

class DeviceManager {
 public:
  DeviceManager(const std::string filename);
  std::vector<Device> devices() const;
  Device getDeviceAtIndex(int idx) const;
  int size() const;

 private:
  std::vector<Device> device_list_;
};

#endif // RUNTIME_DEVICE_MANAGER_H