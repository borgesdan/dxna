﻿# CMakeList.txt : CMake project for dxna, include source and define
# project specific logic here.
#

# Add source to this project's executable.
# Usar dxna WIN32
add_executable (dxna  
"main.cpp"
"game.cpp"
"input/keyboard.cpp"
"gamewindow.cpp"
"structs.cpp"
"cs/cs.cpp"
"input/mouse.cpp"
"input/gamepad.cpp"
"input/input.cpp"
"platforms/platforms.cpp"
"platforms/windows/wgamewindow.cpp"
"platforms/windows/wgamewindow.cpp"
"platforms/windows/winput.cpp"
"graphics/graphics.cpp"
"graphics/shader.cpp"
"graphics/constbuffer.cpp" 
 "graphics/effect.cpp" "cs/stream.cpp" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET dxna PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
