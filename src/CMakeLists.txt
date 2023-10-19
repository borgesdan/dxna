# CMakeList.txt : CMake project for dxna, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (dxna WIN32 "main.cpp" "main.hpp" "input/keyboard.cpp" "input/mouse.cpp" "input/gamepad.cpp" "game.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET dxna PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
