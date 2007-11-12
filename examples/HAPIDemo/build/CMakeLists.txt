# The name of our project is "HELLO".  CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
project (HAPIDemo)

# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found.  Any number of sources could be listed here.

AUX_SOURCE_DIRECTORY(.. HAPIDemo_SRCS)

INCLUDE_DIRECTORIES( .. )

SET(requiredLibs)

SET(CMAKE_MODULE_PATH "../../../build/modules/")

#H3DUtil
FIND_PACKAGE(H3DUtil REQUIRED)

IF(H3DUTIL_FOUND)
  INCLUDE_DIRECTORIES( ${H3DUTIL_INCLUDE_DIR} ) 
  SET(requiredLibs ${requiredLibs} ${H3DUTIL_LIBRARIES} )
ENDIF(H3DUTIL_FOUND)

#HAPI
FIND_PACKAGE(HAPI REQUIRED)

IF(HAPI_FOUND)
  INCLUDE_DIRECTORIES( ${HAPI_INCLUDE_DIR} ) 
  SET(requiredLibs ${requiredLibs} ${HAPI_LIBRARIES} )
ENDIF(HAPI_FOUND)

SET(wxWidgets_USE_LIBS base core)

FIND_PACKAGE(wxWidgets REQUIRED)
IF(wxWidgets_FOUND)
  INCLUDE(${wxWidgets_USE_FILE})
  SET(requiredLibs ${requiredLibs} ${wxWidgets_LIBRARIES} )
ENDIF(wxWidgets_FOUND)

ADD_EXECUTABLE(HAPIDemo MACOSX_BUNDLE ${HAPIDemo_SRCS})

TARGET_LINK_LIBRARIES( HAPIDemo ${requiredLibs} ${optionalLibs} )

#INSTALL( TARGETS HAPIDemo
#	 LIBRARY DESTINATION lib
#	 RUNTIME DESTINATION bin )
