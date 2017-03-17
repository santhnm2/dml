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
    	
      n->outputs()[0]->data1 = n->data1 * n->data2;
    } else {
      MatrixXd gradient = -.01 * n->data1.transpose() * n->outputs()[0]->data1;
      n->data2 += gradient;
    }
  }
};

#endif // OPS_APPLY_WEIGHT_H