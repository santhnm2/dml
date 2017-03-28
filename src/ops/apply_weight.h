#ifndef OPS_APPLY_WEIGHT_H
#define OPS_APPLY_WEIGHT_H

#include <iostream>

#include "../graph/node.h"

#include <Eigen/Dense>

using Eigen::MatrixXd;

class ApplyWeight {
 public:
  static void compute(Node* n, bool fwd) {//MatrixXd &input, MatrixXd &weight, MatrixXd &output, vector) {
  	if (fwd) {
  		if (n->data2.rows() == 0) {
    		// Initialize weight
    		n->data2 = MatrixXd::Zero(n->data1.cols(), 1);

        for (int i = 0; i < n->data2.rows(); i++) {
          for (int j = 0; j < n->data2.cols(); j++) {
            n->data2(i, j) = 2 * static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 1;
          }
        }
    	}
      // std::cout << "Weight shape = (" << n->data2.rows() << ", " << n->data2.cols() << ")" << std::endl;

      // std::cout << n->data2.transpose() << std::endl << std::endl;
    	
      n->outputs()[0]->data1 = n->data1 * n->data2;
    } else {
      // std::cout << "Input shape = (" << n->data1.rows() << ", " << n->data1.cols() << ")" << std::endl;
      // std::cout << "sigmoid shape = (" << n->outputs()[0]->data3.rows() << ", " << n->outputs()[0]->data3.cols() << ")" << std::endl;
      MatrixXd gradient = n->data1.transpose() * n->outputs()[0]->data3;
      // std::cout << "Gradient shape = (" << gradient.rows() << ", " << gradient.cols() << ")" << std::endl;
       // std::cout << gradient.transpose() << std::endl << std::endl;
      n->data2 += gradient;
     // std::cout << n->data2.transpose() << std::endl << std::endl;
    }
  }
};

#endif // OPS_APPLY_WEIGHT_H