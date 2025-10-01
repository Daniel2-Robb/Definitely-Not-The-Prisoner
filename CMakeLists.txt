cmake_minimum_required(VERSION 3.10)
project(NotThePrisoner)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Fetch SFML (git required)
include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 69ea0cd863aed1d4092b970b676924a716ff718b
)
FetchContent_MakeAvailable(SFML)

# Executable creation 
set(SOURCE_FILES 
    src/main.cpp 
    src/Game.h 
    src/Game.cpp 
    src/Settings.h 
    src/Settings.cpp 

    src/Flavour/Camera.h 
    src/Flavour/Camera.cpp 
    "src/Flavour/Cutscene.h" 
    "src/Flavour/Cutscene.cpp" 
    "src/Flavour/Menu.h" 
    "src/Flavour/Menu.cpp" 

    src/Objects/GameObject.h 
    src/Objects/GameObject.cpp 

    src/Objects/Weapons/Weapon.h 
    src/Objects/Weapons/Weapon.cpp 
    src/Objects/Weapons/Projectile.h 
    src/Objects/Weapons/Projectile.cpp 

    src/Objects/Entities/Entity.h 
    src/Objects/Entities/Entity.cpp 
    src/Objects/Entities/Enemy.h 
    src/Objects/Entities/Enemy.cpp 
    src/Objects/Entities/Player.h 
    src/Objects/Entities/Player.cpp 
    
    "src/Environment/Level.h" 
    "src/Environment/Level.cpp" )
add_executable(NotThePrisoner ${SOURCE_FILES})

target_link_libraries(NotThePrisoner PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
target_compile_features(NotThePrisoner PRIVATE cxx_std_20)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/content/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/content/)

if(WIN32)
    add_custom_command(
            TARGET NotThePrisoner
            COMMENT "Copy OpenAL DLL to build directory so app can have sound"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:NotThePrisoner>
            VERBATIM)
endif()