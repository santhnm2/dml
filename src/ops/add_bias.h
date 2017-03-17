#ifndef OPS_ADD_BIAS_H
#define OPS_ADD_BIAS_H

#include <math.h>

#include <Eigen/Dense>

using Eigen::MatrixXd;

class AddBias {
 public:
  static void compute(MatrixXd &input, MatrixXd &weight, MatrixXd &output) {
    if (weight.rows() == 0) {
      weight = MatrixXd::Zero(input.rows(), 10);
    }

    output = input + weight;
  }
};

#endif // OPS_ADD_BIAS_H