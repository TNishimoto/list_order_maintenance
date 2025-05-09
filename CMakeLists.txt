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

if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    message("Release Mode")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()

#if(NOT TARGET stool)
#    add_subdirectory(module/stool)
#endif()



FILE(GLOB SOURCES lib/*.cpp)
INCLUDE_DIRECTORIES(module)
#FILE(GLOB STOOL_SOURCES module/stool/lib/io.cpp)

## Set PROJECT_IS_TOP_LEVEL to ON if if this is the top level project (not
## if this is included as a subproject of something else). Note that this is
## handled automatically for CMake >= 3.21.
#if (CMAKE_VERSION VERSION_LESS 3.21)
#    if ("${CMAKE_PROJECT_NAME}" STREQUAL "${PROJECT_NAME}")
#        message("SET PROJECT_IS_TOP_LEVEL ON IN ${PROJECT_NAME}")
#        set (PROJECT_IS_TOP_LEVEL ON)
#    else()
#        message("SET PROJECT_IS_TOP_LEVEL OFF IN ${PROJECT_NAME}")
#    set (PROJECT_IS_TOP_LEVEL OFF)    
#    endif()
#endif ()


if (PROJECT_IS_TOP_LEVEL)
#add_library(list_order_maintenance STATIC ${SOURCES})
#target_link_libraries(list_order_maintenance)

add_executable(list_order_map_test.out ./main/list_order_map_test.cpp)
##target_link_libraries(list_order_map_test.out)
##target_link_libraries(list_order_map_test.out list_order_maintenance)

add_executable(list_order_test.out ./main/list_order_test.cpp)
##target_link_libraries(list_order_test.out)

##target_link_libraries(list_order_test.out list_order_maintenance)

#add_executable(random.out ./main/random_test.cpp)
#target_link_libraries(random.out list_order_maintenance)

##add_executable(sa_sample.out ./main/sa_sample.cpp)
##target_link_libraries(sa_sample.out list_order_maintenance)

##add_executable(text_to_bwt.out ./main/text_to_bwt_main.cpp)
##target_link_libraries(text_to_bwt.out list_order_maintenance)

##add_executable(dsa.out ./main/dsa.cpp)
##target_link_libraries(dsa.out list_order_maintenance)

else()
add_library(list_order_maintenance STATIC ${SOURCES})
target_link_libraries(list_order_maintenance)
endif()







#add_library(stool STATIC ${SOURCES})




