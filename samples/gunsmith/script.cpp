#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <Windows.h>
#include <shlwapi.h>
#include "Shop.h"
#include "Enemies.h"
#include "SaveLoad.h"
#include "Misc.h"
#include "script.h"
#include "SupplyRuns.h"
#include "initialize.h"
#include "Logic.h"
#include "Menu.h"
#include "Suppliers.h"
#include "Toasts.h"


using namespace std;

float shop_rep = 50;

void main()
{

	srand(time(NULL));



	Ped player = PLAYER::PLAYER_PED_ID();
	Hash cur;
	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, false);

	int money = 0;


	int blip_timer = 0;

	int select_clock;



	int once = 0;


	int stored_int = 0;


	//speech params script
	struct ScriptedSpeechParams
	{
		const char* speechName;
		const char* voiceName;
		alignas(8) int v3;
		alignas(8) Hash speechParamHash;
		alignas(8) Entity entity;
		alignas(8) BOOL v6;
		alignas(8) int v7;
		alignas(8) int v8;
	};


	SaveLoad::Load();

	SaveLoad::Save();


	int save_timer = 0;

	int loop_once = 0;

	int refresh_clock = 0;

	int shop_open_clock = 0;


	int total = 0;
	int prompt_clock = 0;



	int long_timer = 0;

	int stored_timer = 0;

	int load_timer;

	int wait_timer = 0;

	int init = 0;

	int var = 0;


	float addY = 0;


	Shop::daily_expanses = initialize::base_daily_cost;

	int interval_timer = 0;

	//loads the MP textures
	TXD::REQUEST_STREAMED_TEXTURE_DICT("inventory_items_mp", 0);
	WAIT(0);
	//Loads the delivery wagon
	if (!STREAMING::HAS_MODEL_LOADED(MISC::GET_HASH_KEY("CHUCKWAGON000X")));
	{
		STREAMING::REQUEST_MODEL(MISC::GET_HASH_KEY("CHUCKWAGON000X"), false);
		WAIT(0);
	}



	initialize::init();

	Menu::init();

	//loads MP toasts
	TXD::REQUEST_STREAMED_TEXTURE_DICT("toasts_mp_generic", 0); 
	WAIT(0);


	//anne -2942.929, 1321.155, 44.760, 252
	//denis 2720.893, -1282.668, 49.638, 118
	//rho 1325.937, -1318.154, 77.949, 165
	//val -282.795, 785.178, 119.502 180
	//tum -5510.201, -2960.690, -0.664

	bool gunsmithOpen = 0;
	Ped pou;
	Vector3 crimePos;
	while (true)
	{
		//cams setup
		if (!CAM::IS_CAM_ACTIVE(Menu::localCam)) {
			CAM::SET_CAM_ACTIVE(Menu::localCam, 0);
			if (CAM::DOES_CAM_EXIST(Menu::localCam)) {
				CAM::DESTROY_CAM(Menu::localCam, 1);
			}
		}

		//Debug text showing the current mod version
		if (initialize::debug_texts == 1) {
			if (init == 0) {
				Misc::drawText("Loading Gunsmith Business 0.3.2...", 0.8f, 0.97f, 0, 0, 0, 255, 1, 0.401f, 0.401f);
				Misc::drawText("Loading Gunsmith Business 0.3.2...", 0.8f, 0.899f + 0.07f, 255, 255, 255, 255, 1, 0.4f, 0.4f);
			}

			wait_timer++;
			if (wait_timer > 400) { 
				if (!init) {


					init = 1;

				}

				load_timer++;
				if (load_timer < 200) { 
					Misc::drawText("Gunsmith Business 0.3.2 was loaded correctly", 0.8f, 0.97f, 0, 0, 0, 255, 1, 0.401f, 0.401f);
					Misc::drawText("Gunsmith Business 0.3.2 was loaded correctly", 0.8f, 0.899f + 0.07f, 255, 255, 255, 255, 1, 0.4f, 0.4f);


				}

			}
		}

		Ped player2 = PLAYER::_GET_PLAYER_PED_2(1);


		playerPos = ENTITY::GET_ENTITY_COORDS(player, true, false);
		Object seq;
		Hash cur;
		int drop;
		Entity ent;


		//save interval
		if (save_timer < MISC::GET_GAME_TIMER()) { 

			SaveLoad::Save();

			save_timer = MISC::GET_GAME_TIMER() + 10000;
		}



		Toasts::updateUI();




		//////////////////////////Supply Runs//////////////////////////////////

		baseSuppliers::supplyRun.Ambient();

		////////////////////////Supply Runs End////////////////////////////////




		float menuX = 0.09f; //menuX 0.040
		const float menuY = 0.02f; //menuY 0.68


		Logic::gunsmithController();


		Menu::ambient();


		//////////////////////////////Reputation stuff///////////////////////////////////////////


		//unfinished threats system
		HUD::_UIPROMPT_SET_GROUP(initialize::Prompt_Threaten, 0, 0);
		if (distanceBetween(playerPos, Shop::gunsmithVal) <= 4.0f) {
			//PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(player2, &ent);


		//	Entity entity;
			if (PLAYER::IS_PLAYER_TARGETTING_ANYTHING(player2)) {
				if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(player2, &ent)) {
					if (ENTITY::IS_ENTITY_A_PED(ent)) {
						//Ped theTarget = ent;
						HUD::_UIPROMPT_SET_GROUP(initialize::Prompt_Threaten, HUD::_UIPROMPT_GET_GROUP_ID_FOR_TARGET_ENTITY(ent), 0);
						HUD::_UIPROMPT_SET_ENABLED(initialize::Prompt_Threaten, 1); // _UIPROMPT_SET_ENABLED
						HUD::_UIPROMPT_SET_VISIBLE(initialize::Prompt_Threaten, 1);
					}

				}
			}
			else {
				HUD::_UIPROMPT_SET_ENABLED(initialize::Prompt_Threaten, 0);
				HUD::_UIPROMPT_SET_VISIBLE(initialize::Prompt_Threaten, 0);
			}

		}
		else {
			HUD::_UIPROMPT_SET_ENABLED(initialize::Prompt_Threaten, 0); 
			HUD::_UIPROMPT_SET_VISIBLE(initialize::Prompt_Threaten, 0);
		}
		//unfinished threats system
		if (HUD::_UIPROMPT_IS_JUST_RELEASED(initialize::Prompt_Threaten)) {
			HUD::_UIPROMPT_SET_ENABLED(initialize::Prompt_Threaten, 0);
			HUD::_UIPROMPT_SET_VISIBLE(initialize::Prompt_Threaten, 0);

			if (shop_rep > 0) {
				//shop_rep -= 5;
			}

			////works!!
			//potential voice lines
			//RE_GP_FTH_V1_GREET_THREATEN
			//RE_GP_FTH_V2_GREET_THREATEN
			//RE_GP_MNT1_V1_GREET_THREATEN
			//RE_GP_MTN_V2_GREET_THREATEN

			ScriptedSpeechParams params{ "WITNESS_THREATEN_AGAIN", 0, 1, 0x67F3AB43, 0, true, 1, 1 };
			AUDIO::_PLAY_AMBIENT_SPEECH1(PLAYER::PLAYER_PED_ID(), (Any*)&params);

		}


		HUD::_UIPROMPT_SET_ENABLED(initialize::Prompt_Knock, 0);
		HUD::_UIPROMPT_SET_VISIBLE(initialize::Prompt_Knock, 0);


		//checks if the upgrade is bought and allows to use the knock prompt
		if (Shop::dealer) {
			if (CLOCK::GET_CLOCK_HOURS() > 23 || CLOCK::GET_CLOCK_HOURS() < 6) {
				if (!gunsmithOpen) {
					if (distanceBetween(Shop::gunsmithValKnock, playerPos) < 4.f && Shop::val_gunsmith_bought) {
						HUD::_UIPROMPT_SET_ENABLED(initialize::Prompt_Knock, 1);
						HUD::_UIPROMPT_SET_VISIBLE(initialize::Prompt_Knock, 1);
					}
					if (distanceBetween(Shop::gunsmithDenisKnock, playerPos) < 4.f && Shop::denis_gunsmith_bought) {
						HUD::_UIPROMPT_SET_ENABLED(initialize::Prompt_Knock, 1);
						HUD::_UIPROMPT_SET_VISIBLE(initialize::Prompt_Knock, 1);
					}
					if (distanceBetween(Shop::gunsmithRhoKnock, playerPos) < 4.f && Shop::rho_gunsmith_bought) {
						HUD::_UIPROMPT_SET_ENABLED(initialize::Prompt_Knock, 1);
						HUD::_UIPROMPT_SET_VISIBLE(initialize::Prompt_Knock, 1);
					}
					if (distanceBetween(Shop::gunsmithTumKnock, playerPos) < 4.f && Shop::tum_gunsmith_bought) {
						HUD::_UIPROMPT_SET_ENABLED(initialize::Prompt_Knock, 1);
						HUD::_UIPROMPT_SET_VISIBLE(initialize::Prompt_Knock, 1);
					}
					if (distanceBetween(Shop::gunsmithBurgKnock, playerPos) < 4.f && Shop::burg_gunsmith_bought) {
						HUD::_UIPROMPT_SET_ENABLED(initialize::Prompt_Knock, 1);
						HUD::_UIPROMPT_SET_VISIBLE(initialize::Prompt_Knock, 1);
					}
				}
			}
			else {

				gunsmithOpen = 0;
			}
		}
		//Knocking to open the store after-hours
		if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(initialize::Prompt_Knock)) {

			Vector3 tempAnim;
			int tempHeading;
			if (distanceBetween(Shop::gunsmithValKnock, playerPos) < 4.f) {
				tempAnim = Shop::gunsmithValKnock;
				tempHeading = 180;
			}
			if (distanceBetween(Shop::gunsmithDenisKnock, playerPos) < 4.f) {
				tempAnim = Shop::gunsmithDenisKnock;
				tempHeading = 118;
			}
			if (distanceBetween(Shop::gunsmithRhoKnock, playerPos) < 4.f) {
				tempAnim = Shop::gunsmithRhoKnock;
				tempHeading = 165;
			}
			if (distanceBetween(Shop::gunsmithTumKnock, playerPos) < 4.f) {
				tempAnim = Shop::gunsmithTumKnock;
				tempHeading = 195;
			}
			if (distanceBetween(Shop::gunsmithBurgKnock, playerPos) < 4.f) {
				tempAnim = Shop::gunsmithBurgKnock;
				tempHeading = 252;
			}


			TASK::TASK_START_SCENARIO_AT_POSITION(player, MISC::GET_HASH_KEY("WORLD_PLAYER_KNOCK_DOOR"), tempAnim.x, tempAnim.y, tempAnim.z, tempHeading, 3800, true, false, 0, 0, false);

			gunsmithOpen = 1;
		}
		//opening the door
		if (gunsmithOpen) {
			if (Shop::val_gunsmith_bought) {
				OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(475159788, 0);
			}
			if (Shop::denis_gunsmith_bought) {
				OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(2569382931, 0);
			}
			if (Shop::burg_gunsmith_bought) {
				OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(2135900402, 0);
			}


			if (Shop::tum_gunsmith_bought) {
				OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(1880285656, 0);
			}
			if (Shop::rho_gunsmith_bought) {
				OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(393076024, 0);
			}

		}


		




		WAIT(0);




	}
}

void ScriptMain()
{	
	srand(GetTickCount());
	main();
}
