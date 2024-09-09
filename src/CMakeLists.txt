cmake_minimum_required(VERSION 3.25)
project(AraleProject VERSION 1.0
        DESCRIPTION "Orcs-gladiators from outer space gachi fight"
        HOMEPAGE_URL "www.arale.ru"
        LANGUAGES CXX
        )
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(AAGitInfo)
arale_get_git_info()

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/lib)
include_directories(${CMAKE_SOURCE_DIR}/third_party)

set(LIB_NAME SerDesAdapter)
add_subdirectory(lib/libSerDesAdapter)

set(APP_NAME AraleTestCLI)
add_subdirectory(app/cli)
target_link_libraries(${APP_NAME} SerDesAdapter) 
