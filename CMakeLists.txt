cmake_minimum_required(VERSION 3.18)
project(server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME} src/main.cc)

add_subdirectory(dtl)
add_subdirectory(bll)
add_subdirectory(dal)

target_link_libraries(dtl PUBLIC bll)
target_link_libraries(dal PUBLIC bll)

target_link_libraries(${PROJECT_NAME} PUBLIC dtl bll dal)
