cmake_minimum_required(VERSION 3.14)

project(RealTimeCollatzVis LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(UBIITS_INCLUDE_PATH CACHE PATH "specify ubiITS inculde path")
set(UBIITS_BUILD_PATH CACHE PATH "specify ubiITS binary path")

add_executable(serverReceiverParse serverReceiverParse)