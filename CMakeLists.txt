
cmake_minimum_required(VERSION 2.8)

if(CPP_STATIC)
set(CMAKE_CXX_FLAGS "-std=c++14 -m64  -D_INT128 -Wall -Wextra -static")
else(CPP_STATIC)
set(CMAKE_CXX_FLAGS "-std=c++14 -m64  -D_INT128 -Wall -Wextra")
endif(CPP_STATIC)

set(CMAKE_CXX_FLAGS_DEBUG  "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE  "-O3 -DNDEBUG")



FILE(GLOB SOURCES src/*.cpp)
INCLUDE_DIRECTORIES(module)
FILE(GLOB STOOL_SOURCES src/io.cpp)


add_executable(a.out ${SOURCES} ${STOOL_SOURCES} ./main/list_order_test.cpp)


#target_link_libraries(a.out fn)


