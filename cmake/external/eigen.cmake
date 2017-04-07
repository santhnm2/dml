include (ExternalProject)

set( Eigen3_VERSION "3.3.3" )

#set(eigen_URL "http://bitbucket.org/eigen/eigen/get/${Eigen3_VERSION}.tar.bz2")
set(eigen_URL "https://bitbucket.org/eigen/eigen/get/deff8b280204.tar.gz")
set(EIGEN_INSTALL ${CMAKE_CURRENT_BINARY_DIR}/eigen/install)

set(EIGEN_INCLUDE_DIRS
    ${CMAKE_CURRENT_BINARY_DIR}/external/eigen_archive
    )

add_definitions(-DEIGEN_USE_BLAS)
ExternalProject_Add(eigen
    PREFIX eigen
    URL ${eigen_URL}
    DOWNLOAD_DIR "${DOWNLOAD_LOCATION}"
    INSTALL_DIR "${eigen_INSTALL}"
    CMAKE_CACHE_ARGS
    -DCMAKE_BUILD_TYPE:STRING=Release
    -DCMAKE_VERBOSE_MAKEFILE:BOOL=OFF
    -DCMAKE_INSTALL_PREFIX:STRING=${EIGEN_INSTALL}
    -DINCLUDE_INSTALL_DIR:STRING=${CMAKE_CURRENT_BINARY_DIR}/external/eigen_archive
    -DBUILD_TESTING:BOOL=OFF
    )
add_definitions(-DHAS_EIGEN)









#set( Eigen3_VERSION "3.3.3" )
#
#set(EIGEN_INSTALL "${PROJECT_BINARY_DIR}/include/eigen")
#
#add_definitions(-DEIGEN_USE_BLAS -DEIGEN_USE_LAPACKE)
#find_package(BLAS REQUIRED)
#ExternalProject_Add(eigen
#    PREFIX eigen
#    URL "http://bitbucket.org/eigen/eigen/get/${Eigen3_VERSION}.tar.bz2"
#    DOWNLOAD_DIR "${DOWNLOAD_LOCATION}"
#    CONFIGURE_COMMAND ""
#    BUILD_COMMAND ""
#    BUILD_IN_SOURCE 1
#    INSTALL_COMMAND cp -r Eigen unsupported ${EIGEN_INSTALL}
#    INSTALL_DIR ${EIGEN_INSTALL})
#add_definitions(-DHAS_EIGEN)

find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)

macro(requires_eigen NAME)
  target_link_libraries(${NAME} ${BLAS_LIBRARIES})
  target_link_libraries(${NAME} ${LAPACK_LIBRARIES})
  add_dependencies(${NAME} eigen)
endmacro(requires_eigen)