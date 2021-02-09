cmake_minimum_required(VERSION 3.15)
project(program)

set(CMAKE_CXX_STANDARD 14)


add_executable(program trainer.cpp trainee.cpp trainee.h trainer.h)
#add_executable(program trainer.cpp )
