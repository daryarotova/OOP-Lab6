cmake_minimum_required(VERSION 3.10)
project(Laboratory_6)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.0
    TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(SOURCES
    src/npc.cpp
    src/dragon.cpp
    src/elf.cpp
    src/druid.cpp
    src/factory.cpp
    src/arena.cpp
    src/combat_visitor.cpp
)

add_library(${PROJECT_NAME}_lib ${SOURCES})
target_include_directories(${PROJECT_NAME}_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME}_exe main.cpp)
target_link_libraries(${PROJECT_NAME}_exe PRIVATE ${PROJECT_NAME}_lib)

add_executable(${PROJECT_NAME}_test_npc tests/test_npc.cpp)
target_link_libraries(${PROJECT_NAME}_test_npc PRIVATE ${PROJECT_NAME}_lib gtest_main)
add_test(NAME Laboratory_6_test_npc COMMAND ${PROJECT_NAME}_test_npc)

add_executable(${PROJECT_NAME}_test_factory tests/test_factory.cpp)
target_link_libraries(${PROJECT_NAME}_test_factory PRIVATE ${PROJECT_NAME}_lib gtest_main)
add_test(NAME Laboratory_6_test_factory COMMAND ${PROJECT_NAME}_test_factory)

add_executable(${PROJECT_NAME}_test_arena tests/test_arena.cpp)
target_link_libraries(${PROJECT_NAME}_test_arena PRIVATE ${PROJECT_NAME}_lib gtest_main)
add_test(NAME Laboratory_6_test_arena COMMAND ${PROJECT_NAME}_test_arena)

add_executable(${PROJECT_NAME}_test_combat tests/test_combat.cpp)
target_link_libraries(${PROJECT_NAME}_test_combat PRIVATE ${PROJECT_NAME}_lib gtest_main)
add_test(NAME Laboratory_6_test_combat COMMAND ${PROJECT_NAME}_test_combat)

add_executable(${PROJECT_NAME}_test_file_loading tests/test_file_loading.cpp)
target_link_libraries(${PROJECT_NAME}_test_file_loading PRIVATE ${PROJECT_NAME}_lib gtest_main)
add_test(NAME Laboratory_6_test_file_loading COMMAND ${PROJECT_NAME}_test_file_loading)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_data_npcs.txt
    ${CMAKE_CURRENT_BINARY_DIR}/test_data_npcs.txt
    COPYONLY
)