#ifndef OPS_SIGMOID_H
#define OPS_SIGMOID_H

#include <math.h>

#include <iostream>

#include "node.h"

#include <Eigen/Dense>

using Eigen::MatrixXd;

class Sigmoid {
 public:
  static void compute(Node *n, bool fwd) {
    if (fwd) {
      n->fwd_data = MatrixXd::Zero(n->fwd_input.rows(), n->fwd_input.cols());

      for (int i = 0; i < n->fwd_input.rows(); i++) {
        for (int j = 0; j < n->fwd_input.cols(); j++) {
          n->fwd_data(i, j) = 1.0 / (1.0 + exp(-n->fwd_input(i, j)));
        }
      }
      n->outputs()[0]->fwd_input = n->fwd_data;
    } else {
      if (n->bwd.rows() == 0) {
        n->bwd = MatrixXd::Zero(n->fwd_input.rows(), n->fwd_input.cols());  
      }

      for (int i = 0; i < n->bwd.rows(); i++) {
        for (int j = 0; j < n->bwd.cols(); j++) {
          n->bwd(i, j) = n->fwd_data(i, j) * (1 - n->fwd_data(i, j));
        }
      }

      n->bwd = n->outputs()[0]->bwd.cwiseProduct(n->bwd); 
    }
  }
};

#endif // OPS_SIGMOID_H