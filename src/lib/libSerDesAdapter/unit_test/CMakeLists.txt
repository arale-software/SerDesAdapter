cmake_minimum_required(VERSION 3.25)
project(${LIB_NAME}.UnitTest)
message("Building unit test for ${LIB_NAME}")

find_package(Catch2 REQUIRED)
include(CTest)
include(Catch)

file(GLOB_RECURSE TEST_SOURCES src/*.cpp src/*.cxx src/*.c src/*.cc src/*.CPP src/*.CXX src/*.C src/*.CC)
add_executable(${PROJECT_NAME} ${TEST_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE 
Catch2::Catch2WithMain
${LIB_NAME}
)

catch_discover_tests(${PROJECT_NAME})

include(CodeCoverage)
append_coverage_compiler_flags()
setup_target_for_coverage_lcov(NAME coverage EXECUTABLE ctest EXCLUDE "/usr/include/*" "${PROJECT_SOURCE_DIR}/app/*")

set_target_properties(${PROJECT_NAME} PROPERTIES 
POSITION_INDEPENDENT_CODE ON
CXX_STANDARD 20
)

target_compile_features(${PROJECT_NAME} PRIVATE 
cxx_std_20
)

target_compile_options(${PROJECT_NAME} PRIVATE 
"$<$<CONFIG:Release>:-O3;-DNDEBUG>"
"$<$<CONFIG:Debug>:-O0;-g3;-DDEBUG;>" 
-fmessage-length=0 -pedantic
-Wall -Wextra -Wpedantic -Wshadow -Wconversion 
-Werror -Wfloat-equal -Wformat-nonliteral 
-Wformat-security -Wformat-y2k -Wformat=2 
-Wimport -Winvalid-pch -Wlogical-op 
-Wmissing-declarations -Wmissing-field-initializers 
-Wmissing-format-attribute -Wmissing-include-dirs 
-Wmissing-noreturn -Wpacked -Wwrite-strings 
-Wpointer-arith -Wredundant-decls -Wstack-protector 
-Wstrict-null-sentinel -Wswitch-enum -Wundef
)