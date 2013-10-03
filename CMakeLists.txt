cmake_minimum_required(VERSION 2.8)
project( videocap )
find_package( OpenCV REQUIRED )

SET(CMAKE_CXX_FLAGS "--std=c++11 -Wall -Werror")

add_executable( videocap
    src/test.cpp 
    src/Camera.cpp
    src/Recorder.cpp
    )
target_link_libraries( videocap ${OpenCV_LIBS} )
