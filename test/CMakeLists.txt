
include_directories ( ../src )
add_executable (frame test_Frame.cpp)
target_link_libraries( frame videoproc ${OpenCV_LIBS} )
