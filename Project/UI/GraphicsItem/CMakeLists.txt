set( TARGET_NAME GraphicsItem )

set( HEADERS
  AbstractGraphicsItemController.h
)

set( SOURCES
  AbstractGraphicsItemController.cpp
)

add_library( ${TARGET_NAME} OBJECT ${SOURCES} ${HEADERS} )
target_link_libraries( ${TARGET_NAME} Qt5::Core Qt5::Widgets )
