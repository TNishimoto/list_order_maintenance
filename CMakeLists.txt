cmake_minimum_required(VERSION 2.8)
project(list_order_maintenance CXX)


if(CPP_STATIC)
set(CMAKE_CXX_FLAGS "-std=c++11 -m64  -D_INT128 -Wall -Wextra -static")
else(CPP_STATIC)
set(CMAKE_CXX_FLAGS "-std=c++11 -m64  -D_INT128 -Wall -Wextra")
endif(CPP_STATIC)

set(CMAKE_CXX_FLAGS_DEBUG  "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE  "-O3 -DNDEBUG")

if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    message("Release Mode")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()

if(NOT TARGET stool)
    add_subdirectory(module/stool)
endif()



FILE(GLOB SOURCES lib/*.cpp)
INCLUDE_DIRECTORIES(module)
#FILE(GLOB STOOL_SOURCES module/stool/lib/io.cpp)


add_executable(list_order_map_test.out ${SOURCES} ./main/list_order_map_test.cpp)
target_link_libraries(list_order_map_test.out stool)

add_executable(list_order_test.out ${SOURCES} ./main/list_order_test.cpp)
target_link_libraries(list_order_test.out stool)

add_executable(random.out ${SOURCES} ./main/random_test.cpp)
target_link_libraries(random.out stool)

add_executable(sa_sample.out ${SOURCES} ./main/sa_sample.cpp)
target_link_libraries(sa_sample.out stool)

add_executable(text_to_bwt.out ${SOURCES} ./main/text_to_bwt_main.cpp)
target_link_libraries(text_to_bwt.out stool)

add_executable(dsa.out ${SOURCES} ./main/dsa.cpp)
target_link_libraries(dsa.out stool)

add_library(list_order_maintenance STATIC ${SOURCES})
target_link_libraries(list_order_maintenance stool)



#add_library(stool STATIC ${SOURCES})




