cmake_minimum_required(VERSION 3.15)

project(lab2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE ./src/main.cpp)


set (DIR_OUT ${CMAKE_CURRENT_SOURCE_DIR}/out)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${DIR_OUT}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${DIR_OUT}/bin)


add_executable(main ${SOURCE})


add_subdirectory(plugins)


target_link_libraries(main ifc_base ifc_visualizer ifc_num_methods euler_method heun_method adams-bashforth_method runge-kutta_method plot csv_gen  ${CMAKE_DL_LIBS})