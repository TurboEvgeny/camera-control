cmake_minimum_required(VERSION 3.13)
project(camera-control-server CXX)
set(CMAKE_CXX_STANDARD 14)
add_executable(camera-control-server 
    main.cpp
    DiodState.cpp
    DiodColor.cpp
    DiodFrequency.cpp
    CommandsDiodState.cpp
    CommandsDiodColor.cpp)
