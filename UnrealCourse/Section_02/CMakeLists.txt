cmake_minimum_required(VERSION 3.6)
project(CowBullGame)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp FCowBullGame.h FCowBullGame.cpp)
add_executable(CowBullGame ${SOURCE_FILES} FCowBullGame.h)