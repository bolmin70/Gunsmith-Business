#pragma once
#include "script.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <Windows.h>
#include <shlwapi.h>
#include "Shop.h"
#include "Misc.h"

class MenuControls
{
public:

	static int current_cell;
	static int current_cell_x;

	static bool no_right;
	static bool no_left;

	static int menu_controls(int number_of_cells);

	static int menu_controls_alt(int number_of_cells);

	static int menu_controls_amount(int number_of_cells, int& weapon);

};

