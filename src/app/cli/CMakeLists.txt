cmake_minimum_required(VERSION 3.25)
if (NOT APP_NAME)
set(APP_NAME AraleCLIApp)
endif()

project(${APP_NAME} VERSION 1.0
DESCRIPTION "ARALE AraleTestLib CLI"
HOMEPAGE_URL "www.arale.ru"
LANGUAGES CXX
)
message("Building CLI application ${PROJECT_NAME}")

file(GLOB_RECURSE CLI_SOURCES src/*.cpp src/*.cxx src/*.c src/*.cc src/*.CPP src/*.CXX src/*.C src/*.CC)
add_executable(${PROJECT_NAME} ${CLI_SOURCES})

target_compile_definitions(${PROJECT_NAME} PUBLIC 
ARALE_APP_DESCRIPTION="${PROJECT_DESCRIPTION}"
ARALE_APP_VERSION_DATE="${PROJECT_DATE}"
ARALE_APP_VERSION="${PROJECT_VERSION}"
ARALE_APP_NAME=${PROJECT_NAME}
ARALE_APP_BRANCH=${ARALE_BRANCH}
ARALE_APP_COMMIT=${ARALE_COMMIT}
ARALE_APP_COMMIT_DATE=${ARALE_COMMIT_DATE}
ARALE_APP_COMMITED=${ARALE_COMMITED}
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
# -Werror -Wfloat-equal -Wformat-nonliteral 
-Wformat-security -Wformat-y2k -Wformat=2 
-Wimport -Winvalid-pch -Wlogical-op 
-Wmissing-declarations -Wmissing-field-initializers 
-Wmissing-format-attribute -Wmissing-include-dirs 
-Wmissing-noreturn -Wpacked -Wwrite-strings 
-Wpointer-arith -Wredundant-decls -Wstack-protector 
-Wstrict-null-sentinel -Wswitch-enum -Wundef
)