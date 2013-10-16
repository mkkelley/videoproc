cmake_minimum_required(VERSION 2.8)
project( videocap )
find_package( OpenCV REQUIRED )

SET(CMAKE_CXX_FLAGS "--std=c++11 -Wall -Werror -O3")

add_executable( videocap
    src/main.cpp 
    src/Camera.cpp
    src/Recorder.cpp
    src/Video.cpp
    src/VideoStitcher.cpp
    src/CornerDetector.cpp
    src/FlagParser.cpp
    src/CamFilter.cpp
    src/Frame.cpp
    )
target_link_libraries( videocap ${OpenCV_LIBS} )
