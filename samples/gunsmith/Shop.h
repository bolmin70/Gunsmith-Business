#pragma once
#include "Misc.h"
#include "script.h"

class Shop
{
public:
	static float shop_rep;//50
	static bool inRangeVal; //0
	static bool inRangeDenis; //0
	static bool inRangeBurg; //0

	static bool inRangeRho; 
	static bool inRangeTum; 


	static int shop_status; //0 - closed; 1 - open 

	static int sell_rate_visual; //the variable of what is supposed to be shown
	static int paycheck_rate_visual;
	static int paychecks_sum; //10


	static float sell_rate; //1.0 - normal //1.5 - cheap //0.5 - expensive
	static float paycheck_rate; //0. - none // 0.5 - low //1.0 - average //1.5 generous //2.0 very genorous

	static int current_stock;

	static int shop_revenue;

	static int daily_expanses;
	static float current_stock_visual;

	static const int hardLimit;

	//-1 - nothing; 0 - lancaster repeater; 1 - pump action shot; 2 - reapting shot; 3 - springfield; 4 - varmint; 5 - gun oil; 6 - gun belt
	static int pending[30];
	static int stored[30];
	static int stored_visual[30];

	static bool val_gunsmith_bought; //0
	static bool denis_gunsmith_bought;
	static bool burg_gunsmith_bought;

	static bool rho_gunsmith_bought;
	static bool tum_gunsmith_bought;


	static const int suppliersLimit;
	static bool suppliersOrder[7];
	static float suppliersRep[7];

	
	static Vector3 gunsmithVal;
	static Vector3 gunsmithDenis;
	static Vector3 gunsmithBurg;

	static Vector3 gunsmithRho;
	static Vector3 gunsmithTum;


	static Vector3 gunsmithValKnock;
	static Vector3 gunsmithDenisKnock;
	static Vector3 gunsmithBurgKnock;

	static Vector3 gunsmithRhoKnock;
	static Vector3 gunsmithTumKnock;


	//upgrades
	static int bedroll;
	static int wagon;
	static int dealer;
	static int storage;

	static int maxStock;
	static int totalStock;

};

