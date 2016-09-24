####################################################################
#   Project configuration
####################################################################
cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

project (PhoenixCartographie)
set     (PhoenixCartographie_VERSION_MAJOR 0)
set     (PhoenixCartographie_VERSION_MINOR 1)

####################################################################
#   C++14 / C11 flags
####################################################################
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)

set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG=3")
set(CMAKE_C_FLAGS_DEBUG "-DDEBUG=3")
set(CMAKE_CXX_FLAGS_RELEASE "-DDEBUG=0")
set(CMAKE_C_FLAGS_RELEASE "-DDEBUG=0")

add_definitions("-Wall")
# Clean unused sections on link
add_definitions("-ffunction-sections -fdata-sections -Wl,--gc-sections")

####################################################################
#   Source
####################################################################
# Déclaration du nom (public) de la librairie
set(Library cartographieLib)


## Déclaration de la librairie aux projets qui utilisent celui-ci
# Déclaration des sources de la librairie
add_library(${Library} STATIC
    geometrie.c
    obstacles.c
    point.c
    pointList.c
    bestInFirstOut.c
    cartographie.c
    astar.c
    debug.c
)
# Includes publics
target_include_directories(${Library} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(${Library} INTERFACE
    m
)

# Librairie à linker
export(TARGETS ${Library} FILE Librairie.cmake)

include_directories(..)

add_executable(cartographieExemple
    ${CMAKE_CURRENT_SOURCE_DIR}/exemple.c
)
target_link_libraries(cartographieExemple
    ${Library}
)
