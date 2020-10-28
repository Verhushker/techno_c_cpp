cmake_minimum_required(VERSION 3.5)
project(task2)


set(SOURCE_EXE project/src/main.c)

add_executable(main.out ${SOURCE_EXE})

target_compile_features(main.out PRIVATE c_std_11)

set(NAIVE_SOURCE_FILES project/src/naive_sort.c project/src/utils.c)
set(PARALLEL_SOURCE_FILES project/src/parallel_sort.c project/src/utils.c)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wpedantic ")

add_library(${PROJECT_NAME}_naive STATIC ${NAIVE_SOURCE_FILES})
add_library(${PROJECT_NAME}_parallel SHARED ${PARALLEL_SOURCE_FILES})

target_include_directories(${PROJECT_NAME}_naive PUBLIC project/include)
target_include_directories(${PROJECT_NAME}_parallel PUBLIC project/include)


#enable_testing()

add_subdirectory(project/src)

target_link_libraries(main.out ${PROJECT_NAME}_naive ${PROJECT_NAME}_parallel)