#ifndef OPS_APPLY_WEIGHT_H
#define OPS_APPLY_WEIGHT_H

#include <Eigen/Dense>

using Eigen::MatrixXd;

class ApplyWeight : public Operation {
 public:
  static void compute(MatrixXd &input, MatrixXd &weight, MatrixXd &output) {
    output = weight * input;
  }
};

#endif // OPS_APPLY_WEIGHT_H