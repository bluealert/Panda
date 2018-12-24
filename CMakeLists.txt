cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(Panda)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wall -Wno-deprecated-declarations")

# boost
set(Boost_USE_STATIC_RUNTIME ON)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED OFF)
find_package(Boost 1.58 REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

# glog
find_package(Glog)
include_directories(${Glog_INCLUDE_DIRS})
link_directories(${Glog_LIBRARY_DIRS})

# rapidjson
set(RAPIDJSON_USE_SSE2 ON)
find_package(rapidjson REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${RAPIDJSON_CXX_FLAGS}")
include_directories(${CMAKE_SOURCE_DIR}/third_party/rapidjson-1.1.0/include)

# gperftools
find_package(Gperftools)

# picohttpparser
include_directories(${CMAKE_SOURCE_DIR}/third_party/picohttpparser)

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(third_party/picohttpparser)
add_subdirectory(panda)
add_subdirectory(examples)
add_subdirectory(test)
