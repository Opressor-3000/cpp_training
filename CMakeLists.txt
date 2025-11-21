

cmake_minimum_required(VERSION 3.12)


project(cpp_training)


set(CMAKE_CXX_STANDARD 20)


add_subdirectory(src/lessons_ya_contest)
add_subdirectory(src/lessons_02_templates)

set(CMAKE_BUILD_TYPE=Debug)

# Папка, куда будут складываться исполняемые файлы
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)