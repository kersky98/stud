cmake_minimum_required(VERSION 2.6)

set(PROJECT_NAME lab3_client)
set(PROJECT_LANGUAGES CXX)
set(ROOT_PATH "../../../../..")

project(${PROJECT_NAME} ${PROJECT_LANGUAGES})

set(SOURCES
  ../src/client.cpp
)

set(HEADERS
)

#add_definitions(-D_USE_32BIT_TIME_T)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

if(WIN32)
target_link_libraries(${PROJECT_NAME} "ws2_32")
endif(WIN32)

#find_package (MD REQUIRED)
#find_library (LIB_NAME "ws2_32.lib")
#include_directories(${CMAKE_MODULE_PATH})
#message(${CMAKE_MODULE_PATH})

#include_directories(${CMAKE_MODULE_PATH})
#include(${CMAKE_MODULE_FILE})

#message("${CMAKE_MODULE_PATH}}")

#target_link_libraries(${PROJECT_NAME} "${CMAKE_MODULE_FILE}}")
#set(DEPENDS_MODULE
#  bt23_lib
#)
