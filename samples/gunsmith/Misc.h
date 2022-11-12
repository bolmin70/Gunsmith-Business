#pragma once
#include "script.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <Windows.h>
#include <shlwapi.h>
class Misc
{
public:
	static float getGroundPos(Vector3 originalPos);

	static Vector3 getRandomPositionInRange(Vector3 center, int radius);

	static Vector3 getRandomPedPositionInRange(Vector3 source, int radius);

	static Ped createPedOnHorse(char* modelName, Ped horse, int seatIndex);

	static void createPrompt(Prompt& prompt, const char* input, const char* text, int press_type);

	static void createPrompt(Prompt& prompt, const char* input, const char* text, int press_type, int group);

	

	static Ped createPed(char* modelName, Vector3 pos, float heading);
	static Vector3 toVector3(float x, float y, float z);

	static Ped createVehicle(char* modelName, Vector3 pos, float heading);

	static Object createProp(char* model, Vector3 position, float heading, bool isStatic, bool isVisible);

	static void showSubtitle(const char* text);

	static void drawText(const char* text, float x, float y, int r, int g, int b, int a, bool centered, float sx, float sy);

	static void drawTextSmall(const char* text, float x, float y, int r, int g, int b, int a, bool centered, float sx, float sy);

	static void drawSprite(char* category, char* sprite, float x, float y, float scalex, float scaley, float rotation, int r, int g, int b, int a);
	
	static void RemoveBlip(Blip &blip);


};

