cmake_minimum_required(VERSION 3.17)
project(among-us-replay-mod)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

add_subdirectory(external/rcmp)
add_subdirectory(external/fmt)
add_subdirectory(external/magic_enum)

add_library(${PROJECT_NAME} SHARED
        ${PROJECT_SOURCE_DIR}/source/library.cpp
        ${PROJECT_SOURCE_DIR}/source/sniffer.cpp
        ${PROJECT_SOURCE_DIR}/source/utils/encoding.cpp
        ${PROJECT_SOURCE_DIR}/source/utils/utils.cpp
        )

target_compile_definitions(${PROJECT_NAME} PRIVATE WIN32_LEAN_AND_MEAN NOMINMAX)
target_link_libraries(${PROJECT_NAME} PRIVATE rcmp fmt::fmt magic_enum)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/source)

add_executable(injector ${PROJECT_SOURCE_DIR}/injector/main.cpp)
