cmake_minimum_required(VERSION 3.5)
project(vrmenu LANGUAGES CXX)

add_library(vrmenu SHARED src/lib.cpp)
target_include_directories(vrmenu PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(vrmenu PROPERTIES 
    OUTPUT_NAME "vrmenu"
    VERSION 1.0.0
)

add_executable(test_app test/main.cpp)
target_link_libraries(test_app PRIVATE vrmenu)
target_include_directories(test_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
