#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#define ISYESNO(Varible) (Varible != Globals::yes && Varible != Globals::YES &&Varible != Globals::no &&Varible != Globals::NO)

namespace Globals
{
	enum YesNo
	{
		YES = 'Y', yes = 'y', NO = 'N', no = 'n'
	};
	enum concol
	{
		black = 0,
		dark_blue = 1,
		dark_green = 2,
		dark_aqua, 
		dark_cyan = 3,
		dark_red = 4,
		dark_purple = 5, 
		dark_pink = 5,
		dark_magenta = 5,
		dark_yellow = 6,
		dark_white = 7,
		gray = 8,
		blue = 9,
		green = 10,
		aqua = 11, 
		cyan = 11,
		red = 12,
		purple = 13, 
		pink = 13, 
		magenta = 13,
		yellow = 14,
		white = 15
	};
	void ChangeColour(int Colour);
	void PrintLine(int Colour = Globals::red);

	void InputNumber(int& Input);
}

