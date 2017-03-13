#ifndef OPS_OPS_STORE_H
#define OPS_OPS_STORE_H

#include <string>

#include "operation.h"
#include "add_bias.h"
#include "apply_weight.h"
#include "softmax.h"

class OpsStore {
 public:
  static Operation requestOp(std::string op_str) {
    if (op_str == "bias") {
      AddBias op;
      return op;
    } else if (op_str == "softmax") {
      Softmax op;
      return op;
    } else if (op_str == "weight") {
      ApplyWeight op;
      return op;
    }

    Operation op;
    return op;
  }
};

#endif // OPS_OPS_STORE_H