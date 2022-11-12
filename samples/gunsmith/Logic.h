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

class Logic
{
private:
	static void Base();
	static void stockSell();
	static void ownershipBlip();
	static void dailyExpenses();
	static void upgrades();

public:
	static void gunsmithController();
	static void resetOrders();

};

