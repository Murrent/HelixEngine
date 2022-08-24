cmake_minimum_required(VERSION 3.17)
project(HelixEngine)

set(CMAKE_CXX_STANDARD 17)
set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(src ${dir}/src)

add_executable(GameScene ${src}/scene/main.cpp
        ${src}/scene/GameManager.hpp
        ${src}/scene/GameManager.cpp
        ${src}/scene/Scene.hpp
        ${src}/scene/Scene.cpp
        ${src}/scene/GameScene.hpp
        ${src}/scene/GameScene.cpp
        ${src}/tilemap/TileMap.hpp
        ${src}/tilemap/TileMap.cpp
        ${src}/tilemap/Chunk.hpp
        ${src}/tilemap/Chunk.cpp
        ${src}/system/Input.cpp
        ${src}/system/Input.hpp
        ${src}/physics/PhysicsManager.cpp
        ${src}/physics/PhysicsManager.hpp
        ${src}/physics/PhysicsObject.cpp
        ${src}/physics/PhysicsObject.hpp
        ${src}/content/Player.cpp
        ${src}/content/Player.hpp
        ${src}/physics/RectangleObject.cpp
        ${src}/physics/RectangleObject.hpp
        ${src}/physics/CircleObject.cpp
        ${src}/physics/CircleObject.hpp
        ${src}/system/Entity.cpp
        ${src}/system/Entity.hpp
        ${src}/noise/SimplexNoise.cpp
        ${src}/noise/SimplexNoise.hpp
        ${src}/content/Inventory.cpp
        ${src}/content/Inventory.hpp
        ${src}/content/items/Item.cpp
        ${src}/content/items/Item.hpp
        ${src}/physics/ItemObject.cpp
        ${src}/physics/ItemObject.hpp
        ${src}/scene/Resources.cpp
        ${src}/scene/Resources.hpp
        ${src}/content/items/PickaxeIron.cpp
        ${src}/content/items/PickaxeIron.hpp
        ${src}/content/items/IngotGold.cpp
        ${src}/content/items/IngotGold.hpp
        ${src}/content/items/IngotIron.cpp
        ${src}/content/items/IngotIron.hpp
        ${src}/content/items/SwordIron.cpp
        ${src}/content/items/SwordIron.hpp
        ${src}/content/items/Stick.cpp
        ${src}/content/items/Stick.hpp
        ${src}/content/items/Banana.cpp
        ${src}/content/items/Banana.hpp
        ${src}/content/Hotbar.cpp
        ${src}/content/Hotbar.hpp
        ${src}/common/Camera.cpp
        ${src}/common/Camera.hpp
        ${src}/common/Animation.cpp
        ${src}/common/Animation.hpp
        ${src}/common/Random.cpp
        ${src}/common/Random.hpp
        ${src}/tilemap/MapGenerator.cpp
        ${src}/tilemap/MapGenerator.hpp
        ${src}/content/items/TileItem.cpp
        ${src}/content/items/TileItem.hpp
        ${src}/system/ClockSystem.cpp
        ${src}/system/ClockSystem.hpp
        ${src}/system/UserInterface.cpp
        ${src}/system/UserInterface.hpp)

add_executable(verletTest
        ${src}/verlet/verletTest.cpp
        ${src}/verlet/VerletObject.cpp
        ${src}/verlet/VerletObject.hpp
        ${src}/verlet/Solver.cpp
        ${src}/verlet/Solver.hpp
        ${src}/verlet/VectorMath.hpp
        ${src}/verlet/VectorMath.cpp
        ${src}/verlet/Link.cpp
        ${src}/verlet/Link.hpp)


include_directories(headers /usr/include c:/SFML/include)
#include_directories(box2d C:/Users/Martin/Downloads/box2d-master/include)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(GameScene ${SFML_LIBRARIES})
    target_link_libraries(verletTest ${SFML_LIBRARIES})
endif ()

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Copy dlls to build
if (WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
    # file(GLOB MINGW_DEP_DLLS "C:/mingw64/bin/*.dll")
    # file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif ()

#target_link_libraries(Game ${dir}/lib/Debug/box2d.lib ${dir}/lib/Debug/glfw.lib ${dir}/lib/Debug/imgui.lib ${dir}/lib/Debug/sajson.lib ${dir}/lib/Debug/glad.lib)


#target_link_libraries(Game C:/Users/Martin/Downloads/box2d-master/build/bin/Debug/box2d.lib
#        C:/Users/Martin/Downloads/box2d-master/build/bin/Debug/imgui.lib
#        C:/Users/Martin/Downloads/box2d-master/build/bin/Debug/sajson.lib
#        C:/Users/Martin/Downloads/box2d-master/build/bin/Debug/glad.lib)
#target_link_libraries(Physics C:/Users/Martin/Downloads/box2d-master/build/bin/Debug/box2d.lib
#        C:/Users/Martin/Downloads/box2d-master/build/bin/Debug/imgui.lib
#        C:/Users/Martin/Downloads/box2d-master/build/bin/Debug/sajson.lib
#        C:/Users/Martin/Downloads/box2d-master/build/bin/Debug/glad.lib)
#target_link_libraries(test C:/Users/Martin/Downloads/box2d-master/build/bin/Debug/box2d.lib
#        C:/Users/Martin/Downloads/box2d-master/build/bin/Debug/imgui.lib
#        C:/Users/Martin/Downloads/box2d-master/build/bin/Debug/sajson.lib
#        C:/Users/Martin/Downloads/box2d-master/build/bin/Debug/glad.lib)