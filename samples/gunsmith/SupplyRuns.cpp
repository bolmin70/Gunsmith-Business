#include "SupplyRuns.h"
#include "script.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <Windows.h>
#include <shlwapi.h>
#include "Shop.h"
#include "Enemies.h"
#include "Misc.h"
#include "Logic.h"
#include "Toasts.h"
#include "initialize.h"


Vehicle SupplyRuns::wagon;
DeliveryState SupplyRuns::state = DeliveryState::Ambient;
Blip SupplyRuns::wagonBlip;
Blip SupplyRuns::destinationBlip;



int enemies_timer;

int enemy_spawn;

void SupplyRuns::Setup() {
	//wagon spawn
	if (state == DeliveryState::Ambient) {

		state = DeliveryState::InProgress;


		int route_type = rand() % 3;



		if (!STREAMING::HAS_MODEL_LOADED(MISC::GET_HASH_KEY("CHUCKWAGON000X")));
		{
			STREAMING::REQUEST_MODEL(MISC::GET_HASH_KEY("CHUCKWAGON000X"), false);
			WAIT(0);
		}

		if (Shop::val_gunsmith_bought) {
			if (route_type == 0) { //emerald ranch
				wagon = VEHICLE::CREATE_VEHICLE(MISC::GET_HASH_KEY("CHUCKWAGON000X"), 1511.006, 447.293, 89.797, 0, 1, 1, 0, 1);

			}
			if (route_type == 1) {
				wagon = VEHICLE::CREATE_VEHICLE(MISC::GET_HASH_KEY("CHUCKWAGON000X"), -358.555, -344.493, 87.806, 344, 1, 1, 0, 1);

			}
			if (route_type == 2) {
				wagon = VEHICLE::CREATE_VEHICLE(MISC::GET_HASH_KEY("CHUCKWAGON000X"), -1308.506, 383.136, 95.324, 268, 1, 1, 0, 1);

			}
		}

		if (Shop::burg_gunsmith_bought) {
			if (route_type == 0) { //emerald ranch
				wagon = VEHICLE::CREATE_VEHICLE(MISC::GET_HASH_KEY("CHUCKWAGON000X"), 1511.006, 447.293, 89.797, 0, 1, 1, 0, 1);

			}
			if (route_type == 1) { //van horn
				wagon = VEHICLE::CREATE_VEHICLE(MISC::GET_HASH_KEY("CHUCKWAGON000X"), 2963.235, 564.667, 44.413, 5, 1, 1, 0, 1);

			}
			if (route_type == 2) { //stdn
				wagon = VEHICLE::CREATE_VEHICLE(MISC::GET_HASH_KEY("CHUCKWAGON000X"), 2734.754, -1386.240, 46.222, 296, 1, 1, 0, 1);

			}
		}

		if (Shop::denis_gunsmith_bought) {
			if (route_type == 0) { //emerald ranch
				wagon = VEHICLE::CREATE_VEHICLE(MISC::GET_HASH_KEY("CHUCKWAGON000X"), 1511.006, 447.293, 89.797, 180, 1, 1, 0, 1);

			}
			if (route_type == 1) { //rhodes
				wagon = VEHICLE::CREATE_VEHICLE(MISC::GET_HASH_KEY("CHUCKWAGON000X"), 1249.067, -1260.726, 75.064, 238, 1, 1, 0, 1);

			}
			if (route_type == 2) { // van horn
				wagon = VEHICLE::CREATE_VEHICLE(MISC::GET_HASH_KEY("CHUCKWAGON000X"), 2963.235, 564.667, 44.413, 180, 1, 1, 0, 1);

			}
		}


		if (Shop::rho_gunsmith_bought) {
			if (route_type == 0) { //emerald ranch
				wagon = VEHICLE::CREATE_VEHICLE(MISC::GET_HASH_KEY("CHUCKWAGON000X"), 1511.006, 447.293, 89.797, 180, 1, 1, 0, 1);

			}
			if (route_type == 1) { // van horn
				wagon = VEHICLE::CREATE_VEHICLE(MISC::GET_HASH_KEY("CHUCKWAGON000X"), 2963.235, 564.667, 44.413, 180, 1, 1, 0, 1);

			}
			if (route_type == 2) { //stdn
				wagon = VEHICLE::CREATE_VEHICLE(MISC::GET_HASH_KEY("CHUCKWAGON000X"), 2734.754, -1386.240, 46.222, 113, 1, 1, 0, 1);

			}
		}

		if (Shop::tum_gunsmith_bought) {
			if (route_type == 0) { //benedict
				wagon = VEHICLE::CREATE_VEHICLE(MISC::GET_HASH_KEY("CHUCKWAGON000X"), -5251.960, -3468.671, -22.312, 3, 1, 1, 0, 1);

			}
			if (route_type == 1) { //mercer
				wagon = VEHICLE::CREATE_VEHICLE(MISC::GET_HASH_KEY("CHUCKWAGON000X"), -4249.096, -3051.552, -11.367, 81, 1, 1, 0, 1);

			}
			if (route_type == 2) { //arm
				wagon = VEHICLE::CREATE_VEHICLE(MISC::GET_HASH_KEY("CHUCKWAGON000X"), -3729.301, -2650.438, -14.257, 131, 1, 1, 0, 1);

			}
		}



		int i = rand() % 7;
		if (i == 0) {
			PROPSET::_0xD80FAF919A2E56EA(wagon, -1818274469);
		}
		if (i == 1) {
			PROPSET::_0xD80FAF919A2E56EA(wagon, 100192451);
		}
		if (i == 2) {
			PROPSET::_0xD80FAF919A2E56EA(wagon, -1010941253);
		}
		if (i == 3) {
			PROPSET::_0xD80FAF919A2E56EA(wagon, 582515068);
		}
		if (i == 4) {
			PROPSET::_0xD80FAF919A2E56EA(wagon, -488847186);
		}
		if (i == 5) {
			PROPSET::_0xD80FAF919A2E56EA(wagon, 1044628870);
		}
		if (i == 6) {
			PROPSET::_0xD80FAF919A2E56EA(wagon, -447665150);
		}


		Enemies::enemiesSpawned = 0;

		enemy_spawn = 0;

		wagonBlip = MAP::_BLIP_ADD_FOR_ENTITY(0xEC972124, wagon);
		MAP::SET_BLIP_SPRITE(wagonBlip, 0x3C5469D5, false);
		MAP::_SET_BLIP_NAME_FROM_PLAYER_STRING(wagonBlip, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Supply Wagon"));
		MAP::_BLIP_SET_MODIFIER(wagonBlip, MISC::GET_HASH_KEY("BLIP_MODIFIER_PULSE_THREE_TIMES"));


	}


}



void SupplyRuns::InProgress() {
	Ped player = PLAYER::PLAYER_PED_ID();
	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, 0, 0);
	Ped player2 = PLAYER::_GET_PLAYER_PED_2(1);




	//blip creation
	if (PED::IS_PED_SITTING_IN_VEHICLE(player, wagon)) {

		//enemy spawn
		if (!initialize::no_enemies) {
			if (distanceBetween(MAP::GET_BLIP_COORDS(wagonBlip), MAP::GET_BLIP_COORDS(destinationBlip)) > 400 && enemy_spawn < 3) {


				enemies_timer++;

				float i = Shop::shop_rep / 100;
				if (enemies_timer > 25000 * i) {
					int enemy_rand = rand() % 4 + 1;

					if (Shop::shop_rep > 80) {
						enemy_rand--;
					}
					if (Shop::shop_rep > 60) {
						enemy_rand--;
					}


					if (enemy_rand < 0) {
						enemy_rand == 0;
					}


					switch (enemy_rand) {
					case 2:
						enemy_spawn++;
						Enemies::spawnBountyHunters(1);
					case 3:
						enemy_spawn++;
						Enemies::spawnBountyHunters(2);
					case 4:
						enemy_spawn++;
						Enemies::spawnBountyHunters(3);
					};
					enemies_timer = 0;
				}

			}
		}




		if (!MAP::DOES_BLIP_EXIST(destinationBlip)) {

			if (Shop::val_gunsmith_bought) {
				destinationBlip = MAP::_BLIP_ADD_FOR_RADIUS(0x1857A152, Shop::gunsmithVal.x, Shop::gunsmithVal.y, Shop::gunsmithVal.z, 40); 
			}
			if (Shop::burg_gunsmith_bought) {
				destinationBlip = MAP::_BLIP_ADD_FOR_RADIUS(0x1857A152, Shop::gunsmithBurg.x, Shop::gunsmithBurg.y, Shop::gunsmithBurg.z, 40); 
			}
			if (Shop::denis_gunsmith_bought) {
				destinationBlip = MAP::_BLIP_ADD_FOR_RADIUS(0x1857A152, Shop::gunsmithDenis.x, Shop::gunsmithDenis.y, Shop::gunsmithDenis.z, 40); 
			}

			if (Shop::rho_gunsmith_bought) {
				destinationBlip = MAP::_BLIP_ADD_FOR_RADIUS(0x1857A152, Shop::gunsmithRho.x, Shop::gunsmithRho.y, Shop::gunsmithRho.z, 40); 
			}
			if (Shop::tum_gunsmith_bought) {
				destinationBlip = MAP::_BLIP_ADD_FOR_RADIUS(0x1857A152, Shop::gunsmithTum.x, Shop::gunsmithTum.y, Shop::gunsmithTum.z, 40); 
			}


			MAP::_BLIP_SET_MODIFIER(destinationBlip, 0x900A4D0A);

			MAP::SET_BLIP_SPRITE(destinationBlip, 0xDDFBA6AB, false);
			MAP::_SET_BLIP_NAME_FROM_PLAYER_STRING(destinationBlip, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Destination"));
		}
	}
	else {

		MAP::REMOVE_BLIP(&destinationBlip);
	}




	
	

	//Wagon Destroyed
		if (!VEHICLE::IS_VEHICLE_DRIVEABLE(wagon, 1, 1)) {
			

			Misc::RemoveBlip(destinationBlip);
			Misc::RemoveBlip(wagonBlip);

			std::stringstream text;
			text << "Your supplies were ~COLOR_RED~" << "destroyed";

			Misc::showSubtitle(text.str().c_str());

		}
	
		if (PLAYER::IS_PLAYER_DEAD(player2)) {
			Misc::RemoveBlip(destinationBlip);
			Misc::RemoveBlip(wagonBlip);

			std::stringstream text;
			text << "Your supplies were ~COLOR_RED~" << "stolen";



			Misc::showSubtitle(text.str().c_str());

		}


}


void SupplyRuns::Complete() {

	Ped player = PLAYER::PLAYER_PED_ID();
	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, 0, 0);


	///end destination
	if (VEHICLE::IS_VEHICLE_STOPPED(wagon)) {
		if (distanceBetween(MAP::GET_BLIP_COORDS(wagonBlip), MAP::GET_BLIP_COORDS(destinationBlip)) <= 45) {
			CAM::SET_CINEMATIC_MODE_ACTIVE(1);

			TASK::TASK_LEAVE_VEHICLE(player, wagon, 0, 0);

			WAIT(3000);

			CAM::DO_SCREEN_FADE_OUT(10);

			VEHICLE::DELETE_VEHICLE(&wagon);

			WAIT(3000);

			CAM::SET_CINEMATIC_MODE_ACTIVE(0);
			CAM::DO_SCREEN_FADE_IN(1);

			Misc::RemoveBlip(destinationBlip);
			Misc::RemoveBlip(wagonBlip);


			
			Enemies::cleanUp();

			
			std::stringstream text;


			text << "You delievered the ~COLOR_GOLD~" << "supplies";

			Misc::showSubtitle(text.str().c_str());

			for (int i = 0; i < Shop::hardLimit - 1; i++) {
				Shop::stored[i] += Shop::pending[i];
				Shop::pending[i] = 0;
			}

			Logic::resetOrders();

			Toasts::showAdvancedNotification("Gunsmith Business", "Stock is empty", "toasts_mp_generic", "toast_mp_reward_event", 100);


			state = DeliveryState::Ambient;


		}
	}

}



void SupplyRuns::Start() {
	SupplyRuns::Setup();
}

void SupplyRuns::Ambient() {
	
	Ped player2 = PLAYER::_GET_PLAYER_PED_2(1);

	if (state == DeliveryState::InProgress) {
		SupplyRuns::InProgress();


		SupplyRuns::Complete();

	}

	if (PLAYER::IS_PLAYER_DEAD(player2)) {
		Enemies::cleanUp();
	}

}







