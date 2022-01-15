set( TARGET_NAME Shared )

add_subdirectory( Communicator )
add_subdirectory( NodeNetwork )

set( OBJ_FILES
    $<TARGET_OBJECTS:NodeNetwork>
    )

add_library( ${TARGET_NAME} STATIC ${OBJ_FILES})
