// dxna.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "main.hpp"
#include "cs/cs.hpp"
#include <Windows.h>
#include <sstream>
#include <string>
#include <cstdio>
#include <locale>
#include <algorithm>
#include <cwchar>
#include <type_traits>

using namespace dxna;
using namespace std;
using namespace cs;

void Read(Stream* fs) {
	BinaryReader reader(fs);

	cout << "bool  : " << std::boolalpha << reader.ReadBoolean() << endl;
	cout << "byte  : " << (int)reader.ReadByte() << endl;
	cout << "sbyte : " << (int)reader.ReadSByte() << endl;
	cout << "char  : " << (char)reader.ReadChar() << endl;
	cout << "short : " << reader.ReadInt16() << endl;
	cout << "ushort: " << reader.ReadUInt16() << endl;
	cout << "int   : " << reader.ReadInt32() << endl;
	cout << "uint  : " << reader.ReadUInt32() << endl;
	cout << "long  : " << reader.ReadInt64() << endl;
	cout << "ulong : " << reader.ReadUInt64() << endl;
	cout << "single: " << reader.ReadSingle() << endl;
	cout << "double: " << reader.ReadDouble() << endl;
	cout << "string: " << reader.ReadString() << endl;	
}

void Write(Stream* fs)
{
	BinaryWriter writer(fs);
	writer.Write(true);
	writer.Write((bytecs)200);
	writer.Write((sbytecs)-100);
	writer.Write((charcs)'@');
	writer.Write((shortcs)-17);
	writer.Write((ushortcs)18);
	writer.Write((intcs)-19);
	writer.Write((uintcs)20);
	writer.Write((longcs)-21);
	writer.Write((ulongcs)22);
	writer.Write(0.6F);
	writer.Write(0.7);
	const std::string s = "XNA";
	writer.Write(s);
}

class Sorted {
public:
	Sorted() = default;
	Sorted(int i) : i(i){}

	int i{ 0 };

	constexpr bool operator<(const Sorted& other) const noexcept {
		return i <= other.i;
	}
};

int main() {
	SetConsoleOutputCP(CP_UTF8);
	setvbuf(stdout, nullptr, _IONBF, 0);		

	vector<Sorted> s{
		Sorted(35),
		Sorted(-10),
		Sorted(10),
		Sorted(-5),
		Sorted(5),
	};

	sort(s.begin(), s.end());

	for (auto& st : s)
		cout << st.i << endl;

	return 0;
}

