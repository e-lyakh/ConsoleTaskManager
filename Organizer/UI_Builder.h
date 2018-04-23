#pragma once

#include "Header.h"
#include "Category.h"
#include "Task.h"

class UI
{
public:
	static void Header();
	static void StatusLine(Category Cat);
	static void Options(char input);	
	static void Table(vector <Category> CSet, int CCount, int CurCat);
	static void MenuInput();
	static void MenuInput(string WarnMessage);
	static void MenuInput2(string Input1, string &Input2);
};