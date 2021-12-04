set( TARGET_NAME Core )

add_subdirectory( ModuleManager )
add_subdirectory( NodeNetwork )
add_subdirectory( NeuralNetwork )

set( OBJ_FILES
    $<TARGET_OBJECTS:ModuleManager>
    $<TARGET_OBJECTS:NodeNetwork>
    $<TARGET_OBJECTS:NeuralNetwork>
    )

add_library( ${TARGET_NAME} STATIC ${OBJ_FILES})
