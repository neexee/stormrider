# root CMakeLists for the Stormrider project
project(Stormrider)
set(PROJECT_VERSION "0.0.1")

cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include("${PROJECT_SOURCE_DIR}/cmake/sources.cmake")

set(STORMRIDER_SOURCE_DIR "src")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

# Define install paths
set(STORMRIDER_INSTALL_BINARY_DIR "bin" CACHE
	STRING "Install executable to this directory, absolute or relative to CMAKE_INSTALL_PREFIX")
set(STORMRIDER_INSTALL_DATA_DIR "share/stormrider" CACHE
	STRING "Install data folder to this directory, absolute or relative to CMAKE_INSTALL_PREFIX")

set(LIBRARIES ${CMAKE_DL_LIBS})

find_package(LibSndFile ${PACKAGE_OPTION})
if(LIBSNDFILE_FOUND)
		INCLUDE_DIRECTORIES(${LIBSNDFILE_INCLUDE_DIRS})
		list(APPEND LIBRARIES ${LIBSNDFILE_LIBRARIES})
else()
	message(FATAL_ERROR "LibSndFile not found")
endif()


#BOOST
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
FIND_PACKAGE(Boost 1.56 COMPONENTS log log_setup thread date_time filesystem system REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
list(APPEND LIBRARIES ${Boost_LIBRARIES})


#PTHREADS
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
list(APPEND LIBRARIES Threads::Threads)


find_package(Vamp REQUIRED)
INCLUDE_DIRECTORIES(${VAMP_INCLUDE_DIR})
list(APPEND LIBRARIES ${VAMP_LIBRARY})

#OGRE
if(EXISTS "${OGRE_HOME}")

	set(CMAKE_MODULE_PATH "${OGRE_HOME}/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
	set(OGRE_SAMPLES_INCLUDEPATH "${OGRE_HOME}/share/OGRE/samples/Common/include/")

elseif(EXISTS "$ENV{OGRE_HOME}")

	set(CMAKE_MODULE_PATH "$ENV{OGRE_HOME}/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
	set(OGRE_SAMPLES_INCLUDEPATH "$ENV{OGRE_HOME}/share/OGRE/samples/Common/include/")

elseif(EXISTS "/usr/local/lib/OGRE/cmake")

	set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
	set(OGRE_SAMPLES_INCLUDEPATH "/usr/local/share/OGRE/samples/Common/include/") # We could just *assume* that developers uses this basepath : /usr/local

elseif(EXISTS "/usr/lib/OGRE/cmake")

	set(CMAKE_MODULE_PATH "/usr/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
	set(OGRE_SAMPLES_INCLUDEPATH "/usr/share/OGRE/samples/Common/include/") # Otherwise, this one
else ()
	message(SEND_ERROR "Failed to find module path.")
endif(EXISTS "${OGRE_HOME}")
find_package(OIS REQUIRED)
find_package(OGRE REQUIRED)

include_directories( ${OIS_INCLUDE_DIRS}
	${OGRE_INCLUDE_DIRS}
	${OGRE_SAMPLES_INCLUDEPATH}
	${OGRE_Overlay_INCLUDE_DIRS}
)
list(APPEND LIBRARIES ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${OGRE_Overlay_LIBRARIES})

if(UNIX OR MINGW)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -std=c++1y -g")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()

# Build the final executable
add_executable(stormrider ${STORMRIDER_SOURCES} ${STORMRIDER_HEADERS})

# Common library dependencies
target_link_libraries(stormrider ${LIBRARIES})
