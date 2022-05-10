cmake_minimum_required(VERSION 3.0)
project(timed-camera)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
message("OpenCV version: ${OpenCV_VERSION}")

add_executable(timed-camera main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${OpenCV_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        ${OpenCV_LIBS}
        )
