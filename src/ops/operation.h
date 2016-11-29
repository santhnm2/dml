#ifndef OPS_OPERATION_H_
#define OPS_OPERATION_H_

#include <Eigen/Dense>

using Eigen::MatrixXd;

class Operation {
  public:
    virtual void compute(MatrixXd &input_first,MatrixXd &output)=0;
    virtual void compute(MatrixXd &input_first, MatrixXd &input_second,MatrixXd &output)=0;
};

#endif // OPS_OPERATION_H_
