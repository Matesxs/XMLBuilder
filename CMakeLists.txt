cmake_minimum_required(VERSION 3.14)

project(XMLBuilderLib VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Headers
  include/xmlbuilder.hpp
)

add_library(${PROJECT_NAME} INTERFACE ${Headers})
target_include_directories(${PROJECT_NAME} INTERFACE include/)

add_subdirectory(tests/)
add_subdirectory(docs/)
