// Assembler.cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

#include "Assembler.h"

using namespace std;

Assembler::Assembler()
{
	jumpTable["load"] = &Assembler::load;
	jumpTable["loadi"] = &Assembler::loadi;
	jumpTable["store"] = &Assembler::store;
	jumpTable["add"] = &Assembler::add;
	jumpTable["addi"] = &Assembler::addi;
	jumpTable["addc"] = &Assembler::addc;
	jumpTable["addci"] = &Assembler::addci;
	jumpTable["sub"] = &Assembler::sub;
	jumpTable["subi"] = &Assembler::subi;
	jumpTable["subc"] = &Assembler::subc;


	
} // Assembler

int Assembler::assemble(fstream& in, fstream& out)
{
	string line;
	string opcode;
	const int success = false;
	const int error = true;
	//const int debug = false;
	int instruction;

	getline(in, line);

	while (!in.eof()) {
		istringstream str(line.c_str());
		str >> opcode;
		if (opcode[0] == '!') {
			getline(in, line);
			continue;
		}

		try {
			if (not jumpTable[opcode])
				throw NullPointerException();
			else instruction = (this->*jumpTable[opcode])(str);

		}
		catch (NullPointerException e) {
			cerr << e.what() << endl;
			return error;
		}

		if (instruction == -1)
			return error;
		out << instruction << endl;
		getline(in, line);
	}
	return success;
} // assemble

int Assembler::load(istringstream & str)
{
	int rd, addr;
	str >> rd >> addr;
	if (rd < 0 || rd > 3)
		return -1;
	if (addr < 0 || addr > 255)
		return -1;
	int inst = 0;
	inst = inst | rd << 9 | addr;
	return inst;
}

int Assembler::loadi(istringstream & str)
{
	int rd, constant;
	str >> rd >> constant;
	if (rd < 0 || rd > 3)
		return -1;
	if (constant < -128 || constant > 127)
		return -1;
	int inst = 0;
	inst = inst | rd << 9 | 1 << 8 | (0x000000ff & constant);
	return inst;
}

int Assembler::store(istringstream & str)
{
	int rd, addr;
	str >> rd >> addr;
	if (rd < 0 || rd > 3)
		return -1;
	if (addr < 0 || addr > 255)
		return -1;
	int inst = 1;
	inst = inst << 11 | rd << 9 | addr;
	return inst;
}

int Assembler::add(istringstream & str)
{
	int rd, rs;
	str >> rd >> rs;
	if (rd < 0 || rd > 3)
		return -1;
	if (rs < 0 || rs > 3)
		return -1;
	int inst = 2;
	inst = inst << 11 | rd << 9 | rs << 6;
	return inst;
}

int Assembler::addi(istringstream & str)
{
	int rd, constant;
	str >> rd >> constant;
	if (rd < 0 || rd > 3)
		return -1;
	if (constant < -128 || constant > 128)
		return -1;
	int inst = 2;
	inst = inst << 11 | rd | 1 << 8 | (0x000000ff & constant);
	return inst;
}

int Assembler::addc(istringstream & str)
{
	int rd, constant;
	str >> rd >> constant;
	if (rd < 0 || rd > 3)
		return -1;
	if (constant < -128 || constant > 128)
		return -1;
	int inst = 3;
	inst = inst << 11 | rd << 9 | (0x000000ff & constant);
	return inst;
}
int Assembler::addci(istringstream & str)
{
	int rd, constant;
	str >> rd >> constant;
	if (rd < 0 || rd > 3)
		return -1;
	if (constant < -128 || constant > 128)
		return -1;
	int inst = 3;
	inst = inst << 11 | rd << 9 | 1 << 8 | (0x000000ff & constant);
	return inst;
}

int Assembler::sub(istringstream & str)
{
	int rd, rs;
	str >> rd >> rs;
	if (rd < 0 || rd > 3)
		return -1;
	if (rs < 0 || rs > 3)
		return -1;
	int inst = 4;
	inst = inst << 11 | rd << 9 | rs << 6;
	return inst;
}

int Assembler::subi(istringstream & str)
{
	int rd, constant;
	str >> rd >> constant;
	if (rd < 0 || rd > 3)
		return -1;
	if (constant < -128 || constant > 128)
		return -1;
	int inst = 4;
	inst = inst << 11 | rd << 9  | 1 << 8 | (0x000000ff & constant);
	return inst;
}

int Assembler::subc(istringstream & str)
{
	int rd, rs;
	str >> rd >> rs;
	if (rd < 0 || rd > 3)
		return -1;
	if (rs < 0 || rs > 3)
		return -1;
	int inst = 4;
	inst = inst << 11 | rd << 9 | rs << 6;
	return inst;
}