cmake_minimum_required(VERSION 3.21)
project(list_order_maintenance CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(CPP_STATIC)
set(CMAKE_CXX_FLAGS "-m64  -D_INT128 -Wall -Wextra -static")
else(CPP_STATIC)
set(CMAKE_CXX_FLAGS "-m64  -D_INT128 -Wall -Wextra")
endif(CPP_STATIC)

set(CMAKE_CXX_FLAGS_DEBUG  "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE  "-O3 -DNDEBUG")

INCLUDE_DIRECTORIES(../module)

add_executable(list_order_map_test.out list_order_map_test.cpp)
add_executable(list_order_test.out list_order_test.cpp)
add_executable(random.out random_test.cpp)
add_executable(sa_sample.out sa_sample.cpp)
