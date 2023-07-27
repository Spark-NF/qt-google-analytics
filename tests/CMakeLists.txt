cmake_minimum_required(VERSION 3.2)

project(tests)
enable_testing()

set(CMAKE_AUTOMOC ON)

if(DEFINED COVERAGE)
	if(CMAKE_COMPILER_IS_GNUCXX)
		message(STATUS "Compiling with code coverage")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage -fprofile-arcs -ftest-coverage")
	else()
		message(WARNING "Coverage only supported on GNUCXX")
	endif()
endif()

find_package(Qt6 COMPONENTS Core Network)
if(Qt6_FOUND)
	set(QT_LIBRARIES Qt6::Core Qt6::Network)
	message(STATUS "Using Qt ${Qt6_VERSION}")
else()
	find_package(Qt5 COMPONENTS Core Network REQUIRED)
	set(QT_LIBRARIES Qt5::Core Qt5::Network)
	message(STATUS "Using Qt ${Qt5_VERSION}")
endif()

add_subdirectory(vendor/catch2)

file(GLOB_RECURSE SOURCES "src/*.cpp" "../src/*.cpp")
include_directories("src/" "../src/")

add_executable(${PROJECT_NAME} ${SOURCES})
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE ${QT_LIBRARIES} Catch2::Catch2WithMain)
