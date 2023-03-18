cmake_minimum_required(VERSION 3.5)
project(qpTBR)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


include_directories(
  include
)

add_executable(qpTBR src/main.cpp src/Matrix.cpp src/QProblem.cpp)
target_link_libraries(qpTBR lapack blas)