set( TARGET_NAME Neural-Net )
add_subdirectory( Project )
add_subdirectory( Thirdparty )
add_subdirectory( Tests )

set( THIRDPARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Thirdparty )
set( DATASETS_DIR ${THIRDPARTY_DIR}/Imports/Datasets )

# Copy files from source directory to destination directory, substituting any
# variables.  Create destination directory if it does not exist.
macro( copy_files_and_folders source destination name)
    message( STATUS "Copying files" )
    if( ${TARGET_NAME} MATCHES .+ )
        message( STATUS "Configuring ${TARGET_NAME} ${name}" )
    else( ${TARGET_NAME} MATCHES .+ )
        message( STATUS "Configuring Common ${name}" )
    endif( ${TARGET_NAME} MATCHES .+ )
    make_directory( ${destination} )
    file( GLOB_RECURSE files RELATIVE ${source} ${source}/* )
    foreach( file ${files} )
      if( TSN_PRINT_DATACOPY )
        message( STATUS "Found ${file}" )
      endif()
        set( srcPath ${source}/${file} )
        if( NOT IS_DIRECTORY ${srcPath} )
            configure_file(
                    ${srcPath}
                    ${destination}/${file}
                    COPYONLY )
             if( TSN_PRINT_DATACOPY )
               message( STATUS "Copying ${srcPath}" )
             endif( TSN_PRINT_DATACOPY )
        endif( NOT IS_DIRECTORY ${srcPath} )
    endforeach( file )
endmacro()

macro( copy_datasets )
    copy_files_and_folders(${DATASETS_DIR} ${CMAKE_BINARY_DIR}/Thirdparty/Imports/Datasets Datasets)
endmacro( copy_datasets )

copy_datasets()
