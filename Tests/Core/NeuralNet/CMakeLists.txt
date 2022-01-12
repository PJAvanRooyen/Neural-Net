set( TARGET_NAME Tests_Core_NeuralNet )

set( HEADERS
  IrisDataExtractor.h
  NeuralNetTest.h
  NeuralNetTestHelper.h
)

set( SOURCES
)

add_library( ${TARGET_NAME} OBJECT ${SOURCES} ${HEADERS} )
