####################################################################
#   Project configuration
####################################################################
cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

project (PhoenixCartographie)
set     (PhoenixCartographie_VERSION_MAJOR 0)
set     (PhoenixCartographie_VERSION_MINOR 1)

include(${GenericCmakeLists})

####################################################################
#   Source
####################################################################
## Déclaration de la librairie aux projets qui utilisent celui-ci
# Déclaration des sources de la librairie
add_library(${PROJECT_NAME}Lib STATIC
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
target_include_directories(${PROJECT_NAME}Lib INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(${PROJECT_NAME}Lib INTERFACE
    m
)

# Librairie à linker
export(TARGETS ${PROJECT_NAME}Lib FILE Librairie.cmake)

include_directories(..)

add_executable(${PROJECT_NAME}Exemple
    ${CMAKE_CURRENT_SOURCE_DIR}/exemple.c
)
add_executable(main_binary ALIAS ${PROJECT_NAME}Exemple)
target_link_libraries(${PROJECT_NAME}Exemple
    ${PROJECT_NAME}Lib
    ${Toolchain_LFlags}
)
