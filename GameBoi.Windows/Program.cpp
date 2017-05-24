// Program.cpp : Defines the entry point for the console application.
//

#include "pch.h"
#include <iostream>
#include "MemoryMap.h"
#include "Registers.h"

using namespace std;

int main(int argc, char* argv[])
{
	argc;
	argv;

	cout << "Size of Cartridge: 0x" << hex << sizeof(GameBoi::Cartridge) << endl;
	cout << "Size of MemoryMap: 0x" << hex << sizeof(GameBoi::MemoryMap) << endl;

	GameBoi::Registers r;

	// r.A = 0x12;
	// r.F = 0x34;
	// r.B = 0x56;
	// r.C = 0x78;
	// r.D = 0x9A;
	// r.E = 0xBC;
	// r.H = 0xDE;
	// r.L = 0xF0;

	r.AF = 0x1234;
	r.BC = 0x5678;
	r.DE = 0x9ABC;
	r.HL = 0xDEF0;

	cout << hex << "Register AF is 0x" << r.AF << endl;
	cout << hex << "Register A  is 0x" << +r.A << endl;
	cout << hex << "Register F  is 0x" << +r.F << endl;
	cout << hex << "Register BC is 0x" << r.BC << endl;
	cout << hex << "Register B  is 0x" << +r.B << endl;
	cout << hex << "Register C  is 0x" << +r.C << endl;
	cout << hex << "Register DE is 0x" << r.DE << endl;
	cout << hex << "Register D  is 0x" << +r.D << endl;
	cout << hex << "Register E  is 0x" << +r.E << endl;
	cout << hex << "Register HL is 0x" << r.HL << endl;
	cout << hex << "Register H  is 0x" << +r.H << endl;
	cout << hex << "Register L  is 0x" << +r.L << endl;

	return 0;
}
