#cmake_minimum_required (VERSION 3.12)

# List source files to executable
add_executable (${PROJECT_NAME} "main.cpp" 
                                "MRC.cpp" 
                                "MRC.hpp")

target_link_libraries(${PROJECT_NAME} /usr/local/lib/libfftw3.a)

# Ser CPP version
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()
