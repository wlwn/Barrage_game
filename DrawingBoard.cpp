#include "DrawingBoard.h"
#include "Console.h"
#include "Resoure.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <sstream>
using namespace std;

#define LEFT 0
#define RIGHT 1

extern Console console;
extern Resoure resoure;

DrawingBoard::DrawingBoard()
{

}
void DrawingBoard::draw(DrawRole role)
{
	this->role = role;
	initialDrawingBoard();

	while (status != END)
	{
		KeyTest();
	}

	close();
}

void DrawingBoard::initialDrawingBoard()
{
	status = DRAWING;
	OutputCharacter[0] = 'o', OutputCharacter[1] = 'O';
	crHome = { 0,0 };
	bCaps = bShift = false;
	bCtrl_L = bCtrl_R = bAlt_R = bAlt_L = false;
	srWindowRect = { 0,0,199,39 };

	console.createNewConsoleBuf({ 9,12 }, srWindowRect);
	console.closeConsoleBuf();
	console.createNewConsoleBuf({ 9,12 }, srWindowRect);
	hConsoleOutput = console.getNowConsoleBuf();
	hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
}

void DrawingBoard::close()
{
	console.closeConsoleBuf();
}

void DrawingBoard::KeyTest()
{
	ReadConsoleInput(hConsoleInput, &inputRecord, 1, &dwNumberOfEventsRead);

	switch (inputRecord.EventType)
	{
		case MOUSE_EVENT:
			crPos = inputRecord.Event.MouseEvent.dwMousePosition;

			PrintMessage(ALL);

			switchMouseButtonStateEvent();
			break;
		case KEY_EVENT:
			if (inputRecord.Event.KeyEvent.bKeyDown)
			{
				testControlKeyState();
				switchKeyButtonDownStateEvent();
				PrintMessage(ALL);
			}
			else
			{
				switchKeyButtonUpStateEvent();
			}
			break;
	}
}

void DrawingBoard::PrintMessage(Massage massage_type)
{
	DWORD dwNumberOfCharsWritten;
	stringstream ss;
	string InfoRec;
	string Tips;
	CONSOLE_SCREEN_BUFFER_INFO tempbuf;
	GetConsoleScreenBufferInfo(hConsoleOutput, &tempbuf);
	switch (massage_type)
	{
		case ALL:
			FillConsoleOutputAttribute(hConsoleOutput, infomationtext_color, 32, crHome, &dwNumberOfCharsWritten);
			InfoRec = "[Cursor Position] X: ";
			WriteConsoleOutputCharacter(hConsoleOutput, &InfoRec[0], InfoRec.size(), crHome, &dwNumberOfCharsWritten);
			ss.clear();
			ss << inputRecord.Event.MouseEvent.dwMousePosition.X;
			ss >> InfoRec;
			WriteConsoleOutputCharacter(hConsoleOutput, &InfoRec[0], InfoRec.size(), { 21,0 }, &dwNumberOfCharsWritten);
			InfoRec = "Y: ";
			WriteConsoleOutputCharacter(hConsoleOutput, &InfoRec[0], InfoRec.size(), { 26,0 }, &dwNumberOfCharsWritten);
			ss.clear();
			ss << inputRecord.Event.MouseEvent.dwMousePosition.Y;
			ss >> InfoRec;
			WriteConsoleOutputCharacter(hConsoleOutput, &InfoRec[0], InfoRec.size(), { 30,0 }, &dwNumberOfCharsWritten);

			InfoRec = "  [Now Character] Left: ";
			FillConsoleOutputAttribute(hConsoleOutput, infomationtext_color, 21, { 34,0 }, &dwNumberOfCharsWritten);
			WriteConsoleOutputCharacter(hConsoleOutput, &InfoRec[0], InfoRec.size(), { 34,0 }, &dwNumberOfCharsWritten);
			FillConsoleOutputAttribute(hConsoleOutput, printcharacter_color, 1, { 56,0 }, &dwNumberOfCharsWritten);
			FillConsoleOutputCharacter(hConsoleOutput, OutputCharacter[LEFT], 1, { 56,0 }, &dwNumberOfCharsWritten);
			InfoRec = " | Right: ";
			FillConsoleOutputAttribute(hConsoleOutput, infomationtext_color, 9, { 57,0 }, &dwNumberOfCharsWritten);
			WriteConsoleOutputCharacter(hConsoleOutput, &InfoRec[0], InfoRec.size(), { 57,0 }, &dwNumberOfCharsWritten);
			FillConsoleOutputAttribute(hConsoleOutput, printcharacter_color, 1, { 67,0 }, &dwNumberOfCharsWritten);
			FillConsoleOutputCharacter(hConsoleOutput, OutputCharacter[RIGHT], 1, { 67,0 }, &dwNumberOfCharsWritten);
			switch (role)
			{
				case HERO:
					Tips = "Suggest Size: 5 x 3";
					break;
				case MONSTER:
					Tips = "Suggest Size: 5 x 3";
					break;
				case BOSS:
					Tips = "Suggest Size: 30 x 15";
					break;
			}
			FillConsoleOutputAttribute(hConsoleOutput, infomationtext_color, 21, { 70,0 }, &dwNumberOfCharsWritten);
			WriteConsoleOutputCharacter(hConsoleOutput, &Tips[0], Tips.size(), { 70,0 }, &dwNumberOfCharsWritten);
			break;
		case CURSORPOSITION:
			FillConsoleOutputAttribute(hConsoleOutput, infomationtext_color, 32, crHome, &dwNumberOfCharsWritten);
			InfoRec = "[Cursor Position] X: ";
			WriteConsoleOutputCharacter(hConsoleOutput, &InfoRec[0], InfoRec.size(), crHome, &dwNumberOfCharsWritten);
			ss << inputRecord.Event.MouseEvent.dwMousePosition.X;
			ss >> InfoRec;
			WriteConsoleOutputCharacter(hConsoleOutput, &InfoRec[0], InfoRec.size(), { 21,0 }, &dwNumberOfCharsWritten);
			InfoRec = "Y: ";
			WriteConsoleOutputCharacter(hConsoleOutput, &InfoRec[0], InfoRec.size(), { 26,0 }, &dwNumberOfCharsWritten);
			ss << inputRecord.Event.MouseEvent.dwMousePosition.Y;
			ss >> InfoRec;
			WriteConsoleOutputCharacter(hConsoleOutput, &InfoRec[0], InfoRec.size(), { 30,0 }, &dwNumberOfCharsWritten);
			break;
		case CHARACTER:
			InfoRec = "  [Now Character] Left: ";
			FillConsoleOutputAttribute(hConsoleOutput, infomationtext_color, 21, { 34,0 }, &dwNumberOfCharsWritten);
			WriteConsoleOutputCharacter(hConsoleOutput, &InfoRec[0], InfoRec.size(), { 34,0 }, &dwNumberOfCharsWritten);
			FillConsoleOutputAttribute(hConsoleOutput, printcharacter_color, 1, { 56,0 }, &dwNumberOfCharsWritten);
			FillConsoleOutputCharacter(hConsoleOutput, OutputCharacter[LEFT], 1, { 56,0 }, &dwNumberOfCharsWritten);
			InfoRec = " | Right: ";
			FillConsoleOutputAttribute(hConsoleOutput, infomationtext_color, 9, { 57,0 }, &dwNumberOfCharsWritten);
			WriteConsoleOutputCharacter(hConsoleOutput, &InfoRec[0], InfoRec.size(), { 57,0 }, &dwNumberOfCharsWritten);
			FillConsoleOutputAttribute(hConsoleOutput, printcharacter_color, 1, { 67,0 }, &dwNumberOfCharsWritten);
			FillConsoleOutputCharacter(hConsoleOutput, OutputCharacter[RIGHT], 1, { 67,0 }, &dwNumberOfCharsWritten);
			break;
		case TIPS:
			switch (role)
			{
				case HERO:
					Tips = "Suggest Size: 5 x 3";
					break;
				case MONSTER:
					Tips = "Suggest Size: 5 x 3";
					break;
				case BOSS:
					Tips = "Suggest Size: 30 x 15";
					break;
			}
			FillConsoleOutputAttribute(hConsoleOutput, infomationtext_color, 21, { 70,0 }, &dwNumberOfCharsWritten);
			WriteConsoleOutputCharacter(hConsoleOutput, &Tips[0], Tips.size(), { 70,0 }, &dwNumberOfCharsWritten);
			break;
	}
	gotoxy(tempbuf.dwCursorPosition);
}


void DrawingBoard::switchMouseButtonStateEvent()
{
	if (inputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
	{
		if (inputRecord.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)		// 左键双击 撤销改坐标下输出
		{
			tip();
			FillConsoleOutputCharacter(hConsoleOutput, 0, 1, inputRecord.Event.MouseEvent.dwMousePosition, &dwNumberOfEventsRead);
			return;
		}
	}
	else if (inputRecord.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
	{
		if (inputRecord.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)		// 右键双击 清除所有输出
		{
			FillConsoleOutputCharacter(hConsoleOutput, ' ', 1, { 95, 0 }, &dwNumberOfEventsRead);
			saveFile("_Distory", ".");
			CONSOLE_SCREEN_BUFFER_INFO bInfo;
			GetConsoleScreenBufferInfo(hConsoleOutput, &bInfo);
			COORD cls = { 76, 0 };

			FillConsoleOutputCharacter(hConsoleOutput, 0, bInfo.dwSize.X * bInfo.dwSize.Y, crHome, &dwNumberOfEventsRead);
			return;
		}
	}

	switch (inputRecord.Event.MouseEvent.dwButtonState)
	{
		case FROM_LEFT_1ST_BUTTON_PRESSED:			// 左键 输出左字符			
			tip();
			FillConsoleOutputAttribute(hConsoleOutput, getCharacterAttribute(), 1, inputRecord.Event.MouseEvent.dwMousePosition, &dwNumberOfEventsRead);
			FillConsoleOutputCharacter(hConsoleOutput, OutputCharacter[LEFT], 1, inputRecord.Event.MouseEvent.dwMousePosition, &dwNumberOfEventsRead);
			break;
		case RIGHTMOST_BUTTON_PRESSED:				// 右键 输出右字符
			tip();
			FillConsoleOutputAttribute(hConsoleOutput, getCharacterAttribute(), 1, inputRecord.Event.MouseEvent.dwMousePosition, &dwNumberOfEventsRead);
			FillConsoleOutputCharacter(hConsoleOutput, OutputCharacter[RIGHT], 1, inputRecord.Event.MouseEvent.dwMousePosition, &dwNumberOfEventsRead);
			break;
		case FROM_LEFT_2ND_BUTTON_PRESSED:
			{
				tip();
				COORD firstPos = inputRecord.Event.MouseEvent.dwMousePosition;
				FillConsoleOutputAttribute(hConsoleOutput, FOREGROUND_INTENSITY | FOREGROUND_RED, 1, inputRecord.Event.MouseEvent.dwMousePosition, &dwNumberOfEventsRead);
				FillConsoleOutputCharacter(hConsoleOutput, '.', 1, firstPos, &dwNumberOfEventsRead);
				clearBoard_NextActionTest(firstPos);
			}
		default:
			break;
	}
}

void DrawingBoard::switchKeyButtonUpStateEvent()
{
	if (!( inputRecord.Event.KeyEvent.dwControlKeyState & LEFT_CTRL_PRESSED ))		// 左CTRL弹起
		bCtrl_L = false;
	if (!( inputRecord.Event.KeyEvent.dwControlKeyState & RIGHT_CTRL_PRESSED ))		// 右CTRL弹起
		bCtrl_R = false;
	if (!( inputRecord.Event.KeyEvent.dwControlKeyState &  LEFT_ALT_PRESSED ))		// 左ALT弹起
		bAlt_L = false;
	if (!( inputRecord.Event.KeyEvent.dwControlKeyState &  RIGHT_ALT_PRESSED ))		// 右ALT弹起
		bAlt_R = false;
	if (!( inputRecord.Event.KeyEvent.dwControlKeyState &  SHIFT_PRESSED ))			// SHIFT弹起
		bShift = false;
}

void DrawingBoard::switchKeyButtonDownStateEvent()
{
	if (inputRecord.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)	// 按ESC退出并保存缓存文件
	{
		saveFile("_CacheFile", ".");
		status = END;
	}
	else if (inputRecord.Event.KeyEvent.wVirtualKeyCode == VK_DELETE)
	{
		COORD firstPos = crPos;
		FillConsoleOutputAttribute(hConsoleOutput, FOREGROUND_INTENSITY | FOREGROUND_RED, 1, firstPos, &dwNumberOfEventsRead);
		FillConsoleOutputCharacter(hConsoleOutput, '.', 1, firstPos, &dwNumberOfEventsRead);
		clearBoard_NextActionTest(firstPos);
	}

	if (!bShift && !bCtrl_L && !bCtrl_R && !bAlt_L && !bAlt_R)
	{
		if (isPrintableCharacter(inputRecord.Event.KeyEvent.wVirtualKeyCode))
			changeCharacter(inputRecord.Event.KeyEvent.wVirtualKeyCode);
	}
	else
		testHotKey();
}

void DrawingBoard::testControlKeyState()
{
	DWORD dwState = inputRecord.Event.KeyEvent.dwControlKeyState;

	bCaps = dwState & CAPSLOCK_ON ? true : false;
	bShift = dwState & SHIFT_PRESSED ? true : false;

	bCtrl_L = dwState & LEFT_CTRL_PRESSED ? true : false;
	bCtrl_R = dwState & RIGHT_CTRL_PRESSED ? true : false;
	bAlt_L = dwState & LEFT_ALT_PRESSED ? true : false;
	bAlt_R = dwState & RIGHT_ALT_PRESSED ? true : false;
}

void DrawingBoard::testHotKey()
{
	if (bAlt_L)
	{
		string filename;
		switch (inputRecord.Event.KeyEvent.wVirtualKeyCode)
		{
			case 'C':
				saveFile("_CacheFile", ".");
				break;
			case 'S':
				print_and_getFileInfomation(filename);
				if (!filename.empty())
					saveFile(move(filename), ".rf");
				resoure.reset();
				status = END;
				break;
		}
	}
	else if (bCtrl_L)
	{
		switch (inputRecord.Event.KeyEvent.wVirtualKeyCode)
		{
			case '1':
				if (bShift)
					changeColor(0x08, 'i');
				else
					changeColor(0x08, 'c');
				break;
			case '2':
				if (bShift)
					changeColor(0x09, 'i');
				else
					changeColor(0x09, 'c');
				break;
			case '3':
				if (bShift)
					changeColor(0x0a, 'i');
				else
					changeColor(0x0a, 'c');
				break;
			case '4':
				if (bShift)
					changeColor(0x0b, 'i');
				else
					changeColor(0x0b, 'c');
				break;
			case '5':
				if (bShift)
					changeColor(0x0f, 'i');
				else
					changeColor(0x0f, 'c');
				break;
			case '6':
				if (bShift)
					changeColor(0x0d, 'i');
				else
					changeColor(0x0d, 'c');
				break;
			case '7':
				if (bShift)
					changeColor(0x0e, 'i');
				else
					changeColor(0x0e, 'c');
				break;
			case VK_F1:
				if (bShift)
					changeColor(0x07, 'i');
				else
					changeColor(0x07, 'c');
				break;
			case VK_F2:
				if (bShift)
					changeColor(0x06, 'i');
				else
					changeColor(0x06, 'c');
				break;
			case VK_F3:
				if (bShift)
					changeColor(0x05, 'i');
				else
					changeColor(0x05, 'c');
				break;
			case VK_F4:
				if (bShift)
					changeColor(0x04, 'i');
				else
					changeColor(0x04, 'c');
				break;
			case VK_F5:
				if (bShift)
					changeColor(0x03, 'i');
				else
					changeColor(0x03, 'c');
				break;
			case VK_F6:
				if (bShift)
					changeColor(0x02, 'i');
				else
					changeColor(0x02, 'c');
				break;
			case VK_F7:
				if (bShift)
					changeColor(0x01, 'i');
				else
					changeColor(0x01, 'c');
				break;
			case VK_OEM_3:
				if (bShift)
					setDefault();
				break;
		}
	}
}

bool DrawingBoard::isPrintableCharacter(WORD &wVirtualKeyCode)
{
	if (wVirtualKeyCode == 32)
		return true;
	else if (wVirtualKeyCode >= 48 && wVirtualKeyCode <= 57)
		return true;
	else if (wVirtualKeyCode >= 65 && wVirtualKeyCode <= 90)
		return true;
	else if (wVirtualKeyCode >= 96 && wVirtualKeyCode <= 105)
		return true;
	else if (wVirtualKeyCode >= 106 && wVirtualKeyCode <= 111 && wVirtualKeyCode != 108)
		return true;
	else if (wVirtualKeyCode >= 186 && wVirtualKeyCode <= 192)
		return true;
	else if (wVirtualKeyCode >= 219 && wVirtualKeyCode <= 222)
		return true;
	return false;
}

void DrawingBoard::changeCharacter(WORD &wVirtualKeyCode)
{
	char ch = 'a' - 'A';

	if (wVirtualKeyCode >= 'A' && wVirtualKeyCode <= 'Z')
		OutputCharacter[LEFT] = ch + wVirtualKeyCode, OutputCharacter[RIGHT] = wVirtualKeyCode;
	else if (wVirtualKeyCode >= 96 && wVirtualKeyCode <= 105)
		OutputCharacter[LEFT] = OutputCharacter[RIGHT] = wVirtualKeyCode - '0';
	else if (wVirtualKeyCode >= 106 && wVirtualKeyCode <= 111 && wVirtualKeyCode != 108)
		OutputCharacter[LEFT] = OutputCharacter[RIGHT] = wVirtualKeyCode - 64;
	else if (wVirtualKeyCode == 32)
		OutputCharacter[LEFT] = OutputCharacter[RIGHT] = 0;
	else
	{
		if (!bCaps)
		{
			downCharacter(wVirtualKeyCode);
		}
		else
		{
			upCharacter(wVirtualKeyCode);
		}
	}
}

void DrawingBoard::upCharacter(WORD &wVirtualKeyCode)
{
	switch (wVirtualKeyCode)
	{
		case '1': OutputCharacter[LEFT] = OutputCharacter[RIGHT] = '!'; break;
		case '2': OutputCharacter[LEFT] = OutputCharacter[RIGHT] = '@'; break;
		case '3': OutputCharacter[LEFT] = OutputCharacter[RIGHT] = '#'; break;
		case '4': OutputCharacter[LEFT] = OutputCharacter[RIGHT] = '$'; break;
		case '5': OutputCharacter[LEFT] = OutputCharacter[RIGHT] = '%'; break;
		case '6': OutputCharacter[LEFT] = OutputCharacter[RIGHT] = '^'; break;
		case '7': OutputCharacter[LEFT] = OutputCharacter[RIGHT] = '&'; break;
		case '8': OutputCharacter[LEFT] = OutputCharacter[RIGHT] = '*'; break;
		case '9': OutputCharacter[LEFT] = OutputCharacter[RIGHT] = '('; break;
		case '0': OutputCharacter[LEFT] = OutputCharacter[RIGHT] = ')'; break;

		case 186: OutputCharacter[LEFT] = OutputCharacter[RIGHT] = ':'; break;
		case 187: OutputCharacter[LEFT] = OutputCharacter[RIGHT] = '+'; break;
		case 188: OutputCharacter[LEFT] = OutputCharacter[RIGHT] = '<'; break;
		case 189: OutputCharacter[LEFT] = OutputCharacter[RIGHT] = '_'; break;
		case 190: OutputCharacter[LEFT] = OutputCharacter[RIGHT] = '>'; break;
		case 191: OutputCharacter[LEFT] = OutputCharacter[RIGHT] = '?'; break;
		case 192: OutputCharacter[LEFT] = OutputCharacter[RIGHT] = '~'; break;

		case 219: OutputCharacter[LEFT] = OutputCharacter[RIGHT] = '{'; break;
		case 220: OutputCharacter[LEFT] = OutputCharacter[RIGHT] = '|'; break;
		case 221: OutputCharacter[LEFT] = OutputCharacter[RIGHT] = '}'; break;
		case 222: OutputCharacter[LEFT] = OutputCharacter[RIGHT] = '"'; break;
	}
}

void DrawingBoard::downCharacter(WORD &wVirtualKeyCode)
{
	if (wVirtualKeyCode >= '0' && wVirtualKeyCode <= '9')
		OutputCharacter[LEFT] = OutputCharacter[RIGHT] = wVirtualKeyCode;
	else
		switch (wVirtualKeyCode)
		{
			case 186: OutputCharacter[LEFT] = OutputCharacter[RIGHT] = ';'; break;
			case 187: OutputCharacter[LEFT] = OutputCharacter[RIGHT] = '='; break;
			case 188: OutputCharacter[LEFT] = OutputCharacter[RIGHT] = ','; break;
			case 189: OutputCharacter[LEFT] = OutputCharacter[RIGHT] = '-'; break;
			case 190: OutputCharacter[LEFT] = OutputCharacter[RIGHT] = '.'; break;
			case 191: OutputCharacter[LEFT] = OutputCharacter[RIGHT] = '/'; break;
			case 192: OutputCharacter[LEFT] = OutputCharacter[RIGHT] = '`'; break;

			case 219: OutputCharacter[LEFT] = OutputCharacter[RIGHT] = '['; break;
			case 220: OutputCharacter[LEFT] = OutputCharacter[RIGHT] = '\\'; break;
			case 221: OutputCharacter[LEFT] = OutputCharacter[RIGHT] = ']'; break;
			case 222: OutputCharacter[LEFT] = OutputCharacter[RIGHT] = '\''; break;
		}
}

void DrawingBoard::gotoxy(COORD Pos)
{
	SetConsoleCursorPosition(hConsoleOutput, Pos);
}

void DrawingBoard::gotoxy(short x, short y)
{
	COORD Pos = { x,y };
	gotoxy(Pos);
}

void DrawingBoard::changeColor(WORD color, char info)
{
	switch (info)
	{
		case 'c':
			setCharacterAttribute(color);
			PrintMessage(CHARACTER);
			break;
		case 'i':
			setInfomationAttribute(color);
			PrintMessage(ALL);
			break;
	}
}

COORD & DrawingBoard::setClearBeginPoint(COORD &first, COORD &last)
{
	if (first.X < last.X)
	{
		if (first.Y > last.Y)
			first.Y -= abs(first.Y - last.Y);
		return first;
	}
	else
	{
		if (first.Y < last.Y)
			last.Y -= abs(first.Y - last.Y);
		return last;
	}
}

void DrawingBoard::clearBoard_NextActionTest(COORD firstPos)
{
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD inputRec;
	DWORD res;
	COORD crPos;
	while (1)
	{
		ReadConsoleInput(hIn, &inputRec, 1, &res);
		if (inputRec.EventType == MOUSE_EVENT)
		{
			crPos = inputRec.Event.MouseEvent.dwMousePosition;
			gotoxy(crHome);
			PrintMessage(CURSORPOSITION);

			if (inputRec.Event.MouseEvent.dwButtonState == FROM_LEFT_2ND_BUTTON_PRESSED)	// 按下中键 执行删除
			{
				COORD lastPos = crPos;
				int clearbuf_x = abs(firstPos.X - lastPos.X) + 1;
				int clearbuf_y = abs(firstPos.Y - lastPos.Y) + 1;

				COORD begin = setClearBeginPoint(firstPos, lastPos);
				for (int i = 0; i < clearbuf_y; i++, begin.Y++)
					FillConsoleOutputCharacter(hConsoleOutput, 0, clearbuf_x, begin, &res);
				break;
			}
			else if (inputRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED
					 || inputRec.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)	// 按下左右键 放弃删除
			{
				FillConsoleOutputCharacter(hConsoleOutput, 0, 1, firstPos, &dwNumberOfEventsRead);
				break;
			}
		}
		else if (inputRec.EventType == KEY_EVENT && inputRec.Event.KeyEvent.bKeyDown)
		{
			if (inputRec.Event.KeyEvent.wVirtualKeyCode == VK_DELETE)	// 按下delete 执行删除
			{
				COORD lastPos = crPos;
				int clearbuf_x = abs(firstPos.X - lastPos.X) + 1;
				int clearbuf_y = abs(firstPos.Y - lastPos.Y) + 1;

				COORD begin = setClearBeginPoint(firstPos, lastPos);
				for (int i = 0; i < clearbuf_y; i++, begin.Y++)
					FillConsoleOutputCharacter(hConsoleOutput, 0, clearbuf_x, begin, &res);
				break;
			}
			else break;	// 按下其它键 放弃删除
		}
	}
}

void DrawingBoard::saveFile(string &&filename, string &&filetype)
{
	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(hConsoleOutput, &buf);
	string FileName = filename + filetype;
	ofstream outfile(FileName, ios::out);

	if (!outfile)
	{
		exit(EXIT_FAILURE);
	}

	FillConsoleOutputCharacter(hConsoleOutput, ' ', 1, { 95, 0 }, &dwNumberOfEventsRead);
	output_RF_File(outfile, buf, filename);
}

void DrawingBoard::print_and_getFileInfomation(string &filename)
{
	int count;
	switch (role)
	{
		case HERO:
			count = resoure.getHeroGraphCount();
			filename = ".\\Resoure\\Hero\\Hero_";
			break;
		case MONSTER:
			count = resoure.getMonsterGraphCount();
			filename = ".\\Resoure\\Monster\\Monster_";
			break;
		case BOSS:
			count = resoure.getBossGraphCount();
			filename = ".\\Resoure\\Boss\\Boss_";
			break;
	}
	count++;
	string number;
	stringstream ss;
	ss << count;
	ss >> number;
	filename += number;
}

void DrawingBoard::tip()
{
	FillConsoleOutputAttribute(hConsoleOutput, FOREGROUND_INTENSITY | FOREGROUND_RED, 1, { 95, 0 }, &dwNumberOfEventsRead);
	FillConsoleOutputCharacter(hConsoleOutput, '*', 1, { 95, 0 }, &dwNumberOfEventsRead);

}

void DrawingBoard::readConcoleLineCharacter(COORD &crPos, string &record, int size)
{
	char *buf = new char[size + 1];
	memset(buf, 0, size + 1);
	DWORD rec = 0;
	ReadConsoleOutputCharacter(hConsoleOutput, buf, size, crPos, &rec);
	buf[size] = 0;
	record = buf;
	delete[] buf;
}

void DrawingBoard::setDefault()
{
	infomationtext_color = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	printcharacter_color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
}

void DrawingBoard::setInfomationAttribute(WORD infomation)
{
	if (infomation != 0)
		infomationtext_color = infomation;
}

void DrawingBoard::setCharacterAttribute(WORD character)
{
	if (character != 0)
		printcharacter_color = character;
}

WORD DrawingBoard::getInfomationAttribute()
{
	return infomationtext_color;
}

WORD DrawingBoard::getCharacterAttribute()
{
	return printcharacter_color;
}

void DrawingBoard::output_RF_File(ofstream &outfile, CONSOLE_SCREEN_BUFFER_INFO &consolebuf, string filename)
{
	string record;
	COORD cutStart = { 0,1 };
	ofstream colorfile(filename + ".color", ios::out | ios::binary);

	int L = consolebuf.dwMaximumWindowSize.X, R = 0,
		U = consolebuf.dwMaximumWindowSize.Y, D = 0;

	the_num_of_ch = 0;
	graph_l = graph_w = 0;

	for (int i = 1; i < consolebuf.dwMaximumWindowSize.Y; i++)
	{
		readConcoleLineCharacter(cutStart, record, consolebuf.dwMaximumWindowSize.X);
		for (int j = 0; j < consolebuf.dwMaximumWindowSize.X; j++)
		{
			if (record[j] != ' ' && record[j] != 0)
			{
				if (j < L)	L = j;
				if (j > R)	R = j;
				if (i < U)	U = i;
				if (i > D)	D = i;
				the_num_of_ch++;
			}
		}
		cutStart.Y++;
	}

	graph_l = R - L + 1, graph_w = D - U + 1;
	COORD centerPos = { ( graph_l - 1 ) / 2, ( graph_w - 1 ) / 2 };
	WORD *record_color = new WORD[graph_l];
	DWORD rec;
	COORD writeStart = { L,U };
	for (int i = 0; i < graph_w; i++)
	{
		readConcoleLineCharacter(writeStart, record, graph_l);
		ReadConsoleOutputAttribute(hConsoleOutput, record_color, graph_l, writeStart, &rec);

		outfile << record << endl;
		for (short i = 0; i < graph_l; i++)
			if (role == HERO && i == centerPos.X && writeStart.Y == centerPos.Y)
			{
				WORD color = 0x0c;
				colorfile.write(reinterpret_cast<char*>( &color ), sizeof(WORD));
			}
			else
				colorfile.write(reinterpret_cast<char*>( &record_color[i] ), sizeof(WORD));

		writeStart.Y++;
	}
	delete[] record_color;
}

DrawingBoard::~DrawingBoard()
{
	CloseHandle(hConsoleInput);
}