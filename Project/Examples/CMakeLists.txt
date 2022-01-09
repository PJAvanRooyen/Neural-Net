set( TARGET_NAME Examples )


set( HEADERS
  VariadicTemplate.h
)

set( SOURCES
  VariadicTemplate.cpp
)

add_library( ${TARGET_NAME} STATIC ${SOURCES} ${HEADERS} )
target_link_libraries( ${TARGET_NAME} Qt5::Core)
