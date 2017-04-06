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

      n->bwd = n->fwd_data - n->fwd_input;
      
      int correct = 0;
      int incorrect = 0;

      for (int i = 0; i < n->fwd_input.rows(); i++) {
        int pred_idx = 0;
        for (int j = 0; j < n->fwd_input.cols(); j++) {
          if (n->fwd_input(i, j) > n->fwd_input(i, pred_idx)) {
            pred_idx = j;
          }
        }

        int label_idx = 0;
        for (int j = 0; j < n->fwd_data.cols(); j++) {
          if (n->fwd_data(i, j) > n->fwd_data(i, label_idx)) {
            label_idx = j;
          }
        }

        if (pred_idx == label_idx) {
          correct++;
        } else {
          incorrect++;
        }

      }
      std::cout << correct << " correct predictions, " << incorrect << " incorrect predictions" << std::endl;
    }
  }
};

#endif // OPS_ERR_H