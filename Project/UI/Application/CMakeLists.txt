set( TARGET_NAME Application )

set( UI
    mainwindow.ui
    NeuralNetworkTestWidget.ui
)

set( HEADERS
    Application.h
    ApplicationView.h
    CentralWidget.h
    CentralWidgetView.h
    RightDockWidget.h
    RightDockWidgetView.h
    NeuralNetworkTestWidget.h
    NeuralNetworkTestWidgetView.h
)

set( SOURCES
    Application.cpp
    ApplicationView.cpp
    CentralWidget.cpp
    CentralWidgetView.cpp
    RightDockWidget.cpp
    RightDockWidgetView.cpp
    NeuralNetworkTestWidget.cpp
    NeuralNetworkTestWidgetView.cpp
)

include_directories( .. ../.. ../../..)

add_library( ${TARGET_NAME} OBJECT ${SOURCES} ${HEADERS} ${UI} )
target_link_libraries( ${TARGET_NAME} Qt5::Core Qt5::Widgets )

