#pragma once
#include "script.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <Windows.h>
#include <shlwapi.h>
#include "Shop.h"
#include "Misc.h"



enum class MenuState
{
	Off,

	Home,
	Supplies,
	Upgrades,
	Managment,
	Sell,


	Suppliers,
	YourSupplies,
	
	Lancaster,
	Buck,
	Muhlberg,
	Peeters,
	Hutton,
	dd,
	litchfield

	

};


class Menu
{
private:	
	

	static int honorTransform();
	static void menuOn();
	static void menuUpdate();

	static void homePage();
	static void startUp();
	static void shopWidget();

	static void supplies();
	static void suppliers();
	static void suppliersSpecfic();
	static void yourSupplies();

	static void upgrade();


	static void managment();
	static void sell();

protected:
	

	static Prompt Prompt_Order; //place order
	static Prompt Prompt_Buy; //menu
	static Prompt Prompt_Menu; //menu
	static Prompt Prompt_Back; //menu
	static Prompt Prompt_Select; //menu
	static Prompt Work_Start; //start
	static Prompt Duty_Stop; //stop
	static Prompt Prompt_Not_Enough; //stop
	static Prompt Prompt_Open_Shop; //stop
	
	static Prompt Prompt_Buy_Upgrade; 

	static Prompt Prompt_Donate_Up;
	static Prompt Prompt_Donate_Down;
	static Prompt Prompt_Donate;

public:
	static Cam localCam;

	static MenuState menuState;
	static int select_clock;
	static float menuX; //menuX 0.040
	static float menuY; //menuY 0.68



	static void init();
	static void ambient();
	
};

