set( TARGET_NAME Shared )

add_subdirectory( Communicator )
add_subdirectory( NodeNetwork )
add_subdirectory( NeuralNetwork )

set( OBJ_FILES
    $<TARGET_OBJECTS:Communicator>
    $<TARGET_OBJECTS:NodeNetwork>
    $<TARGET_OBJECTS:NeuralNetwork>
    )

add_library( ${TARGET_NAME} STATIC ${OBJ_FILES})
