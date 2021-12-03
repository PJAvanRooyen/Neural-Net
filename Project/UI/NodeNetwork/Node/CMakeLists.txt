set( TARGET_NAME NodeUI )

set( HEADERS
    Node.h
    Neuron.h
    NodeView.h
    NeuronView.h
)

set( SOURCES
    Node.cpp
    Neuron.cpp
    NodeView.cpp
    NeuronView.cpp
)

include_directories( ../../.. )

add_library( ${TARGET_NAME} OBJECT ${SOURCES} ${HEADERS} )
target_link_libraries( ${TARGET_NAME} Qt5::Core  Qt5::Widgets)
