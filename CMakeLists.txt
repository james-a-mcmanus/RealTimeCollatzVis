cmake_minimum_required(VERSION 3.14)

project(RealTimeCollatzVis LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(UBIITS_INCLUDE_PATH CACHE PATH "specify ubiITS inculde path")
set(UBIITS_BUILD_PATH CACHE PATH "specify ubiITS binary path")

#SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_SOURCE_DIR}/lib/boost_1_82_0")
#SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_SOURCE_DIR}/lib/boost_1_82_0/libs")

find_package(Boost 1.10.0 REQUIRED) 
include_directories(${Boost_INCLUDE_DIRS}) 


set(SOURCE_FILES messageParser.cpp SequenceHolder.cpp DataUpdater.cpp serverReceiverParse.cpp)

add_executable(serverReceiverParse ${SOURCE_FILES})
target_link_libraries(serverReceiverParse ${Boost_LIBRARIES})
