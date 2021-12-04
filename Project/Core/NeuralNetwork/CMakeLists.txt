set( TARGET_NAME NeuralNetwork )

set( HEADERS
  Neuron.h
  NeuronConnection.h
)

set( SOURCES
  Neuron.cpp
  NeuronConnection.cpp
)

# needed to find WidgetManager
include_directories( ../.. )

add_library( ${TARGET_NAME} OBJECT ${SOURCES} ${HEADERS} )
target_link_libraries( ${TARGET_NAME} Qt5::Core)
