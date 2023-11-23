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
#include "graphics/graphics.hpp"
#include "types.hpp"
#include <initializer_list>
		

using namespace dxna;
using namespace dxna::graphics;
using namespace std;
using namespace cs;

class Shibica : public IVertexType {
public:
	Shibica() = default;

	Shibica(int i) {
		value = i;
	}
	
	bool operator==(Shibica const& other) const {
		return value == other.value;
	}	

	int value = 0;

	// Inherited via IVertexType
	VertexDeclarationPtr GetVertexDeclaration() const override
	{
		//return New<dxna::graphics::VertexDeclaration>(0, nullptr);
		return nullptr;
	}
};

using ShibicaPtr = std::shared_ptr<Shibica>;

int main() {	
	auto b = NewVector<Shibica>(initializer_list<Shibica>{Shibica(10), Shibica(20) });

	for (size_t i = 0; i < b->size(); ++i) {
		cout << b->at(i).value << endl;
	}
	
	auto s = vector<Shibica>({ Shibica(1), Shibica(2) });

	for (size_t i = 0; i < s.size(); ++i) {
		cout << s.at(i).value << endl;
	}

	return 0;
}