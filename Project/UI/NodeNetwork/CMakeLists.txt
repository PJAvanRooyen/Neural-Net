set( TARGET_NAME NodeNetworkUI )

set( HEADERS
    Node.h
    NodeView.h
    NodeConnection.h
    NodeConnectionView.h
    NodeNetworkLayer.h
    NodeNetwork.h
    Neuron.h
    NeuronView.h
)

set( SOURCES
    Node.cpp
    NodeView.cpp
    NodeConnection.cpp
    NodeConnectionView.cpp
    NodeNetworkLayer.cpp
    NodeNetwork.cpp
    Neuron.cpp
    NeuronView.cpp
)

include_directories( ../.. )

add_library( ${TARGET_NAME} OBJECT ${SOURCES} ${HEADERS})
target_link_libraries( ${TARGET_NAME} Qt5::Core Qt5::Widgets )
