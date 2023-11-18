// dxna.cpp : Defines the entry point for the application.
//

#include "main.hpp"
#include <bitset>
#include <any>
#include <iostream>
#include "graphics/viewport.hpp"
#include "cs/cs.hpp"
#include "structs.hpp"
#include "types.hpp"

using namespace dxna;
using namespace std;
using namespace cs;

int main() {
	auto ptr1 = New<intcs>(5);
	auto ptr2 = ptr1;

	*ptr2 = 6;

	cout << ptr1 << " " << *ptr1 << endl << ptr2 << " " << *ptr2 << endl;

	return 0;
}