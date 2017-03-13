#ifndef OPS_SOFTMAX_H
#define OPS_SOFTMAX_H

#include <math.h>

#include <Eigen/Dense>

using Eigen::MatrixXd;

class Softmax : public Operation {
 public:
  void compute(MatrixXd &input, MatrixXd &weight, MatrixXd &output) {
    output = MatrixXd(input.rows(), 1);

    double sum_exp = 0.0;

    for (int i = 0; i < input.rows(); i++) {
        sum_exp += exp(input(1,0)); 
    }

    for (int i = 0; i < input.rows(); i++) {
      output(i,0) = exp(input(i,0)) / sum_exp;
    }
  }
};

#endif // OPS_SOFTMAX_H