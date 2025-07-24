cmake_minimum_required(VERSION 3.25)
project(SerDesAdapterBaseNodesTests VERSION 1.0
        DESCRIPTION "Catch2 unit tests and benchmark for cpp code"
        HOMEPAGE_URL "www.arale.ru"
        LANGUAGES CXX
        )
set(LIB_NAME SerDesAdapterNodes)
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/../../gen/SourceCPP)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

add_subdirectory(unit_test)
add_subdirectory(benchmark)

