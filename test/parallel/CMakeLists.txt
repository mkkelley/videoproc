include_directories (../../src/parallel ../../include)

add_executable(threadpool test_ThreadPool.cpp)
add_executable(prunner test_PRunner.cpp)
target_link_libraries ( threadpool
    parallel
    test
    )
target_link_libraries ( prunner
    parallel
    test
    )
