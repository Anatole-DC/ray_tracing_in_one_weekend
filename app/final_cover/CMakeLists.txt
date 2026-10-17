cmake_minimum_required(VERSION 3.11)

project(
    FinalCover
)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
        GraphicsUtils
        Surfaces
        Renderer
        RTWeekendCommon
)