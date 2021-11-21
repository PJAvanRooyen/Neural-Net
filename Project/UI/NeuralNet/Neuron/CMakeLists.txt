set( TARGET_NAME Neuron )

set( HEADERS
    Neuron.h
    NeuronView.h
)

set( SOURCES
    Neuron.cpp
    NeuronView.cpp
)

include_directories( ../../.. )

add_library( ${TARGET_NAME} OBJECT ${SOURCES} ${HEADERS} )
target_link_libraries( ${TARGET_NAME} Qt5::Core  Qt5::Widgets)
