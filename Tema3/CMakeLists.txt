cmake_minimum_required(VERSION 3.10)

# Numele proiectului nostru
set(myproject "CyberApp")
project(${myproject})

# Specify the required C++ standard
if(CMAKE_VERSION GREATER "3.1.2") 
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
else()
    if(CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    endif()   
endif()

# II SPUNEM COMPILATORULUI UNDE SA CAUTE FISIERELE .hpp (Aici era problema!)
include_directories(include)

# Setam fisierele librariei noastre
set(myfiles 
    src/NeuralChip.cpp 
    include/NeuralChip.hpp 
    src/ExempleGresite.cpp 
    include/ExempleGresite.hpp
)

# Cream libraria statica 'lib'
add_library(lib STATIC ${myfiles})

# Cream executabilul doar din main.cpp
add_executable(${myproject} src/main.cpp)

# Linkam libraria la executabil
target_link_libraries(${myproject} PUBLIC lib)

# Setam corect directoarele de include pentru executabil (din modelul tau)
target_include_directories(${myproject} 
 PRIVATE src INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)