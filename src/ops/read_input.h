#ifndef OPS_READ_INPUT_H
#define OPS_READ_INPUT_H

#include <iostream>
// #include <fstream>

// #include <arpa/inet.h>
// #include <inttypes.h>

#include <byteswap.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <Eigen/Dense>

using Eigen::MatrixXd;
using namespace std;

class ReadInput {
 public:
  static void compute(MatrixXd &input, MatrixXd &weight, MatrixXd &output) {
    if (input.rows() == 0) {
      FILE *myfile = fopen("examples/test/train-images-idx3-ubyte", "rb");
      if (!myfile) {
        cout << "Could not read data" << endl;
        return;
      }

      uint32_t value;
      size_t bytes;

      // Magic number
      bytes = fread(&value, sizeof(uint32_t), 1, myfile);
      cout << "Read " << bytes << " bytes" << endl;
      uint32_t magic_number = __bswap_32(value);

      cout << "Magic number = " << magic_number << endl;
      if (magic_number != 2051) {
        cout << "Could not read data" << endl;
        return;
      }

      // Images
      fread(&value, sizeof(uint32_t), 1, myfile);
      cout << "Read " << bytes << " bytes" << endl;
      uint32_t images = __bswap_32(value);
      printf("%lu images\n", (unsigned long) images);

      // Rows
      fread(&value, sizeof(uint32_t), 1, myfile);
      cout << "Read " << bytes << " bytes" << endl;
      uint32_t rows = __bswap_32(value);
      printf("%lu rows\n", (unsigned long) rows);

      // Cols
      fread(&value, sizeof(uint32_t), 1, myfile);
      cout << "Read " << bytes << " bytes" << endl;
      uint32_t cols = __bswap_32(value);
      printf("%lu cols\n", (unsigned long) cols);

      input = MatrixXd(images, rows*cols);

      uint8_t pixel;

      for (int i = 0; i < images; i++) {
        for (int j = 0; j < rows*cols; j++) {
          fread(&pixel, sizeof(uint8_t), 1, myfile);
          input(i, j) = pixel;
        }
      }

      // ifstream myfile;
      // size_t size = 4;
      // myfile.open("../../examples/test/train-images-idx3-ubyte", 
      //             ios::in | ios::binary);
      // myfile.seekg(0, ios::beg);
      // char data[size];
      
      // myfile.read(data, size);
      // printf("data = %s\n", data);
      // uint32_t magic_number = ReadInput::_read32(data);
      // cout << "Magic number = " << magic_number << endl;
      // if (magic_number != 2051) {
      //   cout << "Failed to read data." << endl;
      //   return;
      // } else {
      //   cout << "Successfully read data." << endl;
      // }

      // myfile.read(data, size);
      // uint32_t num_images = ReadInput::_read32(data);


      // myfile.read(data, size);
      // uint32_t num_rows = ReadInput::_read32(data);


      // myfile.read(data, size);
      // uint32_t num_columns = ReadInput::_read32(data);

      // num_images = 1000;

      // input = MatrixXd(num_images, num_rows*num_columns);

      // for (uint32_t i = 0; i < num_images; i++) {
      //   for (uint32_t j = 0; j < num_rows * num_columns; j++) {
      //     myfile.read(data, size);
      //     input(i, j) = ReadInput::_read32(data);
      //   }
      // }
      fclose(myfile);
    }
    
    cout << "Finished reading data" << endl;

    uint32_t minibatch_size = 100;
    output = MatrixXd(minibatch_size, input.cols());
    
    for (uint32_t i = 0; i < minibatch_size; i++) {
      int idx = rand() % input.rows();
      output.row(i) = input.row(idx);
    }

    cout << output << endl;
  }
 private:
  static uint32_t _read32(char* buf) {
    uint32_t result = (uint32_t) buf[0] << 24 |
                      (uint32_t) buf[1] << 16 |
                      (uint32_t) buf[2] << 8  |
                      (uint32_t) buf[3];
    return result;
  }
};

#endif // OPS_READ_INPUT_H