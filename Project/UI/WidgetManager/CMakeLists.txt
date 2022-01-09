set( TARGET_NAME WidgetManager )

set( HEADERS
  WidgetManager.h
)

set( SOURCES
  WidgetManager.cpp
)

add_library( ${TARGET_NAME} OBJECT ${SOURCES} ${HEADERS} )
target_link_libraries( ${TARGET_NAME} Qt5::Core  )

