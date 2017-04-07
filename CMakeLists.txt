cmake_minimum_required(VERSION 3.3)
project(dml)

find_package(Threads REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
#set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -std=c99")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

## Set C++14 as standard for the whole project
#set(CMAKE_CXX_STANDARD 14)

# external dependencies
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/external)

# Location where external projects will be downloaded
set (DOWNLOAD_LOCATION "${CMAKE_CURRENT_BINARY_DIR}/downloads"
		CACHE PATH "Location where external projects will be downloaded.")
mark_as_advanced(DOWNLOAD_LOCATION)

# external dependencies
#include(zlib)

include(protobuf)
include(grpc)
include(eigen)

#find_package(ZLIB REQUIRED)

set(dml_EXTERNAL_LIBRARIES
#		${zlib_STATIC_LIBRARIES}
		${protobuf_STATIC_LIBRARIES}
		${grpc_STATIC_LIBRARIES}
		${ZLIB_LIBRARIES}
		${CARES_LIBRARIES}
		)
set(dml_EXTERNAL_DEPENDENCIES
#		zlib_copy_headers_to_destination
		protobuf
		grpc
		eigen
		)

set(DML_INCLUDE_LIST "")
list(APPEND DML_INCLUDE_LIST "${PROJECT_SOURCE_DIR}/include")
#list(APPEND DML_INCLUDE_LIST "${PROJECT_SOURCE_DIR}/include/graph")
#list(APPEND DML_INCLUDE_LIST "${PROJECT_SOURCE_DIR}/include/ops")
#list(APPEND DML_INCLUDE_LIST "${PROJECT_SOURCE_DIR}/include/runtime")
#list(APPEND DML_INCLUDE_LIST "${PROJECT_SOURCE_DIR}/include/util")
#list(APPEND DML_INCLUDE_LIST "${PROJECT_SOURCE_DIR}/include/agent")

#list(APPEND DML_INCLUDE_LIST "${PROJECT_SOURCE_DIR}/include/third_party/json")

list(APPEND DML_INCLUDE_LIST ${zlib_INCLUDE_DIR})
list(APPEND DML_INCLUDE_LIST ${PROTOBUF_INCLUDE_DIRS})
list(APPEND DML_INCLUDE_LIST ${GRPC_INCLUDE_DIRS})
#list(APPEND DML_INCLUDE_LIST ${EIGEN_INSTALL})
list(APPEND DML_INCLUDE_LIST ${EIGEN_INCLUDE_DIRS})


set(proto_gen_folder "${PROJECT_BINARY_DIR}/src/agent/proto")
file(GLOB proto_files "src/agent/proto/*.proto")
dml_protobuf_generate_cpp(${proto_gen_folder} proto_srcs proto_hdrs "${PROJECT_SOURCE_DIR}" "src/agent/proto" ${proto_files})

file(GLOB grpc_proto_files "src/agent/proto/*_grpc.proto")
dml_protobuf_grpc_generate_cpp(${proto_gen_folder} grpc_proto_srcs grpc_proto_hdrs "${PROJECT_SOURCE_DIR}" "src/agent/proto" ${grpc_proto_files})


#list(APPEND DML_INCLUDE_LIST "${PROJECT_BINARY_DIR}/include/")
list(APPEND DML_INCLUDE_LIST "${proto_gen_folder}")

set(SOURCE "")
FILE(GLOB graph_srcs "src/graph/*.cpp")
FILE(GLOB runtime_srcs "src/runtime/*.cpp")
list(APPEND SOURCE ${graph_srcs})
list(APPEND SOURCE ${runtime_srcs})
list(APPEND SOURCE ${proto_srcs})
list(APPEND SOURCE ${grpc_proto_srcs})

list(APPEND DML_INCLUDE_LIST ${CMAKE_CURRENT_BINARY_DIR})
include_directories(${DML_INCLUDE_LIST})

list(APPEND SOURCE ${proto_srcs})
list(APPEND SOURCE ${grpc_proto_srcs})
#add_library(dml ${SOURCE})
#target_link_libraries(dml ${dml_EXTERNAL_LIBRARIES})
#add_dependencies(dml ${dml_EXTERNAL_DEPENDENCIES})

macro(add_dml_executable NAME)
	message("add_executable(${NAME} ${ARGN})")
	add_executable(${NAME} ${ARGN})
#	target_link_libraries(${NAME} dml)
	target_link_libraries(${NAME} ${dml_EXTERNAL_LIBRARIES})
	add_dependencies(${NAME} ${dml_EXTERNAL_DEPENDENCIES})
	requires_eigen(${NAME})
endmacro(add_dml_executable)

add_dml_executable(master src/agent/master.cpp ${SOURCE})
add_dml_executable(worker src/agent/worker.cpp ${SOURCE})
