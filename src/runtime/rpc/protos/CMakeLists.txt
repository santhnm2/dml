cmake_minimum_required(VERSION 2.8)
project(dml)

find_package(Protobuf REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

# Proto files
get_filename_component(node_def_proto "node_def.proto" ABSOLUTE)
get_filename_component(node_def_proto_path "${node_def_proto}" PATH)
get_filename_component(weight_proto "weight.proto" ABSOLUTE)
get_filename_component(weight_proto_path "${weight_proto}" PATH)
get_filename_component(ps_proto "ps.proto" ABSOLUTE)
get_filename_component(ps_proto_path "${ps_proto}" PATH)
get_filename_component(worker_service_proto "worker_service.proto" ABSOLUTE)
get_filename_component(worker_service_proto_path "${worker_service_proto}" PATH)

# Generated sources
protobuf_generate_cpp(node_def_proto_srcs node_def_proto_hdrs "${node_def_proto}")
protobuf_generate_cpp(weight_proto_srcs weight_proto_hdrs "${weight_proto}")
protobuf_generate_cpp(ps_proto_srcs ps_proto_hdrs "${ps_proto}")
protobuf_generate_cpp(worker_service_proto_srcs worker_service_proto_hdrs "${worker_service_proto}")

set(ps_grpc_srcs "ps.grpc.pb.cc")
set(ps_grpc_hdrs "ps.grpc.pb.h")
add_custom_command(
      OUTPUT "${ps_grpc_srcs}" "${ps_grpc_hdrs}"
      COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
      ARGS --grpc_out "." -I "${ps_proto_path}"
        --plugin=protoc-gen-grpc="/usr/local/bin/grpc_cpp_plugin"
        "${ps_proto}"
      DEPENDS "${weight_proto}" "${ps_proto}")

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
				  ${weight_proto_srcs} ${weight_proto_hdrs}
				  ${ps_proto_srcs} ${ps_proto_hdrs}
				  ${ps_grpcs_srcs} ${ps_grpc_hdrs}
				  ${worker_service_proto_srcs} ${worker_service_proto_hdrs}
				  ${worker_service_grpc_srcs} ${worker_service_grpc_hdrs})

target_link_libraries(protos ${PROTOBUF_LIBRARY} grpc++_unsecure gpr)