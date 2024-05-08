cmake_minimum_required(VERSION 3.21)
project(list_order_maintenance CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MY_SERVER)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(CMAKE_SYSROOT /opt/homebrew/Cellar/aarch64-unknown-linux-gnu/13.2.0/toolchain/aarch64-unknown-linux-gnu/sysroot)

set(CMAKE_EXE_LINKER_FLAGS -B/opt/homebrew/Cellar/aarch64-unknown-linux-gnu/13.2.0/toolchain/lib/gcc/aarch64-unknown-linux-gnu/13.2.0)
set(CMAKE_CXX_FLAGS "--target=aarch64-linux-gnu -fexceptions -m64 -D_INT128 -static")
include_directories(/opt/homebrew/Cellar/aarch64-unknown-linux-gnu/13.2.0/toolchain/aarch64-unknown-linux-gnu/include/c++/13.2.0/aarch64-unknown-linux-gnu)
include_directories(/opt/homebrew/Cellar/aarch64-unknown-linux-gnu/13.2.0/toolchain/aarch64-unknown-linux-gnu/include/c++/13.2.0)
link_directories(/opt/homebrew/Cellar/aarch64-unknown-linux-gnu/13.2.0/toolchain/lib/gcc/aarch64-unknown-linux-gnu/13.2.0)

set(CMAKE_EXE_LINKER_FLAGS -B/opt/homebrew/Cellar/aarch64-unknown-linux-gnu/13.2.0/toolchain/lib/gcc/aarch64-unknown-linux-gnu/13.2.0)
set(CMAKE_CXX_FLAGS "--target=aarch64-linux-gnu -fexceptions -m64 -D_INT128 -static")
else(MY_SERVER)
set(CMAKE_CXX_FLAGS "-m64  -D_INT128 -Wall -Wextra")
endif(MY_SERVER)
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
INCLUDE_DIRECTORIES(include)
#FILE(GLOB STOOL_SOURCES module/stool/lib/io.cpp)

# Set PROJECT_IS_TOP_LEVEL to ON if if this is the top level project (not
# if this is included as a subproject of something else). Note that this is
# handled automatically for CMake >= 3.21.
if (CMAKE_VERSION VERSION_LESS 3.21)
    if ("${CMAKE_PROJECT_NAME}" STREQUAL "${PROJECT_NAME}")
        message("SET PROJECT_IS_TOP_LEVEL ON IN ${PROJECT_NAME}")
        set (PROJECT_IS_TOP_LEVEL ON)
    else()
        message("SET PROJECT_IS_TOP_LEVEL OFF IN ${PROJECT_NAME}")
    set (PROJECT_IS_TOP_LEVEL OFF)    
    endif()
endif ()


if (PROJECT_IS_TOP_LEVEL)
#add_library(list_order_maintenance ${SOURCES})
#target_link_libraries(list_order_maintenance stool)

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

add_executable(dsa.out ${SOURCES}  ./main/dsa.cpp)
target_link_libraries(dsa.out stool)

else()
add_library(list_order_maintenance STATIC ${SOURCES})
target_link_libraries(list_order_maintenance)
endif()







#add_library(stool STATIC ${SOURCES})




