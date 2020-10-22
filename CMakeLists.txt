cmake_minimum_required(VERSION 3.5)
project(task2)

set(SOURCE_EXE project/main.c)

add_executable(main.out ${SOURCE_EXE})

set(NAIVE_SOURCE_FILES project/naive_src/naive_sort.c project/naive_src/array.c)
#set(PARALLEL_SOURCE_FILES project/parallel_src/*.c)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic")


add_library(${PROJECT_NAME}_naive STATIC ${NAIVE_SOURCE_FILES})
#add_library(${PROJECT_NAME}_parallel SHARED ${PARALLEL_SOURCE_FILES})


include_directories(project/naive_include)

#enable_testing()

add_subdirectory(project/naive_src)

target_link_libraries(main.out ${PROJECT_NAME}_naive)