#pragma once
#include "script.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <Windows.h>
#include <shlwapi.h>
#include "Shop.h"


enum class DeliveryState
{
	Ambient,
	Started,
	InProgress,
	Completed,
	Failed
};

class SupplyRuns
{
private:
	static void Setup();
	static void InProgress();
	static void Complete();
	static Vehicle wagon;
	static Blip wagonBlip;
	static Blip destinationBlip;

public:
	static void Start();
	static void Ambient();
	static DeliveryState state;


};

