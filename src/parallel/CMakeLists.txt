include_directories ( ../../include)

set( PARALLEL_SOURCES
    PRunner.cpp
    ThreadPool.cpp
    )
add_library( parallel
    ${PARALLEL_SOURCES}
    )
