cmake_minimum_required(VERSION 3.11)

project(
    GraphicsUtils
    LANGUAGES C CXX
)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE
    # ${CMAKE_CURRENT_SOURCE_DIR}/include/vector3.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/vector3.cpp
)

target_sources(${PROJECT_NAME} PRIVATE
    # ${CMAKE_CURRENT_SOURCE_DIR}/include/color.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/color.cpp
)

target_sources(${PROJECT_NAME} PRIVATE
    # ${CMAKE_CURRENT_SOURCE_DIR}/include/ray.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ray.cpp
)

target_sources(${PROJECT_NAME} PRIVATE
    # ${CMAKE_CURRENT_SOURCE_DIR}/include/interval.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/interval.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
        RTWeekendCommon
)