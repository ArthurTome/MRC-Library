cmake_minimum_required (VERSION 3.12)

# Initialize project
project ("mrc")

# Configure output diretories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

SET(CMAKE_CXX_FLAGS "-lm -lfftw3 -fopenmp -lpthread")
SET(CMAKE_C_FLAGS   "-lm -lfftw3")

# Subdiretory
add_subdirectory ("src/mrc")
