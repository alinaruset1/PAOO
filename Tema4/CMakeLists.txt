cmake_minimum_required(VERSION 3.10)
project(EffectiveCpp_Spatiu)
set(CMAKE_CXX_STANDARD 14)

include_directories(inc)

add_executable(aplicatie_spatiu
    src/main.cpp
    src/item4_initializare.cpp
    src/item5_functii_generate.cpp
    src/item6_interzicere.cpp
)
