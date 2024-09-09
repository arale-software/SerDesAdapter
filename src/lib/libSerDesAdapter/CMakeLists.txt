cmake_minimum_required(VERSION 3.25)
if (NOT LIB_NAME)
set(LIB_NAME AraleLib)
endif()

project(${LIB_NAME} VERSION 1.0
DESCRIPTION "ARALE test library"
HOMEPAGE_URL "www.arale.ru"
LANGUAGES CXX
)

option(SHARED_LIB     "Building shared library"     OFF)
option(STATIC_LIB     "Building static library"     ON)

file(GLOB LIB_SOURCES *.cpp *.cxx *.c *.cc *.CPP *.CXX *.C *.CC)
if (SHARED_LIB)
message("Building shared ${PROJECT_NAME}")
add_library(${PROJECT_NAME} SHARED ${LIB_SOURCES})
# add_subdirectory(unit_test)
elseif (STATIC_LIB)
message("Building static ${PROJECT_NAME}")
add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES})
# add_subdirectory(unit_test)
endif()

target_compile_definitions(${PROJECT_NAME} PUBLIC 
ARALE_LIB_DESCRIPTION="${PROJECT_DESCRIPTION}"
ARALE_LIB_VERSION_DATE="${PROJECT_DATE}"
ARALE_LIB_VERSION="${PROJECT_VERSION}"
ARALE_LIB_NAME=${PROJECT_NAME}
ARALE_LIB_BRANCH=${ARALE_BRANCH}
ARALE_LIB_COMMIT=${ARALE_COMMIT}
ARALE_LIB_COMMIT_DATE=${ARALE_COMMIT_DATE}
ARALE_LIB_COMMITED=${ARALE_COMMITED}
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
"$<$<CONFIG:Debug>:-O0;-g3;-DDEBUG>"
-fPIC -fmessage-length=0 -pedantic   
-Wall -Wextra -Wpedantic -Wshadow -Wconversion 
# -Werror -Wfloat-equal -Wformat-nonliteral 
-Wformat-security -Wformat-y2k -Wformat=2 
-Wimport -Winvalid-pch -Wlogical-op 
-Wmissing-declarations -Wmissing-field-initializers 
-Wmissing-format-attribute -Wmissing-include-dirs 
-Wmissing-noreturn -Wpacked -Wwrite-strings 
-Wpointer-arith -Wredundant-decls -Wstack-protector 
-Wstrict-null-sentinel -Wswitch-enum -Wundef
)