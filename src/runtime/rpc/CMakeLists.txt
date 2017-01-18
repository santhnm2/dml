cmake_minimum_required(VERSION 2.8)
project(DML)

find_package(Protobuf REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

# Proto file
get_filename_component(node_def_proto "protos/node_def.proto" ABSOLUTE)
get_filename_component(node_def_proto_path "${node_def_proto}" PATH)
get_filename_component(worker_service_proto "protos/worker_service.proto" ABSOLUTE)
get_filename_component(worker_service_proto_path "${worker_service_proto}" PATH)

# Generated sources
protobuf_generate_cpp(node_def_proto_srcs node_def_proto_hdrs "${node_def_proto}")
protobuf_generate_cpp(worker_service_proto_srcs worker_service_proto_hdrs "${worker_service_proto}")
set(worker_service_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/worker_service.grpc.pb.cc")
set(worker_service_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/worker_service.grpc.pb.h")
add_custom_command(
      OUTPUT "${worker_service_grpc_srcs}" "${worker_service_grpc_hdrs}"
      COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}" -I "${worker_service_proto_path}"
        --plugin=protoc-gen-grpc="/usr/local/bin/grpc_cpp_plugin"
        "${worker_service_proto}"
      DEPENDS "${node_def_proto}" "${worker_service_proto}")

# Generated include directory
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_executable(worker_service worker_service.cpp  ${node_def_proto_srcs}
    ${worker_service_proto_srcs}
    ${worker_service_grpc_srcs})
target_link_libraries(worker_service ${PROTOBUF_LIBRARY} grpc++_unsecure grpc gpr)
add_executable(master_client master_client.cpp  ${node_def_proto_srcs}
    ${worker_service_proto_srcs}
    ${worker_service_grpc_srcs})
target_link_libraries(master_client ${PROTOBUF_LIBRARY} grpc++_unsecure grpc gpr)