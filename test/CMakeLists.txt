cmake_minimum_required(VERSION 3.14)

project(test)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCE ${PROJECT_SOURCE_DIR}/*.cpp)
message(STATUS "test = ${SOURCE}")

find_package(GTest REQUIRED)
message(STATUS "${GTest_FOUND}")
message(STATUS "${GTEST_INCLUDE_DIRS}")
message(STATUS "${GTEST_LIBRARIES}")
message(STATUS "${GTEST_MAIN_LIBRARIES}")
message(STATUS "${GTEST_BOTH_LIBRARIES}")

add_executable(${PROJECT_NAME} ${SOURCE})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_HOME_DIRECTORY}/c98 ${GTEST_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES} pthread)
