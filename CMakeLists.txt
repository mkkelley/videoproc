cmake_minimum_required(VERSION 2.8)
project( videocap )
find_package( OpenCV REQUIRED )
find_package( Qt4 REQUIRED )

SET(CMAKE_EXE_LINKER_FLAGS "-Wl,-R,/opt/gcc/lib64")
IF("${CMAKE_CXX_COMPILER}" MATCHES ".*clang\\+\\+")
    SET(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror -Wno-deprecated-register -Wno-uninitialized --stdlib=libstdc++ -pthread -fcolor-diagnostics")
ELSE()
    SET(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror -pthread")
ENDIF()

IF("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
ENDIF()

add_subdirectory (src)
add_subdirectory (test)
