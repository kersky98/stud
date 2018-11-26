cmake_minimum_required(VERSION 2.6)

set(PROJECT_NAME factor)
set(PROJECT_LANGUAGES CXX)
set(ROOT_PATH "../../../..")

project(${PROJECT_NAME} ${PROJECT_LANGUAGES})

set(SOURCES
  ../src/factor.cpp
)

set(HEADERS
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
