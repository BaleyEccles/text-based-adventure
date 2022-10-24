#pragma once
#include "Globals.h"


namespace Globals {

	void ChangeColour(int Colour)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(hConsole,Colour);

	}



	void InputNumber(int& Input)
	{
		bool bad = false;
		do {
			std::cin >> Input;
			bad = std::cin.fail();
			if (bad) {
				std::cout << "Please input a number" << std::endl;
			}
			std::cin.clear();
			std::cin.ignore(10, '\n');
		} while (bad);
	}



	void PrintLine(int Colour)
	{
		Globals::ChangeColour(Colour);
		for (int i = 0; i < 100; i++)
		{
			std::cout << (char)254u;

		}
		std::cout << '\n';
		Globals::ChangeColour(Globals::white);
	}


}