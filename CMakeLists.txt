cmake_minimum_required(VERSION 3.16)
project(firstTry C)

include(GNUInstallDirs)
include(CheckSymbolExists)

set(CMAKE_C_STANDARD 99)
set(SOURCE_FILES src/main.c)

# cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)

# check if _GNU_SOURCE is available
if (NOT _GNU_SOURCE)
    check_symbol_exists(__GNU_LIBRARY__ "features.h" _GNU_SOURCE)
    if (NOT _GNU_SOURCE)
        unset(_GNU_SOURCE CACHE)
        check_symbol_exists(_GNU_SOURCE "features.h" _GNU_SOURCE)
    endif ()
endif ()
if (_GNU_SOURCE)
    add_definitions(-D_GNU_SOURCE)
endif ()

# Ulfius and Yder libraries
include(FindUlfius)
set(ULFIUS_MIN_VERSION "2.5")
find_package(Ulfius ${ULFIUS_MIN_VERSION} REQUIRED)
set(LIBS ${LIBS} ${ULFIUS_LIBRARIES} "-lorcania -ljansson")
include_directories(${ULFIUS_INCLUDE_DIRS})

include(FindYder)
find_package(Yder)
if (YDER_FOUND)
    set(LIBS ${LIBS} "-lyder")
    include_directories(${YDER_INCLUDE_DIRS})
endif ()


add_executable(firstTry ${SOURCE_FILES})
target_link_libraries(firstTry ${LIBS})
#add_executable(secondTry ${SOURCE_FILES})
#target_link_libraries(secondTry ${LIBS})
target_compile_definitions(firstTry PRIVATE PORT=8080)
#target_compile_definitions(secondTry PRIVATE PORT=7788)