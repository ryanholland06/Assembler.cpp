// Assembler.cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
using namespace std;

int instruction_decoder(string instruction)
{
	map<string, int> op;
	op["load"] = 00000;
	if (op.count(instruction) > 0)
		return op.find(instruction)->second;
	else
		return -1;
}
int main()
{
	vector <string> instructions;
	char space = ' ';
	int testline;
	string line;
	ifstream readfile ("add.txt");
	if (readfile.is_open())
	{
		while (getline(readfile, line, space))
		{
			testline = instruction_decoder(line);
			
		cout << testline << '\n';
		}
		readfile.close();
	}
	else
		cout << "Not able to open file";
	for (int i = 0; i < instructions.size(); i++)
		cout << instructions[i];

	
	cin >> line;
}





// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
