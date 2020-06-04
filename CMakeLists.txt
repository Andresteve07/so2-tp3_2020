cmake_minimum_required(VERSION 3.16)
project(so2-tp3)

include(GNUInstallDirs)
include(CheckSymbolExists)

set(CMAKE_C_STANDARD 99)
set(STATS_SOURCE_FILES
        src/stats/stats_service.c
        src/json/frozen.c
        src/stats/host_stats.c)

set(USERS_SOURCE_FILES
        src/users/user_service.c
        src/json/frozen.c
        src/users/user_manager.c)

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


add_executable(stats ${STATS_SOURCE_FILES})
target_link_libraries(stats ${LIBS})
target_compile_definitions(stats PRIVATE PORT=8080)

add_executable(users ${USERS_SOURCE_FILES})
target_link_libraries(users ${LIBS})
target_compile_definitions(users PRIVATE PORT=7788)