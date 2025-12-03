cmake_minimum_required(VERSION 3.22)

set(EXTRA_COMPONENT_DIRS
    hall
    lib
    mcu
    main
)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(esp32)

add_compile_options(-w)
