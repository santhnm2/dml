#ifndef RUNTIME_DEVICE_MANAGER_H
#define RUNTIME_DEVICE_MANAGER_H

#include <string>
#include <vector>

#include "device.h"

class DeviceManager {
 public:
  void parseDeviceList(const std::string filename);
  std::vector<Device> devices() const;
  Device getDeviceAtIndex(int idx) const;
  int size() const;

 private:
  std::vector<Device> device_list_;
};

#endif // RUNTIME_DEVICE_MANAGER_H