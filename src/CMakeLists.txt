include_directories ( ../include )
SET( SOURCES
    Algorithms.cpp
    Camera.cpp
    Recorder.cpp
    Video.cpp
    VideoStitcher.cpp
    CircleDetector.cpp
    CornerDetector.cpp
    FlagParser.cpp
    Frame.cpp
    View.cpp
    )
add_library ( videoproc
    ${SOURCES}
    )
add_executable( videocap main.cpp )
target_link_libraries( videocap videoproc ${OpenCV_LIBS} )

add_subdirectory( gui )
add_subdirectory( parallel )
