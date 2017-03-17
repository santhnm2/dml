#ifndef OPS_OPERATION_H_
#define OPS_OPERATION_H_

// #include "add_bias.h"
#include "apply_weight.h"
#include "err.h"
#include "read_input.h"
#include "sigmoid.h"
#include "../graph/node.h"

// #include "softmax.h"

#include <Eigen/Dense>

using Eigen::MatrixXd;

class Operation {
 public:
  static void compute(Node *n, bool fwd) {//std::string op, MatrixXd &input, MatrixXd &weight, MatrixXd &output) {
    if (n->op() == "bias") {
      //AddBias::compute(n, fwd)//input, weight, output);
    } else if (n->op() == "error") {
      Error::compute(n, fwd);//input, weight, output);
    } else if (n->op() == "input") {
      ReadInput::compute(n, fwd);//input, weight, output);
    } else if (n->op() == "sigmoid") {
      Sigmoid::compute(n, fwd);//input, weight, output);
    } else if (n->op() == "softmax") {
      //Softmax::compute(input, weight, output);
    } else if (n->op() == "weight") {
      ApplyWeight::compute(n, fwd);//input, weight, output);
    }
  }
};

#endif // OPS_OPERATION_H_
