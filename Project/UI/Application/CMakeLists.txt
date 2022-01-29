set( TARGET_NAME Application )

set( UI
    mainwindow.ui
    NeuralNetworkRunWidget.ui
)

set( HEADERS
    Application.h
    ApplicationView.h
    CentralWidget.h
    CentralWidgetView.h
    RightDockWidget.h
    RightDockWidgetView.h
    NeuralNetworkRunWidget.h
    NeuralNetworkRunWidgetView.h
)

set( SOURCES
    Application.cpp
    ApplicationView.cpp
    CentralWidget.cpp
    CentralWidgetView.cpp
    RightDockWidget.cpp
    RightDockWidgetView.cpp
    NeuralNetworkRunWidget.cpp
    NeuralNetworkRunWidgetView.cpp
)

include_directories( .. ../.. ../../..)

add_library( ${TARGET_NAME} OBJECT ${SOURCES} ${HEADERS} ${UI} )
target_link_libraries( ${TARGET_NAME} Qt5::Core Qt5::Widgets )

