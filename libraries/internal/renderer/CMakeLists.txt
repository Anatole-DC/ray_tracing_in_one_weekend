cmake_minimum_required(VERSION 3.11)

project(
    Renderer
    LANGUAGES C CXX
)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/camera.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
        GraphicsUtils
        RTWeekendCommon
        Surfaces
)