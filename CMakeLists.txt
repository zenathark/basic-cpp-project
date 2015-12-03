cmake_minimum_required(VERSION 3.4.0)

set(PROJECT_NAME_STR basic_c_project)
set(PROJECT_TEST ${PROJECT_NAME_STR}_test)

project(${PROJECT_NAME_STR} C CXX)

file(GLOB MAIN_SRC "src/*.cpp")
file(GLOB TEST_SRC "test/*.cpp")

enable_testing()
find_package(GTest REQUIRED)

# 3rd party libs
set(EXTRA_LIBS_PATH ${PROJECT_SOURCE_DIR}/extra)

# Logger spdlog
set(LOGGER_PATH ${EXTRA_LIBS_PATH}/spdlog)
include_directories(${LOGGER_PATH}/include)

# Flags libs
if(APPLE)
  set(GFLAGS_PATH ${EXTRA_LIBS_PATH}/gflags/osx)
elseif(WIN32)
  set(GFLAGS_PATH ${EXTRA_LIBS_PATH}/gflags/win)
else()
  set(GFLAGS_PATH ${EXTRA_LIBS_PATH}/gflags/unix)
endif()

include_directories(${GFLAGS_PATH}/include)

# Platform specific code
if(WIN32)
  set(MAIN_SRC ${MAIN_SRC} ${PROJECT_SOURCE_DIR}/platform/windows.c)
else ()
  set(MAIN_SRC ${MAIN_SRC} ${PROJECT_SOURCE_DIR}/platform/unix.c)
endif()



set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${GTEST_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME_STR} ${MAIN_SRC})
target_link_libraries(${PROJECT_NAME_STR} ${GFLAGS_PATH}/lib/libgflags_nothreads.dylib)
target_compile_features(${PROJECT_NAME_STR} PRIVATE cxx_alias_templates)

add_executable(${PROJECT_TEST} ${TEST_SRC})
target_link_libraries(${PROJECT_TEST} ${GTEST_BOTH_LIBRARIES})

set_target_properties(${PROJECT_NAME_STR}
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

set_target_properties(${PROJECT_TEST}
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test"
)
