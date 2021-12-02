set( TARGET_NAME Core )

add_subdirectory( ModuleManager )
add_subdirectory( NodeNetwork )

set( OBJ_FILES
    $<TARGET_OBJECTS:ModuleManager>
    $<TARGET_OBJECTS:NodeNetwork>
    )

add_library( ${TARGET_NAME} STATIC ${OBJ_FILES})
