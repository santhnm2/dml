#ifndef OPS_SIGMOID_H
#define OPS_SIGMOID_H

#include <math.h>

#include <iostream>

#include "../graph/node.h"

#include <Eigen/Dense>

using Eigen::MatrixXd;

class Sigmoid {
 public:
  static void compute(Node *n, bool fwd) {
    if (fwd) {
      n->outputs()[0]->data1 = MatrixXd::Zero(n->data1.rows(), n->data1.cols());

      for (int i = 0; i < n->data1.rows(); i++) {
        for (int j = 0; j < n->data1.cols(); j++) {
          n->outputs()[0]->data1(i, j) = 1.0 / (1.0 + exp(-n->data1(i, j)));  
        }
      }
    } else {
      MatrixXd temp = MatrixXd::Zero(n->data1.rows(), n->data2.rows());
      for (int i = 0; i < n->data1.rows(); i++) {
        for (int j = 0; j < n->data1.cols(); j++) {
          double denom = (1.0 + exp(-n->data1(i, j)));
          temp(i, j) = exp(-n->data1(i, j)) / (denom * denom);
        }
      }
      
      n->data1 = n->data2(0, 0) * temp;
    }
  }
};

#endif // OPS_SIGMOID_H