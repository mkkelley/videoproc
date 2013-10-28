cmake_minimum_required(VERSION 2.8)
project( videocap )
find_package( OpenCV REQUIRED )

SET(CMAKE_CXX_FLAGS "--std=c++11 -Wall -Werror -O3")

add_subdirectory (src)
