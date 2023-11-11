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
	auto parameters = std::make_shared<std::vector<intcs>>(10);
	auto offsets = std::make_shared<std::vector<intcs>>(50);	

	auto prm = parameters.get();

	prm->at(0) = 10;

	auto prm2 = parameters.get();

	prm2->at(0) = 50;

	cout << prm->at(0) << " " << prm2->at(0) << endl;

	return 0;
}