#ifndef OPS_SOFTMAX_H
#define OPS_SOFTMAX_H

#include <math.h>

#include <Eigen/Dense>

using Eigen::MatrixXd;

class Softmax {
 public:
  static void compute(MatrixXd &input, MatrixXd &weight, MatrixXd &output) {
    weight = MatrixXd::Zero(input.rows(), input.cols());

    for (int i = 0; i < input.rows(); i++) {
      double sum_exp = 0.0;

      for (int j = 0; j < input.cols(); j++) {
          sum_exp += exp(input(i,j)); 
      }

      for (int j = 0; j < input.cols(); j++) {
        if (sum_exp > 0) {
          weight(i,j) = exp(input(i,j)) / sum_exp;
        }
      }
    }
    
    output = MatrixXd::Zero(input.rows(), 1);

    for (int i = 0; i < weight.rows(); i++) {
      int max = 0;
      for (int j = 1; j < weight.cols(); j++) {
        if (weight(i, j) > weight(i, max)) {
          max = j;
        }
      }
      output(i, 0) = max+1;
    }
    std::cout << output << std::endl;
  }
};

#endif // OPS_SOFTMAX_H