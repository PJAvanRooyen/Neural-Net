set( TARGET_NAME Imports )

set( HEADERS
  Datasets/Iris/iris.names
  Datasets/Iris/iris.data
)

set( SOURCES
)

add_library( ${TARGET_NAME} OBJECT ${SOURCES} ${HEADERS} )

