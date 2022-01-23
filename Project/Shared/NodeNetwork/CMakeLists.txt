set( TARGET_NAME NodeNetworkShared )

set( HEADERS
  NodeNetworkManager.h
  NodeNetworkFactory.h
  AbstractNodeNetwork.h
  AbstractNodeNetworkLayer.h
  AbstractNode.h
  AbstractNodeConnection.h
)

set( SOURCES
  NodeNetworkManager.cpp
  NodeNetworkFactory.cpp
  AbstractNodeNetwork.cpp
  AbstractNodeNetworkLayer.cpp
  AbstractNode.cpp
  AbstractNodeConnection.cpp
)

# needed to find WidgetManager
include_directories( ../.. )

add_library( ${TARGET_NAME} OBJECT ${SOURCES} ${HEADERS} )
target_link_libraries( ${TARGET_NAME} Qt5::Core)
