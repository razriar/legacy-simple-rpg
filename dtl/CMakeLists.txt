cmake_minimum_required(VERSION 3.18)
project(dtl)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME}
    include/public/dtl/concepts/serverconcept.h
    include/public/dtl/actions/echoaction.h
    include/public/dtl/actions/registeraction.h
    include/public/dtl/frontcontroller.h
    include/public/dtl/iocontext.h
    include/public/dtl/listener.h
    include/public/dtl/method.h
    include/public/dtl/request.h
    include/public/dtl/response.h
    include/public/dtl/server.h
    include/public/dtl/serverfactory.h
    include/public/dtl/session.h
    include/public/dtl/sessionfactory.h
    include/public/dtl/target.h
    src/stub.cc
)

target_include_directories(${PROJECT_NAME} PUBLIC include/public)
target_include_directories(${PROJECT_NAME} PRIVATE include/private)

find_package(Boost REQUIRED)
find_package(Threads REQUIRED)
add_subdirectory(lib/json)

target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} 
    PUBLIC 
    ${Boost_LIBRARIES}
    Threads::Threads 
    nlohmann_json::nlohmann_json
)
