#include "Logic.h"
#include "initialize.h"
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
#include "initialize.h"
#include "Toasts.h"

bool noStockToast;

void Logic::Base() {


	if (Shop::val_gunsmith_bought || Shop::denis_gunsmith_bought || Shop::burg_gunsmith_bought || Shop::rho_gunsmith_bought || Shop::tum_gunsmith_bought) {
		Shop::daily_expanses = 10 + Shop::paychecks_sum * Shop::paycheck_rate;

		////////////////////////close shop if stock is 0////////////////////////////////		
		if (Shop::current_stock == 0) {
			Shop::shop_status = 0;
		}



		if (!noStockToast && Shop::current_stock == 0) {
			Toasts::showAdvancedNotification("Gunsmith Business", "Stock is empty", "toasts_mp_generic", "butcher_table_goods", 100);
			noStockToast = 1;
		}

	}


}


float sell_clock = 0;
void Logic::stockSell() {

	//////////////////////////Stock selling/////////////////////////////////
	if (Shop::current_stock > 0 && Shop::shop_status == 1) {


		if (Shop::val_gunsmith_bought) {
			sell_clock += (float)1 * Shop::sell_rate;
		}
		if (Shop::denis_gunsmith_bought) {
			sell_clock += 1.5 * Shop::sell_rate;
		}
		if (Shop::burg_gunsmith_bought) {
			sell_clock += 0.8 * Shop::sell_rate;
		}
		if (Shop::rho_gunsmith_bought) {
			sell_clock += 1.0 * Shop::sell_rate;
		}
		if (Shop::tum_gunsmith_bought) {
			sell_clock += 0.5 * Shop::sell_rate;
		}

		



		if (sell_clock > 60 * initialize::sell_rate_overall) { //50




			sell_clock = 0;

			int sum = 0;
			for (int i; i < Shop::hardLimit - 1; i++) {
				if (Shop::stored[i] > 0) {
					sum++;
				}
			}



			int sell_chance = rand() % 10 + sum;

			if (Shop::shop_rep > 80) {
				sell_chance++;
			}
			if (Shop::shop_rep > 60) {
				sell_chance++;
			}
			if (Shop::shop_rep < 40) {
				sell_chance--;
			}
			if (Shop::shop_rep < 20) {
				sell_chance--;
			}






			int stored_int = 0;
			for (int a = 0; a < Shop::hardLimit - 1; a++) {
				if (Shop::stored[a] > 0) {
					Shop::stored_visual[stored_int] = a;
					stored_int++;
				}
			}

			if (sell_chance >= 9) {
				int sell_random = rand() % stored_int;
				if (Shop::stored[Shop::stored_visual[sell_random]] > 0) {
					Shop::stored[Shop::stored_visual[sell_random]]--;


					for (int i = 0; i < Shop::hardLimit; i++) {
						if (Shop::stored_visual[sell_random] == i) {
							Shop::shop_revenue += (initialize::prices[i] * 1.6) / Shop::sell_rate; //90 base price
						}
					}


				}
			}
			

		}





	}




}


Blip businessBlip;
void Logic::ownershipBlip() {


	if (!INTERIOR::IS_INTERIOR_SCENE()) {

		if (!MAP::DOES_BLIP_EXIST(businessBlip)) {

			//businessBlip = MAP::_BLIP_ADD_FOR_COORD(0x1857A152, -279.102, 781.9, 121.287);



			if (Shop::val_gunsmith_bought) {
				businessBlip = MAP::_BLIP_ADD_FOR_COORD(0x1857A152, -279.102, 781.718, 121.287);

			}

			if (Shop::denis_gunsmith_bought) {
				businessBlip = MAP::_BLIP_ADD_FOR_COORD(0x1857A152, 2714.827, -1286.985, 59.985);

			}
			if (Shop::burg_gunsmith_bought) {

				businessBlip = MAP::_BLIP_ADD_FOR_COORD(0x1857A152, 2941.95, 1320.981, 44.722);

			}

			if (Shop::rho_gunsmith_bought) {

				businessBlip = MAP::_BLIP_ADD_FOR_COORD(0x1857A152, 1325.872, -1322.731, 77.891);

			}
			if (Shop::tum_gunsmith_bought) {

				businessBlip = MAP::_BLIP_ADD_FOR_COORD(0x1857A152, -5506.797, -2967.967, -0.639);

			}


			MAP::_BLIP_SET_MODIFIER(businessBlip, MISC::GET_HASH_KEY("BLIP_MODIFIER_HIDE_HEIGHT_MARKER"));

			

			MAP::SET_BLIP_SPRITE(businessBlip, MISC::GET_HASH_KEY("blip_shop_gunsmith"), false);
			MAP::_SET_BLIP_NAME_FROM_PLAYER_STRING(businessBlip, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Gunsmith Business"));


		}

	}
	else {
		if (MAP::DOES_BLIP_EXIST(businessBlip)) {
			MAP::REMOVE_BLIP(&businessBlip);
		}

		if (Shop::val_gunsmith_bought) {
			if (OBJECT::DOOR_SYSTEM_GET_DOOR_STATE(475159788)) {
			


			}
		}
		if (Shop::denis_gunsmith_bought) {
			if (OBJECT::DOOR_SYSTEM_GET_DOOR_STATE(2569382931)) {

			}
		}
		if (Shop::burg_gunsmith_bought) {
			if (OBJECT::DOOR_SYSTEM_GET_DOOR_STATE(2135900402)) {

			}
		}




	}





}


int day_passed = 0;
void Logic::dailyExpenses() {

	//////////////////////////Daily expenses/honor////////////////////////////
	if (Shop::val_gunsmith_bought || Shop::denis_gunsmith_bought || Shop::burg_gunsmith_bought || Shop::rho_gunsmith_bought || Shop::tum_gunsmith_bought) {
		///daily expenses and other stuff
		if (CLOCK::GET_CLOCK_HOURS() == 0) {
			if (day_passed == 0) {

				if (Shop::shop_status == 1) {
					if (Shop::paycheck_rate_visual == 0) {
						Shop::shop_rep -= 10;
					}
					if (Shop::paycheck_rate_visual == 1) {
						Shop::shop_rep -= 4;
					}
					if (Shop::paycheck_rate_visual == 3) {
						Shop::shop_rep += 4;
					}
					if (Shop::paycheck_rate_visual == 4) {
						Shop::shop_rep += 6;
					}




					if (Shop::sell_rate_visual == 0) {
						Shop::shop_rep += 10;
					}
					if (Shop::paycheck_rate_visual == 1) {
						Shop::shop_rep += 4;
					}
					if (Shop::paycheck_rate_visual == 3) {
						Shop::shop_rep -= 2;
					}
					if (Shop::paycheck_rate_visual == 4) {
						Shop::shop_rep -= 4;
					}


					if (!initialize::no_daily) {
					Shop::shop_revenue -= Shop::daily_expanses; //daily expenses
					}


				}

				day_passed = 1;
			}
		}

		if (CLOCK::GET_CLOCK_HOURS() == 1) {
			day_passed = 0;
		}

	}

}

PropSet tempPropSet;
Vehicle wagon;

Blip wagonBlip;

void Logic::upgrades() {
	Shop::bedroll;
	Shop::wagon;
	Shop::dealer;
	Shop::storage;

	switch (Shop::storage) {
	case 0:
		Shop::maxStock = 20;
		break;
	case 1:
		Shop::maxStock = 40;
		break;
	case 2:
		Shop::maxStock = 60;
		break;
	case 3:
		Shop::maxStock = 100;
		break;
	}



	if (Shop::bedroll) {	
		if (Shop::burg_gunsmith_bought) {
			OBJECT::_ADD_DOOR_TO_SYSTEM_NEW(1335986638, 1, 1, 1, 1, 1, 1);

			OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(1335986638, 0);
		
		}
		if (Shop::tum_gunsmith_bought) {
			OBJECT::_ADD_DOOR_TO_SYSTEM_NEW(2959320055, 1, 1, 1, 1, 1, 1);

			OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(2959320055, 0);
			
		}
	}

	if (Shop::wagon) {
		if (!ENTITY::DOES_ENTITY_EXIST(wagon)) {
			if (Shop::val_gunsmith_bought) {
				wagon = VEHICLE::CREATE_VEHICLE(MISC::GET_HASH_KEY("CHUCKWAGON000X"), -268.450, 769.338, 117.908, 289, 1, 1, 0, 1);
			}
			if (Shop::denis_gunsmith_bought) {
				wagon = VEHICLE::CREATE_VEHICLE(MISC::GET_HASH_KEY("CHUCKWAGON000X"), 2844.322, -1354.925, 44.557, 22, 1, 1, 0, 1);
			}
			if (Shop::burg_gunsmith_bought) {
				wagon = VEHICLE::CREATE_VEHICLE(MISC::GET_HASH_KEY("CHUCKWAGON000X"), 2945.649, 1311.560, 44.485, 72, 1, 1, 0, 1);
			}
			if (Shop::rho_gunsmith_bought) {
				wagon = VEHICLE::CREATE_VEHICLE(MISC::GET_HASH_KEY("CHUCKWAGON000X"), 1336.578, -1325.929, 77.125, 347, 1, 1, 0, 1);
			}
			if (Shop::tum_gunsmith_bought) {
				wagon = VEHICLE::CREATE_VEHICLE(MISC::GET_HASH_KEY("CHUCKWAGON000X"), -5514.262, -2979.290, -1.574, 285, 1, 1, 0, 1);
			}
			
		}

		if (VEHICLE::IS_VEHICLE_DRIVEABLE(wagon, 1, 1)) {
			if (!MAP::DOES_BLIP_EXIST(wagonBlip)) {
				wagonBlip = MAP::_BLIP_ADD_FOR_ENTITY(0xEC972124, wagon);
				MAP::SET_BLIP_SPRITE(wagonBlip, 0x3C5469D5, false);
				MAP::_SET_BLIP_NAME_FROM_PLAYER_STRING(wagonBlip, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Private Wagon"));
				MAP::_BLIP_SET_MODIFIER(wagonBlip, MISC::GET_HASH_KEY("BLIP_MODIFIER_PULSE_THREE_TIMES"));

			}
		}
		else {
			Misc::RemoveBlip(wagonBlip);
		}

	}

		

}



void Logic::gunsmithController() {
	Base();

	stockSell();

	ownershipBlip();

	dailyExpenses();

	upgrades();


}


void Logic::resetOrders() {

	for (int i = 0; i < Shop::suppliersLimit; i++) {
		Shop::suppliersOrder[i] = 0;
	}

}