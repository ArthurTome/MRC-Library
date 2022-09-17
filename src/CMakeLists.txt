# CMakeList.txt: projeto de CMake para CMakeProject1, incluir origem e definir
# lógica específica a um projeto aqui.
#
cmake_minimum_required (VERSION 3.8)

# Adicione a origem ao executável deste projeto.
add_executable (MRC-Library "main.cpp" "MRC.cpp" "MRC.hpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MRC-Library PROPERTY CXX_STANDARD 20)
endif()

# TODO: Adicione testes e instale destinos, se necessário.
