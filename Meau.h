#pragma once

#include <Windows.h>
#include <vector>
#include <string>
using namespace std;

#include "GameManager.h"
#include "DrawingBoard.h"

class Meau
{
public:
	Meau();

	void displayMeau();

	~Meau();
private:
	void displayBasic(HANDLE &);

	void displaySetting();
	void displayDraw();
	void displayPokedex();

	int testKey(HANDLE &, COORD &, COORD, int);

	void choseMeau();
	void choseSetting();
	void choseDraw();
	void chosePokedex();

	void showArrow(HANDLE &, COORD);
	void hideArrow(HANDLE &, COORD);

	COORD top;
	short offset;

	HANDLE MeauBuf;
	HANDLE SettingBuf;
	HANDLE DrawBuf;
	HANDLE PokedexBuf;

	vector <string> meau;
	vector <string> setting;
	vector <string> draw;

	GameManager game;
	DrawingBoard drawingboard;

};

