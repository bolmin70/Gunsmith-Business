#include "MenuControls.h"
#include "script.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <Windows.h>
#include <shlwapi.h>
#include "Shop.h"
#include "Misc.h"


int MenuControls::current_cell = 0;

int MenuControls::current_cell_x = 0;

bool MenuControls::no_right = 0;
bool MenuControls::no_left = 1;


int MenuControls::menu_controls(int number_of_cells) {

	PAD::DISABLE_CONTROL_ACTION(0, MISC::GET_HASH_KEY("INPUT_REVEAL_HUD"), 1);

	//dpad controls
	if (PAD::IS_CONTROL_JUST_PRESSED(0, MISC::GET_HASH_KEY("INPUT_FRONTEND_UP"))) {
		//AUDIO::_0x0F2A2175734926D8("NAV_RIGHT", "PAUSE_MENU_SOUNDSET");

		AUDIO::PLAY_SOUND_FRONTEND("NAV_RIGHT", "PAUSE_MENU_SOUNDSET", 1, 0);

		current_cell--;
		if (current_cell < 0) {
			current_cell = number_of_cells;
		}
	}

	if (PAD::IS_CONTROL_JUST_PRESSED(0, MISC::GET_HASH_KEY("INPUT_FRONTEND_DOWN"))) {
		//AUDIO::_0x0F2A2175734926D8("NAV_LEFT", "PAUSE_MENU_SOUNDSET");

		AUDIO::PLAY_SOUND_FRONTEND("NAV_LEFT", "PAUSE_MENU_SOUNDSET", 1, 0);

		current_cell++;
		if (current_cell > number_of_cells) {
			current_cell = 0;
		}
	}






	return current_cell;
}


int MenuControls::menu_controls_alt(int number_of_cells) {


	PAD::DISABLE_CONTROL_ACTION(0, MISC::GET_HASH_KEY("INPUT_FRONTEND_LEFT"), 1);

	PAD::DISABLE_CONTROL_ACTION(0, MISC::GET_HASH_KEY("INPUT_OPEN_JOURNAL"), 1);

	PAD::DISABLE_CONTROL_ACTION(0, MISC::GET_HASH_KEY("INPUT_OPEN_SATCHEL_MENU"), 1);

	PAD::DISABLE_CONTROL_ACTION(0, MISC::GET_HASH_KEY("INPUT_REVEAL_HUD"), 1);



	//dpad controls
	if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, MISC::GET_HASH_KEY("INPUT_FRONTEND_LEFT"))) {
		//AUDIO::_0x0F2A2175734926D8("NAV_RIGHT", "PAUSE_MENU_SOUNDSET");

		AUDIO::PLAY_SOUND_FRONTEND("NAV_RIGHT", "PAUSE_MENU_SOUNDSET", 1, 0);
		current_cell_x--;
		if (current_cell_x < 0) {
			current_cell_x = number_of_cells;
		}
	}

	if (PAD::IS_CONTROL_JUST_PRESSED(0, MISC::GET_HASH_KEY("INPUT_FRONTEND_RIGHT"))) {
		//AUDIO::_0x0F2A2175734926D8("NAV_LEFT", "PAUSE_MENU_SOUNDSET");

		AUDIO::PLAY_SOUND_FRONTEND("NAV_LEFT", "PAUSE_MENU_SOUNDSET", 1, 0);
		current_cell_x++;
		if (current_cell_x > number_of_cells) {
			current_cell_x = 0;
		}
	}






	return current_cell_x;
}


int MenuControls::menu_controls_amount(int number_of_cells, int& weapon) {


	PAD::DISABLE_CONTROL_ACTION(0, MISC::GET_HASH_KEY("INPUT_FRONTEND_LEFT"), 1);

	PAD::DISABLE_CONTROL_ACTION(0, MISC::GET_HASH_KEY("INPUT_OPEN_SATCHEL_MENU"), 1);

	no_left = 0;
	if (weapon == 0) {
		if (Shop::totalStock + 99 > Shop::maxStock) {
			no_left = 1;
		}

	}


	if (Shop::totalStock + 1 > Shop::maxStock) {
		no_right = 1;
	}
	else {
		no_right = 0;
	}


	//dpad controls
	if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, MISC::GET_HASH_KEY("INPUT_FRONTEND_LEFT"))) {

		weapon--;
		if (weapon < 0) {
			if (Shop::totalStock + 99 <= Shop::maxStock) {
				weapon = 99;
			}
			else {
				weapon = 0;
			}
		}

		
	}

	if (PAD::IS_CONTROL_JUST_PRESSED(0, MISC::GET_HASH_KEY("INPUT_FRONTEND_RIGHT"))) {

		if (Shop::totalStock + 1 <= Shop::maxStock) {
			weapon++;
			if (weapon > number_of_cells) {
				weapon = 0;
			}
		}
	}






	return current_cell_x;
}

