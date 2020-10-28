cmake_minimum_required(VERSION 3.5)
project(task2)

#set(SOURCE_EXE project/src/main.c)


#target_compile_features(main.out PRIVATE c_std_11)


#set(PROJECT_SOURCE_DIR project)




add_subdirectory(src)

enable_testing()

add_subdirectory(tests)