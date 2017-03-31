#ifndef OPS_APPLY_WEIGHT_H
#define OPS_APPLY_WEIGHT_H

#include <iostream>

#include "../graph/node.h"

#include "json.hpp"

#include <Eigen/Dense>

using Eigen::MatrixXd;
using json = nlohmann::json;

class ApplyWeight {
 public:
  static void compute(Node* n, bool fwd) {
  	json args = json::parse(n->args());
    if (fwd) {
  		if (n->fwd_data.rows() == 0) {
    		// Initialize weight
        int rows = args["shape"][0];
        int cols = args["shape"][1];

    		n->fwd_data = MatrixXd::Zero(rows, cols);

        for (int i = 0; i < n->fwd_data.rows(); i++) {
          for (int j = 0; j < n->fwd_data.cols(); j++) {
            n->fwd_data(i, j) = 2 * static_cast <float> (rand()) /
                                static_cast <float> (RAND_MAX) - 1;
          }
        }
    	}
      n->outputs()[0]->fwd_input = n->fwd_input * n->fwd_data;
    } else {
      n->bwd = n->outputs()[0]->bwd * n->fwd_data.transpose();

      double step_size = args["step_size"];
      MatrixXd gradient = n->fwd_input.transpose() * n->outputs()[0]->bwd;
      n->fwd_data += step_size * gradient;
    }
  }
};

#endif // OPS_APPLY_WEIGHT_H