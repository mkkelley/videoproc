include_directories ( ../include ../src/parallel)

add_library (test TestSet.cpp)
add_executable (frame test_Frame.cpp)
#add_executable (threadpool parallel/test_ThreadPool.cpp)
target_link_libraries( frame
    parallel
    videoproc
    test
    ${OpenCV_LIBS}
    )

add_subdirectory (parallel)
