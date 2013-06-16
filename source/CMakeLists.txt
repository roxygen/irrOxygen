project(irrLern)
cmake_minimum_required(VERSION 2.8)

aux_source_directory(. SRC_LIST)
aux_source_directory(./src SRC_LIST)
aux_source_directory(./src/engine SRC_LIST)
aux_source_directory(./src/state SRC_LIST)
include_directories(  ./include)

find_library(IRRLICHT_LIB Irrlicht)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${IRRLICHT_LIB})
