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








//INI file options and prices
int initialize::animation_on = GetPrivateProfileInt("MISC", "ANIMATION_ON", 1, ".\\Gunsmith.ini");
int initialize::quick_anim_on = GetPrivateProfileInt("MISC", "QUICK_ANIMATION_ON", 0, ".\\Gunsmith.ini");
int initialize::debug_texts = GetPrivateProfileInt("MISC", "DEBUG_INFO", 1, ".\\Gunsmith.ini");
int initialize::help_texts = GetPrivateProfileInt("MISC", "HELP_TEXTS", 1, ".\\Gunsmith.ini");

int initialize::no_enemies = GetPrivateProfileInt("GAMEPLAY", "NO_ENEMIES", 0, ".\\Gunsmith.ini");
int initialize::no_daily = GetPrivateProfileInt("GAMEPLAY", "NO_DAILY_EXPENSES", 0, ".\\Gunsmith.ini");
int initialize::base_daily_cost = GetPrivateProfileInt("GAMEPLAY", "BASE_DAILY_EXPENSES", 0, ".\\Gunsmith.ini");



int initialize::lancaster_repeater_price = GetPrivateProfileInt("PRICES", "LANCASTER_REPEATER_PRICE", 90, ".\\Gunsmith.ini");

int initialize::lancaster_pump_shotgun_price = GetPrivateProfileInt("PRICES", "LANCASTER_PUMP_SHOTGUN_PRICE", 104, ".\\Gunsmith.ini");
int initialize::lancaster_repeating_shotgun_price = GetPrivateProfileInt("PRICES", "LANCASTER_REPEATING_SHOTGUN_PRICE", 138, ".\\Gunsmith.ini");
int initialize::lancaster_rifle_price = GetPrivateProfileInt("PRICES", "LANCASTER_RIFLE_PRICE", 80, ".\\Gunsmith.ini");
int initialize::lancaster_varmint_price = GetPrivateProfileInt("PRICES", "LANCASTER_VARMINT_PRICE", 40, ".\\Gunsmith.ini");
int initialize::lancaster_oil_price = GetPrivateProfileInt("PRICES", "LANCASTER_OIL_PRICE", 1, ".\\Gunsmith.ini");
int initialize::lancaster_gunbelt_price = GetPrivateProfileInt("PRICES", "LANCASTER_GUNBELT_PRICE", 23, ".\\Gunsmith.ini");


int initialize::buck_repeater_price = GetPrivateProfileInt("PRICES", "BUCK_REPEATER_PRICE", 50, ".\\Gunsmith.ini");
int initialize::buck_bandolier_price = GetPrivateProfileInt("PRICES", "BUCK_BANDOLIER_PRICE", 25, ".\\Gunsmith.ini");
int initialize::buck_revolver_price = GetPrivateProfileInt("PRICES", "BUCK_REVOLVER_PRICE", 20, ".\\Gunsmith.ini");


int initialize::peeters_sawedoff_price = GetPrivateProfileInt("PRICES", "PEETERS_SAWEDOFF_PRICE", 55, ".\\Gunsmith.ini");
int initialize::peeters_semiauto_price = GetPrivateProfileInt("PRICES", "PEETERS_SEMIAUTO_PRICE", 160, ".\\Gunsmith.ini");
int initialize::peeters_m1899_price = GetPrivateProfileInt("PRICES", "PEETERS_M1899_PRICE", 200, ".\\Gunsmith.ini");

int initialize::hutton_volcanic_price = GetPrivateProfileInt("PRICES", "HUTTON_VOLCANIC_PRICE", 110, ".\\Gunsmith.ini");
int initialize::hutton_schofield_price = GetPrivateProfileInt("PRICES", "HUTTON_SCHOFIELD_PRICE", 54, ".\\Gunsmith.ini");
int initialize::hutton_bolt_price = GetPrivateProfileInt("PRICES", "HUTTON_BOLT_PRICE", 150, ".\\Gunsmith.ini");
int initialize::hutton_evans_price = GetPrivateProfileInt("PRICES", "HUTTON_EVANS_PRICE", 230, ".\\Gunsmith.ini");


int initialize::dd_doublebarreled_price = GetPrivateProfileInt("PRICES", "DD_DOUBLEBARRELED_PRICE", 60, ".\\Gunsmith.ini");
int initialize::dd_doubleaction_price = GetPrivateProfileInt("PRICES", "DD_DOUBLEACTION_PRICE", 38, ".\\Gunsmith.ini");
int initialize::dd_carcano_price = GetPrivateProfileInt("PRICES", "DD_CARCANO_PRICE", 100, ".\\Gunsmith.ini");

int initialize::litchfield_rolling_price = GetPrivateProfileInt("PRICES", "LITCHFIELD_ROLLING_PRICE", 130, ".\\Gunsmith.ini");
int initialize::litchfield_repeater_price = GetPrivateProfileInt("PRICES", "LITCHFIELD_REPEATER_PRICE", 100, ".\\Gunsmith.ini");
int initialize::litchfield_lemat_price = GetPrivateProfileInt("PRICES", "LITCHFIELD_LEMAT_PRICE", 140, ".\\Gunsmith.ini");


int initialize::muhlberg_mauser_price = GetPrivateProfileInt("PRICES", "MUHLBERG_MAUSER_PRICE", 200, ".\\Gunsmith.ini");
int initialize::muhlberg_elephant_price = GetPrivateProfileInt("PRICES", "MUHLBERG_ELEPHANT_PRICE", 450, ".\\Gunsmith.ini");
int initialize::muhlberg_navy_price = GetPrivateProfileInt("PRICES", "MUHLBERG_NAVY_PRICE", 240, ".\\Gunsmith.ini");
int initialize::muhlberg_semiauto_price = GetPrivateProfileInt("PRICES", "MUHLBERG_SEMIAUTO_PRICE", 170, ".\\Gunsmith.ini");




float initialize::paycheck_rate_none = GetPrivateProfileInt("MULTIPLIERS", "PAYCHECK_RATE_NONE", 0, ".\\Gunsmith.ini") / 10;
float initialize::paycheck_rate_low = GetPrivateProfileInt("MULTIPLIERS", "PAYCHECK_RATE_LOW", 5, ".\\Gunsmith.ini") / 10;
float initialize::paycheck_rate_average = GetPrivateProfileInt("MULTIPLIERS", "PAYCHECK_RATE_AVERAGE", 10, ".\\Bunsmithini") / 10;
float initialize::paycheck_rate_generous = GetPrivateProfileInt("MULTIPLIERS", "PAYCHECK_RATE_GENEROUS", 15, ".\\Gunsmith.ini") / 10;
float initialize::paycheck_rate_verygenerous = GetPrivateProfileInt("MULTIPLIERS", "PAYCHECK_RATE_VERY_GENEROUS", 20, ".\\Gunsmith.ini") / 10;

float initialize::sell_rate_free = GetPrivateProfileInt("MULTIPLIERS", "SELL_RATE_FREE", 40, ".\\Gunsmith.ini") / 10;
float initialize::sell_rate_cheap = GetPrivateProfileInt("MULTIPLIERS", "SELL_RATE_CHEAP", 15, ".\\Gunsmith.ini") / 10;
float initialize::sell_rate_average = GetPrivateProfileInt("MULTIPLIERS", "SELL_RATE_AVERAGE", 10, ".\\Gunsmith.ini") / 10;
float initialize::sell_rate_expensive = GetPrivateProfileInt("MULTIPLIERS", "SELL_RATE_EXPENSIVE", 5, ".\\Gunsmith.ini") / 10;
float initialize::sell_rate_veryexpensive = GetPrivateProfileInt("MULTIPLIERS", "SELL_RATE_VERY_EXPENSIVE", 2, ".\\Gunsmith.ini") / 10;

float initialize::sell_rate_overall = GetPrivateProfileInt("MULTIPLIERS", "SELL_RATE_BASE", 30, ".\\Gunsmith.ini");





Prompt initialize::Prompt_Threaten;
Prompt initialize::Prompt_Knock;

int initialize::prices[30] = { initialize::lancaster_repeater_price, initialize::lancaster_pump_shotgun_price, initialize::lancaster_repeating_shotgun_price, initialize::lancaster_rifle_price, initialize::lancaster_varmint_price, initialize::lancaster_oil_price, initialize::lancaster_gunbelt_price,
		initialize::buck_repeater_price, initialize::buck_bandolier_price, initialize::buck_revolver_price,
		initialize::peeters_sawedoff_price,  initialize::peeters_semiauto_price,
		initialize::hutton_volcanic_price, initialize::hutton_schofield_price,
		initialize::dd_doublebarreled_price, initialize::dd_doubleaction_price,
		initialize::litchfield_rolling_price, initialize::litchfield_repeater_price, initialize::litchfield_lemat_price,
		initialize::muhlberg_mauser_price, initialize::muhlberg_elephant_price, initialize::muhlberg_navy_price,
		initialize::peeters_m1899_price, initialize::hutton_bolt_price, initialize::hutton_evans_price, initialize::dd_carcano_price, initialize::muhlberg_semiauto_price };

void initialize::init() {





	Prompt_Threaten = HUD::_UIPROMPT_REGISTER_BEGIN(); //register prompt startINPUT_RELOAD
	HUD::_UIPROMPT_SET_CONTROL_ACTION(Prompt_Threaten, MISC::GET_HASH_KEY("INPUT_RELOAD")); //prompt set input INPUT_TOGGLE_HOLSTER (tab or l1)
	HUD::_UIPROMPT_SET_TEXT(Prompt_Threaten, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Threaten")); //set text

	//HUD::_UIPROMPT_SET_HOLD_MODE(Prompt_Threaten, 1); //UI prompt set hold mode
	HUD::_UIPROMPT_SET_STANDARD_MODE(Prompt_Threaten, 1); //prompt click

	HUD::_UIPROMPT_REGISTER_END(Prompt_Threaten); //register prompt end


	HUD::_UIPROMPT_SET_ENABLED(Prompt_Threaten, 1); // _UIPROMPT_SET_ENABLED
	HUD::_UIPROMPT_SET_VISIBLE(Prompt_Threaten, 1); // _UIPROMPT_SET_VISIBLE



	Prompt_Knock = HUD::_UIPROMPT_REGISTER_BEGIN(); //register prompt start
	HUD::_UIPROMPT_SET_CONTROL_ACTION(Prompt_Knock, MISC::GET_HASH_KEY("INPUT_RELOAD")); //prompt set input INPUT_TOGGLE_HOLSTER (tab or l1)
	HUD::_UIPROMPT_SET_TEXT(Prompt_Knock, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Enter Business")); //set text

	HUD::_UIPROMPT_SET_HOLD_MODE(Prompt_Knock, 50); //UI prompt set hold mode
	//HUD::_UIPROMPT_SET_STANDARD_MODE(Prompt_Knock, 1); //prompt click

	HUD::_UIPROMPT_REGISTER_END(Prompt_Knock); //register prompt end


	HUD::_UIPROMPT_SET_ENABLED(Prompt_Knock, 0); // _UIPROMPT_SET_ENABLED
	HUD::_UIPROMPT_SET_VISIBLE(Prompt_Knock, 0); // _UIPROMPT_SET_VISIBLE




}



