set( TARGET_NAME Widget )

set( HEADERS
  AbstractWidget.h
)

set( SOURCES
  AbstractWidget.cpp
)

add_library( ${TARGET_NAME} OBJECT ${SOURCES} ${HEADERS} )
target_link_libraries( ${TARGET_NAME} Qt5::Core Qt5::Widgets )
