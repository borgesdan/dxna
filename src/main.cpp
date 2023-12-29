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

template <typename T>
class EFT;

enum class EFType {
	Int,
	Float
};

class EF {
public:	
	virtual ~EF() {
	}

	template <typename T>
	void GetData(T& data, dxna::Error* err = nullptr) {

		switch (_type)
		{
		case EFType::Int:
		{
			auto r = dynamic_cast<const EFT<int>*>(this);

			if (r == nullptr) {
				apply_error(err, dxna::ErrorCode::ARGUMENT_IS_NULL);
				return;
			}

			data = r->_Data;
		}
		case EFType::Float:
			break;
		default:
			break;
		}
	}

	template <typename T>
	void SetData(T& data, dxna::Error* err = nullptr) {
		auto r = dynamic_cast<EFT<T>*>(this);

		if (r == nullptr) {
			apply_error(err, dxna::ErrorCode::ARGUMENT_IS_NULL);
			return;
		}

		r->_Data = data;
	}

	EFType _type;
};

template <typename T>
class EFT : public EF {
public:
	EFT(T value) : _Data(value){}

	virtual ~EFT() override {
	}

	T _Data;
};

class IntEFT : public EFT<int> {
public:
	IntEFT(int value) : EFT(value) {
		_type = EFType::Int;
	}
};



int main() {
	SetConsoleOutputCP(CP_UTF8);
	setvbuf(stdout, nullptr, _IONBF, 0);	

	EF* ef = new IntEFT(5);	
	int value = 65;	
	Error err;		
	float v2 = 0.0F;
	ef->SetData(value, &err);
	ef->GetData(v2, &err);
	cout << (int)err.Flag << endl;
	delete ef;

	return 0;
}

