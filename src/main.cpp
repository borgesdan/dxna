// dxna.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "main.hpp"
#include "cs/cs.hpp"

using namespace dxna;
using namespace std;
using namespace cs;

void Read(Stream* fs) {
    BinaryReader reader(fs);   
    cout << "bool  : " << std::boolalpha<< reader.ReadBoolean() << endl;
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

int main() {
	FileStream fs("D:/file.bin");
    auto a = dynamic_cast<Stream*>(&fs);
    Read(a);    

	return 0;
}

