#ifndef RUNTIME_DEVICE_H
#define RUNTIME_DEVICE_H

#include <string>

class Device {
 public:
  Device() {}

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

  std::string name() const { return name_; }

  std::string addr() const { return addr_; }

  std::string type() const { return type_; }

  // TODO(santhnm2): pick a more useful comparison
  bool operator<(const Device& rhs) const {
    return this->name_ < rhs.name_;
  }

 private:
  std::string name_;
  std::string addr_;
  std::string type_;
};

#endif // RUNTIME_DEVICE_H