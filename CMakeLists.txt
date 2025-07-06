cmake_minimum_required(VERSION 3.31)
project(aft)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(spdlog REQUIRED)
find_package(glfw3 REQUIRED)
find_package(imgui REQUIRED)
find_package(glad REQUIRED)

include_directories(
        ${glfw3_INCLUDE_DIR}
        ${glad_INCLUDE_DIR}
        ${imgui_INCLUDE_DIR}
        ${spdlog_INCLUDE_DIR}
)

file(GLOB sources CONFIGURE_DEPENDS
        "src/*.cpp"
        "src/*.h")

add_executable(aft ${sources})

target_link_libraries(aft PUBLIC
        imgui::imgui
        glfw
        glad::glad
        spdlog::spdlog
)
