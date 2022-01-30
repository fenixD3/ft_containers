cmake_minimum_required(VERSION 3.14)

project(ft_containers)

set(CMAKE_CXX_STANDARD 98)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

file(GLOB SOURCE ${PROJECT_SOURCE_DIR}/*.cpp)
message(STATUS "${SOURCE}")

add_executable(${PROJECT_NAME} ${SOURCE})

target_include_directories(${PROJECT_NAME} PRIVATE c98)

add_subdirectory(test)
