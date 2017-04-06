set( Eigen3_VERSION "3.3.3" )

set(EIGEN_INSTALL "${PROJECT_BINARY_DIR}/include/eigen")

add_definitions(-DEIGEN_USE_BLAS -DEIGEN_USE_LAPACKE)
find_package(BLAS REQUIRED)
ExternalProject_Add(eigen
    PREFIX eigen
    URL "http://bitbucket.org/eigen/eigen/get/${Eigen3_VERSION}.tar.bz2"
    DOWNLOAD_DIR "${DOWNLOAD_LOCATION}"
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    BUILD_IN_SOURCE 1
    INSTALL_COMMAND cp -r Eigen unsupported ${EIGEN_INSTALL}
    INSTALL_DIR ${EIGEN_INSTALL})
add_definitions(-DHAS_EIGEN)

macro(requires_eigen NAME)
  target_link_libraries(${NAME} ${BLAS_LIBRARIES})
  add_dependencies(${NAME} eigen)
endmacro(requires_eigen)