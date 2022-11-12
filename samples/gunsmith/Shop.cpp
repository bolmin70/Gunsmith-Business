#include "Shop.h"
#include "Misc.h"
#include "script.h"

float Shop::shop_rep = 50;//50
bool Shop::inRangeVal = 0; //0
bool Shop::inRangeDenis = 0; //0
bool Shop::inRangeBurg = 0; //0

bool Shop::inRangeRho = 0;
bool Shop::inRangeTum = 0;


bool Shop::val_gunsmith_bought = 0; //0
bool Shop::denis_gunsmith_bought = 0;
bool Shop::burg_gunsmith_bought = 0;

bool Shop::rho_gunsmith_bought = 0;
bool Shop::tum_gunsmith_bought = 0;



int Shop::shop_status = 0; //0 - closed; 1 - open 

int Shop::sell_rate_visual = 2; //the variable of what is supposed to be shown
int Shop::paycheck_rate_visual = 2;
int Shop::paychecks_sum = 10; //10


float Shop::sell_rate = 1.0f; //1.0 - normal //1.5 - cheap //0.5 - expensive
float Shop::paycheck_rate = 1.0f; //0. - none // 0.5 - low //1.0 - average //1.5 generous //2.0 very genorous

int Shop::current_stock = 0;

int Shop::shop_revenue = 0;

int Shop::daily_expanses = 0;
float Shop::current_stock_visual = 0;



//-1 - nothing; 0 - lancaster repeater; 1 - pump action shot; 2 - reapting shot; 3 - springfield; 4 - varmint; 5 - gun oil; 6 - gun belt;
//7 - carbine repeater; 8 - upgraded bandolier; 9 - cattleman revolver
//10 -  sawedoff; 11 - semiauto; 22 - m1899
//12 - volcanic; 13 - schofield; 23 - bolt-action rifle; 24 - evans repeater
//14 - doublebarrel; 15 - doubleaction; 25 - carcano rifle
//16 - rolling block; 17 - litchfield repeater //18 - lemat revolver
//19 - mauser pistol; 20 - elephant rifle; 21 - navy revolver; 26 - semi-auto shotgun


const int Shop::hardLimit = 30;

int Shop::pending[hardLimit] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int Shop::stored[hardLimit] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int Shop::stored_visual[hardLimit] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};





const int  Shop::suppliersLimit = 7;


bool  Shop::suppliersOrder[suppliersLimit] = { 0, 0, 0, 0, 0, 0, 0 };
/*
0. bool Shop::lancaster_order = 0;
1. bool Shop::buck_order = 0;
2. bool Shop::muhlberg_order = 0;
3. bool Shop::peeters_order = 0;
4. bool Shop::hutton_order = 0;
5. bool Shop::dd_order = 0;
6. bool Shop::litchfield_order = 0;
*/


float  Shop::suppliersRep[suppliersLimit] = { 50, 30, 80, 40, 60, 70, 90};

/*
0. float lancasterRep = 50;
1. float buckRep = 30;
2. float muhlberg = 80;
3. float peetersRep = 40;
4. float ddRep = 60;
5. float huttonRep = 70;
6. float litchfieldRep = 90;
*/

Vector3 Shop::gunsmithVal = Misc::toVector3(-281.193, 780.699, 119.527);
Vector3 Shop::gunsmithDenis = Misc::toVector3(2718.303, -1284.714, 49.630);
Vector3 Shop::gunsmithBurg = Misc::toVector3(2946.325, 1319.607, 44.820);

Vector3 Shop::gunsmithRho = Misc::toVector3(1325.003, -1323.026, 77.891);
Vector3 Shop::gunsmithTum = Misc::toVector3(-5507.445, -2966.757, -0.639);


Vector3 Shop::gunsmithValKnock = Misc::toVector3(-282.795, 785.178, 119.502);
Vector3 Shop::gunsmithDenisKnock = Misc::toVector3(2720.893, -1282.668, 49.638);
Vector3 Shop::gunsmithBurgKnock = Misc::toVector3(2942.929, 1321.155, 44.760);

Vector3 Shop::gunsmithRhoKnock = Misc::toVector3(1325.937, -1318.154, 77.949);
Vector3 Shop::gunsmithTumKnock = Misc::toVector3(-5510.201, -2960.690, -0.664);



//upgrades
int Shop::bedroll = 0;
int Shop::wagon = 0;
int Shop::dealer = 0;

int Shop::storage = 0;

int Shop::maxStock = 20;
int Shop::totalStock = 0;



