include_directories ( ../../include)

set( PARALLEL_SOURCES
    ThreadPool.cpp
    WorkerThread.h
    )
add_library( parallel
    ${PARALLEL_SOURCES}
    )
