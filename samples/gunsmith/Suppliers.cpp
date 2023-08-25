#include "Suppliers.h"
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
#include "SupplyRuns.h"



SupplyRuns baseSuppliers::supplyRun;

bool selected;


void baseSuppliers::back(int supplierIndex) {
	if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Back) && !selected)
	{
	
		AUDIO::PLAY_SOUND_FRONTEND("BACK", "HUD_SHOP_SOUNDSET", 1, 0);

		Menu::menuState = MenuState::Suppliers;
		MenuControls::current_cell = supplierIndex;

		if (SupplyRuns::state == DeliveryState::Ambient) {
			for (int i = 0; i < Shop::hardLimit - 1; i++) {
				Shop::pending[i] = 0;
			}
		}

	}


}

void baseSuppliers::name(int supplierIndex) {
	Misc::drawSprite("generic_textures", "menu_header_1a", menuX + 0.02, menuY, 0.2, 0.1f, 0, 255, 255, 255, 250);

	const char* supplierName;
	switch (supplierIndex) {
	case 0:
		supplierName = "Lancaster";
		break;
	case 1:
		supplierName = "Buck";
		break;
	case 2:
		supplierName = "Muhlberg";
		break;
	case 3:
		supplierName = "Peeters & Janssens";
		break;
	case 4:
		supplierName = "Hutton & Baird";
		break;
	case 5:
		supplierName = "D.D. packenbush";
		break;
	case 6:
		supplierName = "Litchfield";
		break;

	};


}




float selectX;

float selectY;

void baseSuppliers::controls(int x, int y) {
	if (!selected) {
		selectX = 0.1f * MenuControls::menu_controls_alt(x);

		if (SupplyRuns::state == DeliveryState::Ambient) { //if there is no supply run in progress
			selectY = -0.013f + (0.15f * MenuControls::menu_controls(y));
		}
		else {
			selectY = -0.013f + (0.15f * MenuControls::menu_controls(y - 1));
		}

		if (MenuControls::current_cell == 1 && MenuControls::current_cell_x == 2) {
			MenuControls::current_cell_x = 0;
			selectX = 0.1f * 0;
		}

		if (MenuControls::current_cell == 2 && MenuControls::current_cell_x == 2) {
			MenuControls::current_cell_x = 0;
			selectX = 0.1f * 0;
		}

	}
	else {
		selectX = 0.1f * MenuControls::current_cell_x;

		selectY = -0.013f + (0.15f * MenuControls::current_cell);
	}
}

void baseSuppliers::controls(int x, int y, bool alt) {
	if (!selected) {
		selectX = 0.1f * MenuControls::menu_controls_alt(x);

		if (SupplyRuns::state == DeliveryState::Ambient) { //if there is no supply run in progress
			selectY = -0.013f + (0.15f * MenuControls::menu_controls(y));
		}
		else {
			selectY = -0.013f + (0.15f * MenuControls::menu_controls(y - 1));
		}

		if (MenuControls::current_cell == 1 && MenuControls::current_cell_x == 1) {
			MenuControls::current_cell_x = 0;
			selectX = 0;
		}
		if (MenuControls::current_cell == 1 && MenuControls::current_cell_x == 2) {
			MenuControls::current_cell_x = 0;
			selectX = 0;
		}


		if (MenuControls::current_cell == 2 && MenuControls::current_cell_x == 2) {
			MenuControls::current_cell_x = 0;
			selectX = 0.1f * 0;
		}

	}
	else {
		selectX = 0.1f * MenuControls::current_cell_x;

		selectY = -0.013f + (0.15f * MenuControls::current_cell);
	}
}




int total;

void baseSuppliers::totalPrice(int start, int iterations) {
	total = 0;


	Shop::totalStock = Shop::current_stock;

	iterations = start + iterations;
	for (int i = start; i < iterations; i++) {
		total = total + (Shop::pending[i] * initialize::prices[i]);
		Shop::totalStock = Shop::totalStock + Shop::pending[i];
	}



}

void baseSuppliers::selectBack() {


	if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Back) && selected) {

		
		AUDIO::PLAY_SOUND_FRONTEND("BACK", "HUD_SHOP_SOUNDSET", 1, 0);

		selected = 0;


	}

	select_clock++;
	if (select_clock > 10) {

		if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Select) && SupplyRuns::state == DeliveryState::Ambient) {
			
			AUDIO::PLAY_SOUND_FRONTEND("INFO", "HUD_SHOP_SOUNDSET", 1, 0);


			selected = !selected;
			select_clock = 0;
		}
	}


}



void suppliersCleanUp() {

	Ped player = PLAYER::PLAYER_PED_ID();

	AUDIO::PLAY_SOUND_FRONTEND("INFO", "HUD_SHOP_SOUNDSET", 1, 0);


	TASK::CLEAR_PED_TASKS(player, 1, 1);
	WEAPON::SET_CURRENT_PED_WEAPON(player, MISC::GET_HASH_KEY("weapon_unarmed"), 1, 0, 0, 0);

	HUD::_DISPLAY_HUD_COMPONENT(474191950);

	CAM::RENDER_SCRIPT_CAMS(0, 1, 500, 1, 0, 0);


}

void baseSuppliers::orderButton(int y, int supplierIndex) {
	Ped player = PLAYER::PLAYER_PED_ID();


	if (SupplyRuns::state == DeliveryState::Ambient) {

		if (total > 0) {
			Misc::drawText("Order", menuX + 0.4, menuY + 0.833f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}
		else {
			Misc::drawText("Order", menuX + 0.4, menuY + 0.833f, 60, 60, 60, 255, 1, 0.5f, 0.5f);
		}

	}
	else {

		HUD::_UIPROMPT_SET_ENABLED(Prompt_Select, 0); 
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Select, 0);

		if (Shop::suppliersOrder[supplierIndex]) {
			Misc::drawText("Order preview", menuX + 0.4, menuY + 0.833f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}
		else {
			Misc::drawText("Another order in progress", menuX + 0.4, menuY + 0.833f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}
	}


	Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3, menuY + 0.8f, 0.2, 0.1f, 0, 30, 30, 30, 250);



	if (MenuControls::current_cell == y) {

		HUD::_UIPROMPT_SET_ENABLED(Prompt_Order, 0);

		if (total > 0) {
			if (MONEY::_MONEY_GET_CASH_BALANCE() >= (total * 100) || Shop::shop_revenue >= total) {
				HUD::_UIPROMPT_SET_ENABLED(Prompt_Order, 1); 
			}
		}



		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Order, 1); 

		HUD::_UIPROMPT_SET_ENABLED(Prompt_Select, 0); 
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Select, 0);
	}
	else {
		HUD::_UIPROMPT_SET_ENABLED(Prompt_Order, 0); 
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Order, 0);

		HUD::_UIPROMPT_SET_ENABLED(Prompt_Select, 1); 
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Select, 1);

	}


	if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(Prompt_Order)) {
	

		Shop::suppliersOrder[supplierIndex] = 1;

		supplyRun.Start();


		if (Shop::shop_revenue >= total) {
			Shop::shop_revenue -= total;
		}
		else {
			MONEY::_MONEY_DECREMENT_CASH_BALANCE(total * 100);
		}

		Menu::menuState = MenuState::Off;



	
		suppliersCleanUp();

	}


}

void baseSuppliers::highlighter(int y) {
	if (MenuControls::current_cell == y) {
		selectY = -0.013f + (0.1f * 7);

		Misc::drawSprite("menu_textures", "crafting_highlight_l", menuX + 0.294, menuY + 0.123f + selectY, 0.0135, 0.082f, 0, 255, 0, 0, 250);
		Misc::drawSprite("menu_textures", "crafting_highlight_r", menuX + 0.492, menuY + 0.123f + selectY, 0.0135, 0.082f, 0, 255, 0, 0, 250);
		Misc::drawSprite("menu_textures", "crafting_highlight_b", menuX + 0.3, menuY + 0.1f + selectY, 0.2, 0.03f, 0, 255, 0, 0, 250);
		Misc::drawSprite("menu_textures", "crafting_highlight_t", menuX + 0.3, menuY + 0.2f + selectY, 0.2, 0.03f, 0, 255, 0, 0, 250);

	}
	else {
		if (selected) {

			if (!MenuControls::no_left) {
				Misc::drawSprite("menu_textures", "crafting_highlight_larrow", menuX + 0.294 + selectX - 0.03, menuY + 0.123f + selectY, 0.0135, 0.122f, 0, 255, 0, 0, 250);
			}
			else {
				Misc::drawSprite("menu_textures", "crafting_highlight_l", menuX + 0.294 + selectX - 0.03, menuY + 0.123f + selectY, 0.0135, 0.122f, 0, 255, 0, 0, 250);
			}
			



			if (!MenuControls::no_right) {
				Misc::drawSprite("menu_textures", "crafting_highlight_rarrow", menuX + 0.375 + selectX - 0.03, menuY + 0.123f + selectY, 0.0135, 0.122f, 0, 255, 0, 0, 250);
			}
			else {
				Misc::drawSprite("menu_textures", "crafting_highlight_r", menuX + 0.375 + selectX - 0.03, menuY + 0.123f + selectY, 0.0135, 0.122f, 0, 255, 0, 0, 250);
			}



		}
		else {

			Misc::drawSprite("menu_textures", "crafting_highlight_l", menuX + 0.294 + selectX - 0.03, menuY + 0.123f + selectY, 0.0135, 0.122f, 0, 255, 0, 0, 250);
			Misc::drawSprite("menu_textures", "crafting_highlight_r", menuX + 0.375 + selectX - 0.03, menuY + 0.123f + selectY, 0.0135, 0.122f, 0, 255, 0, 0, 250);

		}

		Misc::drawSprite("menu_textures", "crafting_highlight_b", menuX + 0.3 + selectX - 0.03, menuY + 0.1f + selectY, 0.082f, 0.03f, 0, 255, 0, 0, 250);
		Misc::drawSprite("menu_textures", "crafting_highlight_t", menuX + 0.3 + selectX - 0.03, menuY + 0.235f + selectY, 0.082f, 0.03f, 0, 255, 0, 0, 250);

	}

}

void baseSuppliers::sumText() {
	if (Shop::totalStock == Shop::maxStock) {
		Misc::drawTextSmall("Stock limit reached", menuX + 0.4f, menuY + 0.74f, 255, 0, 30, 200, 1, 0.25f, 0.4f);
	}

	Misc::drawTextSmall("Total", menuX + 0.33f, menuY + 0.77f, 255, 255, 255, 200, 1, 0.25f, 0.4f);

	std::stringstream price_sumss;
	price_sumss << "$";
	price_sumss << total;
	Misc::drawTextSmall(price_sumss.str().c_str(), menuX + 0.47f, menuY + 0.77f, 255, 255, 255, 200, 1, 0.25f, 0.4f);

}

char* weapon_name;
char* desc;


void flavorText(int weapon_num) {


	switch (weapon_num) {
	case 0:
		weapon_name = "Lancaster Repeater";
		desc = "The gun that won both the West\nand South from neer-do-wells.\nWe have received letters from\nthousands of satisfied purchasers\nwho say that the superior\nfirepower of the Lancaster\nis satisfactory in every way.";
		Misc::drawSprite("cmpndm_weapons", "cmpndm_lancaster_repeater_photo", baseSuppliers::menuX - 0.09f + 0.11f, baseSuppliers::menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		break;
	case 1:
		weapon_name = "Springfield Rifle";
		desc = "The rifle that modernized fire power\nis the Lancaster Springfield, the\nperfect breech-loading rifle.\nSpend ateast six months and\npractice target shooting every day\nand we guarantee you will become\ntrue of aim.";
		Misc::drawSprite("cmpndm_weapons", "cmpndm_springfield_rifle_photo", baseSuppliers::menuX - 0.09f + 0.11f, baseSuppliers::menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		break;
	case 2:
		weapon_name = "Pump Action Shotgun";
		desc = "For the man who has more tongue\nthan sense, the mere sound of the\nLancaster Pump-Action Shotgun\nloading a shell into the chamber\nshould have him shut his mouth\nright quick.";
		Misc::drawSprite("cmpndm_weapons", "cmpndm_pump_action_shotgun_photo", baseSuppliers::menuX - 0.09f + 0.11f, baseSuppliers::menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		break;
	case 3:
		weapon_name = "Varmint Rifle";
		desc = "It is absolutely guaranteed to be the\nbest make of this style rifle on the\nmarket. Shoot it once and you will\nsee that it brings down varmints with\na splendid wallop unequalled by other\nlow calibre rifles.";
		Misc::drawSprite("cmpndm_weapons", "cmpndm_lancaster_varmint_rifle_photo", baseSuppliers::menuX - 0.09f + 0.11f, baseSuppliers::menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		break;
	case 4:
		weapon_name = "Repeating Shotgun";
		desc = "An unrivaled marbel of power.\nThis Lancaster Repeating Shotgun\nis nationally recognized as the\nstrongest shooter in the market.";
		Misc::drawSprite("cmpndm_weapons", "cmpndm_repeating_shotgun_photo", baseSuppliers::menuX - 0.09f + 0.11f, baseSuppliers::menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		break;
	case 5:
		weapon_name = "Gun Oil";
		desc = "Gun oil. Preserves all metals from\nrust or tarnish. Will not corrode\nor become rancid. Keeps all\nfirearms clean and neat.";
		Misc::drawSprite("pm_tiles_saves", "saves_newgame", baseSuppliers::menuX - 0.09f + 0.11f, baseSuppliers::menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		break;
	case 6:
		weapon_name = "Upgraded Gun Belt";
		desc = "The Lancaster blackened oiled\ngenuine leather pistol belt featuring\na polished steel roller buckle. Belt 3\ninches wide, soft and pliable\nand will not crack.";
		Misc::drawSprite("pm_tiles_abilities", "abilitycard_loadouts", baseSuppliers::menuX - 0.09f + 0.11f, baseSuppliers::menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		break;

	case 7:
		weapon_name = "Cattleman Revolver";
		desc = "There is no better revolver to have\nat your side when heading west\ninto the land of milk and honey.\nFan the hammer in quick succession\nand you will see how quickly this\nrevolver can be unloaded to the\ndismayed surprise of others.";
		Misc::drawSprite("cmpndm_weapons", "cmpndm_cattleman_revolver_photo", baseSuppliers::menuX - 0.09f + 0.11f, baseSuppliers::menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		break;
		
	case 8:
		weapon_name = "Upgraded Bandolier";
		desc = "Bucks genuine tanned leather\nlongarm Bandolier. We have sold\na great many of these to men who\nfancy displaying volatile ammunition\non their chest.";
		Misc::drawSprite("help_combat", "combat_accessories", baseSuppliers::menuX - 0.09f + 0.11f, baseSuppliers::menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		break;

	case 9:
		weapon_name = "Carbine Repeater";
		desc = "If you are in the market for a\nrepeating rifle then you can do no\nwrong in exchanging your hard\nearned money for the Carbine\nRepeater from Buck";
		Misc::drawSprite("cmpndm_weapons", "cmpndm_repeater_carbine_photo", baseSuppliers::menuX - 0.09f + 0.11f, baseSuppliers::menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		break;


	case 10:
		weapon_name = "Mauser Pistol";
		desc = "The finest self loading automatic\npistol. It has the dandiest of designs,\nhaving originated from a couple of\npassionate brothers in Europe who\nhave spent their lifes work fashioning\ningenious nways to propel lead at\nhigh rates of speed.";
		Misc::drawSprite("cmpndm_weapons", "cmpndm_mauser_pistol_photo", baseSuppliers::menuX - 0.09f + 0.11f, baseSuppliers::menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		break;

	case 11:
		weapon_name = "Semi-Auto Shotgun";
		desc = "Unsurpassed penetration again and\nagain. The Brun et Fabre Semi-Automatic\nShotgun is the highest grade, the most\nperfect and best priced semi-auto shotgun\nmade in the world. One of the most\nattractive fancy firearms on the market.";
		Misc::drawSprite("cmpndm_weapons", "cmpndm_semi_auto_shotgun_photo", baseSuppliers::menuX - 0.09f + 0.11f, baseSuppliers::menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		break;


	case 12:
		weapon_name = "Sawed-Off Shotgun";
		desc = "A lightweight shotgun that is easy\nto use and conceal, as many\nsituations in modern times require.\nThe safety and durability and, above\nall, superior penetration of this fine\nshotgun cannot be matched.";
		Misc::drawSprite("cmpndm_weapons", "cmpndm_sawed_off_shotgun_photo", baseSuppliers::menuX - 0.09f + 0.11f, baseSuppliers::menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		break;

	case 13:
		weapon_name = "Semi-Automatic Pistol";
		desc = "This is strictly a high grade gun\nmeant for solving situations in a\nrapid fire manner. Too much\ncannot be said for the shooting\nqualities of this wonderful pistol.\nFire one round and you will see\nthe recoil of this fine weapon is\na testament to its power.";
		Misc::drawSprite("cmpndm_weapons", "cmpndm_semi_automatic_pistol_photo", baseSuppliers::menuX - 0.09f + 0.11f, baseSuppliers::menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		break;

	case 14:
		weapon_name = "M1899 Pistol";
		desc = "The perfect pistol to assist those\nwhose time has come to go home\nto God. A pure joy to shoot, you will\nthink you can shoot the stars out of\nthe sky. The finest machined parts\nby Peeters & Janssens";
		Misc::drawSprite("cmpndm_weapons_tu", "cmpndm_pistol_m1899_photo", baseSuppliers::menuX - 0.09f + 0.11f, baseSuppliers::menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		break;



	case 15:
		weapon_name = "Volcanic Pistol";
		desc = "This pistol is the finest creation from\nHutton & Baird direct from the factory\nvia our warehouse. Point in the direction\nyou intend, shout an unforgettable\nexpletive, and pull the trigger of the\nHutton & Baird Volcanic Pistol.";
		Misc::drawSprite("cmpndm_weapons", "cmpndm_volcanic_pistol_photo", baseSuppliers::menuX - 0.09f + 0.11f, baseSuppliers::menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		break;
	
	case 16:
		weapon_name = "Schofield Revolver";
		desc = "Every man prefers a revolver or a\ncompanion that is strictly first\nclass in every respect. While second\nor third class can often suffice in\ndesperation or the dark of night, no\ntruer model of revolver exists.";
		Misc::drawSprite("cmpndm_weapons", "cmpndm_schofield_revolver_photo", baseSuppliers::menuX - 0.09f + 0.11f, baseSuppliers::menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		break;

	case 17:
		weapon_name = "Bolt-Action Rifle";
		desc = "Look downrange through the sights.\nFeel the gun stock. Friend, there is\nno better Bolt Action Rifle in any\nstore or outfitter available than the\nB.D & Co. Rest assured that it will not\nhesitate to fill the recipient full of\nequal amounts of lead and dread.";
		Misc::drawSprite("cmpndm_weapons", "cmpndm_bolt_action_rifle_photo", baseSuppliers::menuX - 0.09f + 0.11f, baseSuppliers::menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		break;

	case 18:
		weapon_name = "Evans Repeater";
		desc = "The new and improved Evans\nRepeater is the highest grade repeating\nrifle ever turned out by B.D. and Co. It\nis well known that this fine mechanized\nfirearm requires little academic aptitude.\nSimply shout a sobriquet, pull the trigger\nand repeat.";
		Misc::drawSprite("cmpndm_weapons_tu", "cmpndm_repeater_evans_photo", baseSuppliers::menuX - 0.09f + 0.11f, baseSuppliers::menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		break;




	case 19:
		weapon_name = "Double-Action";
		desc = "You can find no handsomer, up to\ndate design than the D.D Packenbush\nDouble-Action Revolver. It has the best\naction of any revolver for the price, and\nwhen you order one you will be the\njudge, jury and, very likely, the executioner.";
		Misc::drawSprite("cmpndm_weapons", "cmpndm_double_action_revolver_photo", baseSuppliers::menuX - 0.09f + 0.11f, baseSuppliers::menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		break;


	case 20:
		weapon_name = "Double-Barreled";
		desc = "Truly it is the finest shotgun available\ntoday. When you go in a party across\nthe mountains, plains and passes of\nthis great land, there is only one thing\nthat can guarantee your safety, and that\nis the Double-Barreled Shotgun from\nD.D. Packenbush.";
		Misc::drawSprite("cmpndm_weapons", "cmpndm_double_barreled_shotgun_photo", baseSuppliers::menuX - 0.09f + 0.11f, baseSuppliers::menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		break;

	case 21:
		weapon_name = "Carcano Rifle";
		desc = "Rifle of choice for both holy and\nunholy ambition. It has been said\nthat discretion is the better part of\nvalor, and no more valor is exhibited\nthan that of a man hiding behind a\nrock and taking out his enemies\nwhen they least suspect it.";
		Misc::drawSprite("cmpndm_weapons", "cmpndm_carcano_rifle_photo", baseSuppliers::menuX - 0.09f + 0.11f, baseSuppliers::menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		break;




	case 22:
		weapon_name = "Rolling Block Rifle";
		desc = "Do you enjoy sharpshooting? For\nthose that believe close quarters\ncombat is for the foolhardy and\nindeed short lived, then the Litchfield\nRolling Block Rifle is a wonder to behold.";
		Misc::drawSprite("cmpndm_weapons", "cmpndm_rolling_block_photo", baseSuppliers::menuX - 0.09f + 0.11f, baseSuppliers::menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		break;

	case 23:
		weapon_name = "Litchfield Repeater";
		desc = "Imagine a rifle that you could spend\nhours lovingly cleaning on a Sunday\nafternoon, then load with cartridges\nand shoot all week long without\nhaving to reload.";
		Misc::drawSprite("cmpndm_weapons", "cmpndm_litchfield_repeater_photo", baseSuppliers::menuX - 0.09f + 0.11f, baseSuppliers::menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		break;

	case 24:
		weapon_name = "Lemat Revolver";
		desc = "This unique revolver, with its second\nbarrel for buck shot, is so strong and\nso perfect in manufacture, we have\nyet to record one that has become\nshaky or loose. Fire fifty thousand\nrounds with flawless accuracy and\nyou will see";
		Misc::drawSprite("cmpndm_weapons_tu", "cmpndm_revolver_lemat_photo", baseSuppliers::menuX - 0.09f + 0.11f, baseSuppliers::menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		break;




	case 25:
		weapon_name = "Navy Revolver";
		desc = "Behold this .36 caliber single action\nrevolver capable of sending a ball of\nhot lead at an astounding velocity of\n1,000 feet per second.";
		Misc::drawSprite("cmpndm_weapons_tu", "cmpndm_navy_revolver_photo", baseSuppliers::menuX - 0.09f + 0.11f, baseSuppliers::menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		break;

	case 26:
		weapon_name = "Elephant Rifle";
		desc = "The Elephant Gun Rifle from Muhlberg\nis a marvel of manufacturing and has\nbeen likened to holding a cannon. Fire\nit and see if you are still standing or\nable to hear anything other than\nringing for several days.";
		Misc::drawSprite("cmpndm_weapons_tu", "cmpndm_elephant_rifle_photo", baseSuppliers::menuX - 0.09f + 0.11f, baseSuppliers::menuY + 0.15f, 0.2f, 0.2f, 0, 255, 255, 255, 250);
		break;



	};


	Misc::drawText(weapon_name, baseSuppliers::menuX + 0.12f, baseSuppliers::menuY + 0.03f, 255, 255, 255, 255, 1, 0.6f, 0.6f);


	Misc::drawTextSmall(desc, baseSuppliers::menuX + 0.015f, baseSuppliers::menuY + 0.37f, 255, 255, 255, 255, 0, 0.25f, 0.4f);



}

void baseSuppliers::lancasterPage(int x, int y, int supplierIndex) {
	Ped player = PLAYER::PLAYER_PED_ID();

	//lancaster
	if (Menu::menuState == MenuState::Lancaster) {


		//if the item is not selected you can move 
		back(supplierIndex);

		name(supplierIndex);

		controls(x, y);

		totalPrice(0, 7);


		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 - 0.03, menuY + 0.1f, 0.08f, 0.135f, 0, 30, 30, 30, 250);
		Misc::drawSprite("inventory_items", "weapon_repeater_lancaster", menuX + 0.3 - 0.03, menuY + 0.115, 0.087f, 0.11f, 0, 255, 255, 255, 255);

		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 - 0.03, menuY + 0.25f, 0.08f, 0.135f, 0, 30, 30, 30, 250);
		Misc::drawSprite("inventory_items", "weapon_shotgun_pump", menuX + 0.382 - 0.03, menuY + 0.265, -0.087f, 0.11f, 0, 255, 255, 255, 255);

		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 - 0.03, menuY + 0.4f, 0.08f, 0.135f, 0, 30, 30, 30, 250);
		Misc::drawSprite("inventory_items", "weapon_shotgun_repeating", menuX + 0.382 - 0.03, menuY + 0.415, -0.087f, 0.11f, 0, 255, 255, 255, 255);




		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.4 - 0.03, menuY + 0.1f, 0.08f, 0.135f, 0, 30, 30, 30, 250);
		Misc::drawSprite("inventory_items", "weapon_rifle_springfield", menuX + 0.4 - 0.03, menuY + 0.115, 0.087f, 0.11f, 0, 255, 255, 255, 255);

		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.4 - 0.03, menuY + 0.25f, 0.08f, 0.135f, 0, 30, 30, 30, 250);
		Misc::drawSprite("inventory_items", "weapon_rifle_varmint", menuX + 0.4 - 0.03, menuY + 0.265, 0.087f, 0.11f, 0, 255, 255, 255, 255);

		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.4 - 0.03, menuY + 0.4f, 0.08f, 0.135f, 0, 30, 30, 30, 250);
		Misc::drawSprite("inventory_items", "kit_gun_oil", menuX + 0.472 - 0.03, menuY + 0.42, -0.067f, 0.091f, 0, 255, 255, 255, 255);




		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.5 - 0.03, menuY + 0.1f, 0.08f, 0.135f, 0, 30, 30, 30, 250);
		Misc::drawSprite("inventory_items", "clothing_generic_gunbelt", menuX + 0.505 - 0.03, menuY + 0.125, 0.07f, 0.09f, 0, 255, 255, 255, 255);

		

		






		if (Shop::pending[0] > 0) {
			std::stringstream text;
			text << Shop::pending[0];
			Misc::drawText(text.str().c_str(), menuX + 0.37 - 0.03, menuY + 0.198f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

			std::stringstream pricess;
			pricess << "$";
			pricess << Shop::pending[0] * initialize::lancaster_repeater_price;//lancaster_repeater_price
			Misc::drawText(pricess.str().c_str(), menuX + 0.325 - 0.03, menuY + 0.11f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

		}

		if (Shop::pending[1] > 0) {
			std::stringstream text;
			text << Shop::pending[1];
			Misc::drawText(text.str().c_str(), menuX + 0.37 - 0.03, menuY + 0.198f + 0.15f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

			std::stringstream pricess;
			pricess << "$";
			pricess << Shop::pending[1] * initialize::lancaster_pump_shotgun_price;//lancaster_pump_shotgun_price
			Misc::drawText(pricess.str().c_str(), menuX + 0.325 - 0.03, menuY + 0.11f + 0.15f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}

		if (Shop::pending[2] > 0) {
			std::stringstream text;
			text << Shop::pending[2];
			Misc::drawText(text.str().c_str(), menuX + 0.37 - 0.03, menuY + 0.198f + 0.3f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

			std::stringstream pricess;
			pricess << "$";
			pricess << Shop::pending[2] * initialize::lancaster_repeating_shotgun_price;//lancaster_repeating_shotgun_price
			Misc::drawText(pricess.str().c_str(), menuX + 0.325 - 0.03, menuY + 0.11f + 0.3f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}

		if (Shop::pending[3] > 0) {
			std::stringstream text;
			text << Shop::pending[3];
			Misc::drawText(text.str().c_str(), menuX + 0.37 + 0.1 - 0.03, menuY + 0.198f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

			std::stringstream pricess;
			pricess << "$";
			pricess << Shop::pending[3] * initialize::lancaster_rifle_price;//lancaster_rifle_price
			Misc::drawText(pricess.str().c_str(), menuX + 0.325 + 0.1 - 0.03, menuY + 0.11f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}

		if (Shop::pending[4] > 0) {
			std::stringstream text;
			text << Shop::pending[4];
			Misc::drawText(text.str().c_str(), menuX + 0.37 + 0.1f - 0.03, menuY + 0.198f + 0.15, 255, 255, 255, 255, 1, 0.5f, 0.5f);

			std::stringstream pricess;
			pricess << "$";
			pricess << Shop::pending[4] * initialize::lancaster_varmint_price;//lancaster_varmint_price
			Misc::drawText(pricess.str().c_str(), menuX + 0.325 + 0.1f - 0.03, menuY + 0.11f + 0.15f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}

		if (Shop::pending[5] > 0) {
			std::stringstream text;
			text << Shop::pending[5];
			Misc::drawText(text.str().c_str(), menuX + 0.37 + 0.1f - 0.03, menuY + 0.198f + 0.3f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

			std::stringstream pricess;
			pricess << "$";
			pricess << Shop::pending[5] * initialize::lancaster_oil_price;//lancaster_oil_price
			Misc::drawText(pricess.str().c_str(), menuX + 0.325 + 0.1f - 0.03, menuY + 0.11f + 0.3f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}

		if (Shop::pending[6] > 0) {
			std::stringstream text;
			text << Shop::pending[6];
			Misc::drawText(text.str().c_str(), menuX + 0.37 + 0.2f - 0.03, menuY + 0.198f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

			std::stringstream pricess;
			pricess << "$";
			pricess << Shop::pending[6] * initialize::lancaster_gunbelt_price;//lancaster_gunbelt_price
			Misc::drawText(pricess.str().c_str(), menuX + 0.325 + 0.2f - 0.03, menuY + 0.11f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}



		if (selected) {
			if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 0) {
				flavorText(0);
				MenuControls::menu_controls_amount(99, Shop::pending[0]);
			}
			if (MenuControls::current_cell == 1 && MenuControls::current_cell_x == 0) {
				MenuControls::menu_controls_amount(99, Shop::pending[1]);
			}
			if (MenuControls::current_cell == 2 && MenuControls::current_cell_x == 0) {
				MenuControls::menu_controls_amount(99, Shop::pending[2]);
			}
			if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 1) {
				MenuControls::menu_controls_amount(99, Shop::pending[3]);
			}
			if (MenuControls::current_cell == 1 && MenuControls::current_cell_x == 1) {
				MenuControls::menu_controls_amount(99, Shop::pending[4]);
			}
			if (MenuControls::current_cell == 2 && MenuControls::current_cell_x == 1) {
				MenuControls::menu_controls_amount(99, Shop::pending[5]);
			}
			if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 2) {
				MenuControls::menu_controls_amount(99, Shop::pending[6]);
			}
		}


		if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 0) {
			flavorText(0);
		}
		if (MenuControls::current_cell == 1 && MenuControls::current_cell_x == 0) {
			flavorText(2);
		}
		if (MenuControls::current_cell == 2 && MenuControls::current_cell_x == 0) {
			flavorText(4);
		}
		if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 1) {
			flavorText(1);
		}
		if (MenuControls::current_cell == 1 && MenuControls::current_cell_x == 1) {
			flavorText(3);
		}
		if (MenuControls::current_cell == 2 && MenuControls::current_cell_x == 1) {
			flavorText(5);
		}
		if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 2) {
			flavorText(6);
		}







		selectBack();


		orderButton(y, supplierIndex);

		highlighter(y);


		float current_rep = 0.23f;

		sumText();

	}

}


void baseSuppliers::buckPage(int x, int y, int supplierIndex) {
	Ped player = PLAYER::PLAYER_PED_ID();

	if (Menu::menuState == MenuState::Buck) {


		//if the item is not selected you can move 
		back(supplierIndex);

		name(supplierIndex);

		controls(x, y);

		totalPrice(7, 3);


		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 - 0.03, menuY + 0.1f, 0.08f, 0.135f, 0, 30, 30, 30, 250);
		Misc::drawSprite("inventory_items", "weapon_repeater_carbine", menuX + 0.3 - 0.03, menuY + 0.115, 0.087f, 0.11f, 0, 255, 255, 255, 255);

		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.4 - 0.03, menuY + 0.1f, 0.08f, 0.135f, 0, 30, 30, 30, 250);
		Misc::drawSprite("inventory_items", "upgrade_bandolier", menuX + 0.405 - 0.03, menuY + 0.125, 0.07f, 0.09f, -2, 255, 255, 255, 255);

		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.5 - 0.03, menuY + 0.1f, 0.08f, 0.135f, 0, 30, 30, 30, 250);
		Misc::drawSprite("inventory_items", "weapon_revolver_cattleman", menuX + 0.575 - 0.03, menuY + 0.115, -0.075f, 0.11f, 0, 255, 255, 255, 255);





		if (Shop::pending[7] > 0) {
			std::stringstream text;
			text << Shop::pending[7];
			Misc::drawText(text.str().c_str(), menuX + 0.37 - 0.03, menuY + 0.198f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

			std::stringstream pricess;
			pricess << "$";
			pricess << Shop::pending[7] * initialize::buck_repeater_price;//lancaster_repeater_price
			Misc::drawText(pricess.str().c_str(), menuX + 0.325 - 0.03, menuY + 0.11f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

		}

		if (Shop::pending[8] > 0) {
			std::stringstream text;
			text << Shop::pending[8];
			Misc::drawText(text.str().c_str(), menuX + 0.37 + 0.1 - 0.03, menuY + 0.198f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

			std::stringstream pricess;
			pricess << "$";
			pricess << Shop::pending[8] * initialize::buck_bandolier_price;//lancaster_pump_shotgun_price
			Misc::drawText(pricess.str().c_str(), menuX + 0.325 + 0.1 - 0.03, menuY + 0.11f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}

		if (Shop::pending[9] > 0) {
			std::stringstream text;
			text << Shop::pending[9];
			Misc::drawText(text.str().c_str(), menuX + 0.37 + 0.2 - 0.03, menuY + 0.198f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

			std::stringstream pricess;
			pricess << "$";
			pricess << Shop::pending[9] * initialize::buck_revolver_price;//lancaster_repeating_shotgun_price
			Misc::drawText(pricess.str().c_str(), menuX + 0.325 + 0.2 - 0.03, menuY + 0.11f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}



		if (selected) {
			if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 0) {
				MenuControls::menu_controls_amount(99, Shop::pending[7]);
			}
			if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 1) {
				MenuControls::menu_controls_amount(99, Shop::pending[8]);
			}
			if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 2) {
				MenuControls::menu_controls_amount(99, Shop::pending[9]);
			}
		}



		if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 0) {
			flavorText(9);
		}
		if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 1) {
			flavorText(8);
		}
		if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 2) {
			flavorText(7);
		}




		selectBack();


		orderButton(y, supplierIndex);

		highlighter(y);


		float current_rep = 0.23f;

		sumText();

	}
}


void baseSuppliers::muhlbergPage(int x, int y, int supplierIndex) {

	if (Menu::menuState == MenuState::Muhlberg) {


		//if the item is not selected you can move 
		back(supplierIndex);

		name(supplierIndex);

		controls(x, y, 1);

		totalPrice(19, 3);

		

		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 - 0.03, menuY + 0.1f, 0.08f, 0.135f, 0, 30, 30, 30, 250);
		Misc::drawSprite("inventory_items", "weapon_pistol_mauser", menuX + 0.3 - 0.03 + 0.08, menuY + 0.115, -0.075f, 0.11f, 0, 255, 255, 255, 255);

		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.4 - 0.03, menuY + 0.1f, 0.08f, 0.135f, 0, 30, 30, 30, 250);
		Misc::drawSprite("inventory_items_mp", "weapon_rifle_elephant", menuX + 0.405 - 0.03 + 0.08, menuY + 0.115, -0.087f, 0.11f, 0, 255, 255, 255, 255);

		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.5 - 0.03, menuY + 0.1f, 0.08f, 0.135f, 0, 30, 30, 30, 250);
		Misc::drawSprite("inventory_items_mp", "weapon_revolver_navy", menuX + 0.575 - 0.03, menuY + 0.115, -0.075f, 0.11f, 0, 255, 255, 255, 255);


		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 - 0.03, menuY + 0.25f, 0.08f, 0.135f, 0, 30, 30, 30, 250);
		Misc::drawSprite("inventory_items", "weapon_shotgun_semiauto", menuX + 0.3 - 0.025 + 0.08, menuY + 0.265, -0.087f, 0.11f, 0, 255, 255, 255, 255);





		if (Shop::pending[19] > 0) {
			std::stringstream text;
			text << Shop::pending[19];
			Misc::drawText(text.str().c_str(), menuX + 0.37 - 0.03, menuY + 0.198f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

			std::stringstream pricess;
			pricess << "$";
			pricess << Shop::pending[19] * initialize::muhlberg_mauser_price; //lancaster_repeater_price
			Misc::drawText(pricess.str().c_str(), menuX + 0.325 - 0.03, menuY + 0.11f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

		}

		if (Shop::pending[20] > 0) {
			std::stringstream text;
			text << Shop::pending[20];
			Misc::drawText(text.str().c_str(), menuX + 0.37 + 0.1 - 0.03, menuY + 0.198f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

			std::stringstream pricess;
			pricess << "$";
			pricess << Shop::pending[20] * initialize::muhlberg_elephant_price;//lancaster_pump_shotgun_price
			Misc::drawText(pricess.str().c_str(), menuX + 0.325 + 0.1 - 0.03, menuY + 0.11f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}

		if (Shop::pending[21] > 0) {
			std::stringstream text;
			text << Shop::pending[21];
			Misc::drawText(text.str().c_str(), menuX + 0.37 + 0.2 - 0.03, menuY + 0.198f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

			std::stringstream pricess;
			pricess << "$";
			pricess << Shop::pending[21] * initialize::muhlberg_navy_price;//lancaster_repeating_shotgun_price
			Misc::drawText(pricess.str().c_str(), menuX + 0.325 + 0.2 - 0.03, menuY + 0.11f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}

		if (Shop::pending[26] > 0) {
			std::stringstream text;
			text << Shop::pending[26];
			Misc::drawText(text.str().c_str(), menuX + 0.37 - 0.03, menuY + 0.198f + 0.15f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

			std::stringstream pricess;
			pricess << "$";
			pricess << Shop::pending[26] * initialize::prices[26];
			Misc::drawText(pricess.str().c_str(), menuX + 0.325 - 0.03, menuY + 0.11f + 0.15f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}


		total = total + Shop::pending[26] * initialize::prices[26];

		Shop::totalStock = Shop::totalStock + Shop::pending[26];


		if (selected) {
			if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 0) {
				MenuControls::menu_controls_amount(99, Shop::pending[19]);
			}
			if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 1) {
				MenuControls::menu_controls_amount(99, Shop::pending[20]);
			}
			if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 2) {
				MenuControls::menu_controls_amount(99, Shop::pending[21]);
			}

			if (MenuControls::current_cell == 1 && MenuControls::current_cell_x == 0) {
				MenuControls::menu_controls_amount(99, Shop::pending[26]);
			}
		}

		if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 0) {
			flavorText(10);
		}

		if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 1) {
			flavorText(26);
		}

		if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 2) {
			flavorText(25);
		}


		if (MenuControls::current_cell == 1 && MenuControls::current_cell_x == 0) {
			flavorText(11);
		}




		selectBack();


		orderButton(y, supplierIndex);

		highlighter(y);


		float current_rep = 0.23f;

		sumText();

	}
}

void baseSuppliers::peetersPage(int x, int y, int supplierIndex) {

	if (Menu::menuState == MenuState::Peeters) {


		//if the item is not selected you can move 
		back(supplierIndex);

		name(supplierIndex);

		controls(x, y);

		totalPrice(10, 2);


		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 - 0.03, menuY + 0.1f, 0.08f, 0.135f, 0, 30, 30, 30, 250);
		Misc::drawSprite("inventory_items", "weapon_shotgun_sawedoff", menuX + 0.375 - 0.03, menuY + 0.115, -0.07f, 0.11f, 0, 255, 255, 255, 255);

		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.4 - 0.03, menuY + 0.1f, 0.08f, 0.135f, 0, 30, 30, 30, 250);
		Misc::drawSprite("inventory_items", "weapon_pistol_semiauto", menuX + 0.475 - 0.03, menuY + 0.115, -0.07f, 0.11f, 0, 255, 255, 255, 255);


		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.5 - 0.03, menuY + 0.1f, 0.08f, 0.135f, 0, 30, 30, 30, 250);
		Misc::drawSprite("inventory_items_tu", "weapon_pistol_m1899", menuX + 0.575 - 0.03, menuY + 0.115, -0.07f, 0.11f, 0, 255, 255, 255, 255);







		if (Shop::pending[10] > 0) {
			std::stringstream text;
			text << Shop::pending[10];
			Misc::drawText(text.str().c_str(), menuX + 0.37 - 0.03, menuY + 0.198f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

			std::stringstream pricess;
			pricess << "$";
			pricess << Shop::pending[10] * initialize::prices[10]; //lancaster_repeater_price
			Misc::drawText(pricess.str().c_str(), menuX + 0.325 - 0.03, menuY + 0.11f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

		}

		if (Shop::pending[11] > 0) {
			std::stringstream text;
			text << Shop::pending[11];
			Misc::drawText(text.str().c_str(), menuX + 0.37 + 0.1 - 0.03, menuY + 0.198f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

			std::stringstream pricess;
			pricess << "$";
			pricess << Shop::pending[11] * initialize::prices[11];//lancaster_pump_shotgun_price
			Misc::drawText(pricess.str().c_str(), menuX + 0.325 + 0.1 - 0.03, menuY + 0.11f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}

		if (Shop::pending[22] > 0) {
			std::stringstream text;
			text << Shop::pending[22];
			Misc::drawText(text.str().c_str(), menuX + 0.37 + 0.2 - 0.03, menuY + 0.198f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

			std::stringstream pricess;
			pricess << "$";
			pricess << Shop::pending[22] * initialize::prices[22];//lancaster_pump_shotgun_price
			Misc::drawText(pricess.str().c_str(), menuX + 0.325 + 0.2 - 0.03, menuY + 0.11f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}

		total = total + Shop::pending[22] * initialize::prices[22];

		Shop::totalStock = Shop::totalStock + Shop::pending[22];


		if (selected) {
			if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 0) {
				MenuControls::menu_controls_amount(99, Shop::pending[10]);
			}
			if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 1) {
				MenuControls::menu_controls_amount(99, Shop::pending[11]);
			}
			if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 2) {
				MenuControls::menu_controls_amount(99, Shop::pending[22]);
			}
		}

		if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 0) {
			flavorText(12);
		}
		if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 1) {
			flavorText(13);
		}
		if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 2) {
			flavorText(14);
		}


		selectBack();


		orderButton(y, supplierIndex);

		highlighter(y);


		float current_rep = 0.23f;

		sumText();

	}
}

void baseSuppliers::huttonPage(int x, int y, int supplierIndex) {

	if (Menu::menuState == MenuState::Hutton) {


		//if the item is not selected you can move 
		back(supplierIndex);

		name(supplierIndex);

		controls(x, y, 1);

		totalPrice(12, 2);


		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 - 0.03, menuY + 0.1f, 0.08f, 0.135f, 0, 30, 30, 30, 250);
		Misc::drawSprite("inventory_items", "weapon_pistol_volcanic", menuX + 0.375 - 0.03, menuY + 0.115, -0.07f, 0.11f, 0, 255, 255, 255, 255);

		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.4 - 0.03, menuY + 0.1f, 0.08f, 0.135f, 0, 30, 30, 30, 250);
		Misc::drawSprite("inventory_items", "weapon_revolver_schofield", menuX + 0.47 - 0.03, menuY + 0.115, -0.065f, 0.11f, 0, 255, 255, 255, 255);


		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.5 - 0.03, menuY + 0.1f, 0.08f, 0.135f, 0, 30, 30, 30, 250);
		Misc::drawSprite("inventory_items", "weapon_rifle_boltaction", menuX + 0.473, menuY + 0.115, 0.07f, 0.11f, 0, 255, 255, 255, 255);

		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 - 0.03, menuY + 0.25f, 0.08f, 0.135f, 0, 30, 30, 30, 250);
		Misc::drawSprite("inventory_items_mp", "weapon_repeater_evans", menuX + 0.273, menuY + 0.265, 0.065f, 0.11f, 0, 255, 255, 255, 255);







		if (Shop::pending[12] > 0) {
			std::stringstream text;
			text << Shop::pending[12];
			Misc::drawText(text.str().c_str(), menuX + 0.37 - 0.03, menuY + 0.198f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

			std::stringstream pricess;
			pricess << "$";
			pricess << Shop::pending[12] * initialize::hutton_volcanic_price;
			Misc::drawText(pricess.str().c_str(), menuX + 0.325 - 0.03, menuY + 0.11f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

		}

		if (Shop::pending[13] > 0) {
			std::stringstream text;
			text << Shop::pending[13];
			Misc::drawText(text.str().c_str(), menuX + 0.37 + 0.1f - 0.03, menuY + 0.198f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

			std::stringstream pricess;
			pricess << "$";
			pricess << Shop::pending[13] * initialize::hutton_schofield_price;
			Misc::drawText(pricess.str().c_str(), menuX + 0.325 + 0.1f - 0.03, menuY + 0.11f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}


		if (Shop::pending[23] > 0) {
			std::stringstream text;
			text << Shop::pending[23];
			Misc::drawText(text.str().c_str(), menuX + 0.37 + 0.2f - 0.03, menuY + 0.198f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

			std::stringstream pricess;
			pricess << "$";
			pricess << Shop::pending[23] * initialize::prices[23];
			Misc::drawText(pricess.str().c_str(), menuX + 0.325 + 0.2f - 0.03, menuY + 0.11f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

		}

		if (Shop::pending[24] > 0) {
			std::stringstream text;
			text << Shop::pending[24];
			Misc::drawText(text.str().c_str(), menuX + 0.37 - 0.03, menuY + 0.198f + 0.15f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

			std::stringstream pricess;
			pricess << "$";
			pricess << Shop::pending[24] * initialize::prices[24];
			Misc::drawText(pricess.str().c_str(), menuX + 0.325 - 0.03, menuY + 0.11f + 0.15f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}



		total = total + (Shop::pending[23] * initialize::prices[23]) + (Shop::pending[24] * initialize::prices[24]);

		Shop::totalStock = Shop::totalStock + Shop::pending[23] + Shop::pending[24];





		if (selected) {
			if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 0) {
				MenuControls::menu_controls_amount(99, Shop::pending[12]);
			}
			if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 1) {
				MenuControls::menu_controls_amount(99, Shop::pending[13]);
			}
			if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 2) {
				MenuControls::menu_controls_amount(99, Shop::pending[23]);
			}
			if (MenuControls::current_cell == 1 && MenuControls::current_cell_x == 0) {
				MenuControls::menu_controls_amount(99, Shop::pending[24]);
			}
		
		}

		if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 0) {
			flavorText(15);
		}
		if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 1) {
			flavorText(16);
		}
		if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 2) {
			flavorText(17);
		}
		if (MenuControls::current_cell == 1 && MenuControls::current_cell_x == 0) {
			flavorText(18);
		}



		selectBack();


		orderButton(y, supplierIndex);

		highlighter(y);


		float current_rep = 0.23f;

		sumText();

	}
}

void baseSuppliers::ddPage(int x, int y, int supplierIndex) {

	if (Menu::menuState == MenuState::dd) {


		//if the item is not selected you can move 
		back(supplierIndex);

		name(supplierIndex);

		controls(x, y);

		totalPrice(14, 2);


		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 - 0.03, menuY + 0.1f, 0.08f, 0.135f, 0, 30, 30, 30, 250);
		Misc::drawSprite("inventory_items", "weapon_revolver_doubleaction", menuX + 0.375 - 0.03, menuY + 0.115, -0.07f, 0.11f, 0, 255, 255, 255, 255);

		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.4 - 0.03, menuY + 0.1f, 0.08f, 0.135f, 0, 30, 30, 30, 250);
		Misc::drawSprite("inventory_items", "weapon_shotgun_doublebarrel", menuX + 0.475 - 0.03, menuY + 0.115, -0.075f, 0.11f, 0, 255, 255, 255, 255);

		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.5 - 0.03, menuY + 0.1f, 0.08f, 0.135f, 0, 30, 30, 30, 250);
		Misc::drawSprite("inventory_items", "weapon_sniperrifle_carcano", menuX + 0.5 - 0.03, menuY + 0.115, 0.075f, 0.11f, 0, 255, 255, 255, 255);






		if (Shop::pending[14] > 0) {
			std::stringstream text;
			text << Shop::pending[14];
			Misc::drawText(text.str().c_str(), menuX + 0.37 - 0.03, menuY + 0.198f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

			std::stringstream pricess;
			pricess << "$";
			pricess << Shop::pending[14] * initialize::prices[14];
			Misc::drawText(pricess.str().c_str(), menuX + 0.325 - 0.03, menuY + 0.11f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

		}

		if (Shop::pending[15] > 0) {
			std::stringstream text;
			text << Shop::pending[15];
			Misc::drawText(text.str().c_str(), menuX + 0.37 + 0.1 - 0.03, menuY + 0.198f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

			std::stringstream pricess;
			pricess << "$";
			pricess << Shop::pending[15] * initialize::prices[15];
			Misc::drawText(pricess.str().c_str(), menuX + 0.325 + 0.1 - 0.03, menuY + 0.11f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}

		if (Shop::pending[25] > 0) {
			std::stringstream text;
			text << Shop::pending[25];
			Misc::drawText(text.str().c_str(), menuX + 0.37 + 0.2 - 0.03, menuY + 0.198f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

			std::stringstream pricess;
			pricess << "$";
			pricess << Shop::pending[25] * initialize::prices[25];
			Misc::drawText(pricess.str().c_str(), menuX + 0.325 + 0.2 - 0.03, menuY + 0.11f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}



		total = total + Shop::pending[25] * initialize::prices[25];

		Shop::totalStock = Shop::totalStock + Shop::pending[25];


		if (selected) {
			if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 0) {
				MenuControls::menu_controls_amount(99, Shop::pending[14]);
			}
			if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 1) {
				MenuControls::menu_controls_amount(99, Shop::pending[15]);
			}
			if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 2) {
				MenuControls::menu_controls_amount(99, Shop::pending[25]);
			}
		
		}

		if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 0) {
			flavorText(19);
		}
		if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 1) {
			flavorText(20);
		}
		if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 2) {
			flavorText(21);
		}




		selectBack();


		orderButton(y, supplierIndex);

		highlighter(y);


		float current_rep = 0.23f;

		sumText();

	}
}

void baseSuppliers::litchfieldPage(int x, int y, int supplierIndex) {
	if (Menu::menuState == MenuState::litchfield) {


		//if the item is not selected you can move 
		back(supplierIndex);

		name(supplierIndex);

		controls(x, y);

		totalPrice(16, 3);

		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.3 - 0.03, menuY + 0.1f, 0.08f, 0.135f, 0, 30, 30, 30, 250);
		Misc::drawSprite("inventory_items", "weapon_sniperrifle_rollingblock", menuX + 0.375 - 0.03, menuY + 0.115, -0.07f, 0.11f, 0, 255, 255, 255, 255);

		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.4 - 0.03, menuY + 0.1f, 0.08f, 0.135f, 0, 30, 30, 30, 250);
		Misc::drawSprite("inventory_items", "weapon_repeater_henry", menuX + 0.475 - 0.03, menuY + 0.115, -0.075f, 0.11f, 0, 255, 255, 255, 255);

		Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX + 0.5 - 0.03, menuY + 0.1f, 0.08f, 0.135f, 0, 30, 30, 30, 250);
		Misc::drawSprite("inventory_items_mp", "weapon_revolver_lemat", menuX + 0.575 - 0.03, menuY + 0.115, -0.075f, 0.11f, 0, 255, 255, 255, 255);







		if (Shop::pending[16] > 0) {
			std::stringstream text;
			text << Shop::pending[16];
			Misc::drawText(text.str().c_str(), menuX + 0.37 - 0.03, menuY + 0.198f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

			std::stringstream pricess;
			pricess << "$";
			pricess << Shop::pending[16] * initialize::litchfield_rolling_price;//lancaster_repeater_price
			Misc::drawText(pricess.str().c_str(), menuX + 0.325 - 0.03, menuY + 0.11f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

		}

		if (Shop::pending[17] > 0) {
			std::stringstream text;
			text << Shop::pending[17];
			Misc::drawText(text.str().c_str(), menuX + 0.37 + 0.1 - 0.03, menuY + 0.198f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

			std::stringstream pricess;
			pricess << "$";
			pricess << Shop::pending[17] * initialize::litchfield_repeater_price;//lancaster_pump_shotgun_price
			Misc::drawText(pricess.str().c_str(), menuX + 0.325 + 0.1 - 0.03, menuY + 0.11f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}

		if (Shop::pending[18] > 0) {
			std::stringstream text;
			text << Shop::pending[18];
			Misc::drawText(text.str().c_str(), menuX + 0.37 + 0.2 - 0.03, menuY + 0.198f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

			std::stringstream pricess;
			pricess << "$";
			pricess << Shop::pending[18] * initialize::litchfield_lemat_price;
			Misc::drawText(pricess.str().c_str(), menuX + 0.325 + 0.2 - 0.03, menuY + 0.11f, 255, 255, 255, 255, 1, 0.5f, 0.5f);
		}








		if (selected) {
			if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 0) {
				MenuControls::menu_controls_amount(99, Shop::pending[16]);
			}
			if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 1) {
				MenuControls::menu_controls_amount(99, Shop::pending[17]);
			}
			if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 2) {
				MenuControls::menu_controls_amount(99, Shop::pending[18]);
			}
		}

		if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 0) {
			flavorText(22);
		}
		if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 1) {
			flavorText(23);
		}
		if (MenuControls::current_cell == 0 && MenuControls::current_cell_x == 2) {
			flavorText(24);
		}


		selectBack();


		orderButton(y, supplierIndex);

		highlighter(y);


		float current_rep = 0.23f;

		sumText();

	}
}

