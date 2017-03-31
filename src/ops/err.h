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

      // std::cout << n->fwd_input << std::endl;


      // for (int i = 0; i < n->bwd.rows(); i++) {
      //   for (int j = 0; j < n->bwd.cols(); j++) {
          n->bwd = n->fwd_data - n->fwd_input;
      //   }
      // }

      // double loss = 0.0;
      // for (int i = 0; i < n->bwd.rows(); i++) {
      //   for (int j = 0; j < n->bwd.cols(); j++) {
      //     loss += (n->bwd(i, j) * n->bwd(i, j));  
      //   }
      // }
      // loss /= 2.0;
      
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
          // std::cout << "Correct!" << std::endl;
          correct++;
        } else {
          // std::cout << "Predicted " << pred_idx << " but correct answer was " << label_idx << std::endl;
          incorrect++;
        }

      }
      std::cout << correct << " correct predictions, " << incorrect << " incorrect predictions" << std::endl;
      // std::cout << "Loss = " << loss << std::endl;
    }
  }
};

#endif // OPS_ERR_H