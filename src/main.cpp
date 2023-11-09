// dxna.cpp : Defines the entry point for the application.
//

#include "main.hpp"
#include <bitset>
#include <any>
#include <iostream>
#include "graphics/viewport.hpp"
#include "cs/nullable.hpp"
#include "structs.hpp"

using namespace dxna;
using namespace std;
using namespace cs;

int main() {
	any i = 1;
	any ptr = std::make_shared<Vector2>();
	auto cast = any_cast<std::shared_ptr<Vector2>>(ptr);
	cout << ptr.has_value()
		<< " "
		<< ptr.type().name()
		<< " "
		<< cast->X
		<< endl;

	return 0;
}