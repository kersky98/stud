cmake_minimum_required(VERSION 2.6)

set(PROJECT_NAME lab5_client)
set(PROJECT_LANGUAGES CXX)
set(CPP_CLI_SUPPORT YES)
set(ROOT_PATH "../../../../..")

project(${PROJECT_NAME} ${PROJECT_LANGUAGES})

set_target_properties(${TargetName} PROPERTIES COMPILE_FLAGS "/clr")

if(CMAKE_CXX_FLAGS_DEBUG MATCHES "/RTC1")
   string(REPLACE "/RTC1" " " CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
endif()

if(CMAKE_CXX_FLAGS MATCHES "/EHsc")
   string(REPLACE "/EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

set(SOURCES
  ../src/client.cpp
)

set(HEADERS
  ../include/form.h
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
