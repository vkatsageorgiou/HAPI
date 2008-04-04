# - Find Haptik
# Find the native HAPTIK headers and libraries.
#
#  HAPTIK_INCLUDE_DIR -  where to find Haptik headers
#  HAPTIK_LIBRARIES    - List of libraries when using Haptik.
#  HAPTIK_FOUND        - True if Haptik found.


# Look for the header file.
FIND_PATH(HAPTIK_INCLUDE_DIR NAMES RSLib/Haptik.hpp)
MARK_AS_ADVANCED(HAPTIK_INCLUDE_DIR)

# Look for the library.
FIND_LIBRARY(HAPTIK_LIBRARY NAMES Haptik.Library )
MARK_AS_ADVANCED(HAPTIK_LIBRARY)

# Copy the results to the output variables.
IF(HAPTIK_INCLUDE_DIR AND HAPTIK_LIBRARY)
  SET(HAPTIK_FOUND 1)
  SET(HAPTIK_LIBRARIES ${HAPTIK_LIBRARY} )
  SET(HAPTIK_INCLUDE_DIR ${HAPTIK_INCLUDE_DIR})
ELSE(HAPTIK_INCLUDE_DIR AND HAPTIK_LIBRARY)
  SET(HAPTIK_FOUND 0)
  SET(HAPTIK_LIBRARIES)
  SET(HAPTIK_INCLUDE_DIR)
ENDIF(HAPTIK_INCLUDE_DIR  AND HAPTIK_LIBRARY)

