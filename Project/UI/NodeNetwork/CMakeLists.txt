set( TARGET_NAME NodeNetworkUI )

add_subdirectory( Node )

set( OBJ_FILES
    $<TARGET_OBJECTS:NodeUI>
    )

add_library( ${TARGET_NAME} STATIC ${OBJ_FILES})
