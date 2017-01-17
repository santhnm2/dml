#ifndef RUNTIME_DEVICE_H
#define RUNTIME_DEVICE_H

#include <string>

class Device {
 public:
  Device(const std::string name, const std::string addr, 
         const std::string type) {
    name_ = name;
    addr_ = addr;
    type_ = type;
  }

  Device(const Device &d) {
    name_ = d.name_;
    addr_ = d.addr_;
    type_ = d.type_;
  }

  std::string name() { return name_; }

  std::string addr() { return addr_; }

  std::string type() { return type_; }

 private:
  std::string name_;
  std::string addr_;
  std::string type_;
};

#endif // RUNTIME_DEVICE_H