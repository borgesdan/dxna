// dxna.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "main.hpp"
#include "cs/cs.hpp"
#include <Windows.h>
#include <sstream>
#include <string>
#include <cstdio>

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
    auto s = reader.ReadString();
    
    cout << "string: " << s << endl;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IONBF, 0);

	FileStream fs("D:/file2.bin");
    auto a = dynamic_cast<Stream*>(&fs);
    Read(a);    

	return 0;
}

