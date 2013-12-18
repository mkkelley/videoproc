include ( ${QT_USE_FILE} )
include_directories ( ../../include include ../parallel )
add_definitions ( ${QT_DEFINITIONS} )

set ( GUI_SOURCES
    main.cpp
    MainWindow.cpp
    MatView.cpp
    RealtimeUI.cpp
    RecorderUI.cpp
    CameraUI.cpp
    AlgorithmSelector.cpp
    )
set ( GUI_HEADERS
    include/MainWindow.h
    include/MatView.h
    include/RealtimeUI.h
    include/RecorderUI.h
    )
QT4_WRAP_CPP(GUI_HEADERS_MOC ${GUI_HEADERS})
add_executable ( gui
    ${GUI_SOURCES}
    ${GUI_HEADERS_MOC}
    )
target_link_libraries( gui
    videoproc
    parallel
    ${OpenCV_LIBS}
    ${QT_LIBRARIES}
    )
