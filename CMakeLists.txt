cmake_minimum_required(VERSION 3.4.0)


# =========================================================================
#
#                           Main Project Section
#
# =========================================================================

# Project name
set(PROJECT_NAME_STR basic_c_project)

# Project language
project(${PROJECT_NAME_STR} C CXX)

# Source Files
file(GLOB MAIN_SRC "src/*.cpp")
file(GLOB TEST_SRC "test/*.cpp")


# Platform project specific code
if(WIN32)
  set(MAIN_SRC ${MAIN_SRC} ${PROJECT_SOURCE_DIR}/platform/windows.c)
else ()
  set(MAIN_SRC ${MAIN_SRC} ${PROJECT_SOURCE_DIR}/platform/unix.c)
endif()

find_package(OpenCV 3 REQUIRED)
# Main Executable
add_executable(${PROJECT_NAME_STR} ${MAIN_SRC})

# Output build path
set_target_properties(${PROJECT_NAME_STR}
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# 3rd party libs
set(EXTRA_LIBS_PATH ${PROJECT_SOURCE_DIR}/extra)

# =========================================================================
#
#                              Test Section
#
# =========================================================================

enable_testing()

# Project test name(s)
set(PROJECT_TEST ${PROJECT_NAME_STR}_test)

# Project Test(s) executables
add_executable(${PROJECT_TEST} ${TEST_SRC})

# Project test Output path
set_target_properties(${PROJECT_TEST}
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test"
)

# Using Google Test Unit
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_TEST} ${GTEST_BOTH_LIBRARIES})

# =========================================================================
#
#                             Logging Section
#
# =========================================================================

# Logger spdlog, only headers are required
set(LOGGER_PATH ${EXTRA_LIBS_PATH}/spdlog)
include_directories(${LOGGER_PATH}/include)

# spdlog requrie c++11 extension
target_compile_features(${PROJECT_NAME_STR} PRIVATE cxx_alias_templates)


# =========================================================================
#
#                       Command Line Flags Section
#
# =========================================================================

# Using Google Flags Library for command line flags parsing
# Flags compiled libs per platform
if(APPLE)
  set(GFLAGS_PATH ${EXTRA_LIBS_PATH}/gflags/osx)
elseif(WIN32)
  set(GFLAGS_PATH ${EXTRA_LIBS_PATH}/gflags/win)
else()
  set(GFLAGS_PATH ${EXTRA_LIBS_PATH}/gflags/unix)
endif()

# Headers
include_directories(${GFLAGS_PATH}/include)

# Links OSX
if(APPLE)
  target_link_libraries(${PROJECT_NAME_STR} ${GFLAGS_PATH}/lib/libgflags_nothreads.dylib)
endif()
