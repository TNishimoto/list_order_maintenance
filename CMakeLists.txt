cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=gnu++14 -fno-ms-compatibility -fexceptions -m64")
#-l sdsl -l divsufsort -l divsufsort64
#set(CMAKE_CXX_FLAGS "-std=gnu++14 -fno-ms-compatibility -fexceptions -m64")
set(CMAKE_CXX_FLAGS_DEBUG  "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE  "-O3 -DNDEBUG")

# ビルドするためにインクルードするヘッダーファイルの場所
#INCLUDE_DIRECTORIES(./src)
FILE(GLOB SOURCES *.cpp)

SET(PROJECT_NAME
  a.out
)
#LINK_DIRECTORIES(~/lib)
add_executable(a.out ${SOURCES})
#target_link_libraries(a.out Common1 Common2)
#target_include_directories(a.out PRIVATE ~/include)


