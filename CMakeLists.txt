cmake_minimum_required(VERSION 3.25)
project(tetrahedron_in_pyramid)

set(CMAKE_CXX_STANDARD 17)

add_executable(tetrahedron_in_pyramid main.cpp)

target_link_libraries(tetrahedron_in_pyramid "-framework GLUT" "-framework OpenGL")