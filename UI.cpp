#include <Windows.h>
#include <conio.h>
#include <iostream>
#include "UI.h"
#include "Logic.h"

using std::cout;
using std::endl;

void Logo()
{
	system("color F8");

	cout << "\t\t  _   _                   _     _                \n" <<
		"\t\t | \\ | |                 | |   | |         ___   \n" <<
		"\t\t |  \\| | ___  _   _  __ _| |__ | |_ ___   ( _ )  \n" <<
		"\t\t | . ` |/ _ \\| | | |/ _` | '_ \\| __/ __|  / _ \\/\\\n" <<
		"\t\t | |\\  | (_) | |_| | (_| | | | | |_\\__ \\ | (_>  <\n" <<
		"\t\t \\_| \\_/\\___/ \\__,_|\\__, |_| |_|\\__|___/  \\___/\\/\n" <<
		"\t\t                     __/ |                       \n" <<
		"\t\t                    |___/                        \n" <<
		"\t\t   _____                                        \n" <<
		"\t\t  /  __ \\                                        \n" <<
		"\t\t  | /  \\/_ __ ___  ___ ___  ___  ___             \n" <<
		"\t\t  | |   | '__/ _ \\/ __/ __|/ _ \\/ __|            \n" <<
		"\t\t  | \\__/\\ | | (_) \\__ \\__ \\  __/\\__ \\            \n" <<
		"\t\t   \\____/_|  \\___/|___/___/\\___||___/            \n";

	GoTo(25, 18);
	cout << "\tCONSOLE EDITION" << endl;
	GoTo(26, 22);
	cout << "Press any key to continue...";
	_getch();
	system("cls");
}

void GoTo(int x, int y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

int GetColor()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	return info.wAttributes;
}

void SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void HideCursor()
{
	HANDLE hConsoleOutput;
	CONSOLE_CURSOR_INFO structCursorInfo;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(hConsoleOutput, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsoleOutput, &structCursorInfo);
}

void ShowCursor()
{
	HANDLE hConsoleOutput;
	CONSOLE_CURSOR_INFO structCursorInfo;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(hConsoleOutput, &structCursorInfo);
	structCursorInfo.bVisible = TRUE;
	SetConsoleCursorInfo(hConsoleOutput, &structCursorInfo);
}

void Start()
{
	Logo();

	XO xo;

	MainMenu(xo);
}

void MainMenu(XO& xo)
{
	int currColor = GetColor();
	const size_t menuCount = 3;
	char* menuList[menuCount] = { "Play", "Options", "Quit" };

	size_t xPos = 10;
	size_t i = 0;
	int yPos[menuCount] = { 5, 7, 9 };

	bool quit = false;

	while (!quit)
	{
		system("color F8");
		system("cls");
		HideCursor();

		GoTo(13, 3);
		SetColor(currColor);
		cout << "Main menu:" << endl;

		for (size_t i = 0; i < menuCount; i++)
		{
			GoTo(xPos, yPos[i]);
			SetColor(currColor);
			cout << menuList[i];
		}

		GoTo(xPos, 13);
		SetColor(currColor);
		cout << "Tip: Choose the proper action and press ENTER" << endl;

		GoTo(xPos, yPos[i]);
		SetColor(BACKGROUND_INTENSITY);
		cout << menuList[i];

		char resp = _getch();
		switch (resp)
		{
		case ARROW:
			resp = _getch();
			if (resp == UP)
			{
				if (i > 0)
				{
					GoTo(xPos, yPos[i]);
					SetColor(currColor);
					cout << menuList[i] << endl;
					--i;
				}
			}
			else if (resp == DOWN)
			{
				if (i < menuCount - 1)
				{
					GoTo(xPos, yPos[i]);
					SetColor(currColor);
					cout << menuList[i] << endl;
					++i;
				}
			}
			break;
		case ENTER:
			if (i == 0){ xo.Play(); }
			else if (i == 1){ OptionsMenu(xo); }
			else if (i == 2){ quit = true; }
			break;
		default:
			break;
		}
	}
}

void OptionsMenu(XO& xo)
{
	system("color F8");
	int currColor = GetColor();


	const size_t menuCount = 3;
	char* menuList[menuCount] = { "Select difficulty level", "Who moves first?", "Change your sign" };
	size_t xPos = 10;
	size_t i;
	int yPos[menuCount] = { 5, 7, 9 };

	i = 0;
	bool quit = false;

	while (!quit)
	{
		system("color F8");
		system("cls");

		GoTo(13, 3);
		SetColor(currColor);
		cout << "Options menu:" << endl;

		for (size_t i = 0; i < menuCount; i++)
		{
			GoTo(xPos, yPos[i]);
			SetColor(currColor);
			cout << menuList[i];
		}

		GoTo(xPos, 13);
		SetColor(currColor);
		cout << "Press ESC to return to main menu" << endl;

		GoTo(xPos, 15);
		SetColor(currColor);
		cout << "Tip: Choose the proper action and press ENTER" << endl;

		GoTo(xPos, yPos[i]);
		SetColor(BACKGROUND_INTENSITY);
		cout << menuList[i] << endl;
		char resp = _getch();
		switch (resp)
		{
		case ARROW:
			resp = _getch();
			if (resp == UP)
			{
				if (i > 0)
				{
					GoTo(xPos, yPos[i]);
					SetColor(currColor);
					cout << menuList[i] << endl;
					--i;
				}
			}
			else if (resp == DOWN)
			{
				if (i < menuCount - 1)
				{
					GoTo(xPos, yPos[i]);
					SetColor(currColor);
					cout << menuList[i] << endl;
					++i;
				}
			}
			break;
		case ENTER:
			if (i == 0){ ChooseDiffLevel(xo); }
			else if (i == 1){ ChooseFirstMove(xo); }
			else if (i == 2){ ChangeSign(xo); }
			break;
		case ESC:
			quit = true;
		default:
			break;
		}
	}
}

void ChooseDiffLevel(XO& xo)
{
	system("color F8");
	system("cls");

	int currColor = GetColor();
	const size_t menuCount = 3;
	char* menuList[menuCount] = { "Easy", "Medium", "Hard" };
	size_t xPos = 13;
	size_t i;
	int yPos[menuCount] = { 5, 7, 9 };

	GoTo(xPos, 3);
	SetColor(currColor);
	cout << "Choose difficulty level:" << endl;
	xPos = 10;

	for (i = 0; i < menuCount; i++)
	{
		GoTo(xPos, yPos[i]);
		SetColor(currColor);
		cout << menuList[i];
	}

	i = 0;
	bool quit = false;

	while (!quit)
	{
		GoTo(xPos, yPos[i]);
		SetColor(BACKGROUND_INTENSITY);
		cout << menuList[i] << endl;
		char resp = _getch();
		switch (resp)
		{
		case ARROW:
			resp = _getch();
			if (resp == UP)
			{
				if (i > 0)
				{
					GoTo(xPos, yPos[i]);
					SetColor(currColor);
					cout << menuList[i] << endl;
					--i;
				}
			}
			else if (resp == DOWN)
			{
				if (i < menuCount - 1)
				{
					GoTo(xPos, yPos[i]);
					SetColor(currColor);
					cout << menuList[i] << endl;
					++i;
				}
			}
			break;
		case ENTER:
			if (i == 0)
			{
				xo.diffLevel = EASY;
				GoTo(xPos, 11);
				SetColor(currColor);
				cout << "Modified!" << endl;
				GoTo(xPos, 12);
				cout << "Press any key to return to options menu...";
				quit = true;
				_getch();
			}
			else if (i == 1)
			{
				xo.diffLevel = MEDIUM;
				GoTo(xPos, 11);
				SetColor(currColor);
				cout << "Modified!" << endl;
				GoTo(xPos, 12);
				cout << "Press any key to return to options menu...";
				quit = true;
				_getch();
			}
			else if (i == 2)
			{
				xo.diffLevel = HARD;
				GoTo(xPos, 11);
				SetColor(currColor);
				cout << "Modified!" << endl;
				GoTo(xPos, 12);
				cout << "Press any key to return to options menu...";
				quit = true;
				_getch();
			}
			break;
		case ESC:
			quit = true;
			break;
		default:
			GoTo(xPos, 15);
			SetColor(currColor);
			cout << "Tip: Choose the proper action and press ENTER" << endl;
			break;
		}
	}
}

void ChooseFirstMove(XO& xo)
{
	system("color F8");
	system("cls");

	int currColor = GetColor();
	const size_t menuCount = 2;
	char* menuList[menuCount] = { "Computer", "Player" };
	size_t xPos = 13;
	size_t i;
	int yPos[menuCount] = { 5, 7 };

	GoTo(xPos, 3);
	SetColor(currColor);
	cout << "Who moves first?" << endl;
	xPos = 10;

	for (i = 0; i < menuCount; i++)
	{
		GoTo(xPos, yPos[i]);
		SetColor(currColor);
		cout << menuList[i];
	}

	i = 0;
	bool quit = false;

	while (!quit)
	{
		GoTo(xPos, yPos[i]);
		SetColor(BACKGROUND_INTENSITY);
		cout << menuList[i] << endl;
		char resp = _getch();
		switch (resp)
		{
		case ARROW:
			resp = _getch();
			if (resp == UP)
			{
				if (i > 0)
				{
					GoTo(xPos, yPos[i]);
					SetColor(currColor);
					cout << menuList[i] << endl;
					--i;
				}
			}
			else if (resp == DOWN)
			{
				if (i < menuCount - 1)
				{
					GoTo(xPos, yPos[i]);
					SetColor(currColor);
					cout << menuList[i] << endl;
					++i;
				}
			}
			break;
		case ENTER:
			if (i == 0)
			{
				xo.firstMove = COMPUTER;
				GoTo(xPos, 10);
				SetColor(currColor);
				cout << "Modified!" << endl;
				GoTo(xPos, 11);
				cout << "Press any key to return to options menu...";
				quit = true;
				_getch();
			}
			else if (i == 1)
			{
				xo.firstMove = USER;
				GoTo(xPos, 10);
				SetColor(currColor);
				cout << "Modified!" << endl;
				GoTo(xPos, 11);
				cout << "Press any key to return to options menu...";
				quit = true;
				_getch();
			}
			break;
		case ESC:
			quit = true;
			break;
		default:
			GoTo(xPos, 13);
			SetColor(currColor);
			cout << "Tip: Choose the proper action and press ENTER" << endl;
			break;
		}
	}

}

void ChangeSign(XO& xo)
{
	system("color F8");
	system("cls");

	size_t xPos = 13;
	int currColor = GetColor();

	if (xo.computerMark == O)
	{
		xo.computerMark = X;
		xo.userMark = O;
		GoTo(xPos, 8);
		SetColor(currColor);
		cout << "Your sign was changed to: " << xo.userMark << endl;
		GoTo(xPos, 11);
		cout << "Press any key to return to options menu...";
		_getch();
	}
	else
	{
		xo.computerMark = O;
		xo.userMark = X;
		GoTo(xPos, 8);
		SetColor(currColor);
		cout << "Your sign was changed to: " << xo.userMark << endl;
		GoTo(xPos, 11);
		cout << "Press any key to return to options menu...";
		_getch();
	}
}

void PrintField()
{
	size_t xPos = 25;
	size_t yPos = 5;
	GoTo(xPos, yPos);
	cout << '\xc9' << '\xcd' << '\xd1' << '\xcd' << '\xd1' << '\xcd' << '\xbb' << endl;
	++yPos;
	GoTo(xPos, yPos);
	cout << '\xba' << ' ' << '\xb3' << ' ' << '\xb3' << ' ' << '\xba' << endl;
	++yPos;
	GoTo(xPos, yPos);
	cout << '\xc7' << '\xc4' << '\xc5' << '\xc4' << '\xc5' << '\xc4' << '\xc7' << endl;
	++yPos;
	GoTo(xPos, yPos);
	cout << '\xba' << ' ' << '\xb3' << ' ' << '\xb3' << ' ' << '\xba' << endl;
	++yPos;
	GoTo(xPos, yPos);
	cout << '\xc7' << '\xc4' << '\xc5' << '\xc4' << '\xc5' << '\xc4' << '\xc7' << endl;
	++yPos;
	GoTo(xPos, yPos);
	cout << '\xba' << ' ' << '\xb3' << ' ' << '\xb3' << ' ' << '\xba' << endl;
	++yPos;
	GoTo(xPos, yPos);
	cout << '\xc8' << '\xcd' << '\xcf' << '\xcd' << '\xcf' << '\xcd' << '\xbc' << endl;
}

void Print(XO& xo)
{
	system("color F8");
	system("cls");

	PrintField();

	size_t xPos = 26;
	size_t yPos = 6;

	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		GoTo(xPos, yPos);
		for (size_t j = 0; j < BOARD_SIZE; j++)
		{
			GoTo(xPos, yPos);
			if (xo.arr[BOARD_SIZE * i + j] != ' ')
			{
				cout << xo.arr[BOARD_SIZE * i + j];
			}
			xPos += 2;
		}
		xPos = 26;
		yPos += 2;
	}

	GoTo(11, 2);
	cout << "Use arrows to navigate and ENTER to choose cell";
}

void UserMove(XO& xo)
{
	ShowCursor(); 

	int currColor = GetColor();
	const size_t fieldSize = 3;

	size_t xPos = 26;
	size_t yPos = 6;
	GoTo(xPos, yPos);

	size_t i = 0;
	size_t j = 0;
	bool quit = false;

	while (!quit)
	{
		char resp = _getch();
		switch (resp)
		{
		case ARROW:
			resp = _getch();
			if (resp == UP)
			{
				if (i > 0)
				{
					yPos -= 2;
					GoTo(xPos, yPos);
					--i;
				}
			}
			else if (resp == DOWN)
			{
				if (i < fieldSize - 1)
				{
					yPos += 2;
					GoTo(xPos, yPos);
					++i;
				}
			}
			else if (resp == LEFT)
			{
				if (j > 0)
				{
					xPos -= 2;
					GoTo(xPos, yPos);
					--j;
				}
			}
			else if (resp == RIGHT)
			{
				if (j < fieldSize - 1)
				{
					xPos += 2;
					GoTo(xPos, yPos);
					++j;
				}
			}
			break;
		case ENTER:
			if (xo.arr[i* BOARD_SIZE + j] == ' ')
			{
				xo.SetUserMove(i, j);
				quit = true;
			}
			break;
		case ESC:

			break;
		default:
			break;
		}
	}
}

bool CheckState(XO& xo)
{
	size_t xPos = 12;
	size_t yPos = 16;

	for (size_t i = 0; i < SIZE; i++)
	{
		// if sb win
		if (xo.sum[i] == BOARD_SIZE)
		{
			GoTo(xPos, yPos);
			std::cout << "You Win!!!";
			yPos += 2;
			GoTo(xPos, yPos);
			cout << "Press any key to return to main menu...";
			_getch();
			return false;
		}
		else if (xo.sum[i] == -BOARD_SIZE)
		{
			GoTo(xPos, yPos);
			std::cout << "Computer Win!!!";
			yPos += 2;
			GoTo(xPos, yPos);
			cout << "Press any key to return to main menu...";
			_getch();
			return false;
		}
		else if (xo.sum[i] == 2 || xo.sum[i] == -2)
		{
			return true;
		}
	}
	if (xo.moveCount > 7)
	{
		GoTo(xPos, yPos);
		std::cout << "Draw...";
		yPos += 2;
		GoTo(xPos, yPos);
		cout << "Press any key to return to main menu...";
		_getch();
		return false;
	}
}



