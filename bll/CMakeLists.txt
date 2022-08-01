cmake_minimum_required(VERSION 3.18)
project(bll)

add_library(${PROJECT_NAME}
    STATIC
    include/public/bll/queries/query.h
    include/public/bll/queries/existancequery.h
    include/public/bll/queries/creationquery.h
    include/public/bll/property.h
    include/public/bll/regdata.h
    include/public/bll/user.h
    include/public/bll/registry.h
    include/public/bll/iuserservice.h
    include/public/bll/userservice.h
    src/stub.cc
)

target_include_directories(${PROJECT_NAME} PUBLIC include/public)
target_include_directories(${PROJECT_NAME} PRIVATE include/private)
