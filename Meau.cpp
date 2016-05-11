#include "Meau.h"
#include "Console.h"

#include <iostream>
using namespace std;

#define CONSOLEBUF_SIZE_WIDTH 120
#define CONSOLEBUF_SIZE_HEIGTH 30
#define FONT_SIZE_WIDTH 9
#define FONT_SIZE_HEIGHT 20

extern Console console;

Meau::Meau()
{
	top = { CONSOLEBUF_SIZE_WIDTH - 40 ,CONSOLEBUF_SIZE_HEIGTH - 20 };
	offset = 2;
	meau.clear();
	setting.clear();
	draw.clear();

	string temp = "START GAME";
	meau.push_back(temp);
	temp = "DRAWING BOARD";
	meau.push_back(temp);
	temp = "SETTING";
	meau.push_back(temp);
	temp = "POKEDEX";
	meau.push_back(temp);
	temp = "EXIT GAME";
	meau.push_back(temp);

	temp = "CONTROLS";
	setting.push_back(temp);
	temp = "RESOLUTION";
	setting.push_back(temp);
	temp = "DEFAULT";
	setting.push_back(temp);

	temp = "HERO";
	draw.push_back(temp);
	temp = "MOSTER";
	draw.push_back(temp);
	temp = "BOSS";
	draw.push_back(temp);

}

void Meau::displayMeau()
{
	displayBasic(MeauBuf);
	
	DWORD dwNumberOfCharsWritten;
	COORD start = top;
	for (int i = 0; i < meau.size(); i++)
	{
		WriteConsoleOutputCharacter(MeauBuf, meau[i].data(), meau[i].size(), start,&dwNumberOfCharsWritten);
		start.Y += offset;
	}

	choseMeau();
	console.closeConsoleBuf();
}


Meau::~Meau()
{
}

void Meau::displayBasic(HANDLE & hBuf)
{
	console.createNewConsoleBuf({ FONT_SIZE_WIDTH, FONT_SIZE_HEIGHT }, { 0,0,CONSOLEBUF_SIZE_WIDTH,CONSOLEBUF_SIZE_HEIGTH });
	console.closeConsoleBuf();
	console.createNewConsoleBuf({ FONT_SIZE_WIDTH, FONT_SIZE_HEIGHT }, { 0,0,CONSOLEBUF_SIZE_WIDTH,CONSOLEBUF_SIZE_HEIGTH });

	hBuf = console.getNowConsoleBuf();
	DWORD dwNumberOfCharsWritten;
	for (short i = 0; i <= CONSOLEBUF_SIZE_HEIGTH; i++)
	{
		if (i == 0 || i == 1 || i == CONSOLEBUF_SIZE_HEIGTH - 1 || i == CONSOLEBUF_SIZE_HEIGTH)
			FillConsoleOutputCharacter(hBuf, '#', CONSOLEBUF_SIZE_WIDTH + 1, { 0,i }, &dwNumberOfCharsWritten);
		else
		{
			FillConsoleOutputCharacter(hBuf, '#', 3, { 0,i }, &dwNumberOfCharsWritten);
			FillConsoleOutputCharacter(hBuf, '#', 3, { CONSOLEBUF_SIZE_WIDTH - 2,i }, &dwNumberOfCharsWritten);
		}
	}
}



void Meau::displaySetting()
{
	displayBasic(SettingBuf);
	DWORD dwNumberOfCharsWritten;
	COORD start = top;
	start.X = 25;
	for (int i = 0; i < setting.size(); i++)
	{
		WriteConsoleOutputCharacter(SettingBuf, setting[i].data(), setting[i].size(), start, &dwNumberOfCharsWritten);
		start.Y += offset;
	}
	choseSetting();
	console.closeConsoleBuf();
}


void Meau::displayDraw()
{
	displayBasic(DrawBuf);

	DWORD dwNumberOfCharsWritten;
	COORD start = top;
	start.X = 25;
	for (int i = 0; i < draw.size(); i++)
	{
		WriteConsoleOutputCharacter(DrawBuf, draw[i].data(), draw[i].size(), start, &dwNumberOfCharsWritten);
		start.Y += offset;
	}
	choseDraw();
	console.closeConsoleBuf();
}

void Meau::displayPokedex()
{
	displayBasic(PokedexBuf);
	
	DWORD dwNumberOfCharsWritten;
	COORD start = top;
	start.X = 25;
	for (int i = 0; i < draw.size(); i++)
	{
		WriteConsoleOutputCharacter(PokedexBuf, draw[i].data(), draw[i].size(), start, &dwNumberOfCharsWritten);
		start.Y += offset;
	}
	chosePokedex();
	console.closeConsoleBuf();
}

int Meau::testKey(HANDLE & hBuf, COORD & position, COORD top, int item)
{
	DWORD dwNumberOfEventsRead;
	INPUT_RECORD inputRecord;

	ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &inputRecord, 1, &dwNumberOfEventsRead);

	int returnValue = -1;
	switch (inputRecord.EventType)
	{
		case MOUSE_EVENT:
			if (inputRecord.Event.MouseEvent.dwEventFlags == MOUSE_MOVED)
			{
				for (short i = 0; i < item; i++)
					if (( inputRecord.Event.MouseEvent.dwMousePosition.Y == top.Y + offset * i )
						&& ( inputRecord.Event.MouseEvent.dwMousePosition.X >= position.X - 5 && inputRecord.Event.MouseEvent.dwMousePosition.X <= position.X + 15 ))
					{
						hideArrow(hBuf, position);
						position.Y = top.Y + offset * i;
						showArrow(hBuf, position);
						break;
					}
			}
			if(inputRecord.Event.MouseEvent.dwButtonState== FROM_LEFT_1ST_BUTTON_PRESSED)
				returnValue = ( position.Y - top.Y ) / offset + 1;
			break;
		case KEY_EVENT:
			if (inputRecord.Event.KeyEvent.bKeyDown)
			{
				switch (inputRecord.Event.KeyEvent.wVirtualKeyCode)
				{
					case VK_DOWN:
						if (position.Y != top.Y + ( item - 1 ) * offset)
						{
							hideArrow(hBuf, position);
							position.Y += offset;
							showArrow(hBuf, position);
						}
						break;
					case VK_UP:
						if (position.Y != top.Y)
						{
							hideArrow(hBuf, position);
							position.Y -= offset;
							showArrow(hBuf, position);
						}
						break;
					case VK_RETURN:
						returnValue = ( position.Y - top.Y ) / offset + 1;
						break;
					case VK_ESCAPE:
						returnValue = 0;
						break;
				}
			}
			break;
	}
	return returnValue;
}

void Meau::choseMeau()
{
	int chose;
	COORD start = top;
	bool exit = false;

	showArrow(MeauBuf, start);
	while (!exit)
	{
		chose = testKey(MeauBuf, start, top, meau.size());
		switch (chose)
		{
			case 1:
				game.start();
				console.createNewConsoleBuf({ FONT_SIZE_WIDTH, FONT_SIZE_HEIGHT }, { 0,0,CONSOLEBUF_SIZE_WIDTH,CONSOLEBUF_SIZE_HEIGTH });
				console.closeConsoleBuf();
				break;
			case 2:
				displayDraw();
				break;
			case 3:
				displaySetting();
				break;
			case 4:
				displayPokedex();
				break;
			case 5:
				exit = true;
				break;
		}
	}
}


void Meau::choseSetting()
{

	int chose;
	COORD start = top;
	start.X = 25;
	bool exit = false;

	showArrow(SettingBuf, start);
	while (!exit)
	{
		chose = testKey(SettingBuf, start, top, setting.size());
		switch (chose)
		{
			case 0:
				exit = true;
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;

		}
	}
}

void Meau::choseDraw()
{
	int chose;
	COORD start = top;
	start.X = 25;
	bool exit = false;

	showArrow(DrawBuf, start);
	while (!exit)
	{
		chose = testKey(DrawBuf, start, top, draw.size());
		switch (chose)
		{
			case 0:
				exit = true;
				break;
			case 1:
				drawingboard.draw(HERO);
				console.createNewConsoleBuf({ FONT_SIZE_WIDTH, FONT_SIZE_HEIGHT }, { 0,0,CONSOLEBUF_SIZE_WIDTH,CONSOLEBUF_SIZE_HEIGTH });
				console.closeConsoleBuf();
				break;
			case 2:
				drawingboard.draw(MONSTER);
				console.createNewConsoleBuf({ FONT_SIZE_WIDTH, FONT_SIZE_HEIGHT }, { 0,0,CONSOLEBUF_SIZE_WIDTH,CONSOLEBUF_SIZE_HEIGTH });
				console.closeConsoleBuf();
				break;
			case 3:
				drawingboard.draw(BOSS);
				console.createNewConsoleBuf({ FONT_SIZE_WIDTH, FONT_SIZE_HEIGHT }, { 0,0,CONSOLEBUF_SIZE_WIDTH,CONSOLEBUF_SIZE_HEIGTH });
				console.closeConsoleBuf();
				break;

		}
	}
}

void Meau::chosePokedex()
{
	int chose; 
	COORD start = top;
	start.X = 25;
	bool exit = false;

	showArrow(PokedexBuf, start);
	while (!exit)
	{
		chose = testKey(PokedexBuf, start, top, draw.size());
		switch (chose)
		{
			case 0:
				exit = true;
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;

		}
	}
}

void Meau::showArrow(HANDLE & hBuf, COORD position)
{
	DWORD dwNumberOfCharsWritten;
	FillConsoleOutputCharacter(hBuf, '>', 3, { position.X - 5,position.Y }, &dwNumberOfCharsWritten);
}

void Meau::hideArrow(HANDLE & hBuf, COORD position)
{
	DWORD dwNumberOfCharsWritten;
	FillConsoleOutputCharacter(hBuf, 0, 3, { position.X - 5,position.Y }, &dwNumberOfCharsWritten);
}
