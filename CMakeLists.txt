cmake_minimum_required(VERSION 3.7)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 23)
set(WARN_CFLAGS -Wall -Werror -Wextra -Wpedantic)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

project(hv)

find_package(SDL2 REQUIRED)
set(CMAKE_BUILD_TYPE Debug)
include_directories(${SDL2_INCLUDE_DIRS} include)

add_executable(hv
  src/main.c
  src/utils.c
    src/tile/memory.c
    src/tile/logic_tick_update.c
    src/state/memory.c
    src/engine_timers/memory.c
    src/input/mouse.c
    src/draw/hexagon.c
    src/camera/memory.c
    src/camera/manipulate.c
    src/coord/utils.c
    src/tick/camera.c
      src/tick/input/mouse.c
      
)
target_link_libraries(hv ${SDL2_LIBRARIES} m)
