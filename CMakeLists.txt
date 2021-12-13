cmake_minimum_required(VERSION 3.14)

project(ft_containers)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

file(GLOB SOURCE ${PROJECT_SOURCE_DIR}/*.cpp)
message(STATUS "${SOURCE}")

find_package(GTest REQUIRED)
message(STATUS "${GTest_FOUND}")
message(STATUS "${GTEST_INCLUDE_DIRS}")
message(STATUS "${GTEST_LIBRARIES}")
message(STATUS "${GTEST_MAIN_LIBRARIES}")
message(STATUS "${GTEST_BOTH_LIBRARIES}")

set(TEST_BINARY test)
file(GLOB SOURCE_TEST ${PROJECT_SOURCE_DIR}/test/*.cpp)
message(STATUS "${SOURCE_TEST}")

add_executable(${PROJECT_NAME} ${SOURCE})
add_executable(${TEST_BINARY} ${SOURCE_TEST})

target_include_directories(${PROJECT_NAME} PRIVATE c98)
target_include_directories(${TEST_BINARY} PRIVATE c98 ${GTEST_INCLUDE_DIRS})
target_link_libraries(${TEST_BINARY} ${GTEST_BOTH_LIBRARIES})
