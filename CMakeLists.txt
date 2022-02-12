cmake_minimum_required(VERSION 3.14)

project(LConfig LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LOGGER_INCLUDE_DIR C:/Users/Admin/Documents/LLoggerLib)

include_directories(${LOGGER_INCLUDE_DIR})

add_library(LConfig STATIC
  lconfig.cpp
  lconfig.h
  lformat.cpp
  lformat.h
)

target_compile_definitions(LConfig PRIVATE LCONFIG_LIBRARY)
