cmake_minimum_required(VERSION 2.8)
project( videocap )
find_package( OpenCV REQUIRED )

IF("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
    SET(CMAKE_CXX_FLAGS "--std=c++11 -Wall -Werror -O3")
ENDIF()

add_subdirectory (src)
add_subdirectory (test)
