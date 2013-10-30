
include_directories ( ../include )
add_executable (frame test_Frame.cpp)
target_link_libraries( frame videoproc ${OpenCV_LIBS} )
