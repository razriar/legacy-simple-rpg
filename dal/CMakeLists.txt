cmake_minimum_required(VERSION 3.16)
project(dal)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME}
    include/public/dal/dbcontext.h
    include/public/dal/convertor.h
    src/initmetadata.cc
    src/convertor.cc
    src/dbcontext.cc
)

target_include_directories(${PROJECT_NAME} PUBLIC include/public)
target_include_directories(${PROJECT_NAME} PRIVATE include/private)

add_subdirectory(lib/libpqxx)
target_link_libraries(${PROJECT_NAME} PUBLIC pqxx)
