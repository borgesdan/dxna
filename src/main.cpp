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

class Shibica {
	Shibica(int i) {
		value = i;
	}

		int value = 0;
};

int main() {
	auto bit = BitConveter::GetBytes(ShortMaxValue);

	for (size_t i = 0; i < 2; ++i)
		cout << (int)bit[i] << endl;

	delete[] bit;

	return 0;
}