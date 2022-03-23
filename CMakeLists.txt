cmake_minimum_required(VERSION 3.17)
project(HelixEngine)

set(CMAKE_CXX_STANDARD 17)
set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(src ${dir}/src)

add_executable(MainMenu ${src}/scene/main.cpp
        ${src}/scene/GameManager.hpp
        ${src}/scene/GameManager.cpp
        ${src}/scene/Scene.hpp
        ${src}/scene/Scene.cpp
        ${src}/scene/MainMenuScene.hpp
        ${src}/scene/MainMenuScene.cpp
        ${src}/tilemap/Chunk.hpp
        ${src}/tilemap/Chunk.cpp
        ${src}/tilemap/Tilemap.hpp
        ${src}/tilemap/Tilemap.cpp
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
        ${src}/system/Engine.cpp
        ${src}/system/Engine.hpp
        ${src}/noise/SimplexNoise.cpp
        ${src}/noise/SimplexNoise.hpp
        src/content/Inventory.cpp
        src/content/Inventory.hpp
        src/content/items/Item.cpp
        src/content/items/Item.hpp
        src/system/ItemManager.cpp
        src/system/ItemManager.hpp
        src/physics/ItemObject.cpp
        src/physics/ItemObject.hpp
        src/scene/Textures.cpp
        src/scene/Textures.hpp
        src/content/items/PickaxeIron.cpp
        src/content/items/PickaxeIron.hpp
        src/content/items/IngotGold.cpp
        src/content/items/IngotGold.hpp
        src/content/items/IngotIron.cpp
        src/content/items/IngotIron.hpp
        src/content/items/SwordIron.cpp
        src/content/items/SwordIron.hpp
        src/content/items/Stick.cpp
        src/content/items/Stick.hpp)

add_executable(Game ${src}/game.cpp
        src/system/Entity.cpp
        src/system/Entity.hpp
        src/system/Engine.cpp
        src/system/Engine.hpp
        src/noise/SimplexNoise.cpp
        src/noise/SimplexNoise.hpp
        src/system/Input.cpp
        src/system/Input.hpp
        src/content/Player.cpp
        src/content/Player.hpp src/content/items/Item.cpp src/content/items/Item.hpp src/content/items/PickaxeIron.cpp src/content/items/PickaxeIron.hpp src/content/items/IngotGold.cpp src/content/items/IngotGold.hpp src/content/items/IngotIron.cpp src/content/items/IngotIron.hpp src/content/items/Stick.cpp src/content/items/Stick.hpp src/content/items/SwordIron.cpp src/content/items/SwordIron.hpp)

add_executable(Physics ${src}/physics.cpp
        src/oldEngineCode/oldPhysicsManager/PhysicsManager.cpp
        src/oldEngineCode/oldPhysicsManager/PhysicsManager.hpp
        src/physics/PhysicsObject.cpp
        src/physics/PhysicsObject.hpp
        src/physics/VectorMath.cpp
        src/physics/VectorMath.hpp)

add_executable(test ${src}/test.cpp)


include_directories(headers /usr/include c:/SFML/include)
#include_directories(box2d C:/Users/Martin/Downloads/box2d-master/include)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Game ${SFML_LIBRARIES})
    target_link_libraries(Physics ${SFML_LIBRARIES})
    target_link_libraries(test ${SFML_LIBRARIES})
    target_link_libraries(MainMenu ${SFML_LIBRARIES})
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