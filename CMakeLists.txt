cmake_minimum_required(VERSION 3.6)
project(SFMLEngine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")

set(CMAKE_MODULE_PATH  ${CMAKE_SOURCE_DIR}/cmake/modules)
find_package(SFML 2.4 COMPONENTS graphics window system)

include_directories(${SFML_INCLUDE_DIR})
include_directories(headers)
include_directories(headers/commands)
include_directories(headers/scene)
include_directories(headers/states)
include_directories(headers/resources)
include_directories(headers/gui)

set(SOURCE_FILES
        main.cpp
        src/scene/entity.cpp
        src/scene/aircraft.cpp
        src/scene/scene_node.cpp
        src/scene/sprite_node.cpp
        src/scene/world.cpp
        src/commands/command.cpp
        src/commands/command_queue.cpp
        src/player.cpp
        src/states/state_stack.cpp
        src/states/state.cpp
        src/application.cpp
        src/states/game_state.cpp
        src/states/title_state.cpp
        src/states/menu_state.cpp
        src/states/pause_state.cpp
        src/utility.cpp src/states/loading_state.cpp
        src/states/loading_task.cpp
        src/gui/component.cpp
        src/gui/container.cpp
        src/gui/label.cpp
        src/gui/button.cpp src/states/settings_state.cpp headers/states/settings_state.h)
add_executable(SFMLEngine ${SOURCE_FILES})
target_link_libraries(SFMLEngine ${SFML_LIBRARIES})