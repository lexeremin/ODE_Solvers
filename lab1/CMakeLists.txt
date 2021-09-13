cmake_minimum_required(VERSION 3.15)

project(lab1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE ./src/main.cpp)

add_executable(main ${SOURCE})

add_subdirectory(lib/numerical_methods/)
#add_subdirectory(lib/plot_tools)

target_link_libraries(main euler_method runge-kutta_method plot ${CMAKE_DL_LIBS})