#ifndef OPS_ERR_H
#define OPS_ERR_H

#include <math.h>

#include <Eigen/Dense>

#include <iostream>

#include "../graph/node.h"

using Eigen::MatrixXd;

class Error {
 public:
  static void compute(Node *n, bool fwd) {
    if (fwd) {
      // Do nothing
    } else {
      if (n->bwd.rows() == 0) {
        n->bwd = MatrixXd::Zero(n->fwd_input.rows(), n->fwd_input.cols());
      }

      for (int i = 0; i < n->fwd_input.rows(); i++) {
        n->bwd(i, 0) = n->fwd_data(i, 0) - n->fwd_input(i, 0);
      }

      double loss = 0.0;
      for (int i = 0; i < n->bwd.rows(); i++) {
        loss += (n->bwd(i, 0) * n->bwd(i, 0));
      }
      loss /= 2.0;
      std::cout << "Loss = " << loss << std::endl;
    }
  }
};

#endif // OPS_ERR_H