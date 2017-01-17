#include <iostream>
#include <fstream>
#include <string>

#include "device_mgr.h"

void DeviceManager::parseDeviceList(const std::string filename) {
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

Device DeviceManager::getDeviceAtIndex(int idx) {
  //TODO(santhnm2): add error handling
  return device_list_[idx];
}