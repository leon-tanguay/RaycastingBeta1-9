cmake_minimum_required(VERSION 3.16)
project(Raycasting LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(ImGui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG v1.89.9)
FetchContent_MakeAvailable(ImGui)
FetchContent_GetProperties(ImGui SOURCE_DIR IMGUI_DIR)

set(IMGUI_SFML_FIND_SFML OFF)
FetchContent_Declare(ImGui-SFML
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(ImGui-SFML)

add_executable(RaycastingProject 
    "src/header/hueShift.h" 
    "src/header/player.h"
    "src/header/ray.h" 
    "src/header/map.h" 
    "src/header/rcvector.h"
    "src/header/resourcemanager.h"
    "src/main.cpp" 
    "src/hueShift.cpp" 
    "src/player.cpp"
    "src/ray.cpp" 
    "src/map.cpp" "src/header/drawhandler.h")

target_link_libraries(RaycastingProject PRIVATE sfml-graphics ImGui-SFML::ImGui-SFML)
target_compile_features(RaycastingProject PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET RaycastingProject
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:RaycastingProject>
        VERBATIM)
endif()

#copy one file
#add_custom_command(
#        TARGET RaycastingProject POST_BUILD
#        COMMENT "Copy worldmap"
#        COMMAND ${CMAKE_COMMAND} -E copy
#                ${CMAKE_SOURCE_DIR}/worldMap2.png
#                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/worldMap2.png)

#copy folder
add_custom_command(
        TARGET RaycastingProject POST_BUILD
        COMMENT "Copy Arial Font"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/resource
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/)

install(TARGETS RaycastingProject)


# The code below sets up GoogleTest
# Reference: http://google.github.io/googletest/quickstart-cmake.html

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(run_tests
  "tests/testRCVector.cpp"
  "src/header/rcvector.h"
 "src/header/drawhandler.h")

target_compile_features(run_tests PRIVATE cxx_std_17)

target_link_libraries(
  run_tests
  sfml-graphics
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(run_tests)
