#!/bin/bash
# Скрипты для сборки программы
##############################
#      Флаги запуска:        #
##############################
# -c имя_папки - строка - очищает содержимое поддиректории с заданным названием, расположенной в текущем каталоге
# -b тип_сборки - строка - если задан тип сборки Release или Debug, то осуществляется сборка программы, а также опционально сборка покрытия
# -j количество_потоков - число - осуществляется сборка программы на указанном количестве ядер CPU (по умолчанию 4)
# -f 1 или 0 - если имеет значение 1, то очистка каталогов при сборке не осуществляется
# -t 1 или 0 - если имеет значение 1, то осуществляется сборка модульных тестов
# -m 1 или 0 - если имеет значение 1, то осуществляется замер покрытия когда тестами
# -g 1 или 0 - если имеет значение 1, то осуществляется генерация документации Doxygen

##############################
#   Настройки по умолчанию:  #
##############################

g_cores=4
g_fast=0
g_build_type=0
g_unit_test=0
g_coverage=0
g_doxygen=0
g_clear_dir=0

##############################
#   Типовые задачи скрипта:  #
##############################
# /bin/sh build.sh -c build                       очистка папки build
# /bin/sh build.sh -b Debug -t 1 -r localhost     сборка модульных тестов
# /bin/sh build.sh -b Debug -m 1 -r localhost     сборка модульных тестов с замером покрытия кода

# /bin/sh build.sh -b Debug -r localhost          сборка проекта для отладки
# /bin/sh build.sh -b Release -r localhost        сборка проекта для выпуска версии
# /bin/sh build.sh -b Release -g 1 -r localhost   сборка проекта для выпуска версии + генерация автодокументации

## Функция очистки каталога с заданным именем
function f_clear {
    if [[ ! -n $(find . -name "$1") ]]; then
        mkdir -v ./$1
        return 1
    fi
    if [[ ! -n $(find . -name "$1") ]]; then
        echo "can not create $1 directory"
        return 0
    else
        cd $1
        find . -not -name '.gitignore' -delete
        cd ..
        return 1
    fi
}

## Функция сборки программы
function f_build {
    cd build/
    cmake -DCMAKE_BUILD_TYPE=$g_build_type -DUNIT_TEST=${g_unit_test:-0} -DUNIT_TEST_COVERAGE=${g_coverage:-0} ..
    cmake --build . --config $g_build_type -j${g_cores:-4}
    cd ..
}

## Функция созданияя автодокументации
function f_make_doxygen {
    doxygen ./DOXYFILE
    cd latex
    make -j${g_cores:-4}
    cp refman.pdf ../
    cd ..
}

## Функция построения покрытия
function f_make_coverage {
    cd build
    ./unit_test
    make coverage
    mv ./coverage/* ../coverage
    cd ..
}

## Функция сборки проекта с учетом параметров скрипта
function f_make {
    echo "BUILDING: $g_build_type"
    local cleanup_result=1
    if [[ $g_build_type == 'Release' || $g_build_type == 'Debug' ]]; then
        # Сборка
        echo Building programm. Mode: $g_build_type
        if [[ $g_fast != 1 ]]; then
            f_clear build
            cleanup_result=$?
        else
            cleanup_result=1
        fi
        if [[ $cleanup_result == 1 ]]; then
            f_build
        fi
        # Покрытие
        if [[ $g_coverage == 1 ]]; then
            echo Making code coverage measure
            if [[ $g_fast != 1 ]]; then
                f_clear coverage
                cleanup_result=$?
            else
                cleanup_result=1
            fi
            if [[ $cleanup_result == 1 ]]; then
                f_make_coverage
            fi
        fi
    fi
    if [[ $g_doxygen == 1 ]]; then
        #Генерация документации
        echo Making doxygen
        f_make_doxygen
    fi
}

## Основная логика:
# Разбор параметров
while getopts 'b:c:f:g:j:m:t:' opt; do
    case $opt in
    b)
        g_build_type=$OPTARG
        ;;
    c)
        g_clear_dir=$OPTARG
        echo cleaning: $g_clear_dir
        f_clear $g_clear_dir
        exit 0
        ;;
    f)
        g_fast=$OPTARG
        if [[ $g_fast == 1 ]]; then
            echo skipping cleanup
        fi
        ;;
    g)
        g_doxygen=$OPTARG
        ;;
    j)
        g_cores=$OPTARG
        echo build with: $g_cores CPU threads
        ;;
    m)
        g_coverage=$OPTARG
        ;;
    t)
        g_unit_test=$OPTARG
        if [[ $g_unit_test == 1 ]]; then
            echo making unit_test
        fi
        ;;
    esac
done

f_make
