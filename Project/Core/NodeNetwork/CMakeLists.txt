set( TARGET_NAME NodeNetwork )

set( HEADERS
  NodeNetworkFactory.h
  NodeNetwork.h
  Node.h
  NodeConnection.h
)

set( SOURCES
  NodeNetworkFactory.cpp
  NodeNetwork.cpp
  Node.cpp
  NodeConnection.cpp
)

# needed to find WidgetManager
include_directories( ../.. )

add_library( ${TARGET_NAME} OBJECT ${SOURCES} ${HEADERS} )
target_link_libraries( ${TARGET_NAME} Qt5::Core)
