cmake_minimum_required(VERSION 2.6)

set(PROJECT_NAME HoarsMonitor)
set(PROJECT_LANGUAGES C CXX)
set(ROOT_PATH "../../../..")

project(${PROJECT_NAME} ${PROJECT_LANGUAGES})

set(SOURCES
  ../src/HoarMonitor.cpp
)

set(HEADERS
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
