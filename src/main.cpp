// dxna.cpp : Defines the entry point for the application.
//

#include "main.hpp"
#include <windows.h> 
#include <windowsx.h> 
#include <sstream>       

#include "input/input.hpp"

using namespace dxna;
using namespace std;

int main() {
	/*Color color = Colors::AliceBlue;

	Color color2 = Color::Multiply(color, 0.5F);

	cout << (int)color2.R()
		<< " "
		<< (int)color2.G()
		<< " "
		<< (int)color2.B()
		<< " "
		<< (int)color2.A() << endl;*/

	Color color(1.F, 1.F, 1.F, 1.F);
	cout << (int)color.R()
		<< " "
		<< (int)color.G()
		<< " "
		<< (int)color.B()
		<< " "
		<< (int)color.A() << endl;

		return 0;
}