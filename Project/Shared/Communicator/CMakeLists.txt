set( TARGET_NAME Communicator )

set( HEADERS
  Communicator.h
)

set( SOURCES
  Communicator.cpp
)

include_directories( ../.. )

add_library( ${TARGET_NAME} OBJECT ${SOURCES} ${HEADERS} )
target_link_libraries( ${TARGET_NAME} Qt5::Core)
