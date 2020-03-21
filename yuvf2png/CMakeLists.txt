cmake_minimum_required(VERSION 2.8.3)
project(yuv2img)


add_compile_options(-std=c++11)

find_package(OpenCV 3 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} yuv2img.cc)
target_link_libraries(${PROJECT_NAME}
    ${OpenCV_LIBRARIES}
    boost_filesystem boost_system
)