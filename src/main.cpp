// dxna.cpp : Defines the entry point for the application.
//

#include "main.hpp"
#include <bitset>

using namespace dxna;
using namespace std;
using namespace cs;

int main() {
	charcs temp = (charcs)bytecs(250);
	std::bitset<16> y(temp);	

	cout << y << endl;

	temp |= ((charcs)bytecs(100) << 8);

	std::bitset<16> z(temp);

	cout << z << endl;

	return 0;
}