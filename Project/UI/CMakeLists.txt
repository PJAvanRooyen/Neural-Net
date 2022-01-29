set( TARGET_NAME UI )

add_subdirectory( ViewController )
add_subdirectory( GraphicsItem )
add_subdirectory( Application )
add_subdirectory( WidgetManager )
add_subdirectory( NodeNetwork )

set( OBJ_FILES
    $<TARGET_OBJECTS:ViewController>
    $<TARGET_OBJECTS:GraphicsItem>
    $<TARGET_OBJECTS:Application>
    $<TARGET_OBJECTS:WidgetManager>
    )

add_library( ${TARGET_NAME} STATIC ${OBJ_FILES})
target_link_libraries( ${TARGET_NAME} Qt5::Core Qt5::Widgets NodeNetworkShared NodeNetworkUI)
