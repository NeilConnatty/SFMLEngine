cmake_minimum_required(VERSION 3.6)
project(SFMLEngine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")

set(CMAKE_MODULE_PATH  ${CMAKE_SOURCE_DIR}/cmake/modules)
find_package(SFML 2.4 COMPONENTS graphics window system)

include_directories(${SFML_INCLUDE_DIR})
include_directories(headers)

set(SOURCE_FILES main.cpp src/Game.cpp src/texture_holder.cpp headers/resource_holder.h)
add_executable(SFMLEngine ${SOURCE_FILES})
target_link_libraries(SFMLEngine ${SFML_LIBRARIES})