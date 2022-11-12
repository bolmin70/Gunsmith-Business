#pragma once
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
#include "Menu.h"
#include "SupplyRuns.h"

class baseSuppliers : public Menu
{

private:
	static void back(int supplierIndex);
	static void name(int supplierIndex);

	static void controls(int x, int y);
	
	static void controls(int x, int y, bool alt);



	static void totalPrice(int start, int iterations);
	static void selectBack();

	static void orderButton(int y, int supplierIndex);
	static void highlighter(int y);
	static void sumText();

public:
	static SupplyRuns supplyRun;


	static void lancasterPage(int x, int y, int supplierIndex);
	static void buckPage(int x, int y, int supplierIndex);
	static void muhlbergPage(int x, int y, int supplierIndex);
	static void peetersPage(int x, int y, int supplierIndex);
	static void huttonPage(int x, int y, int supplierIndex);
	static void ddPage(int x, int y, int supplierIndex);
	static void litchfieldPage(int x, int y, int supplierIndex);



};

