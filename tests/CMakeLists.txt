cmake_minimum_required(VERSION 3.2)

project(tests)
enable_testing()

set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core Network REQUIRED)
set(QT_LIBRARIES Qt5::Core Qt5::Network)
message(STATUS "Using Qt ${Qt5_VERSION}")

add_subdirectory(vendor/catch2)

file(GLOB_RECURSE SOURCES "src/*.cpp" "../src/*.cpp")
include_directories("src/" "../src/")

add_executable(${PROJECT_NAME} ${SOURCES})
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE ${QT_LIBRARIES} Catch2::Catch2WithMain)
