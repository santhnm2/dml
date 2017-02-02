cmake_minimum_required(VERSION 2.8)
project(dml)

find_package(Protobuf REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

# Proto files
get_filename_component(node_def_proto "node_def.proto" ABSOLUTE)
get_filename_component(node_def_proto_path "${node_def_proto}" PATH)
get_filename_component(worker_service_proto "worker_service.proto" ABSOLUTE)
get_filename_component(worker_service_proto_path "${worker_service_proto}" PATH)

# Generated sources
protobuf_generate_cpp(node_def_proto_srcs node_def_proto_hdrs "${node_def_proto}")
protobuf_generate_cpp(worker_service_proto_srcs worker_service_proto_hdrs "${worker_service_proto}")
#set(worker_service_grpc_srcs "${CMAKE_SOURCE_DIR}/runtime/rpc/worker_service.grpc.pb.cc")
#set(worker_service_grpc_hdrs "${CMAKE_SOURCE_DIR}/runtime/rpc/worker_service.grpc.pb.h")
set(worker_service_grpc_srcs "worker_service.grpc.pb.cc")
set(worker_service_grpc_hdrs "worker_service.grpc.pb.h")
add_custom_command(
      OUTPUT "${worker_service_grpc_srcs}" "${worker_service_grpc_hdrs}"
      COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
      ARGS --grpc_out "." -I "${worker_service_proto_path}"
        --plugin=protoc-gen-grpc="/usr/local/bin/grpc_cpp_plugin"
        "${worker_service_proto}"
      DEPENDS "${node_def_proto}" "${worker_service_proto}")

add_library(protos ${node_def_proto_srcs} ${node_def_proto_hdrs}
				  ${worker_service_proto_srcs} ${worker_service_proto_hdrs}
				  ${worker_service_grpc_srcs} ${worker_service_grpc_hdrs})

target_link_libraries(protos ${PROTOBUF_LIBRARY} grpc++_unsecure gpr)