cmake_minimum_required(VERSION 3.8)
project(projetoDeArquivos)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        libs/array/array.c
        libs/array/array.h
        libs/random/random.c
        libs/random/random.h
        libs/quickSort/quickSort.c
        libs/quickSort/quickSort.h
        libs/utils.h
        libs/utils.c
        libs/sortUtils.c
        libs/sortUtils.h
        main.c
        main.h
        registry.c
        registry.h
        registryGenerator.c
        registryGenerator.h
        registryReader.c
        registryReader.h
        registrySort.c
        registrySort.h)

add_executable(projetoDeArquivos ${SOURCE_FILES})