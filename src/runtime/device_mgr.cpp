#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "device_mgr.h"

DeviceManager::DeviceManager(const std::string filename) {
  std::ifstream device_file(filename.c_str(), std::ifstream::in);
  std::string name;
  std::string addr;
  std::string type;
  std::string newline;

  if (device_file.is_open()) {
    while (getline(device_file, name) && getline(device_file, addr) &&
           getline(device_file, type)) {
      Device d(name, addr, type);
      device_list_.push_back(d);
      getline(device_file, newline);
    }
    device_file.close();
  }
}

std::vector<Device> DeviceManager::devices() const {
  return device_list_;
}

Device DeviceManager::getDeviceAtIndex(int idx) const {
  return device_list_[idx];
}

int DeviceManager::size() const {
  return device_list_.size();
}