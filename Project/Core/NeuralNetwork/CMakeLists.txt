set( TARGET_NAME NeuralNetwork )

set( HEADERS
  Neuron.h
  NeuralNetworkLayer.h
  NeuralNetwork.h
  NeuralNetworkFactory.h
  NeuralNetworkManager.h
  IrisDataExtractor.h
)

set( SOURCES
  Neuron.cpp
  NeuralNetworkLayer.cpp
  NeuralNetwork.cpp
  NeuralNetworkFactory.cpp
  NeuralNetworkManager.cpp
)

# needed to find WidgetManager
include_directories( ../.. )

add_library( ${TARGET_NAME} OBJECT ${SOURCES} ${HEADERS} )
target_link_libraries( ${TARGET_NAME} Qt5::Core)
