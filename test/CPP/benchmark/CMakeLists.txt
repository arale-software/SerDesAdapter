cmake_minimum_required(VERSION 3.25)
project(${LIB_NAME}.Benchmark)
message("Building benchmark for ${LIB_NAME}")

file(GLOB_RECURSE BENCHMARK_SOURCES src/*.cpp src/*.cxx src/*.c src/*.cc src/*.CPP src/*.CXX src/*.C src/*.CC)
add_executable(${PROJECT_NAME} ${BENCHMARK_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE 
benchmark
)

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