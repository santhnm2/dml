# DML
Distributed Machine Learning framework

Installation instructions:
CMake: https://cmake.org/download/
gRPC: http://www.grpc.io/docs/quickstart/cpp.html
MNIST data: http://yann.lecun.com/exdb/mnist/

...
cmake .
make
./build/worker examples/test/testdevicespec localhost:50051
./build/master examples/test/testdevicespec examples/test/testgraphspec.json
...
