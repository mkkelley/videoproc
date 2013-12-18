include_directories ( ../../include)

set( PARALLEL_SOURCES
    ThreadPool.cpp
    AsyncRecorder.cpp
    )
add_library( parallel
    ${PARALLEL_SOURCES}
    )
