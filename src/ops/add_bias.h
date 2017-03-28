#ifndef OPS_ADD_BIAS_H
#define OPS_ADD_BIAS_H

#include <math.h>

#include <Eigen/Dense>

using Eigen::MatrixXd;

class AddBias {
 public:
  static void compute(Node* n, bool fwd) {
    if (fwd) {
    	n->data1.conservativeResize(n->data1.rows(), n->data1.cols()+1);
    	for (int i = 0; i < n->data1.rows(); i++) {
    		n->data1(i, n->data1.cols()-1) = 1;
    	}
    	n->outputs()[0]->data1 = n->data1;
    }
  }
};

#endif // OPS_ADD_BIAS_H