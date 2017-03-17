#ifndef OPS_APPLY_WEIGHT_H
#define OPS_APPLY_WEIGHT_H

#include <iostream>

#include "../graph/node.h"

#include <Eigen/Dense>

using Eigen::MatrixXd;

class ApplyWeight {
 public:
  static void compute(Node *n, bool fwd) {//MatrixXd &input, MatrixXd &weight, MatrixXd &output, vector) {
  	if (fwd) {
  		if (n->data2.rows() == 0) {
    		// Initialize weight
    		n->data2 = MatrixXd::Zero(n->data1.cols(), 1);
    	}
    	// std::cout << input.row(0) << std::endl << std::endl;
    	// std::cout << weight.col(0) << std::endl << std::endl;
      // n->setOutput(n->getInput() * n->getWeight());
      n->outputs()[0]->data1 = n->data1 * n->data2;
      // std::cout << output.col(0) << std::endl << std::endl;
    } else {
      MatrixXd gradient = -.01 * n->data1.transpose() * n->outputs()[0]->data1;
     // std::cout << gradient.transpose() << std::endl;
      n->data2 += gradient;

    }
  }

  // static void computeBwd(MatrixXd &input, MatrixXd &weight, MatrixXd &output) {
  // 	output = input.transpose() * output;

  // 	weight -= 0.5 * output;
  // }
};

#endif // OPS_APPLY_WEIGHT_H