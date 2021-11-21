cmake_minimum_required (VERSION 2.8)

project(myoptional CXX)

set(CMAKE_CXX_STANDARD 14)

option(MYOPTIONAL_WITH_TESTS "Build with test" ON)

if(NOT MSVC)
    add_definitions(-Wall -Wextra)
endif()

# Hedear-Only library
add_library(myoptional INTERFACE)
target_include_directories(myoptional INTERFACE include/)

if(MYOPTIONAL_WITH_TESTS)
    enable_testing()
    #include_directories(3rdParty/catch2/include/)

    add_subdirectory(3rdParty/catch2)
    add_subdirectory(test)
endif()
