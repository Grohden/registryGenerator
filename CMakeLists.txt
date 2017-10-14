cmake_minimum_required(VERSION 3.8)
project(projetoDeArquivos)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        libs/array/array.c
        libs/array/array.h
        libs/chainedList/chainedList.c
        libs/chainedList/chainedList.h
        libs/random/random.c
        libs/random/random.h
        libs/SO/specifics.c
        libs/SO/specifics.h
        libs/quickSort/quickSort.c
        libs/quickSort/quickSort.h
        libs/textualGUI/textualGUI.c
        libs/textualGUI/textualGUI.h
        libs/utils.h
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