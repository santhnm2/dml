#ifndef OPS_APPLY_WEIGHT_H
#define OPS_APPLY_WEIGHT_H

#include <iostream>

#include <Eigen/Dense>

using Eigen::MatrixXd;

class ApplyWeight {
 public:
  static void compute(MatrixXd &input, MatrixXd &weight, MatrixXd &output) {
  	if (weight.rows() == 0) {
  		// Initialize weight
  		weight = MatrixXd(input.rows(), input.cols());
  	}
    output = weight.transpose() * input;
  }
};

#endif // OPS_APPLY_WEIGHT_H