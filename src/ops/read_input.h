#ifndef OPS_READ_INPUT_H
#define OPS_READ_INPUT_H

#include <iostream>

#include "../graph/node.h"

#include <byteswap.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <Eigen/Dense>

using Eigen::MatrixXd;
using namespace std;

class ReadInput {
 public:
  static void compute(Node* n, bool fwd) {
    if (fwd) {
      if (n->fwd_input.rows() == 0) {
        std::cout << "Reading data..." << std::endl;
        FILE *image_file = fopen("examples/test/train-images-idx3-ubyte", "rb");
        if (!image_file) {
          cout << "Could not read data" << endl;
          return;
        }

        uint32_t value;
        
        // Magic number
        fread(&value, sizeof(uint32_t), 1, image_file);
        uint32_t magic_number = __bswap_32(value);

        if (magic_number != 2051) {
          cout << "Could not read data" << endl;
          return;
        }

        // Images
        fread(&value, sizeof(uint32_t), 1, image_file);
        uint32_t images = __bswap_32(value);

        // Rows
        fread(&value, sizeof(uint32_t), 1, image_file);
        uint32_t rows = __bswap_32(value);

        // Cols
        fread(&value, sizeof(uint32_t), 1, image_file);
        uint32_t cols = __bswap_32(value);

        n->fwd_input = MatrixXd::Zero(images, rows*cols);

        uint8_t pixel;

        for (int i = 0; i < images; i++) {
          for (int j = 0; j < rows*cols; j++) {
            fread(&pixel, sizeof(uint8_t), 1, image_file);
            n->fwd_input(i, j) = pixel / 255.0;
          }
        }

        fclose(image_file);

        FILE *label_file = fopen("examples/test/train-labels-idx1-ubyte", "rb");
        if (!label_file) {
          cout << "Could not read labels" << endl;
          return;
        }

        fread(&value, sizeof(uint32_t), 1, label_file);
        magic_number = __bswap_32(value);

        if (magic_number != 2049) {
          cout << "Could not read labels" << endl;
          return;
        }

        fread(&value, sizeof(uint32_t), 1, label_file);
        images = __bswap_32(value);
        if (images != n->fwd_input.rows()) {
          cout << "Mismatch between images and labels" << endl;
          return;
        }

        n->fwd_data = MatrixXd::Zero(images, 10);

        uint8_t label;

        for (int i = 0; i < images; i++) {
          fread(&label, sizeof(uint8_t), 1, label_file);
          n->fwd_data(i, label) = 1;
        }

        fclose(label_file);

        cout << "Finished reading data" << endl;

        
         // // Source: https://iamtrask.github.io/2015/07/12/basic-python-network/
         // n->fwd_input = MatrixXd::Zero(4,3);
         // n->fwd_data = MatrixXd::Zero(4,1);
         
         // n->fwd_input << 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1;
         // n->fwd_data << 0, 1, 1, 0;
         
         // n->outputs()[0]->fwd_input = n->fwd_input;
         // n->outputs()[1]->fwd_data = n->fwd_data;
         
      }

      uint32_t minibatch_size = 100;
      n->outputs()[0]->fwd_input = MatrixXd::Zero(minibatch_size,
                                                  n->fwd_input.cols());
      n->outputs()[1]->fwd_data = MatrixXd::Zero(minibatch_size, 10);
      
      for (int i = 0; i < minibatch_size; i++) {
        int idx = rand() % n->fwd_input.rows();
        
        n->outputs()[0]->fwd_input.row(i) = n->fwd_input.row(idx);
        n->outputs()[1]->fwd_data.row(i) = n->fwd_data.row(idx);
      }
    } else {
      // Do nothing
    }
  } 
};

#endif // OPS_READ_INPUT_H