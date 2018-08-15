cmake_minimum_required(VERSION 3.12)
project(elevator_model)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(
        elevator_model
        Assistance.h
        Building.h
        Elevator.h
        Floor.h
        main.cpp
        Passenger.h
        Passenger.cpp
        Floor.cpp
        Elevator.cpp
        Building.cpp)
