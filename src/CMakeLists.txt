
include_directories ( ../include )
add_library (videoproc 
    Camera.cpp
    Recorder.cpp
    Video.cpp
    VideoStitcher.cpp
    CornerDetector.cpp
    FlagParser.cpp
    CamFilter.cpp
    Frame.cpp
    )
add_executable( videocap main.cpp )
target_link_libraries( videocap videoproc ${OpenCV_LIBS} )
