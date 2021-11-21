set( TARGET_NAME NeuralNet )

add_subdirectory( Neuron )

set( OBJ_FILES
    $<TARGET_OBJECTS:Neuron>
    )

add_library( ${TARGET_NAME} STATIC ${OBJ_FILES})
