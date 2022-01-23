set( TARGET_NAME NeuralNetworkShared )

set( HEADERS
  Defines.h
)

set( SOURCES
)

add_library( ${TARGET_NAME} OBJECT ${SOURCES} ${HEADERS} )
target_link_libraries( ${TARGET_NAME} Qt5::Core)
