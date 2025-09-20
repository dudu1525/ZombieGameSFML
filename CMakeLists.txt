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


target_include_directories(ZombieGame PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/ZombieGame/include"
     "${CMAKE_CURRENT_SOURCE_DIR}/sqlite"
)

#visual studio setup for windows
if(MSVC)
set_target_properties(ZombieGame PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/ZombieGame"
)
source_group("Header Files" FILES ${GAME_HEADERS})
source_group("Source Files" FILES ${GAME_SOURCES})

endif()



set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sfml/lib/cmake/SFML")
find_package(SFML 2 REQUIRED COMPONENTS graphics window system audio)



target_link_libraries(ZombieGame PRIVATE
    sfml-graphics 
    sfml-audio  
)



set(SFML_DLL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sfml/bin")
add_custom_command(TARGET ZombieGame POST_BUILD
 
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