#include "SaveLoad.h"
#include "Shop.h"
#include <fstream>
#include <iostream>

using namespace std;




void SaveLoad::Save()
{
	//save
	ofstream SaveFile;
	SaveFile.open("Gunsmith.dat", std::ofstream::trunc);

	SaveFile << Shop::current_stock << " " << Shop::shop_revenue << " " << Shop::shop_status << " " << Shop::shop_rep << " " << Shop::val_gunsmith_bought << " " << 
		Shop::denis_gunsmith_bought << " " << Shop::burg_gunsmith_bought << " " << Shop::rho_gunsmith_bought << " " << Shop::tum_gunsmith_bought << " " << 
		Shop::sell_rate_visual << " " << Shop::paycheck_rate_visual << " " << Shop::storage << " " << Shop::bedroll << " " << Shop::wagon << " " << Shop::dealer << " "; //save unlockables

	for (int i = 0; i < Shop::hardLimit - 1; i++) { //save current stock
		SaveFile << Shop::stored[i] << " ";
	}

	SaveFile.close();

}

void SaveLoad::Load()
{
	ifstream LoadFile;
	LoadFile.open("Gunsmith.dat", std::ofstream::in);

	LoadFile >> Shop::current_stock >> Shop::shop_revenue >> Shop::shop_status >> Shop::shop_rep >> Shop::val_gunsmith_bought >> 
		Shop::denis_gunsmith_bought >> Shop::burg_gunsmith_bought >> Shop::rho_gunsmith_bought >> Shop::tum_gunsmith_bought >>
		Shop::sell_rate_visual >> Shop::paycheck_rate_visual >> Shop::storage >> Shop::bedroll >> Shop::wagon >> Shop::dealer; //load unlockables

	for (int i = 0; i < Shop::hardLimit - 1; i++) { //load current stock
		LoadFile >> Shop::stored[i];
	}

	LoadFile.close();
}










