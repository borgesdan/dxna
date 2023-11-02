// dxna.cpp : Defines the entry point for the application.
//

#include "main.hpp"

using namespace dxna;
using namespace std;
using namespace cs;

int main() {
	Nullable<float> f;
	cout
		<< f.HasValue()
		<< " "
		<< f.Value()
		<< endl;

	Nullable<float> f2(1.5F);
	cout
		<< f2.HasValue()
		<< " "
		<< f2.Value()
		<< endl;

	return 0;
}