#ifndef OPS_READ_INPUT_H
#define OPS_READ_INPUT_H

#include <iostream>
// #include <fstream>

// #include <arpa/inet.h>
// #include <inttypes.h>

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
  static void compute(Node *n, bool fwd) {
    if (fwd) {
      if (n->data1.rows() == 0) {
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

        n->data1 = MatrixXd::Zero(images, rows*cols);

        uint8_t pixel;

        for (int i = 0; i < images; i++) {
          for (int j = 0; j < rows*cols; j++) {
            fread(&pixel, sizeof(uint8_t), 1, image_file);
            n->data1(i, j) = pixel / 255.0;
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

        // cout << "Magic number = " << magic_number << endl;

        if (magic_number != 2049) {
          cout << "Could not read labels" << endl;
          return;
        }

        fread(&value, sizeof(uint32_t), 1, label_file);
        images = __bswap_32(value);
        if (images != n->data1.rows()) {
          cout << "Mismatch between images and labels" << endl;
          return;
        }

        n->data2 = MatrixXd::Zero(images, 1);

        uint8_t label;

        for (int i = 0; i < images; i++) {
          fread(&label, sizeof(uint8_t), 1, label_file);
          n->data2(i, 0) = label;
        }

        fclose(label_file);

        cout << "Finished reading data" << endl;
      }

      uint32_t minibatch_size = 100;
      n->outputs()[0]->data1 = MatrixXd::Zero(minibatch_size, n->data1.cols());
      n->outputs()[1]->data2 = MatrixXd::Zero(minibatch_size, 1);
      
      for (uint32_t i = 0; i < minibatch_size; i++) {
        int idx = rand() % n->data1.rows();
        double label = n->data2(idx, 0);
        n->outputs()[0]->data1.row(i) = n->data1.row(idx);
        if (label == 9) {
          n->outputs()[1]->data2(i, 0) = 1;  
        } else {
          n->outputs()[1]->data2(i, 0) = 0;
        }
      }
    } else {
      // Do nothing
    }
  } 
};

#endif // OPS_READ_INPUT_H