cmake_minimum_required(VERSION 3.9)
project(decorator)

set(PROJECT_LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)

find_package(Doxygen)

set(SOURCE_FILES main.cpp)
set(HEADERS_FILES decorator.h)

message(${PROJECT_SOURCE_DIR})
message(${CMAKE_CURRENT_BINARY_DIR})
#set (EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})

if(DOXYGEN_FOUND)
  set(DOXYGEN_GENERATE_HTML YES)
  #set(DOXYGEN_GENERATE_MAN  YES)
  set(DOXYGEN_GENERATE_RTF  YES)
  set(DOXYGEN_IN ${PROJECT_SOURCE_DIR})
  set(DOXYGEN_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
  set(DOXYGEN_OUTPUT_LANGUAGE "Russian")


  doxygen_add_docs(
          doxygen
          ${DOXYGEN_IN}
          COMMENT "Generate my docs"
  )


  #add_custom_command(
  #        OUTPUT ${DOXYGEN_OUTPUT}
  #        COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
  #        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
  #        COMMAND ${CMAKE_COMMAND} -E echo "Done."
  #        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  #        DEPENDS ${DOXYGEN_INPUT}
  #)

  #add_custom_target(apidoc ALL DEPENDS ${DOXYGEN_OUTPUT})

  #add_custom_target(apidoc_forced
  #        COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
  #        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
  #        COMMAND ${CMAKE_COMMAND} -E echo "Done."
  #        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  #        )

endif(DOXYGEN_FOUND)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_executable(decorator ${SOURCE_FILES} ${HEADERS_FILES})
