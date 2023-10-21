# CMakeList.txt : CMake project for dxna, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (dxna WIN32 
"main.cpp"
"cs/cs.cpp"
"input/keyboard.cpp"
"input/mouse.cpp"
"input/gamepad.cpp"
"input/input.cpp"
"platforms/windows/gamewindow.cpp"
"game.cpp"
"gamewindow.cpp"
 "platforms/platforms.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET dxna PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
