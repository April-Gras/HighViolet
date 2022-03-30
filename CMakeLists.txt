cmake_minimum_required(VERSION 3.7)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(CMAKE_C_STANDARD 23)
set(WARN_CFLAGS -Wall -Werror -Wextra -Wpedantic -Wshadow -Wdouble-promotion -O2 -Wundef)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")

project(hv)

find_package ( SDL2 REQUIRED )

if ( NOT SDL2_FOUND )
   message ( FATAL_ERROR "SDL2 not found!" )
endif ( NOT SDL2_FOUND )

find_package (SDL2TTF REQUIRED )

if ( NOT SDL2TTF_FOUND )
   message ( FATAL_ERROR "SDL2_ttf not found!" )
endif ( NOT SDL2TTF_FOUND )


set(CMAKE_BUILD_TYPE Debug)
include_directories(${SDL2_INCLUDE_DIRS} include)

add_executable(hv
  src/main.c
  src/debug.c
  src/utils.c
    src/tile/memory.c
    src/tile/logic_tick_update.c
    src/state/memory.c
    src/engine_timers/memory.c
    src/input/mouse.c
    src/input/keyboard.c
    src/draw/hexagon.c
    src/camera/memory.c
    src/camera/manipulate.c
    src/coord/utils.c
    src/tick/camera.c
      src/tick/input/mouse.c
)
target_link_libraries(hv ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARY} m)
