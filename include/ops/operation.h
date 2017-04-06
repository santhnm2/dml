#ifndef OPS_OPERATION_H_
#define OPS_OPERATION_H_

#include "ops/apply_weight.h"
#include "ops/err.h"
#include "ops/read_input.h"
#include "ops/sigmoid.h"
#include "graph/node.h"

#include <Eigen/Dense>

using Eigen::MatrixXd;

class Operation {
 public:
  static void compute(Node* n, bool fwd) {
    if (n->op() == "error") {
      Error::compute(n, fwd);
    } else if (n->op() == "input") {
      ReadInput::compute(n, fwd);
    } else if (n->op() == "sigmoid") {
      Sigmoid::compute(n, fwd);
    } else if (n->op() == "weight") {
      ApplyWeight::compute(n, fwd);
    }
  }
};

#endif // OPS_OPERATION_H_
