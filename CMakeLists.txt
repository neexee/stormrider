# root CMakeLists for the Stormrider project
project(Stormrider)
set(PROJECT_VERSION "0.0.1")

cmake_minimum_required(VERSION 2.8.4)

set(STORMRIDER_SOURCE_DIR "src")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

# Define install paths
set(STORMRIDER_INSTALL_BINARY_DIR "bin" CACHE
    STRING "Install executable to this directory, absolute or relative to CMAKE_INSTALL_PREFIX")
set(STORMRIDER_INSTALL_DATA_DIR "share/stormrider" CACHE
    STRING "Install data folder to this directory, absolute or relative to CMAKE_INSTALL_PREFIX")


#Setup aubio lib
INCLUDE(ExternalProject)
SET(AUBIO_INSTALL_DIR ${PROJECT_BINARY_DIR}/project_aubio-prefix/install)
SET(AUBIO_DIR ${PROJECT_BINARY_DIR}/project_aubio-prefix/src/project_aubio)
EXTERNALPROJECT_ADD(
  project_aubio
  GIT_REPOSITORY https://github.com/aubio/aubio
  UPDATE_COMMAND ""
  #UPDATE_COMMAND git pull
  CONFIGURE_COMMAND cd ${AUBIO_DIR} && make getwaf && ./waf configure --prefix=${AUBIO_INSTALL_DIR}
  BUILD_COMMAND cd ${AUBIO_DIR} && ./waf build
  INSTALL_COMMAND  cd ${AUBIO_DIR} && ./waf install
)

ADD_LIBRARY(aubio STATIC IMPORTED)
SET_PROPERTY(TARGET aubio PROPERTY IMPORTED_LOCATION ${AUBIO_INSTALL_DIR}/lib/libaubio.so)
ADD_DEPENDENCIES(aubio project_aubio)
include_directories(${AUBIO_INSTALL_DIR}/include/)

#BOOST
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
FIND_PACKAGE(Boost 1.56 COMPONENTS log log_setup thread date_time filesystem system REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

#PTHREADS
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

if(UNIX OR MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -std=c++1y")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()

# Provides list of source and header files (STORMRIDER_SOURCES and STORMRIDER_HEADERS)
include(sources.cmake)

# Build the final executable
add_executable(stormrider ${STORMRIDER_SOURCES} ${STORMRIDER_HEADERS})
add_dependencies(stormrider aubio)

# Common library dependencies
target_link_libraries(stormrider aubio Threads::Threads ${Boost_LIBRARIES})
