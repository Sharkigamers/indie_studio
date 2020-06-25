cmake_minimum_required(VERSION 3.14)

project(bomberman)

set(CMAKE_CXX_STANDARD 17)

add_compile_options( "-g3" )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "irrlicht")

find_package(Irrlicht)
message( "irrlicht found: " ${Irrlicht_FOUND} )

if(UNIX)
    add_custom_target (distclean @echo cleaning for source distribution)

    add_custom_command(
        COMMENT "distribution clean"
        COMMAND make
        ARGS -C ${CMAKE_CURRENT_BINARY_DIR} clean
        COMMAND find
        ARGS ${CMAKE_CURRENT_BINARY_DIR} -name "CMakeCache.txt" | xargs rm -rf
        COMMAND find
        ARGS ${CMAKE_CURRENT_BINARY_DIR} -name "CMakeFiles" | xargs rm -rf
        COMMAND find
        ARGS ${CMAKE_CURRENT_BINARY_DIR} -name "Makefile" | xargs rm -rf
        COMMAND find
        ARGS ${CMAKE_CURRENT_BINARY_DIR} -name "*.cmake" | xargs rm -rf
        COMMAND find
        ARGS ${CMAKE_CURRENT_SOURCE_DIR} -name "*.qm" | xargs rm -rf
        COMMAND rm
        ARGS -rf ${CMAKE_CURRENT_BINARY_DIR}/install_manifest.txt
        TARGET  distclean
    )
endif(UNIX)


set(SRCS 
    src/main.cpp
    src/Core.cpp
)

set(SRCS_GRAPHIC 
    graphic/src/AGameObject.cpp graphic/src/Bomberman.cpp 
    graphic/src/helper.cpp graphic/src/GameGraphic.cpp graphic/src/BombermanRotation.cpp
    graphic/src/Bomb.cpp graphic/src/MeshContainer.cpp graphic/src/Flame.cpp
    graphic/src/Music.cpp graphic/src/Sound.cpp graphic/src/MenuPause.cpp
  )

set(SRCS_GAME
    game/src/GameBomb.cpp
    game/src/FireCluster.cpp
    game/src/GameClass.cpp
    game/src/GameClock.cpp
    game/src/Map.cpp
    game/src/MapCreation.cpp
    game/src/Object.cpp
    game/src/Player.cpp
    game/src/Saver.cpp
  )

set (SRCS_MENU
    menu/src/Keys.cpp
    menu/src/Menu.cpp
)

include_directories( ${Irrlicht_INCLUDE_DIRS} "graphic/include/Objects/" "./game/include/" "include/" "graphic/include/" "graphic/include/Animators/" "menu/include" )


add_executable(bomberman ${SRCS} ${SRCS_GRAPHIC} ${SRCS_GAME} ${SRCS_MENU} )
target_link_libraries(bomberman ${Irrlicht_LIBRARIES} sfml-system sfml-audio )