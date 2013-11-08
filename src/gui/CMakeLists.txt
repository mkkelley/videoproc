include ( ${QT_USE_FILE} )
include_directories ( ../../include include )
add_definitions ( ${QT_DEFINITIONS} )

set ( GUI_SOURCES
    main.cpp
    MainWindow.cpp
    MatView.cpp
    RealtimeViewer.cpp
    )
set ( GUI_HEADERS
    include/MainWindow.h
    include/MatView.h
    include/RealtimeViewer.h
    )
QT4_WRAP_CPP(GUI_HEADERS_MOC ${GUI_HEADERS})
add_executable ( gui
    ${GUI_SOURCES}
    ${GUI_HEADERS_MOC}
    )
target_link_libraries( gui
    videoproc
    ${OpenCV_LIBS}
    ${QT_LIBRARIES}
    )
