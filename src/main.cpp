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

struct Shd {

	Shd(int i) : value(i){}

	int value;
};

int main() {
	vector<shared_ptr<Shd>> vec1{
		make_shared<Shd>(5),
		make_shared<Shd>(6),
		make_shared<Shd>(7),
		make_shared<Shd>(8),
		make_shared<Shd>(9),
	};

	cout << vec1.at(0)->value << " " << endl;

	auto vec2 = vec1;

	vec2.at(0)->value = 1;

	cout << vec1.at(0)->value << " " << vec1.at(0)->value << endl;

	return 0;
}