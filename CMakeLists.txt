cmake_minimum_required(VERSION 3.28)

project(dz2)

add_library(View_Lib dz2/View.h dz2/View.cpp)
add_library(Controller_Lib dz2/Controller.h dz2/Controller.cpp)
add_library(Model_Lib dz2/Model.h dz2/Model.cpp)

add_executable(dz2 dz2/dz2.cpp dz2/Model.cpp dz2/Controller.cpp dz2/View.cpp)
target_link_libraries(dz2 ${Model_Lib} ${Controller_Lib} ${View_Lib})