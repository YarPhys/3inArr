cmake_minimum_required(VERSION 3.21)
set(PROJECT_NAME AAAAAAAA)

project(${PROJECT_NAME})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -static")

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES})
else ()
    add_executable(${PROJECT_NAME} ${SOURCE_FILES})
endif ()

set(SFML_DIR "C:/Users/iaren/CLionProjects/3inArr/SFML/lib/cmake/SFML")

set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2 COMPONENTS graphics audio REQUIRED)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} sfml-audio sfml-network sfml-graphics sfml-window sfml-system)
endif ()
