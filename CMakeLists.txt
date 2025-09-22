cmake_minimum_required(VERSION 4.1.1)
project(ZombieGame)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_CFG_INTDIR}/bin")


file(GLOB GAME_SOURCES "ZombieGame/src/*.cpp")
file(GLOB GAME_HEADERS "ZombieGame/include/*.h")



add_executable(ZombieGame
    ${GAME_SOURCES}
    ${GAME_HEADERS}
    sqlite/sqlite3.c
)

set_target_properties(ZombieGame PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

target_include_directories(ZombieGame PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/ZombieGame/include"
     "${CMAKE_CURRENT_SOURCE_DIR}/sqlite"
)




set(SFML_ROOT_DIR "")
if(MSVC)
    set(SFML_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sfml/msvc")
elseif(MINGW)
    set(SFML_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sfml/mingw")
elseif(UNIX AND NOT APPLE)
    set(SFML_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sfml/linux")
endif()





find_package(SFML REQUIRED COMPONENTS graphics window system audio
HINTS "${SFML_ROOT_DIR}"    
)


#visual studio setup for windows
if(MSVC)
set_target_properties(ZombieGame PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/ZombieGame"
)
endif()



target_link_libraries(ZombieGame PRIVATE
    sfml-graphics 
    sfml-audio  
)


if(WIN32)

set(SFML_DLL_DIR "${SFML_ROOT_DIR}/bin")

add_custom_command(TARGET ZombieGame POST_BUILD
  
    COMMAND ${CMAKE_COMMAND} -E copy
        "${SFML_DLL_DIR}/$<IF:$<CONFIG:Debug>,sfml-graphics-d-2,sfml-graphics-2>.dll"
        "$<TARGET_FILE_DIR:ZombieGame>"
    COMMAND ${CMAKE_COMMAND} -E copy
        "${SFML_DLL_DIR}/$<IF:$<CONFIG:Debug>,sfml-window-d-2,sfml-window-2>.dll"
        "$<TARGET_FILE_DIR:ZombieGame>"
    COMMAND ${CMAKE_COMMAND} -E copy
        "${SFML_DLL_DIR}/$<IF:$<CONFIG:Debug>,sfml-system-d-2,sfml-system-2>.dll"
        "$<TARGET_FILE_DIR:ZombieGame>"
    COMMAND ${CMAKE_COMMAND} -E copy
        "${SFML_DLL_DIR}/$<IF:$<CONFIG:Debug>,sfml-audio-d-2,sfml-audio-2>.dll"
        "$<TARGET_FILE_DIR:ZombieGame>"
   
    COMMAND ${CMAKE_COMMAND} -E copy
        "${SFML_DLL_DIR}/openal32.dll"
        "$<TARGET_FILE_DIR:ZombieGame>"
)

endif()


if(UNIX AND NOT APPLE)

    set(CMAKE_INSTALL_RPATH "$ORIGIN")
    set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

    set(SFML_SO_DIR "${SFML_ROOT_DIR}/lib")
    set(ASSETS_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ZombieGame/assets")
    set(ASSETS_DEST_DIR "$<TARGET_FILE_DIR:ZombieGame>/assets")

    add_custom_command(TARGET ZombieGame POST_BUILD

        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
            "${ASSETS_SRC_DIR}"
            "${ASSETS_DEST_DIR}"

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_SO_DIR}/libsfml-graphics.so.2.6.1" "$<TARGET_FILE_DIR:ZombieGame>"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_SO_DIR}/libsfml-window.so.2.6.1" "$<TARGET_FILE_DIR:ZombieGame>"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_SO_DIR}/libsfml-system.so.2.6.1" "$<TARGET_FILE_DIR:ZombieGame>"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_SO_DIR}/libsfml-audio.so.2.6.1" "$<TARGET_FILE_DIR:ZombieGame>"

        COMMAND ${CMAKE_COMMAND} -E create_symlink libsfml-graphics.so.2.6.1 libsfml-graphics.so
        COMMAND ${CMAKE_COMMAND} -E create_symlink libsfml-window.so.2.6.1 libsfml-window.so
        COMMAND ${CMAKE_COMMAND} -E create_symlink libsfml-system.so.2.6.1 libsfml-system.so
        COMMAND ${CMAKE_COMMAND} -E create_symlink libsfml-audio.so.2.6.1 libsfml-audio.so
    )
endif()



