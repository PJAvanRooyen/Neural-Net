set( TARGET_NAME Tests_Core_NeuralNetwork )

set( HEADERS
  NeuralNetworkTest.h
)

set( SOURCES
)

add_library( ${TARGET_NAME} OBJECT ${SOURCES} ${HEADERS} )
target_link_libraries( ${TARGET_NAME} Qt5::Core)

