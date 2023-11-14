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
	auto alfa = NewVectorPtr<bytecs>(10);
	auto omega = NewVectorPtr<bytecs>(10);

	auto alfasize = alfa->size();
	auto omegasize = omega->size();

	for (size_t i = 0; i < alfa->size(); ++i) {
		cout << (int)omega->at(i) << " ";
	}

	cout << endl;

	alfa->at(0) = 0;
	alfa->at(1) = 1;
	alfa->at(2) = 2;
	alfa->at(3) = 3;
	alfa->at(4) = 4;
	alfa->at(5) = 5;
	alfa->at(6) = 6;
	alfa->at(7) = 7;
	alfa->at(8) = 8;
	alfa->at(9) = 9;

	//alfa->shrink_to_fit();

	alfasize = alfa->size();
	omegasize = omega->size();

	//memmove_s(omega->data(), omega->size(), alfa->data(), alfa->size());
	Buffer::BlockCopy(alfa->data(), 0, omega->data(), 0, 5);

	for (size_t i = 0; i < alfa->size(); ++i) {
		cout << (int)omega->at(i) << " ";
	}

	cout << endl;

	return 0;
}