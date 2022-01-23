set( TARGET_NAME NodeNetworkUI )

set( HEADERS
    Node.h
    NodeView.h
    NodeConnection.h
    NodeConnectionView.h
    NodeNetworkLayer.h
    NodeNetworkLayerView.h
    NodeNetwork.h
    NodeNetworkView.h
    Neuron.h
    NeuronView.h
    NeuralNetworkManager.h
)

set( SOURCES
    Node.cpp
    NodeView.cpp
    NodeConnection.cpp
    NodeConnectionView.cpp
    NodeNetworkLayer.cpp
    NodeNetworkLayerView.cpp
    NodeNetwork.cpp
    NodeNetworkView.cpp
    Neuron.cpp
    NeuronView.cpp
    NeuralNetworkManager.cpp
)

include_directories( ../.. )

add_library( ${TARGET_NAME} OBJECT ${SOURCES} ${HEADERS})
target_link_libraries( ${TARGET_NAME} Qt5::Core Qt5::Widgets )
