cmake_minimum_required(VERSION 3.23)
project(opengl_example)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(opengl_example src/opengl_example.cpp)
target_link_libraries(opengl_example PUBLIC GL GLU glut GLEW)

add_executable(opengl_image src/opengl_image.cpp)
target_link_libraries(opengl_image PUBLIC GL GLU glut GLEW)
