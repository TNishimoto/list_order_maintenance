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
FILE(GLOB STOOL_SOURCES module/stool/src/io.cpp)


add_executable(list_order_map_test.out ${SOURCES} ${STOOL_SOURCES} ./main/list_order_map_test.cpp)
add_executable(list_order_test.out ${SOURCES} ${STOOL_SOURCES} ./main/list_order_test.cpp)

#add_executable(b.out ${SOURCES} ${STOOL_SOURCES} ./main/main.cpp)
add_executable(random.out ${SOURCES} ${STOOL_SOURCES} ./main/random_test.cpp)
add_executable(sa_sample.out ${SOURCES} ${STOOL_SOURCES} ./main/sa_sample.cpp)
add_executable(text_to_bwt.out ${SOURCES} ${STOOL_SOURCES} ./main/text_to_bwt_main.cpp)

#add_executable(dsa.out ${SOURCES} ${STOOL_SOURCES} ./main/dsa.cpp)

#target_link_libraries(a.out fn)


