cmake_minimum_required(VERSION 2.8)
project(dml)

find_package(Protobuf REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(CMAKE_SOURCE_DIR "src")
set(CMAKE_BINARY_DIR "build")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories(/usr/local/include)
include_directories(third_party/eigen3)
include_directories(third_party/json)
link_directories(/usr/local/lib)

add_subdirectory(src/runtime/rpc/protos)

set_source_files_properties(${CMAKE_SOURCE_DIR}/runtime/rpc/protos/node_def.pb.cc 
			 ${CMAKE_SOURCE_DIR}/runtime/rpc/protos/weight.pb.cc
			 ${CMAKE_SOURCE_DIR}/runtime/rpc/protos/ps.pb.cc
			 ${CMAKE_SOURCE_DIR}/runtime/rpc/protos/ps.grpc.pb.cc
			 ${CMAKE_SOURCE_DIR}/runtime/rpc/protos/worker_service.pb.cc
			 ${CMAKE_SOURCE_DIR}/runtime/rpc/protos/worker_service.grpc.pb.cc
                            PROPERTIES GENERATED TRUE)

set (SOURCES ${CMAKE_SOURCE_DIR}/runtime/graph_mgr.cpp 
			 ${CMAKE_SOURCE_DIR}/runtime/device_mgr.cpp 
			 ${CMAKE_SOURCE_DIR}/graph/node.cpp 
			 ${CMAKE_SOURCE_DIR}/runtime/rpc/protos/node_def.pb.cc
			 ${CMAKE_SOURCE_DIR}/runtime/rpc/protos/weight.pb.cc
			 ${CMAKE_SOURCE_DIR}/runtime/rpc/protos/ps.pb.cc
			 ${CMAKE_SOURCE_DIR}/runtime/rpc/protos/ps.grpc.pb.cc
			 ${CMAKE_SOURCE_DIR}/runtime/rpc/protos/worker_service.pb.cc
			 ${CMAKE_SOURCE_DIR}/runtime/rpc/protos/worker_service.grpc.pb.cc)
add_executable(master ${CMAKE_SOURCE_DIR}/runtime/master.cpp ${SOURCES})
target_link_libraries(master protos)
add_executable(worker ${CMAKE_SOURCE_DIR}/runtime/worker.cpp ${SOURCES})
target_link_libraries(worker protos)