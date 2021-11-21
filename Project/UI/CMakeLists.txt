set( TARGET_NAME UI )

add_subdirectory( Widget )
add_subdirectory( Application )
add_subdirectory( WidgetManager )
add_subdirectory( NeuralNet )

set( OBJ_FILES
    $<TARGET_OBJECTS:Widget>
    $<TARGET_OBJECTS:Application>
    $<TARGET_OBJECTS:WidgetManager>
    )

add_library( ${TARGET_NAME} STATIC ${OBJ_FILES})
target_link_libraries( ${TARGET_NAME} Qt5::Core Qt5::Widgets NeuralNet Neuron)
