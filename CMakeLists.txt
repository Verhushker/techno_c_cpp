cmake_minimum_required(VERSION 3.5)
project(task2)

set(SOURCE_EXE project/main.c)

add_executable(main.out ${SOURCE_EXE})

set(NAIVE_SOURCE_FILES project/naive_src/naive_sort.c project/utils/utils.c)
set(PARALLEL_SOURCE_FILES project/parallel_src/parallel_sort.c project/utils/utils.c)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic")

#add_library(array STATIC project/array/array.c)
add_library(${PROJECT_NAME}_naive STATIC ${NAIVE_SOURCE_FILES})
add_library(${PROJECT_NAME}_parallel STATIC ${PARALLEL_SOURCE_FILES})

#target_include_directories(array PUBLIC project/array)
target_include_directories(${PROJECT_NAME}_naive PUBLIC project/naive_include project/utils)
target_include_directories(${PROJECT_NAME}_parallel PUBLIC project/parallel_include project/utils)

#target_link_libraries(${PROJECT_NAME}_naive PUBLIC)
target_link_libraries(${PROJECT_NAME}_parallel PUBLIC ${PROJECT_NAME}_naive)

#enable_testing()

add_subdirectory(project/naive_src)
add_subdirectory(project/parallel_src)
add_subdirectory(project/utils)

target_link_libraries(main.out ${PROJECT_NAME}_naive ${PROJECT_NAME}_parallel)