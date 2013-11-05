include_directories ( ../include )
SET( SOURCES
    Camera.cpp
    Recorder.cpp
    Video.cpp
    VideoStitcher.cpp
    CornerDetector.cpp
    FlagParser.cpp
    CamFilter.cpp
    Frame.cpp
    )
add_library ( videoproc
    ${SOURCES}
    ${HEADERS}
    )
add_executable( videocap main.cpp )
target_link_libraries( videocap videoproc ${OpenCV_LIBS} )
