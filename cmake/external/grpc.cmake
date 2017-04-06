include (ExternalProject)

set(GRPC_INCLUDE_DIRS ${CMAKE_CURRENT_BINARY_DIR}/grpc/src/grpc/include)
set(GRPC_URL https://github.com/grpc/grpc.git)
set(GRPC_BUILD ${CMAKE_CURRENT_BINARY_DIR}/grpc/src/grpc)
set(GRPC_TAG e2cfe9df79c4eda4e376222df064c4c65e616352)

if(WIN32)
  set(grpc_STATIC_LIBRARIES
      ${CMAKE_CURRENT_BINARY_DIR}/grpc/src/grpc/${CMAKE_BUILD_TYPE}/grpc++_unsecure.lib
      ${CMAKE_CURRENT_BINARY_DIR}/grpc/src/grpc/${CMAKE_BUILD_TYPE}/grpc_unsecure.lib
      ${CMAKE_CURRENT_BINARY_DIR}/grpc/src/grpc/${CMAKE_BUILD_TYPE}/gpr.lib)
else()
  set(grpc_STATIC_LIBRARIES
      ${CMAKE_CURRENT_BINARY_DIR}/grpc/src/grpc/libgrpc++_unsecure.a
      ${CMAKE_CURRENT_BINARY_DIR}/grpc/src/grpc/libgrpc_unsecure.a
      ${CMAKE_CURRENT_BINARY_DIR}/grpc/src/grpc/libgpr.a)
  set(grpc_cpp_plugin_executable ${CMAKE_CURRENT_BINARY_DIR}/grpc/src/grpc/grpc_cpp_plugin)
endif()

ExternalProject_Add(grpc
    PREFIX grpc
    DEPENDS protobuf
    GIT_REPOSITORY ${GRPC_URL}
    GIT_TAG ${GRPC_TAG}
    DOWNLOAD_DIR "${DOWNLOAD_LOCATION}"
    BUILD_IN_SOURCE 1
    PATCH_COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/cmake/patches/grpc/CMakeLists.txt ${GRPC_BUILD}
    INSTALL_COMMAND ""
    CMAKE_CACHE_ARGS
    -DCMAKE_BUILD_TYPE:STRING=Release
    -DCMAKE_VERBOSE_MAKEFILE:BOOL=OFF
    -DPROTOBUF_INCLUDE_DIRS:STRING=${PROTOBUF_INCLUDE_DIRS}
    -DPROTOBUF_LIBRARIES:STRING=${protobuf_STATIC_LIBRARIES}
    -DPROTOBUF_PROTOC_LIBRARIES:STRING=${protobuf_PROTOC_STATIC_LIBRARIES}
    )

function(dml_protobuf_grpc_generate_cpp output_dir srcs_var hdrs_var work_path proto_path)
  if(NOT ARGN)
    message(SEND_ERROR "Error: dml_protobuf_generate_cpp() called without any proto files")
    return()
  endif()

  if(PROTOBUF_GENERATE_CPP_APPEND_PATH)
    # Create an include path for each file specified
    foreach(fil ${ARGN})
      get_filename_component(abs_fil ${fil} ABSOLUTE)
      get_filename_component(abs_path ${abs_fil} PATH)
      list(FIND _protoc_include ${abs_path} _contains_already)
      if(${_contains_already} EQUAL -1)
        list(APPEND _protoc_include -I ${abs_path})
      endif()
    endforeach()
  else()
    set(_protoc_include -I ${CMAKE_CURRENT_SOURCE_DIR})
  endif()

  if(DEFINED PROTOBUF_IMPORT_DIRS)
    foreach(dir ${PROTOBUF_IMPORT_DIRS})
      get_filename_component(abs_path ${dir} ABSOLUTE)
      list(FIND _protoc_include ${abs_path} _contains_already)
      if(${_contains_already} EQUAL -1)
        list(APPEND _protoc_include -I ${abs_path})
      endif()
    endforeach()
  endif()

  set(${srcs_var})
  set(${hdrs_var})
  foreach(fil ${ARGN})
    get_filename_component(abs_fil ${fil} ABSOLUTE)
    get_filename_component(fil_we ${fil} NAME_WE)
    string(REPLACE ${work_path}/ "" o_fil ${abs_fil})
    string(REPLACE "${fil_we}.proto" "" o_fil_path ${o_fil})

    list(APPEND ${srcs_var} "${o_fil_path}/${fil_we}.grpc.pb.cc")
    list(APPEND ${hdrs_var} "${o_fil_path}/${fil_we}.grpc.pb.h")

    add_custom_command(
        OUTPUT "${o_fil_path}/${fil_we}.grpc.pb.cc"
        "${o_fil_path}/${fil_we}.grpc.pb.h"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${output_dir}"
        COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} --grpc_out ${output_dir} ${o_fil} --proto_path ${proto_path} --plugin=protoc-gen-grpc=${grpc_cpp_plugin_executable}
        DEPENDS ${abs_fil}
        WORKING_DIRECTORY ${work_path}
        COMMENT "Running C++ protocol buffer compiler on ${o_fil}" VERBATIM )
  endforeach()

  set_source_files_properties(${${srcs_var}} ${${hdrs_var}} PROPERTIES GENERATED TRUE)
  set(${srcs_var} ${${srcs_var}} PARENT_SCOPE)
  set(${hdrs_var} ${${hdrs_var}} PARENT_SCOPE)
endfunction()

