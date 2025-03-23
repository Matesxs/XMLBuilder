cmake_minimum_required(VERSION 3.14)

project(XMLBuilderLib_Tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.16.0
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB TEST_SOURCES ./*.cpp ./*.hpp)
file(GLOB UTILS_SOURCES ./utils/*.cpp ./utils/*.hpp)

add_executable(
  ${PROJECT_NAME}
  ${TEST_SOURCES}
  ${UTILS_SOURCES}
)

target_include_directories(
  ${PROJECT_NAME} PRIVATE
  utils/
)

target_link_libraries(
  ${PROJECT_NAME}
  XMLBuilderLib
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
