#ifndef OPS_ADD_BIAS_H
#define OPS_ADD_BIAS_H

#include <math.h>

#include <Eigen/Dense>

using Eigen::MatrixXd;

class AddBias : public Operation {
 public:
  void compute(MatrixXd &input, MatrixXd &weight, MatrixXd &output) {
    output = input;
    output.conservativeResize(output.rows(), output.cols()+1);

    int cols = output.cols();
    for (int i = 0; i < output.rows(); i++) {
      output(i, cols-1) = 1;
    }
  }
};

#endif // OPS_ADD_BIAS_H