cmake_minimum_required(VERSION 3.19)
project(PolymorphEngine)
set(CMAKE_CXX_STANDARD 20)



# MyXMLpp library
include(cmake/FindMyxmlpp.cmake)
set_target_properties(myxmlpp PROPERTIES POSITION_INDEPENDENT_CODE ON)



# Source files
file(GLOB_RECURSE SRC src/*.cpp)
file(GLOB_RECURSE ICL include/*.hpp)
file(GLOB_RECURSE ICL_HEADERS include/polymorph/*.hpp)



# Target Library
add_library(PolymorphEngine
        ${SRC}
        ${ICL}
        ${ICL_HEADERS}
)



# Target Properties
if (UNIX)
    target_link_libraries(PolymorphEngine myxmlpp dl)
    target_link_options(PolymorphEngine PUBLIC "-Wl,--no-undefined")
else()
    target_link_libraries(PolymorphEngine myxmlpp)
endif()

target_include_directories(PolymorphEngine PUBLIC 
        lib/myxmlpp/include
        include
)

set_target_properties(PolymorphEngine PROPERTIES POSITION_INDEPENDENT_CODE ON)

