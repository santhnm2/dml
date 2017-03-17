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
  static void compute(Node *n, bool fwd) {//)MatrixXd &input, MatrixXd &weight, MatrixXd &output) {
    if (fwd) {
      //std::cout << "y_hat:" << std::endl;
      //std::cout << n->data1 << std::endl;
      double loss = 0.0;
       for (int i = 0; i < n->data1.rows(); i++) {
        loss += (n->data1(i, 0) - n->data2(i, 0));
      }
      loss /= 2.0;
      std::cout << "Loss = " << loss << std::endl;
      //std::this_thread::sleep_for (std::chrono::seconds(2));
    } else {
      n->inputs()[1]->data2 = MatrixXd::Zero(1, 1);
      for (int i = 0; i < n->data1.rows(); i++) {
        n->inputs()[1]->data2(0, 0) += (n->data1(i, 0) - n->data2(i, 0));
      }
      n->inputs()[1]->data2(0, 0) = n->inputs()[1]->data2(0, 0) * -1.0 / n->data1.rows();
    }

    // output = MatrixXd::Zero(1, 1);
    // for (int i = 0; i < input.rows(); i++) {
    //   output(0, 0) += (input(i, 0) - weight(i, 0)) * 
    //                   (input(i, 0) - weight(i, 0));
    //   output(0, 0) /= 2.0;
  }

  // static void computeBwd(MatrixXd &input, MatrixXd &weight, MatrixXd &output) {
  //   output = MatrixXd::Zero(1, 1);
    
  // }
};

#endif // OPS_ERR_H