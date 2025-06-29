cmake_minimum_required(VERSION 3.15)
project(myproject)

# C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output dirs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include header files
include_directories(include)

# Collect all source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
src/*.cpp
)

# Define executable
add_executable(myproject ${SOURCES})

install(TARGETS myproject
RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)

