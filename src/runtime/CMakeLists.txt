cmake_minimum_required(VERSION 2.8)
project(graph_mgr)

find_package(Protobuf REQUIRED)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

set (SOURCES graph_mgr.cpp graph_mgr_test.cpp ../graph/node.cpp rpc/node_def.pb.cc)
add_executable(graph_mgr ${SOURCES})
target_link_libraries(graph_mgr ${PROTOBUF_LIBRARY})
# project(device_mgr)
# set(SOURCES device_mgr.cpp device_mgr_test.cpp)
# add_executable(device_mgr ${SOURCES})