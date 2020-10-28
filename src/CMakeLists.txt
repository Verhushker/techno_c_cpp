add_executable(main.out main.c)

set(NAIVE_SOURCE_FILES naive_sort.c utils.c)
set(PARALLEL_SOURCE_FILES parallel_sort.c utils.c)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wpedantic ")

add_library(${PROJECT_NAME}_naive STATIC ${NAIVE_SOURCE_FILES})
add_library(${PROJECT_NAME}_parallel SHARED ${PARALLEL_SOURCE_FILES})

target_include_directories(${PROJECT_NAME}_naive PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME}_parallel PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(main.out ${PROJECT_NAME}_naive ${PROJECT_NAME}_parallel)