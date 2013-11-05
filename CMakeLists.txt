cmake_minimum_required(VERSION 2.8)
project( videocap )
find_package( OpenCV REQUIRED )
find_package( Qt4 REQUIRED )

IF("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
    SET(CMAKE_CXX_FLAGS "--std=c++11 -Wall -Werror -O3")
ENDIF()

add_subdirectory (src)
add_subdirectory (src/gui)
add_subdirectory (test)
