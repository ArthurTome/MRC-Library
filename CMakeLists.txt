# CMakeList.txt: arquivo de projeto de CMake de nível superior, fazer configuração global
# e inclua subprojetos aqui.
#
cmake_minimum_required (VERSION 3.8)

project ("MRC-Library")

# Inclua subprojetos.
add_subdirectory ("src")
