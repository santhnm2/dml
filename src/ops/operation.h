#ifndef OPS_OPERATION_H_
#define OPS_OPERATION_H_

#include "add_bias.h"
#include "apply_weight.h"
#include "read_input.h"
#include "softmax.h"

#include <Eigen/Dense>

using Eigen::MatrixXd;

class Operation {
 public:
  static void compute(std::string op, MatrixXd &input, MatrixXd &weight,
               MatrixXd &output) {
    if (op == "bias") {
      AddBias::compute(input, weight, output);
    } else if (op == "input") {
      ReadInput::compute(input, weight, output);
    } else if (op == "softmax") {
      Softmax::compute(input, weight, output);
    } else if (op == "weight") {
      ApplyWeight::compute(input, weight, output);
    }
  }
};

#endif // OPS_OPERATION_H_
