cmake_minimum_required(VERSION 2.8)

project(memory)
set(SOURCES src/memory.cpp)

add_library(${PROJECT_NAME}_lib STATIC ${SOURCES})
add_executable(${PROJECT_NAME}_test src/test.cpp)

target_include_directories(${PROJECT_NAME}_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_compile_options(${PROJECT_NAME}_lib PUBLIC
    $<$<CXX_COMPILER_ID:GNU>:-Wall;-pedantic>
)

target_compile_definitions(${PROJECT_NAME}_lib PUBLIC
    $<$<CONFIG:Debug>:DEBUG;_DEBUG>
)

set_target_properties(${PROJECT_NAME}_lib
    PROPERTIES CXX_STANDARD 14)

set_target_properties(${PROJECT_NAME}_test
    PROPERTIES CXX_STANDARD 14)

target_link_libraries(${PROJECT_NAME}_test
    ${PROJECT_NAME}_lib
)
