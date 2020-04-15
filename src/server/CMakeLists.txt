cmake_minimum_required(VERSION 3.13)
project(camera-control-server CXX)
set(CMAKE_CXX_STANDARD 14)
set(BOOST_ROOT /opt/boost)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS system)

include_directories(${Boost_INCLUDE_DIR})
add_executable(camera-control-server 
    main.cpp
    DiodState.cpp
    DiodColor.cpp
    DiodFrequency.cpp
    CommandsDiodState.cpp
    CommandsDiodColor.cpp
    CommandsDiodFreq.cpp
    Server.cpp
    AsyncTcpServer.cpp)
target_link_libraries(camera-control-server ${Boost_LIBRARIES} pthread)
configure_file(../../settings/server.ini server.ini COPYONLY)
