#include "Menu.h"
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
#include "initialize.h"
#include "Suppliers.h"
#include "Toasts.h"
#include <xstring>

Prompt Menu::Prompt_Order; 
Prompt Menu::Prompt_Buy; 
Prompt Menu::Prompt_Menu; 
Prompt Menu::Prompt_Back; 
Prompt Menu::Prompt_Select; 
Prompt Menu::Work_Start; 
Prompt Menu::Duty_Stop; 
Prompt Menu::Prompt_Not_Enough; 
Prompt Menu::Prompt_Open_Shop; 
Prompt Menu::Prompt_Buy_Upgrade;

Prompt Menu::Prompt_Donate_Up; 
Prompt Menu::Prompt_Donate_Down;
Prompt Menu::Prompt_Donate;








void Menu::init() {

	Misc::createPrompt(Prompt_Buy, "INPUT_SPRINT", "Buy Business $2000", 1);

	Misc::createPrompt(Prompt_Menu, "INPUT_SPRINT", "Business", 1);

	Misc::createPrompt(Prompt_Back, "INPUT_RELOAD", "Back", 2);
	Misc::createPrompt(Prompt_Select, "INPUT_FRONTEND_ACCEPT", "Select", 2);
	Misc::createPrompt(Prompt_Order, "INPUT_FRONTEND_ACCEPT", "Place order", 0);

	Misc::createPrompt(Prompt_Not_Enough, "INPUT_FRONTEND_ACCEPT", "Stock is empty", 0);

	Misc::createPrompt(Prompt_Open_Shop, "INPUT_FRONTEND_ACCEPT", "Open shop", 1);

	Misc::createPrompt(Prompt_Buy_Upgrade, "INPUT_FRONTEND_ACCEPT", "Buy upgrade", 1);

	Misc::createPrompt(Prompt_Donate_Up, "INPUT_INTERACT_OPTION1", "Increase Amount", 0);
	Misc::createPrompt(Prompt_Donate_Down, "INPUT_INTERACT_OPTION2", "Decrease Amount", 0);

	Misc::createPrompt(Prompt_Donate, "INPUT_FRONTEND_ACCEPT", "Cash-In", 0);


}

float current_rep = 0.23f;
int honor_shade = 220;

int Menu::honorTransform() {
	if (current_rep < 0.12) {
		honor_shade = 100;
	}
	if (current_rep < 0.11) {
		honor_shade = 110;
	}
	if (current_rep < 0.10) {
		honor_shade = 120;
	}
	if (current_rep < 0.09) {
		honor_shade = 130;
	}
	if (current_rep < 0.08) {
		honor_shade = 140;
	}
	if (current_rep < 0.07) {
		honor_shade = 150;
	}
	if (current_rep < 0.06) {
		honor_shade = 160;
	}
	if (current_rep < 0.05) {
		honor_shade = 170;
	}
	if (current_rep < 0.04) {
		honor_shade = 180;
	}
	if (current_rep < 0.03) {
		honor_shade = 190;
	}
	if (current_rep < 0.02) {
		honor_shade = 200;
	}
	if (current_rep < 0.01) {
		honor_shade = 210;
	}

	if (current_rep >= 0.12) {
		honor_shade = 120;
	}
	if (current_rep > 0.13) {
		honor_shade = 130;
	}
	if (current_rep > 0.14) {
		honor_shade = 140;
	}
	if (current_rep > 0.15) {
		honor_shade = 150;
	}
	if (current_rep > 0.16) {
		honor_shade = 160;
	}
	if (current_rep > 0.17) {
		honor_shade = 180;
	}
	if (current_rep > 0.18) {
		honor_shade = 190;
	}
	if (current_rep > 0.19) {
		honor_shade = 200;
	}
	if (current_rep > 0.20) {
		honor_shade = 210;
	}
	if (current_rep > 0.21) {
		honor_shade = 220;
	}
	if (current_rep > 0.22) {
		honor_shade = 230;
	}

	return honor_shade;
}

Cam Menu::localCam;

void Menu::startUp() {

	Ped player = PLAYER::PLAYER_PED_ID();
	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, false);

	//Launch animation and after 5 seconds show the menu
	if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(Prompt_Menu))
	{

		if (CAM::DOES_CAM_EXIST(localCam)) {
			CAM::DESTROY_CAM(localCam, 1);
		}
		Vector3 local;
		
		int localHeading;
		if (distanceBetween(playerPos, Shop::gunsmithVal) <= 4.0f) {
			local = Misc::toVector3(-281.593, 780.961, 119.527);
			localCam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", -281.f, 780.6, 120.0, 0, 0, 0, 60, 1, 2);
			localHeading = 181;
			CAM::POINT_CAM_AT_COORD(localCam, -281.0, 779.0, 120.0);
		}


		if (distanceBetween(playerPos, Shop::gunsmithDenis) <= 4.0f) {
			local = Misc::toVector3(2716.328, -1285.464, 49.630);
			localCam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 2716.8, -1285.0, 50.f, 0, 0, 0, 60, 1, 2);
			localHeading = 200;
			CAM::POINT_CAM_AT_COORD(localCam, 2717.8f, -1287., 50.2);
		}


		if (distanceBetween(playerPos, Shop::gunsmithBurg) <= 4.0f) {
			local = Misc::toVector3(2946.6, 1320.018, 44.820);
			localCam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 2946.699, 1320.8, 45.3f, 0, 0, 0, 60, 1, 2);
			localHeading = 250;
			CAM::POINT_CAM_AT_COORD(localCam, 2948.257, 1320.305, 45.3);
		}

		if (distanceBetween(playerPos, Shop::gunsmithRho) <= 4.0f) {
			local = Misc::toVector3(1322.894, -1321.477, 77.889);
			localCam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1323.351, -1321.674, 78.389f, 0, 0, 0, 60, 1, 2);
			localHeading = 163;
			CAM::POINT_CAM_AT_COORD(localCam, 1322.594, -1326.359, 78.389f);
		}

		if (distanceBetween(playerPos, Shop::gunsmithTum) <= 4.0f) {
			local = Misc::toVector3(-5508.210, -2964.236, -0.6f);
			localCam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", -5508.1, -2963.727, -0.1f, 0, 0, 0, 60, 1, 2);
			localHeading = 283;
			CAM::POINT_CAM_AT_COORD(localCam, -5506.853, -2963.147, -0.1f);
		}




		Object seq;
		
		
		TASK::TASK_START_SCENARIO_AT_POSITION(player, MISC::GET_HASH_KEY("WORLD_HUMAN_VAL_BANKTELLER"), local.x, local.y, local.z, localHeading, -1, true, false, 0, 0, false);

		TASK::CLEAR_PED_TASKS(player, 1, 1);
		

		
	

		menuState = MenuState::Home;
		MenuControls::current_cell = 0;


		HUD::_UIPROMPT_SET_ENABLED(Prompt_Menu, 0); 
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Menu, 0);


		HUD::_UIPROMPT_SET_ENABLED(Prompt_Back, 1); 
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Back, 1);




		
		CAM::RENDER_SCRIPT_CAMS(1, 1, 500, 1, 0, 0);

		

		CAM::SET_CAM_ACTIVE(localCam, 1);

		WEAPON::SET_CURRENT_PED_WEAPON(player, MISC::GET_HASH_KEY("weapon_unarmed"), 1, 0, 0, 0);



	}

}

float Menu::menuX = 0.02f; 
float Menu::menuY = 0.02f; 

bool toastOnce;

void Menu::shopWidget() {
	Ped player = PLAYER::PLAYER_PED_ID();
	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, 0, 0);
	Ped player2 = PLAYER::_GET_PLAYER_PED_2(1);




	////////////////////////////////////Prompts////////////////////////////////

	if (distanceBetween(playerPos, Shop::gunsmithVal) <= 4.0f || distanceBetween(playerPos, Shop::gunsmithDenis) <= 4.0f || distanceBetween(playerPos, Shop::gunsmithBurg) <= 4.0f || distanceBetween(playerPos, Shop::gunsmithRho) <= 4.0f || distanceBetween(playerPos, Shop::gunsmithTum) <= 4.0f) {
		Entity EntityTarget;


		bool bought = 0;

		if (distanceBetween(playerPos, Shop::gunsmithVal) <= 4.0f) {
			Shop::inRangeVal = 1;
			if (Shop::val_gunsmith_bought) {
				bought = 1;
			}
			else {
				HUD::_UIPROMPT_SET_TEXT(Prompt_Buy, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Buy Business $2000")); //set text
			}
		}
		else {
			Shop::inRangeVal = 0;
		}

		if (distanceBetween(playerPos, Shop::gunsmithDenis) <= 4.0f) {
			Shop::inRangeDenis = 1;
			if (Shop::denis_gunsmith_bought) {
				bought = 1;
			}
			else {
				HUD::_UIPROMPT_SET_TEXT(Prompt_Buy, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Buy Business $5000")); //set text
			}
		}
		else {
			Shop::inRangeDenis = 0;
		}

		if (distanceBetween(playerPos, Shop::gunsmithBurg) <= 4.0f) {
			Shop::inRangeBurg = 1;
			if (Shop::burg_gunsmith_bought) {
				bought = 1;
			}
			else {
				HUD::_UIPROMPT_SET_TEXT(Prompt_Buy, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Buy Business $1500")); //set text
			}
		}
		else {
			Shop::inRangeBurg = 0;
		}



		if (distanceBetween(playerPos, Shop::gunsmithRho) <= 4.0f) {
			Shop::inRangeRho = 1;
			if (Shop::rho_gunsmith_bought) {
				bought = 1;
			}
			else {
				HUD::_UIPROMPT_SET_TEXT(Prompt_Buy, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Buy Business $3000")); //set text
			}
		}
		else {
			Shop::inRangeRho = 0;
		}

		if (distanceBetween(playerPos, Shop::gunsmithTum) <= 4.0f) {
			Shop::inRangeTum = 1;
			if (Shop::tum_gunsmith_bought) {
				bought = 1;
			}
			else {
				HUD::_UIPROMPT_SET_TEXT(Prompt_Buy, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Buy Business $1000")); //set text
			}
		}
		else {
			Shop::inRangeTum = 0;
		}



		float menuX = 0.09f;


		if (bought) {


		
				std::stringstream budget;
				budget << "$";
				budget << Shop::shop_revenue;

				int green, blue;
				if (Shop::shop_revenue >= 0) {
					green = 240;
					blue = 240;
				}
				else {
					green = 0;
					blue = 0;
				}

				Misc::drawText(budget.str().c_str(), menuX + 0.8452f, menuY + 0.047f, 0, 0, 0, 255, 1, 0.6f, 0.6f);
				Misc::drawText(budget.str().c_str(), menuX + 0.845f, menuY + 0.045f, 240, green, blue, 255, 1, 0.6f, 0.6f);


				float i = Shop::current_stock;
				Shop::current_stock_visual = i / 100; //Shop::current_stock /
				if (Shop::shop_revenue >= 0) {
					Misc::drawSprite("hud_textures", "camp_tent", menuX + 0.037 + 0.833, menuY + 0.045f, 0.018f, 0.033f, 0, 255, 255, 255, 255);
				}
				else {
					Misc::drawSprite("hud_textures", "camp_tent", menuX + 0.037 + 0.833, menuY + 0.045f, 0.018f, 0.033f, 0, 255, 0, 0, 255);
				}



				float i2 = Shop::totalStock;
				i2 = i2 / 100;



				if (Shop::current_stock > 0) {

					Misc::drawSprite("mp_trader", "butcher_table_goods", menuX + 0.037f + 0.814f + 0.025f, menuY + 0.39f - 0.3f, 0.018f, 0.033f, 0, 255, 255, 255, 255);

					Misc::drawSprite("mp_trader", "butcher_table_background_bar", menuX + 0.75f + 0.025f, menuY + 0.4f - 0.3f, 0.101f, 0.019f, 0, 0, 0, 0, 250);

					Misc::drawSprite("mp_trader", "butcher_table_background_bar", menuX + 0.75f + 0.025f, menuY + 0.4f - 0.3f, 0.1f, 0.017f, 0, 255, 255, 255, 100);



					Misc::drawSprite("mp_trader", "butcher_table_foreground_bar", menuX + 0.75f + 0.025f, menuY + 0.4f - 0.3f, 0.1f * i2, 0.017f, 0, 255, 255, 255, 150);

					Misc::drawSprite("mp_trader", "butcher_table_foreground_bar", menuX + 0.75f + 0.025f, menuY + 0.4f - 0.3f, 0.1f * Shop::current_stock_visual, 0.017f, 0, 255, 255, 255, 255);

				}
				else {
					Misc::drawSprite("mp_trader", "butcher_table_goods", menuX + 0.037f + 0.814f + 0.025f, menuY + 0.39f - 0.3f, 0.018f, 0.033f, 0, 255, 0, 0, 255);

					Misc::drawSprite("mp_trader", "butcher_table_background_bar", menuX + 0.75f + 0.025f, menuY + 0.4f - 0.3f, 0.101f, 0.019f, 0, 0, 0, 0, 250);

					Misc::drawSprite("mp_trader", "butcher_table_background_bar", menuX + 0.75f + 0.025f, menuY + 0.4f - 0.3f, 0.1f, 0.017f, 0, 255, 0, 0, 100);


					Misc::drawSprite("mp_trader", "butcher_table_foreground_bar", menuX + 0.75f + 0.025f, menuY + 0.4f - 0.3f, 0.1f * i2, 0.017f, 0, 255, 255, 255, 150);

				}

				switch (Shop::storage) {
				case 0:
					Misc::drawSprite("mp_trader", "butcher_table_line_divider", menuX + 0.75f + 0.0449f, menuY + 0.4f - 0.301f, 0.001f, 0.017f, 0, 255, 255, 255, 255);
					break;
				case 1:
					Misc::drawSprite("mp_trader", "butcher_table_line_divider", menuX + 0.75f + 0.0648f, menuY + 0.4f - 0.301f, 0.001f, 0.017f, 0, 255, 255, 255, 255);
					break;
				case 2:
					Misc::drawSprite("mp_trader", "butcher_table_line_divider", menuX + 0.75f + 0.0847f, menuY + 0.4f - 0.301f, 0.001f, 0.017f, 0, 255, 255, 255, 255);
					break;

				}

			HUD::_UIPROMPT_SET_ENABLED(Prompt_Menu, 0); 
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Menu, 0);

			Entity ent;
			if (PLAYER::IS_PLAYER_TARGETTING_ANYTHING(player2)) {
				if (PLAYER::GET_PLAYER_TARGET_ENTITY(player2, &ent)) {
					if (ENTITY::IS_ENTITY_A_PED(ent)) {
						HUD::_UIPROMPT_SET_GROUP(Prompt_Menu, HUD::_UIPROMPT_GET_GROUP_ID_FOR_TARGET_ENTITY(ent), 0);
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Menu, 1);
						HUD::_UIPROMPT_SET_VISIBLE(Prompt_Menu, 1);
					}

				}
			}





			HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
		}
		else {

			Entity ent;
			if (PLAYER::IS_PLAYER_TARGETTING_ANYTHING(player2)) {
				if (PLAYER::GET_PLAYER_TARGET_ENTITY(player2, &ent)) {
					if (ENTITY::IS_ENTITY_A_PED(ent)) {
						HUD::_UIPROMPT_SET_GROUP(Prompt_Buy, HUD::_UIPROMPT_GET_GROUP_ID_FOR_TARGET_ENTITY(ent), 0);
						if (Shop::inRangeVal) {
							if (MONEY::_MONEY_GET_CASH_BALANCE() > 2000 * 100) {
								HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 1); 

							}
							else {
								HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
							}
						}
						if (Shop::inRangeDenis) {
							if (MONEY::_MONEY_GET_CASH_BALANCE() > 5000 * 100) { 
								HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 1); 

							}
							else {
								HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
							}
						}
						if (Shop::inRangeBurg) {
							if (MONEY::_MONEY_GET_CASH_BALANCE() > 1500 * 100) { 
								HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 1); 

							}
							else {
								HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
							}
						}



						if (Shop::inRangeRho) {
							if (MONEY::_MONEY_GET_CASH_BALANCE() > 3000 * 100) { 
								HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 1); 

							}
							else {
								HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
							}
						}
						if (Shop::inRangeTum) {
							if (MONEY::_MONEY_GET_CASH_BALANCE() > 1000 * 100) { 
								HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 1); 

							}
							else {
								HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
							}
						}
						




						HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 1);

					}

				}
			}
			else {
				HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0); 
				HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
			}



			HUD::_UIPROMPT_SET_ENABLED(Prompt_Menu, 0); 
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Menu, 0);

		}





	}
	else {
		HUD::_UIPROMPT_SET_ENABLED(Prompt_Menu, 0); 
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Menu, 0);

		HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0); 
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);

	}
	





	if (Shop::val_gunsmith_bought || Shop::denis_gunsmith_bought || Shop::burg_gunsmith_bought || Shop::rho_gunsmith_bought || Shop::tum_gunsmith_bought) {
		HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0); 
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
	}







	/////////////////////////////buying out the gunsmith///////////////////////////////////
	if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(Prompt_Buy)) {

		if (Shop::inRangeVal) {
			if (!Shop::val_gunsmith_bought) {

				MONEY::_MONEY_DECREMENT_CASH_BALANCE(200000);


				Shop::val_gunsmith_bought = 1;
			}
		}
		if (Shop::inRangeDenis) {
			if (!Shop::denis_gunsmith_bought) {

				MONEY::_MONEY_DECREMENT_CASH_BALANCE(500000);


				Shop::denis_gunsmith_bought = 1;
			}
		}
		if (Shop::inRangeBurg) {
			if (!Shop::burg_gunsmith_bought) {

				MONEY::_MONEY_DECREMENT_CASH_BALANCE(150000);


				Shop::burg_gunsmith_bought = 1;
			}
		}
		if (Shop::inRangeRho) {
			if (!Shop::rho_gunsmith_bought) {

				MONEY::_MONEY_DECREMENT_CASH_BALANCE(300000);


				Shop::rho_gunsmith_bought = 1;
			}
		}
		if (Shop::inRangeTum) {
			if (!Shop::tum_gunsmith_bought) {

				MONEY::_MONEY_DECREMENT_CASH_BALANCE(100000);


				Shop::tum_gunsmith_bought = 1;
			}
		}



		if (!toastOnce) {
			Toasts::showAdvancedNotification("Gunsmith Business", "You are now the owner of this gunsmith!", "toasts_mp_generic", "toast_mp_season_reward", 200);
			toastOnce = 1;
		}

	}



}






int refresh_clock;

int Menu::select_clock;

int shop_open_clock;

int stored_int;

bool keyboard = 1;
int cashin = 0;


MenuState Menu::menuState;

void menuCleanUp() {

	Ped player = PLAYER::PLAYER_PED_ID();


	AUDIO::PLAY_SOUND_FRONTEND("BACK", "HUD_SHOP_SOUNDSET", 1, 0);

	HUD::_DISPLAY_HUD_COMPONENT(474191950);

	CAM::RENDER_SCRIPT_CAMS(0, 1, 500, 1, 0, 0);

	PAD::ENABLE_CONTROL_ACTION(0, MISC::GET_HASH_KEY("INPUT_OPEN_JOURNAL"), 1);
	PAD::ENABLE_CONTROL_ACTION(0, MISC::GET_HASH_KEY("INPUT_PLAYER_MENU"), 1);
	
	CAM::SET_CAM_ACTIVE(Menu::localCam, 0);
	CAM::DESTROY_CAM(Menu::localCam, 1);

	TASK::CLEAR_PED_TASKS(player, 1, 1);

}

void Menu::menuOn() {

	//ambient stats
	if (menuState != MenuState::Off) {


		refresh_clock++;
		if (refresh_clock > 100) {

			Shop::current_stock = 0;

			for (int i = 0; i < Shop::hardLimit - 1; i++) {
				Shop::current_stock += Shop::stored[i];
			}


			stored_int = 0;
			for (int a = 0; a < Shop::hardLimit - 1; a++) {
				if (Shop::stored[a] > 0) {
					Shop::stored_visual[stored_int] = a;
					Shop::stored_visual[stored_int + 1] = -1;
					stored_int++;
				}

			}

			refresh_clock = 0;
		}


		HUD::_UIPROMPT_SET_ENABLED(Prompt_Select, 1);
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Select, 1);

	
		Misc::drawSprite("menu_textures", "translate_bg_1a", menuX - 0.03, menuY - 0.02, 0.3f, 1.f, 0, 0, 0, 0, 255);
		Misc::drawSprite("menu_textures", "translate_bg_1a", menuX + 0.22, menuY - 0.02, 0.4f, 1.f, 0, 0, 0, 0, 255);
		
		HUD::_HIDE_HUD_COMPONENT(474191950);

		HUD::_DISPLAY_HUD_COMPONENT(1920936087);


		PAD::DISABLE_CONTROL_ACTION(0, MISC::GET_HASH_KEY("INPUT_PLAYER_MENU"), 1);
		PAD::DISABLE_CONTROL_ACTION(0, MISC::GET_HASH_KEY("INPUT_OPEN_JOURNAL"), 1);

		float i = Shop::current_stock;
		Shop::current_stock_visual = i / 100;

		float i2 = Shop::totalStock;
		i2 = i2 / 100;


		if (menuState == MenuState::Home) {

		if (Shop::inRangeVal) {
			Misc::drawText("Valentine Gunsmith", menuX + 0.12f, menuY + 0.03f, 255, 255, 255, 255, 1, 0.65f, 0.65f);
		}
		if (Shop::inRangeDenis) {
			Misc::drawText("Saint Denis Gunsmith", menuX + 0.12f, menuY + 0.03f, 255, 255, 255, 255, 1, 0.65f, 0.65f);
		}
		if (Shop::inRangeBurg) {
			Misc::drawText("Annesburg Gunsmith", menuX + 0.12f, menuY + 0.03f, 255, 255, 255, 255, 1, 0.65f, 0.65f);
		}

		if (Shop::inRangeRho) {
			Misc::drawText("Rhodes Gunsmith", menuX + 0.12f, menuY + 0.03f, 255, 255, 255, 255, 1, 0.65f, 0.65f);
		}
		if (Shop::inRangeTum) {
			Misc::drawText("Tumbleweed Gunsmith", menuX + 0.12f, menuY + 0.03f, 255, 255, 255, 255, 1, 0.65f, 0.65f);
		}


		Misc::drawSprite("generic_textures", "menu_header_1a", menuX + 0.02, menuY, 0.2, 0.1f, 0, 255, 255, 255, 250);
		

		if (Shop::inRangeVal) {
			Misc::drawSprite("map_card_val_gunsmith", "image", menuX - 0.09f + 0.11f, menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		}
		if (Shop::inRangeDenis) {
			Misc::drawSprite("map_card_nbx_gunsmith", "image", menuX - 0.09f + 0.11f, menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		}
		if (Shop::inRangeBurg) {
			Misc::drawSprite("map_card_ann_gunsmith", "image", menuX - 0.09f + 0.11f, menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		}
		if (Shop::inRangeRho) {
			Misc::drawSprite("map_card_rho_gunsmith", "image", menuX - 0.09f + 0.11f, menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		}
		if (Shop::inRangeTum) {
			Misc::drawSprite("map_card_tbl_gunsmith", "image", menuX - 0.09f + 0.11f, menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		}



		Misc::drawSprite("generic_textures", "menu_bar", menuX, menuY + 0.37f, 0.25, 0.0025f, 0, 255, 255, 255, 210);



		

		
			if (Shop::current_stock > 0) {
				Misc::drawSprite("toast_mp_roles", "butcher_table_goods", menuX + 0.037, menuY + 0.38f, 0.025f, 0.05f, 0, 255, 255, 255, 255);
				Misc::drawText("Stock", menuX + 0.02f, menuY + 0.395f, 255, 255, 255, 255, 1, 0.35f, 0.35f);

				Misc::drawSprite("mp_trader", "butcher_table_background_bar", menuX + 0.07, menuY + 0.4f, 0.17f, 0.02f, 0, 255, 255, 255, 30);


				Misc::drawSprite("mp_trader", "butcher_table_foreground_bar", menuX + 0.07, menuY + 0.4f, 0.17f * i2, 0.02f, 0, 255, 255, 255, 100);


				Misc::drawSprite("mp_trader", "butcher_table_foreground_bar", menuX + 0.07, menuY + 0.4f, 0.17f * Shop::current_stock_visual, 0.02f, 0, 255, 255, 255, 230);


			}
			else {
				Misc::drawSprite("toast_mp_roles", "butcher_table_goods", menuX + 0.037, menuY + 0.38f, 0.025f, 0.05f, 0, 255, 0, 0, 255);
				Misc::drawText("Stock", menuX + 0.02f, menuY + 0.395f, 255, 0, 0, 255, 1, 0.35f, 0.35f);
				Misc::drawSprite("mp_trader", "butcher_table_background_bar", menuX + 0.07, menuY + 0.4f, 0.17f, 0.02f, 0, 255, 0, 0, 100);


				Misc::drawSprite("mp_trader", "butcher_table_foreground_bar", menuX + 0.07, menuY + 0.4f, 0.17f * i2, 0.02f, 0, 255, 255, 255, 100);


			}




			switch (Shop::storage) {
			case 0:
				Misc::drawSprite("mp_trader", "butcher_table_line_divider", menuX + 0.1035, menuY + 0.4f, 0.001f, 0.02f, 0, 255, 255, 255, 255);
				break;
			case 1:
				Misc::drawSprite("mp_trader", "butcher_table_line_divider", menuX + 0.1369, menuY + 0.4f, 0.001f, 0.02f, 0, 255, 255, 255, 255);
				break;
			case 2:
				Misc::drawSprite("mp_trader", "butcher_table_line_divider", menuX + 0.1703, menuY + 0.4f, 0.001f, 0.02f, 0, 255, 255, 255, 255);
				break;
			case 3:
				//Shop::maxStock = 100;
				break;
			}



			Misc::drawText("Staff", menuX + 0.02f, menuY + 0.44f, 255, 255, 255, 255, 1, 0.35f, 0.35f);


			Misc::drawText("Condition", menuX + 0.03f, menuY + 0.485f, 255, 255, 255, 255, 1, 0.35f, 0.35f);



			Misc::drawSprite("toast_mp_roles", "butcher_table_production", menuX + 0.037, menuY + 0.52f, 0.025f, 0.04f, 0, 255, 255, 255, 255);

			Misc::drawText("Tools", menuX + 0.02f, menuY + 0.53f, 255, 255, 255, 255, 1, 0.35f, 0.35f);


			Misc::drawSprite("generic_textures", "menu_bar", menuX, menuY + 0.575f, 0.25, 0.0025f, 0, 255, 255, 255, 210);




			//statistics
			Misc::drawTextSmall("Expenses", menuX + 0.04f, menuY + 0.67f, 255, 255, 255, 200, 1, 0.25f, 0.4f);

			std::stringstream expensesss;
			expensesss << "$";
			expensesss << Shop::daily_expanses;
			Misc::drawTextSmall(expensesss.str().c_str(), menuX + 0.22f, menuY + 0.67f, 255, 255, 255, 200, 1, 0.25f, 0.4f);


			Misc::drawTextSmall("Staff", menuX + 0.027f, menuY + 0.70f, 255, 255, 255, 200, 1, 0.25f, 0.4f);
			Misc::drawTextSmall("1/6", menuX + 0.22f, menuY + 0.70f, 255, 255, 255, 200, 1, 0.25f, 0.4f);



			Misc::drawTextSmall("Salaries", menuX + 0.036f, menuY + 0.73f, 255, 255, 255, 200, 1, 0.25f, 0.4f);

			std::stringstream paychecks;

			switch (Shop::paycheck_rate_visual) {
			case 0:
				paychecks << "None";
				Shop::paycheck_rate = initialize::paycheck_rate_none;
				break;
			case 1:
				paychecks << "Low";
				Shop::paycheck_rate = initialize::paycheck_rate_low;
				break;
			case 2:
				paychecks << "Average";
				Shop::paycheck_rate = initialize::paycheck_rate_average;
				break;
			case 3:
				paychecks << "Generous";
				Shop::paycheck_rate = initialize::paycheck_rate_generous;
				break;
			case 4:
				paychecks << "Very generous";
				Shop::paycheck_rate = initialize::paycheck_rate_verygenerous;
				break;
			};
			Misc::drawTextSmall(paychecks.str().c_str(), menuX + 0.22f, menuY + 0.73f, 255, 255, 255, 200, 1, 0.25f, 0.4f);



			Misc::drawTextSmall("Prices", menuX + 0.032f, menuY + 0.76f, 255, 255, 255, 200, 1, 0.25f, 0.4f);

			std::stringstream prices;

			switch (Shop::sell_rate_visual) {
			case 0:
				prices << "Free!";
				Shop::sell_rate = initialize::sell_rate_free;
				break;
			case 1:
				prices << "Cheap";
				Shop::sell_rate = initialize::sell_rate_cheap;
				break;
			case 2:
				prices << "Average";
				Shop::sell_rate = initialize::sell_rate_average;
				break;
			case 3:
				prices << "Expensive";
				Shop::sell_rate = initialize::sell_rate_expensive;
				break;
			case 4:
				prices << "Very expensive";
				Shop::sell_rate = initialize::sell_rate_veryexpensive;
				break;
			};
			Misc::drawTextSmall(prices.str().c_str(), menuX + 0.22f, menuY + 0.76f, 255, 255, 255, 200, 1, 0.25f, 0.4f);






			//current money and budget
			Misc::drawSprite("generic_textures", "menu_bar", menuX, menuY + 0.80f, 0.25, 0.0025f, 0, 255, 255, 255, 210);


			Misc::drawText("Shop budget:", menuX + 0.05f, menuY + 0.81f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

			std::stringstream budget;
			budget << "$";
			budget << Shop::shop_revenue;

			int green, blue;
			if (Shop::shop_revenue >= 0) {
				green = 255;
				blue = 255;
			}
			else {
				green = 0;
				blue = 0;
			}

			Misc::drawText(budget.str().c_str(), menuX + 0.23f, menuY + 0.81f, 255, green, blue, 255, 1, 0.5f, 0.5f);


			Misc::drawText("Your money:", menuX + 0.047f, menuY + 0.86f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
			std::stringstream money;
			money << "$";
			money << MONEY::_MONEY_GET_CASH_BALANCE() / 100;
			Misc::drawText(money.str().c_str(), menuX + 0.23f, menuY + 0.86f, 255, 255, 255, 255, 1, 0.5f, 0.5f);



			Misc::drawSprite("generic_textures", "menu_bar", menuX, menuY + 0.9f, 0.25, 0.0025f, 0, 255, 255, 255, 210);


			if (Shop::shop_status == 0) {
				Misc::drawText("Shop is closed", menuX + 0.12f, menuY + 0.11f, 255, 0, 0, 255, 1, 0.5f, 0.5f);
			}
			else {
				Misc::drawText("Shop is open", menuX + 0.12f, menuY + 0.11f, 0, 177, 106, 255, 1, 0.5f, 0.5f);

			}


			//converts shop reputation to current rep
			current_rep = 0.23 * (Shop::shop_rep / 100);






			Misc::drawSprite("honor_display", "honor_bar_grad_half", menuX - 0.0f, menuY + 0.6f, 0.25f, 0.008f, 0, 250, 250, 250, 250);
			Misc::drawSprite("honor_display", "honor_bar_grad_half", menuX - 0.0f, menuY + 0.6f, 0.25f, 0.008f, 180, 250, 0, 0, 250);

			Misc::drawSprite("honor_display", "honor_background", menuX - 0.0f + current_rep, menuY + 0.584f, 0.025f, 0.035f, 0, 10, 10, 10, 220);

			if (current_rep >= 0.12) {
				Misc::drawSprite("honor_display", "honor_good", menuX - 0.0f + current_rep, menuY + 0.584f, 0.024f, 0.035f, 0, honorTransform(), honorTransform(), honorTransform(), 250);
			}
			if (current_rep < 0.12) {
				Misc::drawSprite("honor_display", "honor_bad", menuX - 0.0f + current_rep, menuY + 0.584f, 0.024f, 0.035f, 0, honorTransform(), 30, 30, 250);
			}


		}



	}
	else {
		HUD::_UIPROMPT_SET_ENABLED(Prompt_Select, 0);
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Select, 0);

		HUD::_UIPROMPT_SET_ENABLED(Prompt_Order, 0); 
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Order, 0); 

		HUD::_UIPROMPT_SET_ENABLED(Prompt_Back, 0); 
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Back, 0); 

		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Not_Enough, 0);
		HUD::_UIPROMPT_SET_ENABLED(Prompt_Not_Enough, 0);

		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Open_Shop, 0);
		HUD::_UIPROMPT_SET_ENABLED(Prompt_Open_Shop, 0);


	}



}


void Menu::homePage() {
	Ped player = PLAYER::PLAYER_PED_ID();

	//base menu
	if (menuState == MenuState::Home) {

		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy_Upgrade, 0);
		HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy_Upgrade, 0);

		HUD::_UIPROMPT_SET_TEXT(Prompt_Open_Shop, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Open shop")); //set text

		if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Back))
		{
			

			menuState = MenuState::Off;

			MenuControls::current_cell = 0;


			HUD::_UIPROMPT_SET_ENABLED(Prompt_Back, 0);
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Back, 0);

			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Select, 0);
			HUD::_UIPROMPT_SET_ENABLED(Prompt_Select, 0);

			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Open_Shop, 0);
			HUD::_UIPROMPT_SET_ENABLED(Prompt_Open_Shop, 0);


			HUD::_UIPROMPT_SET_ENABLED(Prompt_Menu, 1); 
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Menu, 1);

			menuCleanUp();
		}


		Misc::drawSprite("generic_textures", "menu_bar", menuX + 0.3f, menuY + 0.1f, 0.20, 0.0025f, 0, 255, 255, 255, 210);

		Misc::drawText("Supplies", menuX + 0.4, menuY + 0.133f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3, menuY + 0.1f, 0.2, 0.1f, 0, 30, 30, 30, 250);

		Misc::drawText("Staff", menuX + 0.4, menuY + 0.133f + 0.1f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3, menuY + 0.2f, 0.2, 0.1f, 0, 30, 30, 30, 250);

		Misc::drawText("Upgrades", menuX + 0.4, menuY + 0.133f + 0.2f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3, menuY + 0.3f, 0.2, 0.1f, 0, 30, 30, 30, 250);

		Misc::drawText("Manage", menuX + 0.4, menuY + 0.133f + 0.3f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3, menuY + 0.4f, 0.2, 0.1f, 0, 30, 30, 30, 250);


		Misc::drawSprite("generic_textures", "menu_bar", menuX + 0.3f, menuY + 0.5f, 0.20, 0.0025f, 0, 255, 255, 255, 210);


		if (Shop::shop_status == 0) {
			Misc::drawText("Open Shop", menuX + 0.4, menuY + 0.133f + 0.7f, 0, 177, 106, 255, 1, 0.5f, 0.5f);
		}
		else {
			Misc::drawText("Close Shop", menuX + 0.4, menuY + 0.133f + 0.7f, 255, 0, 0, 255, 1, 0.5f, 0.5f);

		}




		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3, menuY + 0.8f, 0.2, 0.1f, 0, 30, 30, 30, 250);


		float selectY = -0.013f + (0.1f * MenuControls::menu_controls(4));


		if (Shop::current_stock > 0) {

		}
		else {

			Misc::drawSprite("generic_textures", "lock", menuX + 0.45, menuY + 0.83f, 0.02, 0.04, 0, 255, 255, 255, 250);

		}

		Misc::drawSprite("generic_textures", "lock", menuX + 0.45, menuY + 0.23f, 0.02, 0.04, 0, 255, 255, 255, 250);





		if (MenuControls::current_cell == 4) {
			selectY = -0.013f + (0.1f * 7);
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Select, 0);
			HUD::_UIPROMPT_SET_ENABLED(Prompt_Select, 0);
			if (Shop::current_stock <= 0) {

				HUD::_UIPROMPT_SET_VISIBLE(Prompt_Not_Enough, 1);
				HUD::_UIPROMPT_SET_ENABLED(Prompt_Not_Enough, 0);
			}
			else {
				HUD::_UIPROMPT_SET_VISIBLE(Prompt_Open_Shop, 1);
				HUD::_UIPROMPT_SET_ENABLED(Prompt_Open_Shop, 1);
			}

		}
		else {
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Select, 1);
			HUD::_UIPROMPT_SET_ENABLED(Prompt_Select, 1);
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Not_Enough, 0);
			HUD::_UIPROMPT_SET_ENABLED(Prompt_Not_Enough, 0);
		}

		if (MenuControls::current_cell == 1) {
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Select, 0);
			HUD::_UIPROMPT_SET_ENABLED(Prompt_Select, 0);

			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Open_Shop, 0);
			HUD::_UIPROMPT_SET_ENABLED(Prompt_Open_Shop, 0);
		}


		if (select_clock > 10) {


			if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Select))
			{
		
				AUDIO::PLAY_SOUND_FRONTEND("INFO", "HUD_SHOP_SOUNDSET", 1, 0);

				

				switch (MenuControls::menu_controls(5)) {
				case 0:
					menuState = MenuState::Supplies;
					break;
				case 1:
					break;
				case 2:
					menuState = MenuState::Upgrades;
					break;
				case 3:
					menuState = MenuState::Managment;
					break;
				case 4:
					
					break;
				case 5:
					menuState = MenuState::Sell;
					break;


				};

				MenuControls::current_cell = 0;

				select_clock = 0;
			}



		}


		shop_open_clock++;
		if (shop_open_clock > 45) {
			if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(Prompt_Open_Shop)) {

				AUDIO::PLAY_SOUND_FRONTEND("INFO", "HUD_SHOP_SOUNDSET", 1, 0);


				if (MenuControls::current_cell == 4) {
					Shop::shop_status = !Shop::shop_status;
					//select_clock = 0;
					shop_open_clock = 0;
				}



			}

		}


		Misc::drawSprite("menu_textures", "crafting_highlight_l", menuX + 0.294, menuY + 0.123f + selectY, 0.0135, 0.082f, 0, 255, 0, 0, 250);
		Misc::drawSprite("menu_textures", "crafting_highlight_r", menuX + 0.492, menuY + 0.123f + selectY, 0.0135, 0.082f, 0, 255, 0, 0, 250);
		Misc::drawSprite("menu_textures", "crafting_highlight_b", menuX + 0.3, menuY + 0.1f + selectY, 0.2, 0.03f, 0, 255, 0, 0, 250);
		Misc::drawSprite("menu_textures", "crafting_highlight_t", menuX + 0.3, menuY + 0.2f + selectY, 0.2, 0.03f, 0, 255, 0, 0, 250);









	}

}



void Menu::supplies() {


	//order supplies/your supplies
	if (menuState == MenuState::Supplies) {
		if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Back))
		{
		
			AUDIO::PLAY_SOUND_FRONTEND("BACK", "HUD_SHOP_SOUNDSET", 1, 0);
			menuState = MenuState::Home;

		}


		float selectY = -0.013f + (0.1f * MenuControls::menu_controls(1) + 0.2f);

		if (select_clock > 10) {
			if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Select))
			{
				
				AUDIO::PLAY_SOUND_FRONTEND("INFO", "HUD_SHOP_SOUNDSET", 1, 0);

				switch (MenuControls::menu_controls(1)) {
				case 0:
					menuState = MenuState::Suppliers;
					break;
				case 1:
					menuState = MenuState::YourSupplies;
					break;
				};
				select_clock = 0;
			}
		}


		//combat_gun_rack

		char* weapon_name;
		char* desc;

		Misc::drawSprite("generic_textures", "menu_header_1a", menuX + 0.02, menuY, 0.2, 0.1f, 0, 255, 255, 255, 250);


		if (MenuControls::current_cell == 0) {
			weapon_name = "Order Supplies";
			desc = "Order more weapons to later sell\nwith profit.";
			Misc::drawSprite("sp_missions_1", "mission_rmud32", baseSuppliers::menuX - 0.09f + 0.11f, baseSuppliers::menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		}

		if (MenuControls::current_cell == 1) {
			weapon_name = "Your Supplies";
			desc = "Browse through your stock.";
			Misc::drawSprite("help_combat", "combat_gun_rack", baseSuppliers::menuX - 0.09f + 0.11f, baseSuppliers::menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		}

		Misc::drawText(weapon_name, baseSuppliers::menuX + 0.12f, baseSuppliers::menuY + 0.03f, 255, 255, 255, 255, 1, 0.6f, 0.6f);


		Misc::drawTextSmall(desc, baseSuppliers::menuX + 0.015f, baseSuppliers::menuY + 0.37f, 255, 255, 255, 255, 0, 0.25f, 0.4f);


		if (Shop::current_stock == 0 && MenuControls::current_cell == 1) {
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Select, 0);
			HUD::_UIPROMPT_SET_ENABLED(Prompt_Select, 0);
		}



		Misc::drawSprite("generic_textures", "menu_bar", menuX + 0.3f, menuY + 0.3f, 0.20, 0.0025f, 0, 255, 255, 255, 210);


		Misc::drawText("Order Supplies", menuX + 0.4f, menuY + 0.133f + 0.2f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3f, menuY + 0.3f, 0.2, 0.1f, 0, 30, 30, 30, 250);

		Misc::drawText("Your Supplies", menuX + 0.4f, menuY + 0.133f + 0.3f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3f, menuY + 0.4f, 0.2, 0.1f, 0, 30, 30, 30, 250);

		if (Shop::current_stock == 0) {


			Misc::drawText("Out of stock", menuX + 0.46f, menuY + 0.17f + 0.3f, 255, 0, 0, 255, 1, 0.35f, 0.35f);
	}



		Misc::drawSprite("generic_textures", "menu_bar", menuX + 0.3f, menuY + 0.5f, 0.20, 0.0025f, 0, 255, 255, 255, 210);




		Misc::drawSprite("menu_textures", "crafting_highlight_l", menuX + 0.294, menuY + 0.123f + selectY, 0.0135, 0.082f, 0, 255, 0, 0, 250);
		Misc::drawSprite("menu_textures", "crafting_highlight_r", menuX + 0.492, menuY + 0.123f + selectY, 0.0135, 0.082f, 0, 255, 0, 0, 250);
		Misc::drawSprite("menu_textures", "crafting_highlight_b", menuX + 0.3, menuY + 0.1f + selectY, 0.2, 0.03f, 0, 255, 0, 0, 250);
		Misc::drawSprite("menu_textures", "crafting_highlight_t", menuX + 0.3, menuY + 0.2f + selectY, 0.2, 0.03f, 0, 255, 0, 0, 250);


	}



}


void Menu::suppliers() {
	if (menuState == MenuState::Suppliers) {

		bool other_on = 0;
		if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Back))
		{
			
			AUDIO::PLAY_SOUND_FRONTEND("BACK", "HUD_SHOP_SOUNDSET", 1, 0);
			menuState = MenuState::Supplies;
			MenuControls::current_cell = 0;
		}


	
		Misc::drawSprite("generic_textures", "menu_bar", menuX + 0.3f, menuY + 0.1f, 0.20, 0.0025f, 0, 255, 255, 255, 210);


		Misc::drawText("Lancaster", menuX + 0.4, menuY + 0.133f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3, menuY + 0.1f, 0.2, 0.1f, 0, 30, 30, 30, 250);

		Misc::drawText("Buck", menuX + 0.4, menuY + 0.133f + 0.1f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3, menuY + 0.2f, 0.2, 0.1f, 0, 30, 30, 30, 250);

		Misc::drawText("Muhlberg", menuX + 0.4, menuY + 0.133f + 0.2f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3, menuY + 0.3f, 0.2, 0.1f, 0, 30, 30, 30, 250);

		Misc::drawText("Peeters & Janssens", menuX + 0.4, menuY + 0.133f + 0.3f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3, menuY + 0.4f, 0.2, 0.1f, 0, 30, 30, 30, 250);

		Misc::drawText("Hutton & Baird", menuX + 0.4, menuY + 0.133f + 0.4f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3, menuY + 0.5f, 0.2, 0.1f, 0, 30, 30, 30, 250);

		Misc::drawText("D.D. packenbush", menuX + 0.4, menuY + 0.133f + 0.5f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3, menuY + 0.6f, 0.2, 0.1f, 0, 30, 30, 30, 250);

		Misc::drawText("Litchfield", menuX + 0.4, menuY + 0.133f + 0.6f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3, menuY + 0.7f, 0.2, 0.1f, 0, 30, 30, 30, 250);

	
		Misc::drawSprite("generic_textures", "menu_bar", menuX + 0.3f, menuY + 0.8f, 0.20, 0.0025f, 0, 255, 255, 255, 210);

		//	float selectY = -0.013f; //nexus
		float selectY = -0.013f + (0.1f * MenuControls::menu_controls(6)); //patreon

		Misc::drawSprite("menu_textures", "crafting_highlight_l", menuX + 0.294, menuY + 0.123f + selectY, 0.0135, 0.082f, 0, 255, 0, 0, 250);
		Misc::drawSprite("menu_textures", "crafting_highlight_r", menuX + 0.492, menuY + 0.123f + selectY, 0.0135, 0.082f, 0, 255, 0, 0, 250);
		Misc::drawSprite("menu_textures", "crafting_highlight_b", menuX + 0.3, menuY + 0.1f + selectY, 0.2, 0.03f, 0, 255, 0, 0, 250);
		Misc::drawSprite("menu_textures", "crafting_highlight_t", menuX + 0.3, menuY + 0.2f + selectY, 0.2, 0.03f, 0, 255, 0, 0, 250);





		current_rep = 0.23f;

		char* supplier_name;

		switch (MenuControls::current_cell) {
		case 0:			
			current_rep = current_rep * Shop::suppliersRep[0] / 100;
			supplier_name = "Lancaster";
			break;
		case 1:		
			current_rep = current_rep * Shop::suppliersRep[1] / 100;
			supplier_name = "Buck";
			break;
		case 2:
			current_rep = current_rep * Shop::suppliersRep[2] / 100;
			supplier_name = "Muhlberg";
			break;
		case 3:
			current_rep = current_rep * Shop::suppliersRep[3] / 100;
			supplier_name = "Peeters & Janssens";
			break;
		case 4:
			current_rep = current_rep * Shop::suppliersRep[4] / 100;
			supplier_name = "Hutton & Baird";
			break;
		case 5:
			current_rep = current_rep * Shop::suppliersRep[5] / 100;
			supplier_name = "D.D. packenbush";
			break;
		case 6:
			current_rep = current_rep * Shop::suppliersRep[6] / 100;
			supplier_name = "Litchfield";
			break;
		case 7:
			current_rep = 50;
			other_on = 1;
			supplier_name = "Other";
			break;

		};

		if (select_clock > 20) {
			if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Select))
			{

				AUDIO::PLAY_SOUND_FRONTEND("INFO", "HUD_SHOP_SOUNDSET", 1, 0);

				//current_cell = 0;
				//current_cell_x = 0;

				switch (MenuControls::current_cell) {
				case 0:
					menuState = MenuState::Lancaster;
					break;
				case 1:
					menuState = MenuState::Buck;
					break;
				case 2:
					menuState = MenuState::Muhlberg;
					break;
				case 3:
					menuState = MenuState::Peeters;
					break;
				case 4:
					menuState = MenuState::Hutton;
					break;
				case 5:
					menuState = MenuState::dd;
					break;
				case 6:
					menuState = MenuState::litchfield;
					break;
				case 7:
					//menu_on = 10100;
					break;

				};
				MenuControls::current_cell = 0;
				MenuControls::current_cell_x = 0;

				select_clock = 0;
			}

		}





		Misc::drawText(supplier_name, menuX + 0.12f, menuY + 0.03f, 255, 255, 255, 255, 1, 0.65f, 0.65f);

		Misc::drawSprite("generic_textures", "menu_header_1a", menuX + 0.02, menuY, 0.2, 0.1f, 0, 255, 255, 255, 250);

		Misc::drawSprite("map_card_camp_supply_ammo", "image", menuX - 0.09f + 0.11f, menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);




		if (!other_on) {

			Misc::drawSprite("honor_display", "honor_bar_grad_half", menuX + 0.f, menuY + 0.5f, 0.25f, 0.008f, 0, 250, 250, 250, 250);
			Misc::drawSprite("honor_display", "honor_bar_grad_half", menuX + 0.f, menuY + 0.5f, 0.25f, 0.008f, 180, 250, 0, 0, 250);

			Misc::drawSprite("honor_display", "honor_background", menuX + 0.f + current_rep, menuY + 0.484f, 0.025f, 0.035f, 0, 10, 10, 10, 220);

			if (current_rep >= 0.12) {
				Misc::drawSprite("honor_display", "honor_good", menuX + 0.f + current_rep, menuY + 0.484f, 0.024f, 0.035f, 0, honorTransform(), honorTransform(), honorTransform(), 250);
			}
			if (current_rep < 0.12) {
				Misc::drawSprite("honor_display", "honor_bad", menuX + 0.f + current_rep, menuY + 0.484f, 0.024f, 0.035f, 0, honorTransform(), 30, 30, 250);
			}

		}

	}
}

void Menu::suppliersSpecfic() {
	baseSuppliers::lancasterPage(2, 3, 0);

	baseSuppliers::buckPage(2, 1, 1);

	baseSuppliers::muhlbergPage(2, 2, 2);

	baseSuppliers::peetersPage(2, 1, 3);

	baseSuppliers::huttonPage(2, 2, 4);

	baseSuppliers::ddPage(2, 1, 5);

	baseSuppliers::litchfieldPage(2, 1, 6);
}

void Menu::yourSupplies() {

	if (menuState == MenuState::YourSupplies) {

		if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Back))
		{
			
			AUDIO::PLAY_SOUND_FRONTEND("BACK", "HUD_SHOP_SOUNDSET", 1, 0);
			menuState = MenuState::Supplies;
			MenuControls::current_cell = 1;
		}


		HUD::_UIPROMPT_SET_ENABLED(Prompt_Select, 0); 
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Select, 0);

		//if the item is not selected you can move the arrows
		float selectX;

		float selectY;


		refresh_clock++;
		if (refresh_clock > 60) {

			stored_int = 0;
			for (int a = 0; a < Shop::hardLimit - 3; a++) {
				if (Shop::stored[a] > 0) {
					Shop::stored_visual[stored_int] = a;
					Shop::stored_visual[stored_int + 1] = -1;
					stored_int++;
				}
				else {
					Shop::stored_visual[stored_int] = -1;
				}
			}

			refresh_clock = 0;
		}


		float addY = 0;

		float menuX = -0.26;

		if (Shop::current_stock != 0) {
			for (int c = 0; c < Shop::hardLimit - 3; c++) {
				//if (b >= )

				int b = c;
				if (c >= 5) {
					addY = 0.15;
					b = c - 5;
				}

				if (c >= 10) {
					addY = 0.3;
					b = c - 10;
				}

				if (c >= 15) {
					addY = 0.45;
					b = c - 15;
				}

				if (c >= 20) {
					addY = 0.6;
					b = c - 20;
				}

				if (c >= 25) {
					addY = 0.75;
					b = c - 25;
				}

				if (c >= 30) {
					addY = 0.9;
					b = c - 30;
				}

				if (Shop::stored_visual[c] == 0) {
					Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 + (b * 0.1f), menuY + 0.1f + addY, 0.08f, 0.135f, 0, 30, 30, 30, 250);
					Misc::drawSprite("inventory_items", "weapon_repeater_lancaster", menuX + 0.3 + (b * 0.1f), menuY + 0.115 + addY, 0.087f, 0.11f, 0, 255, 255, 255, 255);

					std::stringstream text;
					text << Shop::stored[0];
					Misc::drawText(text.str().c_str(), menuX + 0.37 + (b * 0.1f), menuY + 0.198f + addY, 255, 255, 255, 255, 1, 0.5f, 0.5f);
				}

				if (Shop::stored_visual[c] == 1) {
					Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 + (b * 0.1f), menuY + 0.1f + addY, 0.08f, 0.135f, 0, 30, 30, 30, 250);
					Misc::drawSprite("inventory_items", "weapon_shotgun_pump", menuX + 0.382 + (b * 0.1f), menuY + 0.115 + addY, -0.087f, 0.11f, 0, 255, 255, 255, 255);

					std::stringstream text;
					text << Shop::stored[1];
					Misc::drawText(text.str().c_str(), menuX + 0.37 + (b * 0.1f), menuY + 0.198f + addY, 255, 255, 255, 255, 1, 0.5f, 0.5f);
				}

				if (Shop::stored_visual[c] == 2) {
					Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 + (b * 0.1f), menuY + 0.1f + addY, 0.08f, 0.135f, 0, 30, 30, 30, 250);
					Misc::drawSprite("inventory_items", "weapon_shotgun_repeating", menuX + 0.382 + (b * 0.1f), menuY + 0.115 + addY, -0.087f, 0.11f, 0, 255, 255, 255, 255);

					std::stringstream text;
					text << Shop::stored[2];
					Misc::drawText(text.str().c_str(), menuX + 0.37 + (b * 0.1f), menuY + 0.198f + addY, 255, 255, 255, 255, 1, 0.5f, 0.5f);
				}

				if (Shop::stored_visual[c] == 3) {
					Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 + (b * 0.1f), menuY + 0.1f + addY, 0.08f, 0.135f, 0, 30, 30, 30, 250);
					Misc::drawSprite("inventory_items", "weapon_rifle_springfield", menuX + 0.3 + (b * 0.1f), menuY + 0.115 + addY, 0.087f, 0.11f, 0, 255, 255, 255, 255);

					std::stringstream text;
					text << Shop::stored[3];
					Misc::drawText(text.str().c_str(), menuX + 0.37 + (b * 0.1f), menuY + 0.198f + addY, 255, 255, 255, 255, 1, 0.5f, 0.5f);
				}

				if (Shop::stored_visual[c] == 4) {
					Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 + (b * 0.1f), menuY + 0.1f + addY, 0.08f, 0.135f, 0, 30, 30, 30, 250);
					Misc::drawSprite("inventory_items", "weapon_rifle_varmint", menuX + 0.3 + (b * 0.1f), menuY + 0.115 + addY, 0.087f, 0.11f, 0, 255, 255, 255, 255);

					std::stringstream text;
					text << Shop::stored[4];
					Misc::drawText(text.str().c_str(), menuX + 0.37 + (b * 0.1f), menuY + 0.198f + addY, 255, 255, 255, 255, 1, 0.5f, 0.5f);
				}

				if (Shop::stored_visual[c] == 5) {
					Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3f + (b * 0.1f), menuY + 0.1f + addY, 0.08f, 0.135f, 0, 30, 30, 30, 250);
					Misc::drawSprite("inventory_items", "kit_gun_oil", menuX + 0.37f + (b * 0.1f), menuY + 0.13f + addY, -0.067f, 0.091f, 0, 255, 255, 255, 255);

					std::stringstream text;
					text << Shop::stored[5];
					Misc::drawText(text.str().c_str(), menuX + 0.37 + (b * 0.1f), menuY + 0.198f + addY, 255, 255, 255, 255, 1, 0.5f, 0.5f);
				}

				if (Shop::stored_visual[c] == 6) {
					Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 + (b * 0.1f), menuY + 0.1f + addY, 0.08f, 0.135f, 0, 30, 30, 30, 250);
					Misc::drawSprite("inventory_items", "clothing_generic_gunbelt", menuX + 0.37 + (b * 0.1f), menuY + 0.13 + addY, -0.067f, 0.091f, 0, 255, 255, 255, 255);
					// + (b * 0.1f)
					std::stringstream text;
					text << Shop::stored[6];
					Misc::drawText(text.str().c_str(), menuX + 0.37 + (b * 0.1f), menuY + 0.198f + addY, 255, 255, 255, 255, 1, 0.5f, 0.5f);
				}



				//////////////////////update 0.2///////////////////////////////////
				if (Shop::stored_visual[c] == 7) {
					Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 + (b * 0.1f), menuY + 0.1f + addY, 0.08f, 0.135f, 0, 30, 30, 30, 250);
					Misc::drawSprite("inventory_items", "weapon_repeater_carbine", menuX + 0.3 + (b * 0.1f), menuY + 0.115 + addY, 0.087f, 0.11f, 0, 255, 255, 255, 255);

					std::stringstream text;
					text << Shop::stored[7];
					Misc::drawText(text.str().c_str(), menuX + 0.37 + (b * 0.1f), menuY + 0.198f + addY, 255, 255, 255, 255, 1, 0.5f, 0.5f);
				}

				if (Shop::stored_visual[c] == 8) {
					Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 + (b * 0.1f), menuY + 0.1f + addY, 0.08f, 0.135f, 0, 30, 30, 30, 250);
					Misc::drawSprite("inventory_items", "upgrade_bandolier", menuX + 0.37 + (b * 0.1f), menuY + 0.125 + addY, -0.067f, 0.091f, 0, 255, 255, 255, 255);

					std::stringstream text;
					text << Shop::stored[8];
					Misc::drawText(text.str().c_str(), menuX + 0.37 + (b * 0.1f), menuY + 0.198f + addY, 255, 255, 255, 255, 1, 0.5f, 0.5f);
				}

				if (Shop::stored_visual[c] == 9) {
					Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 + (b * 0.1f), menuY + 0.1f + addY, 0.08f, 0.135f, 0, 30, 30, 30, 250);
					Misc::drawSprite("inventory_items", "weapon_revolver_cattleman", menuX + 0.37 + (b * 0.1f), menuY + 0.12f + addY, -0.067f, 0.11f, 0, 255, 255, 255, 255);

					std::stringstream text;
					text << Shop::stored[9];
					Misc::drawText(text.str().c_str(), menuX + 0.37 + (b * 0.1f), menuY + 0.198f + addY, 255, 255, 255, 255, 1, 0.5f, 0.5f);
				}

				if (Shop::stored_visual[c] == 10) {
					Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 + (b * 0.1f), menuY + 0.1f + addY, 0.08f, 0.135f, 0, 30, 30, 30, 250);
					Misc::drawSprite("inventory_items", "weapon_shotgun_sawedoff", menuX + 0.37 + (b * 0.1f), menuY + 0.13f + addY, -0.067f, 0.091f, 0, 255, 255, 255, 255);

					std::stringstream text;
					text << Shop::stored[10];
					Misc::drawText(text.str().c_str(), menuX + 0.37 + (b * 0.1f), menuY + 0.198f + addY, 255, 255, 255, 255, 1, 0.5f, 0.5f);
				}

				if (Shop::stored_visual[c] == 11) {
					Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 + (b * 0.1f), menuY + 0.1f + addY, 0.08f, 0.135f, 0, 30, 30, 30, 250);
					Misc::drawSprite("inventory_items", "weapon_pistol_semiauto", menuX + 0.37 + (b * 0.1f), menuY + 0.12f + addY, -0.067f, 0.11f, 0, 255, 255, 255, 255);

					std::stringstream text;
					text << Shop::stored[11];
					Misc::drawText(text.str().c_str(), menuX + 0.37 + (b * 0.1f), menuY + 0.198f + addY, 255, 255, 255, 255, 1, 0.5f, 0.5f);
				}

				if (Shop::stored_visual[c] == 12) {
					Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 + (b * 0.1f), menuY + 0.1f + addY, 0.08f, 0.135f, 0, 30, 30, 30, 250);
					Misc::drawSprite("inventory_items", "weapon_pistol_volcanic", menuX + 0.37 + (b * 0.1f), menuY + 0.12f + addY, -0.067f, 0.11f, 0, 255, 255, 255, 255);

					std::stringstream text;
					text << Shop::stored[12];
					Misc::drawText(text.str().c_str(), menuX + 0.37 + (b * 0.1f), menuY + 0.198f + addY, 255, 255, 255, 255, 1, 0.5f, 0.5f);
				}

				if (Shop::stored_visual[c] == 13) {
					Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 + (b * 0.1f), menuY + 0.1f + addY, 0.08f, 0.135f, 0, 30, 30, 30, 250);
					Misc::drawSprite("inventory_items", "weapon_revolver_schofield", menuX + 0.37 + (b * 0.1f), menuY + 0.12f + addY, -0.067f, 0.11f, 0, 255, 255, 255, 255);

					std::stringstream text;
					text << Shop::stored[13];
					Misc::drawText(text.str().c_str(), menuX + 0.37 + (b * 0.1f), menuY + 0.198f + addY, 255, 255, 255, 255, 1, 0.5f, 0.5f);
				}

				if (Shop::stored_visual[c] == 14) {
					Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 + (b * 0.1f), menuY + 0.1f + addY, 0.08f, 0.135f, 0, 30, 30, 30, 250);
					Misc::drawSprite("inventory_items", "weapon_revolver_doubleaction", menuX + 0.37 + (b * 0.1f), menuY + 0.13f + addY, -0.067f, 0.091f, 0, 255, 255, 255, 255);

					std::stringstream text;
					text << Shop::stored[14];
					Misc::drawText(text.str().c_str(), menuX + 0.37 + (b * 0.1f), menuY + 0.198f + addY, 255, 255, 255, 255, 1, 0.5f, 0.5f);
				}

				if (Shop::stored_visual[c] == 15) {
					Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 + (b * 0.1f), menuY + 0.1f + addY, 0.08f, 0.135f, 0, 30, 30, 30, 250);
					Misc::drawSprite("inventory_items", "weapon_shotgun_doublebarrel", menuX + 0.38 + (b * 0.1f), menuY + 0.115 + addY, -0.087f, 0.11f, 0, 255, 255, 255, 255);

					std::stringstream text;
					text << Shop::stored[15];
					Misc::drawText(text.str().c_str(), menuX + 0.37 + (b * 0.1f), menuY + 0.198f + addY, 255, 255, 255, 255, 1, 0.5f, 0.5f);
				}

				if (Shop::stored_visual[c] == 16) {
					Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 + (b * 0.1f), menuY + 0.1f + addY, 0.08f, 0.135f, 0, 30, 30, 30, 250);
					Misc::drawSprite("inventory_items", "weapon_sniperrifle_rollingblock", menuX + 0.3 + (b * 0.1f), menuY + 0.115 + addY, 0.087f, 0.11f, 0, 255, 255, 255, 255);

					std::stringstream text;
					text << Shop::stored[16];
					Misc::drawText(text.str().c_str(), menuX + 0.37 + (b * 0.1f), menuY + 0.198f + addY, 255, 255, 255, 255, 1, 0.5f, 0.5f);
				}

				if (Shop::stored_visual[c] == 17) {
					Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 + (b * 0.1f), menuY + 0.1f + addY, 0.08f, 0.135f, 0, 30, 30, 30, 250);
					Misc::drawSprite("inventory_items", "weapon_repeater_henry", menuX + 0.3 + (b * 0.1f), menuY + 0.115 + addY, 0.087f, 0.11f, 0, 255, 255, 255, 255);

					std::stringstream text;
					text << Shop::stored[17];
					Misc::drawText(text.str().c_str(), menuX + 0.37 + (b * 0.1f), menuY + 0.198f + addY, 255, 255, 255, 255, 1, 0.5f, 0.5f);
				}
				if (Shop::stored_visual[c] == 18) {
					Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 + (b * 0.1f), menuY + 0.1f + addY, 0.08f, 0.135f, 0, 30, 30, 30, 250);
					Misc::drawSprite("inventory_items_mp", "weapon_revolver_lemat", menuX + 0.37 + (b * 0.1f), menuY + 0.13f + addY, -0.067f, 0.091f, 0, 255, 255, 255, 255);

					std::stringstream text;
					text << Shop::stored[18];
					Misc::drawText(text.str().c_str(), menuX + 0.37 + (b * 0.1f), menuY + 0.198f + addY, 255, 255, 255, 255, 1, 0.5f, 0.5f);
				}
				if (Shop::stored_visual[c] == 19) {
					Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 + (b * 0.1f), menuY + 0.1f + addY, 0.08f, 0.135f, 0, 30, 30, 30, 250);
					Misc::drawSprite("inventory_items", "weapon_pistol_mauser", menuX + 0.37 + (b * 0.1f), menuY + 0.13f + addY, -0.067f, 0.091f, 0, 255, 255, 255, 255);

					std::stringstream text;
					text << Shop::stored[19];
					Misc::drawText(text.str().c_str(), menuX + 0.37 + (b * 0.1f), menuY + 0.198f + addY, 255, 255, 255, 255, 1, 0.5f, 0.5f);
				}
				if (Shop::stored_visual[c] == 20) {
					Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 + (b * 0.1f), menuY + 0.1f + addY, 0.08f, 0.135f, 0, 30, 30, 30, 250);
					Misc::drawSprite("inventory_items_mp", "weapon_rifle_elephant", menuX + 0.38 + (b * 0.1f), menuY + 0.115 + addY, -0.087f, 0.11f, 0, 255, 255, 255, 255);

					std::stringstream text;
					text << Shop::stored[20];
					Misc::drawText(text.str().c_str(), menuX + 0.37 + (b * 0.1f), menuY + 0.198f + addY, 255, 255, 255, 255, 1, 0.5f, 0.5f);
				}
				if (Shop::stored_visual[c] == 21) {
					Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 + (b * 0.1f), menuY + 0.1f + addY, 0.08f, 0.135f, 0, 30, 30, 30, 250);
					Misc::drawSprite("inventory_items_mp", "weapon_revolver_navy", menuX + 0.37 + (b * 0.1f), menuY + 0.13f + addY, -0.067f, 0.091f, 0, 255, 255, 255, 255);

					std::stringstream text;
					text << Shop::stored[21];
					Misc::drawText(text.str().c_str(), menuX + 0.37 + (b * 0.1f), menuY + 0.198f + addY, 255, 255, 255, 255, 1, 0.5f, 0.5f);
				}
				if (Shop::stored_visual[c] == 22) {
					Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 + (b * 0.1f), menuY + 0.1f + addY, 0.08f, 0.135f, 0, 30, 30, 30, 250);
					Misc::drawSprite("inventory_items_tu", "weapon_pistol_m1899", menuX + 0.37 + (b * 0.1f), menuY + 0.13f + addY, -0.067f, 0.091f, 0, 255, 255, 255, 255);

					std::stringstream text;
					text << Shop::stored[22];
					Misc::drawText(text.str().c_str(), menuX + 0.37 + (b * 0.1f), menuY + 0.198f + addY, 255, 255, 255, 255, 1, 0.5f, 0.5f);
				}
				if (Shop::stored_visual[c] == 23) {
					Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 + (b * 0.1f), menuY + 0.1f + addY, 0.08f, 0.135f, 0, 30, 30, 30, 250);
					Misc::drawSprite("inventory_items", "weapon_rifle_boltaction", menuX + 0.3 + (b * 0.1f), menuY + 0.115 + addY, 0.087f, 0.11f, 0, 255, 255, 255, 255);

					std::stringstream text;
					text << Shop::stored[23];
					Misc::drawText(text.str().c_str(), menuX + 0.37 + (b * 0.1f), menuY + 0.198f + addY, 255, 255, 255, 255, 1, 0.5f, 0.5f);
				}
				if (Shop::stored_visual[c] == 24) {
					Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 + (b * 0.1f), menuY + 0.1f + addY, 0.08f, 0.135f, 0, 30, 30, 30, 250);
					Misc::drawSprite("inventory_items_mp", "weapon_repeater_evans", menuX + 0.3 + (b * 0.1f), menuY + 0.115 + addY, 0.087f, 0.11f, 0, 255, 255, 255, 255);

					std::stringstream text;
					text << Shop::stored[24];
					Misc::drawText(text.str().c_str(), menuX + 0.37 + (b * 0.1f), menuY + 0.198f + addY, 255, 255, 255, 255, 1, 0.5f, 0.5f);
				}
				if (Shop::stored_visual[c] == 25) {
					Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 + (b * 0.1f), menuY + 0.1f + addY, 0.08f, 0.135f, 0, 30, 30, 30, 250);
					Misc::drawSprite("inventory_items", "weapon_sniperrifle_carcano", menuX + 0.3 + (b * 0.1f), menuY + 0.115 + addY, 0.087f, 0.11f, 0, 255, 255, 255, 255);

					std::stringstream text;
					text << Shop::stored[25];
					Misc::drawText(text.str().c_str(), menuX + 0.37 + (b * 0.1f), menuY + 0.198f + addY, 255, 255, 255, 255, 1, 0.5f, 0.5f);
				}
				if (Shop::stored_visual[c] == 26) {
					Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 + (b * 0.1f), menuY + 0.1f + addY, 0.08f, 0.135f, 0, 30, 30, 30, 250);
					Misc::drawSprite("inventory_items", "weapon_shotgun_semiauto", menuX + 0.38 + (b * 0.1f), menuY + 0.115 + addY, -0.087f, 0.11f, 0, 255, 255, 255, 255);

					std::stringstream text;
					text << Shop::stored[26];
					Misc::drawText(text.str().c_str(), menuX + 0.37 + (b * 0.1f), menuY + 0.198f + addY, 255, 255, 255, 255, 1, 0.5f, 0.5f);
				}

			}
		}


	}
	


}

//1335986638 -1819321039
//tum 3208189941 -164490887
void Menu::upgrade() {
	Ped player = PLAYER::PLAYER_PED_ID();
	//sell
	if (menuState == MenuState::Upgrades) {

		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Select, 0);
		HUD::_UIPROMPT_SET_ENABLED(Prompt_Select, 0);

		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy_Upgrade, 1);
		HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy_Upgrade, 0);

		
		if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Back))
		{
			
			AUDIO::PLAY_SOUND_FRONTEND("BACK", "HUD_SHOP_SOUNDSET", 1, 0);

			menuState = MenuState::Home;
			MenuControls::current_cell = 2;

		
		}

		select_clock++;
		if (select_clock > 120) {
			if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(Prompt_Buy_Upgrade)) {
				
				AUDIO::PLAY_SOUND_FRONTEND("PURCHASE", "Ledger_Sounds", 1, 0);

				switch (MenuControls::menu_controls(3)) {
				case 0:
					Shop::bedroll++;
					break;
				case 1:
					Shop::wagon++;
					break;
				case 2:
					Shop::dealer++;
					break;
				case 3:


					if (Shop::storage == 0) {

						if (Shop::shop_revenue >= 2000) {
							Shop::shop_revenue -= 2000;
							Shop::storage++;
							break;
						}

						if (MONEY::_MONEY_GET_CASH_BALANCE() >= 2000 * 100) {
							MONEY::_MONEY_DECREMENT_CASH_BALANCE(2000 * 100);
							Shop::storage++;
							break;
						}

					}

					if (Shop::storage == 1) {
						if (Shop::shop_revenue >= 5000) {
							Shop::shop_revenue -= 5000;
							Shop::storage++;
							break;
						}

						if (MONEY::_MONEY_GET_CASH_BALANCE() >= 5000 * 100) {
							MONEY::_MONEY_DECREMENT_CASH_BALANCE(5000 * 100);
							Shop::storage++;
							break;
						}
					}

					if (Shop::storage == 2) {
						if (Shop::shop_revenue >= 20000) {
							Shop::shop_revenue -= 20000;
							Shop::storage++;
							break;
						}

						if (MONEY::_MONEY_GET_CASH_BALANCE() >= 20000 * 100) {
							MONEY::_MONEY_DECREMENT_CASH_BALANCE(20000 * 100);
							Shop::storage++;
							break;
						}
					}






					break;

				};
				select_clock = 0;
			}

		}

		if (MenuControls::current_cell == 0) {
			if (!Shop::bedroll) {
				if (Shop::burg_gunsmith_bought || Shop::tum_gunsmith_bought) {
					if (MONEY::_MONEY_GET_CASH_BALANCE() >= 500 * 100 || Shop::shop_revenue >= 500) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy_Upgrade, 1);
					}
				}
				else {
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy_Upgrade, 0);
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy_Upgrade, 0);
				}
			}
			if (Shop::bedroll) {
				HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy_Upgrade, 0);
				HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy_Upgrade, 0);

			}
			//postponed
		//	HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy_Upgrade, 0);
		//	HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy_Upgrade, 0);

		}

		if (MenuControls::current_cell == 1) {
			if (!Shop::wagon) {
				if (MONEY::_MONEY_GET_CASH_BALANCE() >= 5000 * 100 || Shop::shop_revenue >= 5000) {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy_Upgrade, 1);
				}
			}
			if (Shop::wagon) {
				HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy_Upgrade, 0);
				HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy_Upgrade, 0);

			}

	

		}

		if (MenuControls::current_cell == 2) {
			if (!Shop::dealer) {
				if (MONEY::_MONEY_GET_CASH_BALANCE() >= 800 * 100 || Shop::shop_revenue >= 800) {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy_Upgrade, 1);
				}
			}
			if (Shop::dealer) {
				HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy_Upgrade, 0);
				HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy_Upgrade, 0);

			}

		

		}

		if (MenuControls::current_cell == 3) {
			if (Shop::storage == 0) {
				if (MONEY::_MONEY_GET_CASH_BALANCE() >= 2000 * 100 || Shop::shop_revenue >= 2000) {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy_Upgrade, 1);
				}
			}
			if (Shop::storage == 1) {
				if (MONEY::_MONEY_GET_CASH_BALANCE() >= 5000 * 100 || Shop::shop_revenue >= 5000) {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy_Upgrade, 1);
				}
			}
			if (Shop::storage == 2) {
				if (MONEY::_MONEY_GET_CASH_BALANCE() >= 20000 * 100 || Shop::shop_revenue >= 20000) {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy_Upgrade, 1);
				}
			}
			if (Shop::storage == 3) {
				HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy_Upgrade,0);
				HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy_Upgrade, 0);

			}

		}

		//Misc::drawTextSmall("You will be given back the original price", menuX + 0.4f, menuY + 0.2f, 255, 255, 255, 200, 1, 0.25f, 0.4f);

		//tick
		//generic_textures

		

		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3f, menuY + 0.1f, 0.2, 0.1f, 0, 30, 30, 30, 250);
		if (Shop::bedroll == 0) {
			Misc::drawText("Accomodation", menuX + 0.353f, menuY + 0.133f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
			Misc::drawText("$500", menuX + 0.47f, menuY + 0.133f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}
		if (Shop::bedroll == 1) {
			Misc::drawSprite("generic_textures", "tick", menuX + 0.455f, menuY + 0.133f, 0.03, 0.04f, 0, 250, 250, 250, 250);
			Misc::drawText("Accomodation", menuX + 0.353f, menuY + 0.133f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}




		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3f, menuY + 0.2f, 0.2, 0.1f, 0, 30, 30, 30, 250);	
		if (Shop::wagon == 0) {
			Misc::drawText("$5000", menuX + 0.47f, menuY + 0.233f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
			Misc::drawText("Wagon", menuX + 0.33f, menuY + 0.233f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}
		if (Shop::wagon == 1) {
			Misc::drawSprite("generic_textures", "tick", menuX + 0.455f, menuY + 0.233f, 0.03, 0.04f, 0, 250, 250, 250, 250);
			Misc::drawText("Wagon", menuX + 0.33f, menuY + 0.233f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}




		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3f, menuY + 0.3f, 0.2, 0.1f, 0, 30, 30, 30, 250);
		if (Shop::dealer == 0) {
			Misc::drawText("$800", menuX + 0.47f, menuY + 0.333f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
			Misc::drawText("After Hours", menuX + 0.35f, menuY + 0.333f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}
		if (Shop::dealer == 1) {
			Misc::drawSprite("generic_textures", "tick", menuX + 0.455f, menuY + 0.33f, 0.03, 0.04f, 0, 250, 250, 250, 250);
			Misc::drawText("After Hours", menuX + 0.35f, menuY + 0.333f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}
		


		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3f, menuY + 0.4f, 0.2, 0.1f, 0, 30, 30, 30, 250);
		if (Shop::storage == 0) {
			Misc::drawText("$2000", menuX + 0.47f, menuY + 0.433f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
			Misc::drawText("Extra storage", menuX + 0.355f, menuY + 0.433f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}
		if (Shop::storage == 1) {
			Misc::drawText("$5000", menuX + 0.47f, menuY + 0.433f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
			Misc::drawText("More storage", menuX + 0.353f, menuY + 0.433f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}
		if (Shop::storage == 2) {
			Misc::drawText("$20000", menuX + 0.47f, menuY + 0.433f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
			Misc::drawText("Warehouse", menuX + 0.347f, menuY + 0.433f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}
		if (Shop::storage == 3) {
			Misc::drawSprite("generic_textures", "tick", menuX + 0.455f, menuY + 0.43f, 0.03, 0.04f, 0, 250, 250, 250, 250);
			Misc::drawText("Warehouse", menuX + 0.347f, menuY + 0.433f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}


		char* option_name;
		char* desc_name;

		switch (MenuControls::current_cell) {
		case 0:
			option_name = "Accomodation";
			if (Shop::burg_gunsmith_bought || Shop::tum_gunsmith_bought) {
				desc_name = "Allows you to freely use the room\nin the hotel part of the store";
			}
			else {
				desc_name = "Allows you to freely use the room\nin the hotel part of the store\n\n(This gunsmith doesn't have a\nsleeping compartment)";
			}

			Misc::drawSprite("sp_missions_11", "mission_rmllr4", menuX - 0.09f + 0.11f, menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
			break;
		case 1:
			option_name = "Wagon";
			desc_name = "By purchasing the wagon you can\nexport your goods for a quick profit";
			Misc::drawSprite("sp_missions_11", "mission_be22", menuX - 0.09f + 0.11f, menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
			break;
		case 2:
			option_name = "After Hours";
			desc_name = "Gives your employees a bonus for\nstaying up late. This allows you to\nenter your business after hours";
			Misc::drawSprite("sp_missions_12", "mission_rgng02", menuX - 0.09f + 0.11f, menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
			break;
		case 3:
			option_name = "Extra Storage";
			desc_name = "Extends your storage, allowing you\nto keep more guns in stock and to\naccept larger deliveries";
			Misc::drawSprite("help_combat", "combat_gun_rack", menuX - 0.09f + 0.11f, menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
			break;


		};
		
		Misc::drawTextSmall(desc_name, menuX + 0.015f, menuY + 0.37f, 255, 255, 255, 255, 0, 0.25f, 0.4f);


		Misc::drawText(option_name, menuX + 0.12f, menuY + 0.03f, 255, 255, 255, 255, 1, 0.65f, 0.65f);

		Misc::drawSprite("generic_textures", "menu_header_1a", menuX + 0.02, menuY, 0.2, 0.1f, 0, 255, 255, 255, 250);




		float selectY = -0.013f + (0.1f * MenuControls::menu_controls(3));


		Misc::drawSprite("menu_textures", "crafting_highlight_b", menuX + 0.3f, menuY + 0.1f + selectY, 0.2, 0.03f, 0, 255, 0, 0, 250);
		Misc::drawSprite("menu_textures", "crafting_highlight_t", menuX + 0.3f, menuY + 0.2f + selectY, 0.2, 0.03f, 0, 255, 0, 0, 250);


		Misc::drawSprite("menu_textures", "crafting_highlight_l", menuX + 0.294f, menuY + 0.123f + selectY, 0.0135, 0.082f, 0, 255, 0, 0, 250);
		Misc::drawSprite("menu_textures", "crafting_highlight_r", menuX + 0.492f, menuY + 0.123f + selectY, 0.0135, 0.082f, 0, 255, 0, 0, 250);



	}

}



bool selected2;

int donate_timer;
int donate_value;

int prompt_text_timer;

void text_junk(Prompt prompt) {
	if (donate_value == 0) {
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In"));
	}
	else {
		stringstream moneyStream;
		moneyStream << "Cash-In ($";
		moneyStream << donate_value;
		moneyStream << ")";
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", moneyStream.str().c_str()));

	}
	
	/*
	switch (donate_value) {
	case 0:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In")); break;
	case 10:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($10)")); break;
	case 20:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($20)")); break;
	case 30:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($30)")); break;
	case 40:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($40)")); break;
	case 50:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($50)")); break;
	case 60:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($60)")); break;
	case 70:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($70)")); break;
	case 80:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($80)")); break;
	case 90:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($90)")); break;
	case 100:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($100)")); break;
	case 110:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($110)")); break;
	case 120:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($120)")); break;
	case 130:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($130)")); break;
	case 140:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($140)")); break;
	case 150:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($150)")); break;
	case 160:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($160)")); break;
	case 170:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($170)")); break;
	case 180:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($180)")); break;
	case 190:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($190)")); break;
	case 200:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($200)")); break;
	case 210:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($210)")); break;
	case 220:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($220)")); break;
	case 230:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($230)")); break;
	case 240:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($240)")); break;
	case 250:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($250)")); break;
	
	
	case 260:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($260)")); break;
	case 270:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($270)")); break;
	case 280:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($280)")); break;
	case 290:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($290)")); break;
	case 300:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($300)")); break;
	case 310:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($310)")); break;
	case 320:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($320)")); break;
	case 330:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($330)")); break;
	case 340:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($340)")); break;
	case 350:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($350)")); break;
	case 360:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($360)")); break;
	case 370:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($370)")); break;
	case 380:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($380)")); break;
	case 390:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($390)")); break;
	case 400:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($400)")); break;
	case 410:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($410)")); break;
	case 420:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($420)")); break;
	case 430:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($430)")); break;
	case 440:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($440)")); break;
	case 450:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($450)")); break;
	case 460:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($460)")); break;
	case 470:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($470)")); break;
	case 480:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($480)")); break;
	case 490:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($490)")); break;
	case 500:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-In ($500)")); break;
		
	}
	*/
}

void text_junk_out(Prompt prompt) {
	if (donate_value == 0) {
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out"));
	}
	else {
		stringstream moneyStream;
		moneyStream << "Cash-Out ($";
		moneyStream << donate_value;
		moneyStream << ")";
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", moneyStream.str().c_str()));

	}
	/*
	switch (donate_value) {
	case 0:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out")); break;
	case 10:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($10)")); break;
	case 20:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($20)")); break;
	case 30:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($30)")); break;
	case 40:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($40)")); break;
	case 50:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($50)")); break;
	case 60:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($60)")); break;
	case 70:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($70)")); break;
	case 80:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($80)")); break;
	case 90:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($90)")); break;
	case 100:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($100)")); break;
	case 110:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($110)")); break;
	case 120:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($120)")); break;
	case 130:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($130)")); break;
	case 140:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($140)")); break;
	case 150:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($150)")); break;
	case 160:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($160)")); break;
	case 170:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($170)")); break;
	case 180:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($180)")); break;
	case 190:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($190)")); break;
	case 200:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($200)")); break;
	case 210:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($210)")); break;
	case 220:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($220)")); break;
	case 230:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($230)")); break;
	case 240:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($240)")); break;
	case 250:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($250)")); break;


	case 260:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($260)")); break;
	case 270:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($270)")); break;
	case 280:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($280)")); break;
	case 290:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($290)")); break;
	case 300:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($300)")); break;
	case 310:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($310)")); break;
	case 320:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($320)")); break;
	case 330:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($330)")); break;
	case 340:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($340)")); break;
	case 350:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($350)")); break;
	case 360:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($360)")); break;
	case 370:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($370)")); break;
	case 380:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($380)")); break;
	case 390:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($390)")); break;
	case 400:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($400)")); break;
	case 410:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($410)")); break;
	case 420:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($420)")); break;
	case 430:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($430)")); break;
	case 440:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($440)")); break;
	case 450:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($450)")); break;
	case 460:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($460)")); break;
	case 470:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($470)")); break;
	case 480:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($480)")); break;
	case 490:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($490)")); break;
	case 500:
		HUD::_UIPROMPT_SET_TEXT(prompt, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out ($500)")); break;

	}
	*/
}



void Menu::managment() {


	//management
	if (menuState == MenuState::Managment) {
		if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Back) && !selected2)
		{
			//AUDIO::_0x0F2A2175734926D8("BACK", "HUD_SHOP_SOUNDSET");

			AUDIO::PLAY_SOUND_FRONTEND("BACK", "HUD_SHOP_SOUNDSET", 1, 0);
			if (keyboard) {
				menuState = MenuState::Home;
				MenuControls::current_cell = 3;
			}
			else {

				HUD::_UIPROMPT_SET_VISIBLE(Prompt_Donate, 0);
				HUD::_UIPROMPT_SET_ENABLED(Prompt_Donate, 0);

				HUD::_UIPROMPT_SET_VISIBLE(Prompt_Donate_Up, 0);
				HUD::_UIPROMPT_SET_ENABLED(Prompt_Donate_Up, 0);

				HUD::_UIPROMPT_SET_VISIBLE(Prompt_Donate_Down, 0);
				HUD::_UIPROMPT_SET_ENABLED(Prompt_Donate_Down, 0);

				donate_value = 0;

				keyboard = 1;
			}
		}

		if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(Prompt_Open_Shop)) {

			if (Shop::inRangeVal && Shop::val_gunsmith_bought) {
				Shop::val_gunsmith_bought = 0;
				MONEY::_MONEY_INCREMENT_CASH_BALANCE(2000 * 100, 0);
			}
			if (Shop::inRangeDenis && Shop::denis_gunsmith_bought) {
				Shop::denis_gunsmith_bought = 0;
				MONEY::_MONEY_INCREMENT_CASH_BALANCE(5000 * 100, 0);
			}
			if (Shop::inRangeBurg && Shop::burg_gunsmith_bought) {
				Shop::burg_gunsmith_bought = 0;
				MONEY::_MONEY_INCREMENT_CASH_BALANCE(1500 * 100, 0);
			}


			if (Shop::inRangeRho && Shop::rho_gunsmith_bought) {
				Shop::rho_gunsmith_bought = 0;
				MONEY::_MONEY_INCREMENT_CASH_BALANCE(3000 * 100, 0);
			}
			if (Shop::inRangeTum && Shop::tum_gunsmith_bought) {
				Shop::tum_gunsmith_bought = 0;
				MONEY::_MONEY_INCREMENT_CASH_BALANCE(1000 * 100, 0);
			}

			MONEY::_MONEY_INCREMENT_CASH_BALANCE(Shop::shop_revenue * 100, 0);

			Shop::shop_revenue = 0;
			Shop::shop_rep = 50;
			Shop::shop_status = 0;
			Shop::sell_rate = 1.0f;
			Shop::paycheck_rate = 1.0f;
			for (int i = 0; i < 9; i++) {
				Shop::stored[i] = 0;
			}


			menuState = MenuState::Off;

			HUD::_UIPROMPT_SET_ENABLED(Prompt_Back, 0); // _UIPROMPT_SET_ENABLED
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Back, 0);

			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Select, 0);
			HUD::_UIPROMPT_SET_ENABLED(Prompt_Select, 0);

			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Open_Shop, 0);
			HUD::_UIPROMPT_SET_ENABLED(Prompt_Open_Shop, 0);



			//0.2.6
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Donate_Up, 0);
			HUD::_UIPROMPT_SET_ENABLED(Prompt_Donate_Up, 0);

			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Donate_Down, 0);
			HUD::_UIPROMPT_SET_ENABLED(Prompt_Donate_Down, 0);

			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Donate, 0);
			HUD::_UIPROMPT_SET_ENABLED(Prompt_Donate, 0);


			//WAIT(3000);

			menuCleanUp();



		}

		if (!keyboard) {
			
				HUD::_UIPROMPT_SET_VISIBLE(Prompt_Donate, 1);
				HUD::_UIPROMPT_SET_ENABLED(Prompt_Donate, 1);

				HUD::_UIPROMPT_SET_VISIBLE(Prompt_Donate_Up, 1);
				HUD::_UIPROMPT_SET_ENABLED(Prompt_Donate_Up, 1);

				HUD::_UIPROMPT_SET_VISIBLE(Prompt_Donate_Down, 1);
				HUD::_UIPROMPT_SET_ENABLED(Prompt_Donate_Down, 1);


			
				if (cashin == 1) {

					
					if (donate_value >= 300) {
						if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(Prompt_Donate_Up)) {
							if (MISC::GET_GAME_TIMER() > donate_timer) {
								donate_timer = MISC::GET_GAME_TIMER() + 200;
								donate_value += 100;
							}
						}

						if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(Prompt_Donate_Down)) {
							if (MISC::GET_GAME_TIMER() > donate_timer) {
								donate_timer = MISC::GET_GAME_TIMER() + 200;
								if (donate_value > 0) {
									donate_value -= 100;
								}
								if (donate_value < 0) {
									donate_value = 0;
								}

							}
						}
					}
					else {
						if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(Prompt_Donate_Up)) {
							if (MISC::GET_GAME_TIMER() > donate_timer) {
								donate_timer = MISC::GET_GAME_TIMER() + 200;
								donate_value += 10;
							}
						}

						if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(Prompt_Donate_Down)) {
							if (MISC::GET_GAME_TIMER() > donate_timer) {
								donate_timer = MISC::GET_GAME_TIMER() + 200;
								if (donate_value > 0) {
									donate_value -= 10;
								}
								if (donate_value < 0) {
									donate_value = 0;
								}

							}
						}
					}
					
					text_junk(Prompt_Donate);

					if (!donate_value) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Donate, 0);
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Donate_Down, 0);
					}

					if (donate_value >= 300) {
						//HUD::_UIPROMPT_SET_ENABLED(Prompt_Donate_Up, 0);

						if ((donate_value + 100) * 100 > MONEY::_MONEY_GET_CASH_BALANCE()) {
							HUD::_UIPROMPT_SET_ENABLED(Prompt_Donate_Up, 0);
						}

					}
					else {

						if ((donate_value + 10) * 100 > MONEY::_MONEY_GET_CASH_BALANCE()) {
							HUD::_UIPROMPT_SET_ENABLED(Prompt_Donate_Up, 0);
						}
					}
					if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(Prompt_Donate)) {
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(donate_value * 100);
						Shop::shop_revenue += donate_value;


						HUD::_UIPROMPT_SET_VISIBLE(Prompt_Donate, 0);
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Donate, 0);

						HUD::_UIPROMPT_SET_VISIBLE(Prompt_Donate_Up, 0);
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Donate_Up, 0);

						HUD::_UIPROMPT_SET_VISIBLE(Prompt_Donate_Down, 0);
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Donate_Down, 0);

						donate_value = 0;

						keyboard = 1;

					}

					/*
					if (MONEY::_MONEY_GET_CASH_BALANCE() / 100 >= intValue) {
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(intValue * 100);
						Shop::shop_revenue += intValue;
					}
					else {
						Shop::shop_revenue += MONEY::_MONEY_GET_CASH_BALANCE() / 100;
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(intValue * 100);
					}
					*/

					



				}

				if (cashin == 2) {

					//HUD::_UIPROMPT_SET_TEXT(Prompt_Donate, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Cash-Out")); //set text


					text_junk_out(Prompt_Donate);

					if (!donate_value) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Donate, 0);
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Donate_Down, 0);
					}


					if (donate_value >= 300) {
						//HUD::_UIPROMPT_SET_ENABLED(Prompt_Donate_Up, 0);

						if ((donate_value + 100) > Shop::shop_revenue) {
							HUD::_UIPROMPT_SET_ENABLED(Prompt_Donate_Up, 0);
						}

					}
					else {

						if ((donate_value + 10) > Shop::shop_revenue) {
							HUD::_UIPROMPT_SET_ENABLED(Prompt_Donate_Up, 0);
						}
					}

					
					if (donate_value >= 300) {
						if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(Prompt_Donate_Up)) {
							if (MISC::GET_GAME_TIMER() > donate_timer) {
								donate_timer = MISC::GET_GAME_TIMER() + 200;

								donate_value += 100;
							}
						}

						if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(Prompt_Donate_Down)) {
							if (MISC::GET_GAME_TIMER() > donate_timer) {
								donate_timer = MISC::GET_GAME_TIMER() + 200;
								if (donate_value > 0) {
									donate_value -= 100;
								}
								if (donate_value < 0) {
									donate_value = 0;
								}

							}
						}
					}
					else {
						if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(Prompt_Donate_Up)) {
							if (MISC::GET_GAME_TIMER() > donate_timer) {
								donate_timer = MISC::GET_GAME_TIMER() + 200;

								donate_value += 10;
							}
						}

						if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(Prompt_Donate_Down)) {
							if (MISC::GET_GAME_TIMER() > donate_timer) {
								donate_timer = MISC::GET_GAME_TIMER() + 200;
								if (donate_value > 0) {
									donate_value -= 10;
								}
								if (donate_value < 0) {
									donate_value = 0;
								}

							}
						}
					}


					if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(Prompt_Donate)) {
						

						MONEY::_MONEY_INCREMENT_CASH_BALANCE(donate_value * 100, 0);
						Shop::shop_revenue -= donate_value;

						HUD::_UIPROMPT_SET_VISIBLE(Prompt_Donate, 0);
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Donate, 0);

						HUD::_UIPROMPT_SET_VISIBLE(Prompt_Donate_Up, 0);
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Donate_Up, 0);

						HUD::_UIPROMPT_SET_VISIBLE(Prompt_Donate_Down, 0);
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Donate_Down, 0);

						donate_value = 0;

						keyboard = 1;

					}


					/*
					if (Shop::shop_revenue > 0) {
						if (Shop::shop_revenue >= intValue) {
							MONEY::_MONEY_INCREMENT_CASH_BALANCE(intValue * 100, 0);
							Shop::shop_revenue -= intValue;
						}
						else {
							MONEY::_MONEY_INCREMENT_CASH_BALANCE(Shop::shop_revenue * 100, 0);
							Shop::shop_revenue = 0;

						}
					}
					*/
					//MONEY::_MONEY_INCREMENT_CASH_BALANCE(intValue * 100, 0);
				}

				//keyboard = 1;
			
		}
		//drawSprite("generic_textures", "menu_header_1a", menuX + 0.05, menuY + 0.03f, 0.2, 0.1f, 0, 255, 255, 255, 250);

		//drawSprite("generic_textures", "title_divider", menuX + 0.28, menuY + 0.05f, 0.004, 0.9f, 0, 255, 255, 255, 250);


		
		if (select_clock > 10) {
			if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Select))
			{
				//AUDIO::_0x0F2A2175734926D8("INFO", "HUD_SHOP_SOUNDSET");

				AUDIO::PLAY_SOUND_FRONTEND("INFO", "HUD_SHOP_SOUNDSET", 1, 0);

				switch (MenuControls::menu_controls(4)) {
				case 2:
					keyboard = 0;
					cashin = 1; //cash in
					break;
				case 3:
					keyboard = 0;
					cashin = 2; //cash out
					break;


				};
				select_clock = 0;
			}

		}



		if (MenuControls::current_cell == 0) {
			MenuControls::current_cell_x = Shop::sell_rate_visual;
			Shop::sell_rate_visual = MenuControls::menu_controls_alt(4);
		}

		if (MenuControls::current_cell == 1) {
			MenuControls::current_cell_x = Shop::paycheck_rate_visual;
			Shop::paycheck_rate_visual = MenuControls::menu_controls_alt(4);
		}




		Misc::drawText("Prices", menuX + 0.33, menuY + 0.133f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3, menuY + 0.1f, 0.2, 0.1f, 0, 30, 30, 30, 250);

		Misc::drawText("Staff paycheck", menuX + 0.36, menuY + 0.133f + 0.1f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3, menuY + 0.2f, 0.2, 0.1f, 0, 30, 30, 30, 250);


		Misc::drawText("Cash-in", menuX + 0.335, menuY + 0.133f + 0.2f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3, menuY + 0.3f, 0.2, 0.1f, 0, 30, 30, 30, 250);

		Misc::drawText("Cash-out", menuX + 0.34, menuY + 0.133f + 0.3f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3, menuY + 0.4f, 0.2, 0.1f, 0, 30, 30, 30, 250);



		Misc::drawText("Sell Business", menuX + 0.4, menuY + 0.833f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3, menuY + 0.8f, 0.2, 0.1f, 0, 30, 30, 30, 250);

		//Misc::drawTextSmall("You will be given back the original price", menuX + 0.4f, menuY + 0.9f, 255, 255, 255, 200, 1, 0.25f, 0.4f);




		switch (Shop::sell_rate_visual) {
		case 0:
			Misc::drawSprite("mp_lobby_textures", "leaderboard_cash", menuX + 0.45f, menuY + 0.135f, 0.025f, 0.035f, 0, 250, 250, 250, 250);
			Misc::drawSprite("mp_lobby_textures", "cross", menuX + 0.45f, menuY + 0.135f, 0.025f, 0.035f, 0, 250, 250, 250, 250);
			break;
		case 1:
			Misc::drawSprite("rpg_textures", "rpg_core_background", menuX + 0.45f, menuY + 0.135f, 0.022, 0.032f, 0, 0, 0, 0, 255);
			Misc::drawSprite("mp_lobby_textures", "leaderboard_cash", menuX + 0.45f, menuY + 0.135f, 0.025f, 0.035f, 0, 250, 250, 250, 250);
			break;
		case 2:
			Misc::drawSprite("rpg_textures", "rpg_core_background", menuX + 0.445f, menuY + 0.135f, 0.022, 0.032f, 0, 0, 0, 0, 255);
			Misc::drawSprite("mp_lobby_textures", "leaderboard_cash", menuX + 0.445f, menuY + 0.135f, 0.025f, 0.035f, 0, 250, 250, 250, 250);

			Misc::drawSprite("rpg_textures", "rpg_core_background", menuX + 0.455f, menuY + 0.135f, 0.022, 0.032f, 0, 0, 0, 0, 255);
			Misc::drawSprite("mp_lobby_textures", "leaderboard_cash", menuX + 0.455f, menuY + 0.135f, 0.025f, 0.035f, 0, 250, 250, 250, 250);
			break;
		case 3:
			Misc::drawSprite("rpg_textures", "rpg_core_background", menuX + 0.44f, menuY + 0.135f, 0.022, 0.032f, 0, 0, 0, 0, 255);
			Misc::drawSprite("mp_lobby_textures", "leaderboard_cash", menuX + 0.44f, menuY + 0.135f, 0.025f, 0.035f, 0, 250, 250, 250, 250);

			Misc::drawSprite("rpg_textures", "rpg_core_background", menuX + 0.45f, menuY + 0.135f, 0.022, 0.032f, 0, 0, 0, 0, 255);
			Misc::drawSprite("mp_lobby_textures", "leaderboard_cash", menuX + 0.45f, menuY + 0.135f, 0.025f, 0.035f, 0, 250, 250, 250, 250);

			Misc::drawSprite("rpg_textures", "rpg_core_background", menuX + 0.46f, menuY + 0.135f, 0.022, 0.032f, 0, 0, 0, 0, 255);
			Misc::drawSprite("mp_lobby_textures", "leaderboard_cash", menuX + 0.46f, menuY + 0.135f, 0.025f, 0.035f, 0, 250, 250, 250, 250);
			break;
		case 4:
			Misc::drawSprite("rpg_textures", "rpg_core_background", menuX + 0.45f, menuY + 0.135f, 0.022, 0.032f, 0, 0, 0, 0, 255);
			Misc::drawSprite("mp_lobby_textures", "leaderboard_gold", menuX + 0.45f, menuY + 0.135f, 0.025f, 0.035f, 0, 250, 250, 250, 250);
			break;

		};

		switch (Shop::paycheck_rate_visual) {
		case 0:
			Misc::drawSprite("rpg_textures", "rpg_core_background", menuX + 0.45f, menuY + 0.235f, 0.022, 0.032f, 0, 0, 0, 0, 255);
			Misc::drawSprite("mp_lobby_textures", "leaderboard_cash", menuX + 0.45f, menuY + 0.235f, 0.025f, 0.035f, 0, 250, 250, 250, 250);
			Misc::drawSprite("mp_lobby_textures", "cross", menuX + 0.45f, menuY + 0.235f, 0.025f, 0.035f, 0, 250, 250, 250, 250);
			break;
		case 1:
			Misc::drawSprite("rpg_textures", "rpg_core_background", menuX + 0.45f, menuY + 0.235f, 0.022, 0.032f, 0, 0, 0, 0, 255);
			Misc::drawSprite("mp_lobby_textures", "leaderboard_cash", menuX + 0.45f, menuY + 0.235f, 0.025f, 0.035f, 0, 250, 250, 250, 250);
			break;
		case 2:
			Misc::drawSprite("rpg_textures", "rpg_core_background", menuX + 0.445f, menuY + 0.235f, 0.022, 0.032f, 0, 0, 0, 0, 255);
			Misc::drawSprite("mp_lobby_textures", "leaderboard_cash", menuX + 0.445f, menuY + 0.235f, 0.025f, 0.035f, 0, 250, 250, 250, 250);

			Misc::drawSprite("rpg_textures", "rpg_core_background", menuX + 0.455f, menuY + 0.235f, 0.022, 0.032f, 0, 0, 0, 0, 255);
			Misc::drawSprite("mp_lobby_textures", "leaderboard_cash", menuX + 0.455f, menuY + 0.235f, 0.025f, 0.035f, 0, 250, 250, 250, 250);
			break;
		case 3:
			Misc::drawSprite("rpg_textures", "rpg_core_background", menuX + 0.44f, menuY + 0.235f, 0.022, 0.032f, 0, 0, 0, 0, 255);
			Misc::drawSprite("mp_lobby_textures", "leaderboard_cash", menuX + 0.44f, menuY + 0.235f, 0.025f, 0.035f, 0, 250, 250, 250, 250);

			Misc::drawSprite("rpg_textures", "rpg_core_background", menuX + 0.45f, menuY + 0.235f, 0.022, 0.032f, 0, 0, 0, 0, 255);
			Misc::drawSprite("mp_lobby_textures", "leaderboard_cash", menuX + 0.45f, menuY + 0.235f, 0.025f, 0.035f, 0, 250, 250, 250, 250);

			Misc::drawSprite("rpg_textures", "rpg_core_background", menuX + 0.46f, menuY + 0.235f, 0.022, 0.032f, 0, 0, 0, 0, 255);
			Misc::drawSprite("mp_lobby_textures", "leaderboard_cash", menuX + 0.46f, menuY + 0.235f, 0.025f, 0.035f, 0, 250, 250, 250, 250);
			break;
		case 4:
			Misc::drawSprite("rpg_textures", "rpg_core_background", menuX + 0.45f, menuY + 0.235f, 0.022, 0.032f, 0, 0, 0, 0, 255);
			Misc::drawSprite("mp_lobby_textures", "leaderboard_gold", menuX + 0.45f, menuY + 0.235f, 0.025f, 0.035f, 0, 250, 250, 250, 250);
			break;

		};



		//Misc::drawSprite("pausemenu_index", "pocketwatch_face", menuX + 0.6, menuY + 0.4f, 0.07f, 0.1f, 0, 255, 255, 255, 255);
		//Misc::drawSprite("pausemenu_index", "pocketwatch_big_hand", menuX + 0.629, menuY + 0.395f, 0.01f, 0.13f, 0, 0, 0, 0, 255);
		//Misc::drawSprite("pausemenu_index", "pocketwatch_center", menuX + 0.629, menuY + 0.395f, 0.01f, 0.01f, 0, 0, 0, 0, 255);







		//
		current_rep = 0.23f;

		char* option_name;
		char* desc_name;

		std::stringstream prices;

		std::stringstream paychecks;

		switch (MenuControls::current_cell) {
		case 0:
			option_name = "Prices";
			desc_name = "Sets the prices modifier for items in\nyour shop. Depending on it your\nitem selling rate and reputation\nmay change.";

			Misc::drawSprite("frontend_store", "store_big_image", menuX - 0.09f + 0.11f, menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);

			Misc::drawTextSmall("Prices", menuX + 0.032f, menuY + 0.85f, 255, 255, 255, 200, 1, 0.25f, 0.4f);

			

			switch (Shop::sell_rate_visual) {
			case 0:
				prices << "Free!";
				Shop::sell_rate = initialize::sell_rate_free;
				break;
			case 1:
				prices << "Cheap";
				Shop::sell_rate = initialize::sell_rate_cheap;
				break;
			case 2:
				prices << "Average";
				Shop::sell_rate = initialize::sell_rate_average;
				break;
			case 3:
				prices << "Expensive";
				Shop::sell_rate = initialize::sell_rate_expensive;
				break;
			case 4:
				prices << "Very expensive";
				Shop::sell_rate = initialize::sell_rate_veryexpensive;
				break;
			};
			Misc::drawTextSmall(prices.str().c_str(), menuX + 0.21f, menuY + 0.85f, 255, 255, 255, 200, 1, 0.25f, 0.4f);



			break;
		case 1:
			option_name = "Staff Paycheck";
			desc_name = "Changes the amount you pay to your\nstaff. Not paying them may result in\nreputation loss.";

			Misc::drawSprite("map_card_camp_tithing_box", "image", menuX - 0.09f + 0.11f, menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);

			Misc::drawTextSmall("Salaries", menuX + 0.036f, menuY + 0.85f, 255, 255, 255, 200, 1, 0.25f, 0.4f);

			

			switch (Shop::paycheck_rate_visual) {
			case 0:
				paychecks << "None";
				Shop::paycheck_rate = initialize::paycheck_rate_none;
				break;
			case 1:
				paychecks << "Low";
				Shop::paycheck_rate = initialize::paycheck_rate_low;
				break;
			case 2:
				paychecks << "Average";
				Shop::paycheck_rate = initialize::paycheck_rate_average;
				break;
			case 3:
				paychecks << "Generous";
				Shop::paycheck_rate = initialize::paycheck_rate_generous;
				break;
			case 4:
				paychecks << "Very generous";
				Shop::paycheck_rate = initialize::paycheck_rate_verygenerous;
				break;
			};
			Misc::drawTextSmall(paychecks.str().c_str(), menuX + 0.21f, menuY + 0.85f, 255, 255, 255, 200, 1, 0.25f, 0.4f);





			break;
		case 2:
			option_name = "Cash-in";
			desc_name = "Cashes in your personal funds into\nthe shops budget.";
			Misc::drawSprite("map_card_blk_bank", "image", menuX - 0.09f + 0.11f, menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
			
			break;
		case 3:
			option_name = "Cash-out";
			desc_name = "Cashes out money from the shops\nbudget into your personal balance.";
			Misc::drawSprite("map_card_blk_bank", "image", menuX - 0.09f + 0.11f, menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
			
			break;
		case 4:
			option_name = "Sell Business";
			desc_name = "Sells your business to the original\nowner, giving you back the price\nyou paid for it";
			Misc::drawSprite("sp_missions_6", "mission_rmary3", menuX - 0.09f + 0.11f, menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);

			Misc::drawTextSmall("Sell price", menuX + 0.015f, menuY + 0.85f, 255, 255, 255, 200, 0, 0.25f, 0.4f);

			if (Shop::val_gunsmith_bought) {
				Misc::drawTextSmall("$2000", menuX + 0.185f, menuY + 0.85f, 255, 255, 255, 200, 0, 0.25f, 0.4f);

			}
			if (Shop::denis_gunsmith_bought) {
				Misc::drawTextSmall("$5000", menuX + 0.19f, menuY + 0.85f, 255, 255, 255, 200, 0, 0.25f, 0.4f);

			}
			if (Shop::burg_gunsmith_bought) {
				Misc::drawTextSmall("$1500", menuX + 0.19f, menuY + 0.85f, 255, 255, 255, 200, 0, 0.25f, 0.4f);
			}

			if (Shop::rho_gunsmith_bought) {
				Misc::drawTextSmall("$3000", menuX + 0.19f, menuY + 0.85f, 255, 255, 255, 200, 0, 0.25f, 0.4f);
			}
			if (Shop::tum_gunsmith_bought) {
				Misc::drawTextSmall("$1000", menuX + 0.19f, menuY + 0.85f, 255, 255, 255, 200, 0, 0.25f, 0.4f);
			}
			

			break;

		};

		Misc::drawTextSmall(desc_name, menuX + 0.015f, menuY + 0.37f, 255, 255, 255, 255, 0, 0.25f, 0.4f);


		Misc::drawText(option_name, menuX + 0.12f, menuY + 0.03f, 255, 255, 255, 255, 1, 0.65f, 0.65f);

		Misc::drawSprite("generic_textures", "menu_header_1a", menuX + 0.02, menuY, 0.2, 0.1f, 0, 255, 255, 255, 250);

		
		//TODO map_card_camp_horse_hitch.ytd upgrade


		float selectY = -0.013f + (0.1f * MenuControls::menu_controls(4));

		if (MenuControls::current_cell == 4) {
			selectY = -0.013f + (0.1f * 7);
		}

		if (MenuControls::current_cell == 0 || MenuControls::current_cell == 1) {
			Misc::drawSprite("menu_textures", "crafting_highlight_larrow", menuX + 0.294, menuY + 0.123f + selectY, 0.0135, 0.082f, 0, 255, 0, 0, 250);
			Misc::drawSprite("menu_textures", "crafting_highlight_rarrow", menuX + 0.492, menuY + 0.123f + selectY, 0.0135, 0.082f, 0, 255, 0, 0, 250);
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Select, 0);
			HUD::_UIPROMPT_SET_ENABLED(Prompt_Select, 0);
		}
		else {
			Misc::drawSprite("menu_textures", "crafting_highlight_l", menuX + 0.294, menuY + 0.123f + selectY, 0.0135, 0.082f, 0, 255, 0, 0, 250);
			Misc::drawSprite("menu_textures", "crafting_highlight_r", menuX + 0.492, menuY + 0.123f + selectY, 0.0135, 0.082f, 0, 255, 0, 0, 250);
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Select, 1);
			HUD::_UIPROMPT_SET_ENABLED(Prompt_Select, 1);
		}


		if (MenuControls::current_cell == 4) {
			

			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Select, 0);
			HUD::_UIPROMPT_SET_ENABLED(Prompt_Select, 0);

			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Open_Shop, 1);
			HUD::_UIPROMPT_SET_ENABLED(Prompt_Open_Shop, 1);
			HUD::_UIPROMPT_SET_TEXT(Prompt_Open_Shop, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Sell business")); //set text

		}
		else {
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Open_Shop, 0);
			HUD::_UIPROMPT_SET_ENABLED(Prompt_Open_Shop, 0);
		}

		if (!keyboard) {
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Select, 0);
			HUD::_UIPROMPT_SET_ENABLED(Prompt_Select, 0);
		}

		Misc::drawSprite("menu_textures", "crafting_highlight_b", menuX + 0.3f, menuY + 0.1f + selectY, 0.2, 0.03f, 0, 255, 0, 0, 250);
		Misc::drawSprite("menu_textures", "crafting_highlight_t", menuX + 0.3f, menuY + 0.2f + selectY, 0.2, 0.03f, 0, 255, 0, 0, 250);

		

		

	}

}



void Menu::sell() {
	Ped player = PLAYER::PLAYER_PED_ID();
	//sell
	if (menuState == MenuState::Sell) {

		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Select, 0);
		HUD::_UIPROMPT_SET_ENABLED(Prompt_Select, 0);

		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Open_Shop, 1);
		HUD::_UIPROMPT_SET_ENABLED(Prompt_Open_Shop, 1);
		HUD::_UIPROMPT_SET_TEXT(Prompt_Open_Shop, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Sell business")); //set text

		if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Back) && !selected2)
		{
			//AUDIO::_0x0F2A2175734926D8("BACK", "HUD_SHOP_SOUNDSET");

			AUDIO::PLAY_SOUND_FRONTEND("BACK", "HUD_SHOP_SOUNDSET", 1, 0);

			menuState = MenuState::Home;
			MenuControls::current_cell = 5;
		}

		if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(Prompt_Open_Shop)) {
			
			if (Shop::inRangeVal && Shop::val_gunsmith_bought) {
				Shop::val_gunsmith_bought = 0;
				MONEY::_MONEY_INCREMENT_CASH_BALANCE(2000 * 100, 0);
			}
			if (Shop::inRangeDenis && Shop::denis_gunsmith_bought) {
				Shop::denis_gunsmith_bought = 0;
				MONEY::_MONEY_INCREMENT_CASH_BALANCE(5000 * 100, 0);
			}
			if (Shop::inRangeBurg && Shop::burg_gunsmith_bought) {
				Shop::burg_gunsmith_bought = 0;
				MONEY::_MONEY_INCREMENT_CASH_BALANCE(1500 * 100, 0);
			}

			if (Shop::inRangeRho && Shop::rho_gunsmith_bought) {
				Shop::rho_gunsmith_bought = 0;
				MONEY::_MONEY_INCREMENT_CASH_BALANCE(3000 * 100, 0);
			}
			if (Shop::inRangeTum && Shop::tum_gunsmith_bought) {
				Shop::tum_gunsmith_bought = 0;
				MONEY::_MONEY_INCREMENT_CASH_BALANCE(1000 * 100, 0);
			}

			MONEY::_MONEY_INCREMENT_CASH_BALANCE(Shop::shop_revenue * 100, 0);

			Shop::shop_revenue = 0;
			Shop::shop_rep = 50;
			Shop::shop_status = 0;
			Shop::sell_rate = 1.0f;
			Shop::paycheck_rate = 1.0f;
			for (int i = 0; i < 9; i++) {
				Shop::stored[i] = 0;
			}


			menuState = MenuState::Off;

			HUD::_UIPROMPT_SET_ENABLED(Prompt_Back, 0); // _UIPROMPT_SET_ENABLED
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Back, 0);

			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Select, 0);
			HUD::_UIPROMPT_SET_ENABLED(Prompt_Select, 0);

			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Open_Shop, 0);
			HUD::_UIPROMPT_SET_ENABLED(Prompt_Open_Shop, 0);

			//WAIT(3000);

			menuCleanUp();
			


		}

		Misc::drawTextSmall("You will be given back the original price", menuX + 0.4f, menuY + 0.2f, 255, 255, 255, 200, 1, 0.25f, 0.4f);



		Misc::drawText("Sell Business", menuX + 0.4, menuY + 0.133f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3, menuY + 0.1f, 0.2, 0.1f, 0, 30, 30, 30, 250);



		float selectY = -0.013f + (0.1f * MenuControls::menu_controls(0));


		Misc::drawSprite("menu_textures", "crafting_highlight_b", menuX + 0.3f, menuY + 0.1f + selectY, 0.2, 0.03f, 0, 255, 0, 0, 250);
		Misc::drawSprite("menu_textures", "crafting_highlight_t", menuX + 0.3f, menuY + 0.2f + selectY, 0.2, 0.03f, 0, 255, 0, 0, 250);


		Misc::drawSprite("menu_textures", "crafting_highlight_l", menuX + 0.294f, menuY + 0.123f + selectY, 0.0135, 0.082f, 0, 255, 0, 0, 250);
		Misc::drawSprite("menu_textures", "crafting_highlight_r", menuX + 0.492f, menuY + 0.123f + selectY, 0.0135, 0.082f, 0, 255, 0, 0, 250);



	}

}



//1335986638 annesburg hotel door





void Menu::ambient() {

	select_clock++;


	refresh_clock++;
	if (refresh_clock > 600) {

		Shop::current_stock = 0;

		for (int i = 0; i < Shop::hardLimit - 1; i++) {
			Shop::current_stock += Shop::stored[i];
		}


		stored_int = 0;
		for (int a = 0; a < Shop::hardLimit - 1; a++) {
			if (Shop::stored[a] > 0) {
				Shop::stored_visual[stored_int] = a;
				Shop::stored_visual[stored_int + 1] = -1;
				stored_int++;
			}

		}

		refresh_clock = 0;
	}



	startUp();


	menuOn();

	homePage();



	supplies();


	suppliers();

	suppliersSpecfic();

	yourSupplies();


	upgrade();
	managment();
	sell();



	shopWidget();
}


