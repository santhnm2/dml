#ifndef OPS_ERR_H
#define OPS_ERR_H

#include <math.h>

#include <Eigen/Dense>

#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono> 

#include "../graph/node.h"

using Eigen::MatrixXd;

class Error {
 public:
  static void compute(Node *n, bool fwd) {
    if (fwd) {
      if (n->data3.rows() == 0) {
        n->data3 = MatrixXd::Zero(n->data1.rows(), n->data1.cols());  
      }
      
      for (int i = 0; i < n->data1.rows(); i++) {
        n->data3(i, 0) = n->data2(i, 0) - n->data1(i, 0);
      }

      
      //std::this_thread::sleep_for (std::chrono::seconds(2));
    } else {
      double loss = 0.0;
      for (int i = 0; i < n->data3.rows(); i++) {
        loss += (n->data3(i, 0) * n->data3(i, 0));
      }
      loss /= 2.0;
      std::cout << "Loss = " << loss << std::endl;
      // std::cout << "Loss: " << n->data3.transpose() << std::endl;
      // n->inputs()[1]->data2 = MatrixXd::Zero(1, 1);
      // for (int i = 0; i < n->data1.rows(); i++) {
      //   n->inputs()[1]->data2(0, 0) += (n->data1(i, 0) - n->data2(i, 0));
      // }
      // n->inputs()[1]->data2(0, 0) = n->inputs()[1]->data2(0, 0) * -1.0 / (2 * n->data1.rows());


    }
  }
};

#endif // OPS_ERR_H