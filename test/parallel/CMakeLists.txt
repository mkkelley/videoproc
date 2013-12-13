include_directories (../../src/parallel ../../include)

add_executable(threadpool test_ThreadPool.cpp)
target_link_libraries ( threadpool
    parallel
    test
    )
