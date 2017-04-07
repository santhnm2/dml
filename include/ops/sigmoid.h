#ifndef OPS_SIGMOID_H
#define OPS_SIGMOID_H

#include <math.h>

#include <iostream>

#include "graph/node.h"

#include <Eigen/Dense>

using Eigen::MatrixXd;

class Sigmoid {
 public:
  static void compute(Node *n, bool fwd) {
    if (fwd) {
      n->fwd_data = MatrixXd::Zero(n->fwd_input.rows(), n->fwd_input.cols());

      // 1 / [ exp(-x) + 1 ]
      n->fwd_data = ((-n->fwd_input).array().exp() + 1).inverse().matrix();

      n->outputs()[0]->fwd_input = n->fwd_data;
    } else {
      if (n->bwd.rows() == 0) {
        n->bwd = MatrixXd::Zero(n->fwd_input.rows(), n->fwd_input.cols());  
      }

      // x * (1-x)
      n->bwd = ( n->fwd_data.array() * (1 - n->fwd_data.array()) ).matrix();

      n->bwd = n->outputs()[0]->bwd.cwiseProduct(n->bwd); 
    }
  }
};

#endif // OPS_SIGMOID_H