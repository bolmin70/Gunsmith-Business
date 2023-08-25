#include "script.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <Windows.h>
#include <shlwapi.h>
#include "Enemies.h"
#include "Misc.h"

using namespace std;



std::vector<Ped> enemies1;


//creates an enemy and adds it to the enemies vector
void Enemies::addEnemy(Vector3 pos, vector<Ped> &enemies) {


	Ped enemyPed = Misc::createPed("G_M_M_UniCriminals_01", pos, 0);
	PED::SET_PED_RELATIONSHIP_GROUP_HASH(enemyPed, MISC::GET_HASH_KEY("REL_CRIMINALS"));
	enemies.push_back(enemyPed);

	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(enemyPed, 1);
	TASK::CLEAR_PED_TASKS(enemyPed, true, true);
}

//creates an enemy on horseback and adds it to the enemies vector
void Enemies::addHorseEnemy(Vector3 pos, vector<Ped>& enemies) {


	Ped enemyPed = Misc::createPed("G_M_M_UniCriminals_01", pos, 0);
	PED::SET_PED_RELATIONSHIP_GROUP_HASH(enemyPed, MISC::GET_HASH_KEY("REL_CRIMINALS"));
	enemies.push_back(enemyPed);

	Ped ped = PED::CREATE_PED_ON_MOUNT(MISC::GET_HASH_KEY("A_C_Horse_AmericanStandardbred_Black"), MISC::GET_HASH_KEY("G_M_M_UniCriminals_01"), 0, 0, 0, 0, 0);

	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(enemyPed, 1);
	TASK::CLEAR_PED_TASKS(enemyPed, true, true);

}




//creates blips for enemies
void Enemies::createEnemyBlips(vector<Ped> &enemies)
{
	std::vector<Ped>::iterator it;
	for (it = enemies.begin(); it != enemies.end(); ++it)
	{
		Blip blip = MAP::_BLIP_ADD_FOR_ENTITY(0x318C617C, *it);
		MAP::SET_BLIP_SPRITE(blip, 0UL, false);

	}
}

//Makes the enemies attack the player with their best available weapon
void Enemies::aggro(vector<Ped> &enemies)
{
	Ped player = PLAYER::PLAYER_PED_ID();
	vector<Ped>::iterator pedItr;
	for (pedItr = enemies.begin(); pedItr != enemies.end(); pedItr++)
	{
		PED::SET_PED_PANIC_EXIT_SCENARIO(*pedItr, 0, 0, 0);
		WEAPON::SET_CURRENT_PED_WEAPON(*pedItr, WEAPON::GET_BEST_PED_WEAPON(*pedItr, 0, 0), true, 0, false, false);



		Object seq;
		TASK::OPEN_SEQUENCE_TASK(&seq);
		TASK::TASK_COMBAT_PED(0, player, 0, 16);
		TASK::CLOSE_SEQUENCE_TASK(seq);

		TASK::CLEAR_PED_TASKS(*pedItr, 1, 1);
		TASK::TASK_PERFORM_SEQUENCE(*pedItr, seq);
	}


}



//a custom encounter that spawns during delivery runs
void Enemies::Enemies_Custom(Vector3 vec, vector<Ped>& enemies) {

	int enemy_amount = rand() % 3;

	if (enemy_amount >= 0) {
		addEnemy(Misc::toVector3(vec.x + (rand() % 10), vec.y + (rand() % 10), vec.z), enemies);
		addEnemy(Misc::toVector3(vec.x + (rand() % 10), vec.y + (rand() % 10), vec.z), enemies);
		addEnemy(Misc::toVector3(vec.x + (rand() % 10), vec.y + (rand() % 10), vec.z), enemies);
	}
	if (enemy_amount >= 1) {
		addEnemy(Misc::toVector3(vec.x + (rand() % 10), vec.y + (rand() % 10), vec.z), enemies);
		addEnemy(Misc::toVector3(vec.x + (rand() % 10), vec.y + (rand() % 10), vec.z), enemies);
		addEnemy(Misc::toVector3(vec.x + (rand() % 10), vec.y + (rand() % 10), vec.z), enemies);
	}
	if (enemy_amount >= 2) {
		addEnemy(Misc::toVector3(vec.x + (rand() % 10), vec.y + (rand() % 10), vec.z), enemies);
		addEnemy(Misc::toVector3(vec.x + (rand() % 10), vec.y + (rand() % 10), vec.z), enemies);
		addEnemy(Misc::toVector3(vec.x + (rand() % 10), vec.y + (rand() % 10), vec.z), enemies);
	}



	//createEnemyBlips();

	aggro(enemies);


	//if (distanceBetween(toVector3(814.320, 384.743, 116.0), player) <= 100) {
	createEnemyBlips(enemies);
	//}

}

vector<Ped> bountyHunters;
vector<Ped> bountyhorses;

int Enemies::enemiesSpawned = 0;

void Enemies::spawnBountyHunters(int amount)
{
	Ped player = PLAYER::PLAYER_PED_ID();
	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, 0);
	Vector3 enemiesSourcePos = Misc::getRandomPedPositionInRange(playerPos, 60);


	for (int i = 0; i < amount - 1; i++) {

		Ped horse1 = Misc::createPed("A_C_Horse_TennesseeWalker_DappleBay", Misc::getRandomPedPositionInRange(playerPos, 60), rand() % 360);
		Ped horse2 = Misc::createPed("A_C_Horse_TennesseeWalker_DappleBay", Misc::getRandomPedPositionInRange(playerPos, 60), rand() % 360);
		Ped horse3 = Misc::createPed("A_C_Horse_TennesseeWalker_DappleBay", Misc::getRandomPedPositionInRange(playerPos, 60), rand() % 360);


		bountyhorses.push_back(horse1);
		bountyhorses.push_back(horse2);
		bountyhorses.push_back(horse3);

		PED::_SET_PED_COMPONENT_ENABLED(horse1, 0x8D9D754C, 1, 0, 0);
		PED::_SET_PED_COMPONENT_ENABLED(horse2, 0xE52BAC3F, 1, 0, 0);
		PED::_SET_PED_COMPONENT_ENABLED(horse3, 0x78F07DFA, 1, 0, 0);

		addBountyHunter(horse1, true);
		addBountyHunter(horse2, true);
		addBountyHunter(horse3, true);

	}

	vector<Ped>::iterator pedItr;
	for (pedItr = bountyHunters.begin(); pedItr != bountyHunters.end(); pedItr++)
	{
		Ped curr = *pedItr;
		TASK::TASK_COMBAT_PED(curr, player, 0, 16);
	}




	enemiesSpawned = 1;
}

void Enemies::addBountyHunter(Ped horse, bool isDriver)
{
	Ped bh = Misc::createPedOnHorse("G_M_M_UniCriminals_01", horse, isDriver ? -1 : 0);
	PED::SET_PED_RELATIONSHIP_GROUP_HASH(bh, MISC::GET_HASH_KEY("REL_CRIMINALS"));
	DECORATOR::DECOR_SET_INT(bh, "honor_override", 0);


	bountyHunters.push_back(bh);

	Blip blip = MAP::_BLIP_ADD_FOR_ENTITY(0x318C617C, bh);

	int i = rand() % 3;

	WEAPON::REMOVE_WEAPON_FROM_PED(bh, WEAPON::GET_BEST_PED_WEAPON(bh, 0, 0), false, 0);

	switch (i) {
	case 0:
		WEAPON::SET_CURRENT_PED_WEAPON(bh, 0x7BBD1FF6, true, 0, false, false);
		break;
	case 1:

		WEAPON::SET_CURRENT_PED_WEAPON(bh, 0xA84762EC, true, 0, false, false);
		break;

	case 2:
		WEAPON::SET_CURRENT_PED_WEAPON(bh, 0x95B24592, true, 0, false, false);

		break;

	};


	WEAPON::SET_CURRENT_PED_WEAPON(bh, WEAPON::GET_BEST_PED_WEAPON(bh, 0, 0), true, 0, false, false);

}


void Enemies::cleanUp() {
	vector<Ped>::iterator pedItr;
	for (pedItr = bountyHunters.begin(); pedItr != bountyHunters.end(); pedItr++)
	{
		Entity ent = *pedItr;

		if (ENTITY::DOES_ENTITY_EXIST(ent))
		{
			ENTITY::DELETE_ENTITY(&ent);
		}

	}
}

