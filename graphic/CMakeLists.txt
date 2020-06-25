cmake_minimum_required(VERSION 3.14)
project(sample)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "irrlicht")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g3")

message( "CMAKE_CURRENT_SOURCE_DIR coucou" )


add_compile_options( "-g3" )

#add_executable(sample src/main.cpp)
add_executable(sample src/main.cpp src/AGameObject.cpp src/Bomberman.cpp src/helper.cpp
        src/GameGraphic.cpp src/BombermanRotation.cpp src/Bomb.cpp
        ../game/src/Map.cpp ../game/src/Player.cpp
        src/MeshContainer.cpp src/Flame.cpp)

find_package(Irrlicht)

message( ${Irrlicht_FOUND} )

include_directories( ${Irrlicht_INCLUDE_DIRS} include/ include/Objects ../include/ ../game/include/ ./include/Animators/ )
target_link_libraries(sample ${Irrlicht_LIBRARIES} )