cmake_minimum_required(VERSION 4.1.1)
project(ZombieGame)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_CFG_INTDIR}/bin")


file(GLOB GAME_SOURCES "ZombieGame/src/*.cpp")


file(GLOB GAME_HEADERS "ZombieGame/include/*.h")

target_include_directories(ZombieGame PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/ZombieGame/include"
)


add_executable(ZombieGame
    ${GAME_SOURCES}
    ${GAME_HEADERS}
)


if(MSVC)
set_target_properties(ZombieGame PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:ZombieGame>"
)
source_group("Header Files" FILES ${GAME_HEADERS})
source_group("Source Files" FILES ${GAME_SOURCES})
endif()



set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sfml/lib/cmake/SFML")
find_package(SFML 2 REQUIRED COMPONENTS graphics window system audio)


add_library(sqlite_lib STATIC "sqlite/sqlite3.c")
target_include_directories(sqlite_lib PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/sqlite"
)



target_link_libraries(ZombieGame PRIVATE
    sfml-graphics # Links graphics, window, and system automatically
    sfml-audio
    sqlite_lib    # Links the SQLite library we created in step 7
)


set(ASSET_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ZombieGame/assets")
set(DB_FILE "${CMAKE_CURRENT_SOURCE_DIR}/ZombieGame/gamedb.db")
set(SFML_DLL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sfml/bin")

add_custom_command(TARGET ZombieGame POST_BUILD
    # Copy the assets folder
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${ASSET_DIR}"
        "$<TARGET_FILE_DIR:ZombieGame>/assets"
    # Copy the database file
    COMMAND ${CMAKE_COMMAND} -E copy
        "${DB_FILE}"
        "$<TARGET_FILE_DIR:ZombieGame>/gamedb.db"
    # Copy all required SFML DLLs
    COMMAND ${CMAKE_COMMAND} -E copy
        "${SFML_DLL_DIR}/sfml-graphics-2.dll" "$<TARGET_FILE_DIR:ZombieGame>"
    COMMAND ${CMAKE_COMMAND} -E copy
        "${SFML_DLL_DIR}/sfml-window-2.dll" "$<TARGET_FILE_DIR:ZombieGame>"
    COMMAND ${CMAKE_COMMAND} -E copy
        "${SFML_DLL_DIR}/sfml-system-2.dll" "$<TARGET_FILE_DIR:ZombieGame>"
    COMMAND ${CMAKE_COMMAND} -E copy
        "${SFML_DLL_DIR}/sfml-audio-2.dll" "$<TARGET_FILE_DIR:ZombieGame>"
    COMMAND ${CMAKE_COMMAND} -E copy
        "${SFML_DLL_DIR}/openal32.dll" "$<TARGET_FILE_DIR:ZombieGame>"
    
   
)