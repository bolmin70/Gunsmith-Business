#pragma once
#include "script.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <Windows.h>
#include <shlwapi.h>



using namespace std;

class Enemies
{
public:
	//static vector<Ped> enemies;
	
	static void addEnemy(Vector3 pos, vector<Ped> &enemies);
	static void addHorseEnemy(Vector3 pos, vector<Ped>& enemies);
	static void createEnemyBlips(vector<Ped> &enemies);
	static void aggro(vector<Ped> &enemies);

	static void addBountyHunter(Ped horse, bool isDriver);



	static int enemiesSpawned;

	static void cleanUp();
	static void Enemies_Custom(Vector3 vec, vector<Ped>& enemies);
	static void spawnBountyHunters(int amount);
};

