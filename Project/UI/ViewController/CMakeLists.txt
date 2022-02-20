set( TARGET_NAME ViewController )

set( HEADERS
  AbstractViewController.h
)

set( SOURCES
  AbstractViewController.cpp
)

add_library( ${TARGET_NAME} OBJECT ${SOURCES} ${HEADERS} )
target_link_libraries( ${TARGET_NAME} Qt5::Core Qt5::Widgets )
