#ifndef OPS_ADD_BIAS_H
#define OPS_ADD_BIAS_H

#include <math.h>

#include <Eigen/Dense>

using Eigen::MatrixXd;

class AddBias {
 public:
  static void compute(MatrixXd &input, MatrixXd &weight, MatrixXd &output) {
    // output = input;
    // output.conservativeResize(output.rows(), output.cols()+1);

    // int cols = output.cols();
    // for (int i = 0; i < output.rows(); i++) {
    //   output(i, cols-1) = 1;
    // }

    if (weight.rows() == 0) {
      weight = MatrixXd::Zero(input.rows(), 10);
    }

    output = input + weight;
  }
};

#endif // OPS_ADD_BIAS_H