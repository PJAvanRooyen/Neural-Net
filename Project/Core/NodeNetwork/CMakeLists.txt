set( TARGET_NAME NodeNetwork )

set( HEADERS
  NodeNetwork.h
  NodeNetworkLayer.h
  Node.h
  NodeConnection.h
)

set( SOURCES
  NodeNetwork.cpp
  NodeNetworkLayer.cpp
  Node.cpp
  NodeConnection.cpp
)

# needed to find WidgetManager
include_directories( ../.. )

add_library( ${TARGET_NAME} OBJECT ${SOURCES} ${HEADERS} )
target_link_libraries( ${TARGET_NAME} Qt5::Core)
