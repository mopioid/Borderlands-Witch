cmake_minimum_required(VERSION 3.24)
project(Borderlands-Witch)

include_directories(../pyunrealsdk/src ../pyunrealsdk/libs)
add_subdirectory(../pyunrealsdk ../../pyunrealsdk/out/build)

pyunrealsdk_add_module(witch witch.cpp)

add_custom_command(TARGET witch POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/build/willow2-x86/witch.pyd ${CMAKE_SOURCE_DIR}/build/witch/__init__.cp313-win32.pyd
)
add_custom_command(TARGET witch POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/build/oak-x64/witch.pyd ${CMAKE_SOURCE_DIR}/build/witch/__init__.cp313-win_amd64.pyd
)
add_custom_command(TARGET witch POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/witch.pyi ${CMAKE_SOURCE_DIR}/build/witch/__init__.pyi
)
add_custom_command(TARGET witch POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/LICENSE ${CMAKE_SOURCE_DIR}/build/witch/LICENSE
)
