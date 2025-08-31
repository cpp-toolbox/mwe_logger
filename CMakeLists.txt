cmake_minimum_required(VERSION 3.10)
project(mwe_logger)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)


file(GLOB_RECURSE SOURCES "src/*.cpp")
# Add the main executable
add_executable(${PROJECT_NAME} ${SOURCES})
        

# Automatically generated from conan install
find_package(spdlog)
find_package(fmt)
target_link_libraries(${PROJECT_NAME} spdlog::spdlog fmt::fmt)
