set( TARGET_NAME Tests_Core )
add_subdirectory( NeuralNetwork )

set( OBJ_FILES
    $<TARGET_OBJECTS:NeuralNetwork>
    )

