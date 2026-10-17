cmake_minimum_required(VERSION 3.11)

project(
    Surfaces
    LANGUAGES C CXX
)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/hittable.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/hittable.cpp
)

target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/sphere.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sphere.cpp
)

target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/hittable_list.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/hittable_list.cpp
)

target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/materials.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/materials.cpp
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
)