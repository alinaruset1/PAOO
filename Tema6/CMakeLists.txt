cmake_minimum_required(VERSION 3.10)
project(EffectiveCpp_13_14 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(demo main.cpp Item13.cpp Item14.cpp)
