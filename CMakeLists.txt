cmake_minimum_required(VERSION 3.30)
project(cop3530proj2)

set(CMAKE_CXX_STANDARD 14)

set(wxWidgets_USE_STATIC ON)

find_package(wxWidgets CONFIG REQUIRED)

add_executable(cop3530proj2
        main.cpp
)

target_link_libraries(cop3530proj2 PRIVATE wx::core wx::base)