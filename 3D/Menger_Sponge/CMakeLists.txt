CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(Menger_sponge)


FIND_PACKAGE(OpenGL REQUIRED)
IF(NOT OPENGL_FOUND)
  MESSAGE(FATAL_ERROR "Error : OpenGL Libraries not found")
ENDIF(NOT OPENGL_FOUND)

FIND_PACKAGE(GLEW REQUIRED)


FIND_PACKAGE(GLUT REQUIRED)
IF(NOT GLUT_FOUND)
  MESSAGE(FATAL_ERROR "Error : GLUT Library not found")
ENDIF(NOT GLUT_FOUND)


#
# Try to find SOIL library and include path.
# Once done this will define
#
# SOIL_FOUND
# SOIL_INCLUDE_PATH
# SOIL_LIBRARY
#


IF(WIN32)
FIND_PATH( SOIL_INCLUDE_PATH SOIL/SOIL.h
  $ENV{PROGRAMFILES}/SOIL/include
  ${SOIL_ROOT_DIR}/include
  DOC "The directory where SOIL/SOIL.h resides")
FIND_LIBRARY( SOIL_LIBRARY
  NAMES libSOIL.a SOIL
  PATHS
  $ENV{PROGRAMFILES}/SOIL/lib
  ${SOIL_ROOT_DIR}/lib
  DOC "The SOIL library")
ELSE(WIN32)
  FIND_PATH( SOIL_INCLUDE_PATH SOIL/SOIL.h
    /usr/include
    /usr/local/include
    /sw/include
    /opt/local/include
    ${SOIL_ROOT_DIR}/include
    DOC "The directory where SOIL/SOIL.h resides")
  # Prefer the static library.
  FIND_LIBRARY( SOIL_LIBRARY
    NAMES libSOIL.a SOIL
    PATHS
    /usr/lib64
    /usr/lib
    /usr/local/lib64
    /usr/local/lib
    /sw/lib
    /opt/local/lib
    ${SOIL_ROOT_DIR}/lib
    DOC "The SOIL library")
ENDIF(WIN32)

SET(SOIL_FOUND "NO")
IF(SOIL_INCLUDE_PATH AND SOIL_LIBRARY)
  SET(SOIL_LIBRARIES ${SOIL_LIBRARY})
  SET(SOIL_FOUND "YES")
  message(STATUS "Found SOIL")
ENDIF(SOIL_INCLUDE_PATH AND SOIL_LIBRARY)
  

add_executable(menger.out menger_sponge.cpp)
INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR}  ${GLUT_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${SOIL_INCLUDE_PATH} ${CMAKE_SOURCE_DIR}/Common)
target_link_libraries(menger.out ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${SOIL_LIBRARY} lsystem shader)
install(TARGETS menger.out RUNTIME DESTINATION bin)
