// dxna.cpp : Defines the entry point for the application.
//

#include "main.hpp"
#include <windows.h> 
#include <windowsx.h> 
#include <sstream>     
#include "mathhelper.hpp"

#include "input/input.hpp"

using namespace dxna;
using namespace std;

int main() {
	Vector2 vec1(5);
	Vector2 vec2(10);

	//auto vec3 = vec1 * vec2;
	auto equal = vec1 != vec2;

	return 0;
}