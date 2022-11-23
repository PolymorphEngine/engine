cmake_minimum_required(VERSION 3.19)
project(PolymorphEngine)
set(CMAKE_CXX_STANDARD 20)



# MyXMLpp library
include(cmake/FindMyxmlpp.cmake)
set_target_properties(myxmlpp PROPERTIES POSITION_INDEPENDENT_CODE ON)



# Source files
file(GLOB_RECURSE PRIVATE_SRC src/*.cpp)
file(GLOB_RECURSE PUBLIC_ICL include/*.hpp)
file(GLOB_RECURSE PRIVATE_ICL src/include/*.hpp)
get_target_property(MYXMLPP_INCLUDE_DIR myxmlpp INCLUDE_DIRECTORIES)


# Target Library
add_library(PolymorphEngine
        ${PRIVATE_SRC}
        ${PRIVATE_ICL}
        ${PUBLIC_ICL}
)



# Target Properties
if (UNIX)
    target_link_libraries(PolymorphEngine myxmlpp dl)
    target_link_options(PolymorphEngine PUBLIC "-Wl,--no-undefined")
else()
    target_link_libraries(PolymorphEngine myxmlpp)
endif()

target_include_directories(PolymorphEngine PUBLIC 
        include
        ${MYXMLPP_INCLUDE_DIR}
)
target_include_directories(PolymorphEngine PRIVATE
        src/include
)

set_target_properties(PolymorphEngine PROPERTIES POSITION_INDEPENDENT_CODE ON)

