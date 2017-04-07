# DML
Distributed Machine Learning framework

Installation instructions:
CMake: https://cmake.org/download/
gRPC: http://www.grpc.io/docs/quickstart/cpp.html

```
sudo apt-get update && sudo apt-get install build-essential git autoconf libtool cmake
sudo apt-get install libopenblas-dev liblapacke-dev libssl-dev 
```

To run the code:
First, download the training dataset from
http://yann.lecun.com/exdb/mnist/
```
./build/worker examples/test/testdevicelist localhost:50051
./build/master examples/test/testdevicelist examples/test/testgraphspec.json
```

TODO:
Reduce for loops