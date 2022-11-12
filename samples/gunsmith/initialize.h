#pragma once
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


class initialize
{
private:
	static bool isEnabled;


public:


	static int lancaster_repeater_price;
	static int lancaster_pump_shotgun_price;
	static int lancaster_repeating_shotgun_price;
	static int lancaster_rifle_price;
	static int lancaster_varmint_price;
	static int lancaster_oil_price;
	static int lancaster_gunbelt_price;


	static int buck_repeater_price;
	static int buck_bandolier_price;
	static int buck_revolver_price;


	static int peeters_sawedoff_price;
	static int peeters_semiauto_price;
	static int peeters_m1899_price;

	static int hutton_volcanic_price;
	static int hutton_schofield_price;
	static int hutton_bolt_price; 
	static int hutton_evans_price;

	static int dd_doublebarreled_price;
	static int dd_doubleaction_price;
	static int dd_carcano_price;

	static int litchfield_rolling_price;
	static int litchfield_repeater_price;
	static int litchfield_lemat_price;


	static int muhlberg_mauser_price;
	static int muhlberg_elephant_price;
	static int muhlberg_navy_price;
	static int muhlberg_semiauto_price;




	static int prices[];

	static int animation_on;
	static int quick_anim_on;
	static int debug_texts;
	static int help_texts;

	static int no_enemies;
	static int no_daily;
	static int base_daily_cost;


	static float paycheck_rate_none;
	static float paycheck_rate_low;
	static float paycheck_rate_average;
	static float paycheck_rate_generous;
	static float paycheck_rate_verygenerous;

	static float sell_rate_free;
	static float sell_rate_cheap;
	static float sell_rate_average;
	static float sell_rate_expensive;
	static float sell_rate_veryexpensive;

	static float sell_rate_overall;



	static Prompt Prompt_Threaten;
	static Prompt Prompt_Knock;





	static void init();

	static void hide(Prompt prompt, bool isEnabled);
	
	
};

