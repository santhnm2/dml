cmake_minimum_required(VERSION 2.8)
project(dml)

find_package(Protobuf REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_SOURCE_DIR "src")
set(CMAKE_BINARY_DIR "bin")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

# Proto files
get_filename_component(node_def_proto "${CMAKE_SOURCE_DIR}/runtime/rpc/protos/node_def.proto" ABSOLUTE)
get_filename_component(node_def_proto_path "${node_def_proto}" PATH)
get_filename_component(worker_service_proto "${CMAKE_SOURCE_DIR}/runtime/rpc/protos/worker_service.proto" ABSOLUTE)
get_filename_component(worker_service_proto_path "${worker_service_proto}" PATH)

# Generated sources
protobuf_generate_cpp(node_def_proto_srcs node_def_proto_hdrs "${node_def_proto}")
protobuf_generate_cpp(worker_service_proto_srcs worker_service_proto_hdrs "${worker_service_proto}")
set(worker_service_grpc_srcs "${CMAKE_SOURCE_DIR}/runtime/rpc/worker_service.grpc.pb.cc")
set(worker_service_grpc_hdrs "${CMAKE_SOURCE_DIR}/runtime/rpc/worker_service.grpc.pb.h")
add_custom_command(
      OUTPUT "${worker_service_grpc_srcs}" "${worker_service_grpc_hdrs}"
      COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
      ARGS --grpc_out "${CMAKE_SOURCE_DIR}/runtime/rpc" -I "${worker_service_proto_path}"
        --plugin=protoc-gen-grpc="/usr/local/bin/grpc_cpp_plugin"
        "${worker_service_proto}"
      DEPENDS "${node_def_proto}" "${worker_service_proto}")

set (SOURCES ${CMAKE_SOURCE_DIR}/runtime/graph_mgr.cpp ${CMAKE_SOURCE_DIR}/runtime/device_mgr.cpp 
	${CMAKE_SOURCE_DIR}/runtime/partitioner.cpp ${CMAKE_SOURCE_DIR}/graph/node.cpp 
	${node_def_proto_srcs} ${worker_service_proto_srcs} ${worker_service_grpc_srcs})
add_executable(master ${CMAKE_SOURCE_DIR}/runtime/master.cpp ${SOURCES})
target_link_libraries(master ${PROTOBUF_LIBRARY} grpc++_unsecure gpr)
add_executable(worker ${CMAKE_SOURCE_DIR}/runtime/worker.cpp ${SOURCES})
target_link_libraries(worker ${PROTOBUF_LIBRARY} grpc++_unsecure gpr)

# project(device_mgr)
# set(SOURCES device_mgr.cpp device_mgr_test.cpp)
# add_executable(device_mgr ${SOURCES})	