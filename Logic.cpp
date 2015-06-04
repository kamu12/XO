#include <conio.h>
#include <iostream>
#include <ctime>
#include "Logic.h"
#include "UI.h"

using std::cin;
using std::cout;

void XO::Init()
{
	for (size_t i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
	{
		arr[i] = ' ';
	}
	for (size_t i = 0; i < SIZE; i++)
	{
		sum[i] = 0;
		isFull[i] = FALSE;
	}
	indRow = 0;
	indCol = 0;
	moveCount = 1;
}

void XO::Play()
{
	this->Init();
	PlayPtr funcPtr;
	
	if (diffLevel == EASY)
	{
		funcPtr = &XO::ComputerMoveEasy;
	}
	else if (diffLevel == MEDIUM)
	{
		funcPtr = &XO::ComputerMoveMed;
	}
	else
	{
		funcPtr = &XO::ComputerMoveHard;
	}

	if (firstMove)
	{
		Print(*this);
		bool quit = false;
		while (CheckState(*this))
		{
			UserMove(*this);
			Print(*this);
			if (CheckState(*this))
			{
				(this->*(funcPtr))();
				Print(*this);
			}
			else
			{
				break;
			}
		}
	}
	else
	{
		FirstMove();
		Print(*this);
		while (CheckState(*this))
		{
			UserMove(*this);
			Print(*this);
			if (CheckState(*this))
			{
				(this->*(funcPtr))();
				Print(*this);
			}
			else
			{
				break;
			}
		}
	}
}

void XO::ComputerMoveEasy()
{
	indRow = 0;
	indCol = 0;
	
	//find row with min sum
	int minRow = FindMinRow();
	
	// find col with min sum
	FindMinCol(minRow);
	
	arr[BOARD_SIZE * indRow + indCol] = computerMark;
	--sum[indRow];
	--sum[BOARD_SIZE + indCol];

	//change sum of diagonals
	resumDiag();
	
	IsRowFull(indRow);
	IsColFull(indCol);

	++moveCount;
}

void XO::ComputerMoveMed()
{
	indRow = 0;
	indCol = 0;

	// if could move on digonal
	if (CheckDiagonals())
	{
		/* NULL */
	}
	else
	{
		//find row with min sum
		int minRow = FindMinRow();
		
		// find col with min sum
		FindMinCol(minRow);
	}

	arr[BOARD_SIZE * indRow + indCol] = computerMark;
	--sum[indRow];
	--sum[BOARD_SIZE + indCol];

	//change sum of diagonals
	resumDiag();

	IsRowFull(indRow);
	IsColFull(indCol);

	++moveCount;
}

void XO::ComputerMoveHard()
{
	indRow = 0;
	indCol = 0;

	// take central place
	if ((moveCount == 2 || moveCount == 3) && arr[4] == ' ')
	{
		indRow = 1;
		indCol = 1;
	}
	// if could move on digonal
	else if (CheckDiagonals())
	{
		/* NULL */
	}
	else
	{
		//find row with min sum
		int minRow = FindMinRow();

		// find col with min sum
		FindMinCol(minRow);
	}

	arr[BOARD_SIZE * indRow + indCol] = computerMark;
	--sum[indRow];
	--sum[BOARD_SIZE + indCol];

	//change sum of diagonals
	resumDiag();

	IsRowFull(indRow);
	IsColFull(indCol);

	++moveCount;
}

void XO::FirstMove()
{	
	srand(time(NULL));
	indRow = rand() % 3;
	indCol = rand() % 3;

	arr[BOARD_SIZE * indRow + indCol] = computerMark;
	--sum[indRow];
	--sum[BOARD_SIZE + indCol];

	//change sum of diagonals
	resumDiag();

	IsRowFull(indRow);
	IsColFull(indCol);

	++moveCount;
}

void XO::SetUserMove(int indRow, int indCol)
{
	arr[BOARD_SIZE * indRow + indCol] = userMark;
	++sum[indRow];
	++sum[BOARD_SIZE + indCol];

	//change sum of diagonals
	resumDiag();

	IsRowFull(indRow);
	IsColFull(indCol);

	++moveCount;
}

void XO::IsRowFull(int indRow)
{
	bool flag = TRUE;
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		if (arr[BOARD_SIZE * indRow + i] == ' ')
		{
			flag = FALSE;
		}
	}
	if (flag)
	{
		isFull[indRow] = TRUE;
	}
}

void XO::IsColFull(int indCol)
{
	bool flag = TRUE;
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		if (arr[BOARD_SIZE * i  +indCol] == ' ')
		{
			flag = FALSE;
		}
	}
	if (flag)
	{
		isFull[BOARD_SIZE + indCol] = TRUE;
	}
}

int XO::FindMinRow()
{
	int min = 4;
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		if (sum[i] == -2) 
		{
			min = sum[i];
			indRow = i;
			break;
		}
		else if (sum[i] == 2)
		{
			min = sum[i];
			indRow = i;
			break;
		}
		else if (sum[i] < min && !isFull[i])
		{
			min = sum[i];
			indRow = i;
		}
	}
	return min;
}

void XO::FindMinCol(int minRow)
{
	// search for winning move and checks for block if ther's
	// such possibility in row
	if (minRow == -2) 
	{
		FindIndCol();
		//*min = sum[i];  // recoment in case of need of sum in curr col
		return;
	}
	else if (minRow == 2)
	{
		FindIndCol();
		//*min = sum[i];  // recoment in case of need of sum in curr col
		return;
	}

	int oldIndRow = indRow;
	int flag = true;
	int min = 4;

	for (size_t i = BOARD_SIZE; i < BOARD_SIZE * 2; i++)
	{
		//search for winning move
		if (sum[i] == -2)
		{
			FindIndRow(i, oldIndRow);
			//*min = sum[i];
			indCol = i - BOARD_SIZE;
			break;
		}

		// checks for block 
		else if (sum[i] == 2)
		{
			FindIndRow(i, oldIndRow);
			//*min = sum[i];
			indCol = i - BOARD_SIZE;
			break;
		}
		else if (sum[i] < min && !isFull[i])
		{
			if (arr[BOARD_SIZE * indRow + i - BOARD_SIZE] == ' ')
			{
				min = sum[i];
				indCol = i - BOARD_SIZE;
				continue;
			}
			while (arr[BOARD_SIZE * indRow + i - BOARD_SIZE] != ' ')
			{
				// if there's no free cell 
				if (indRow == 2)
				{
					flag = false;
					indRow = oldIndRow;
					break;
				}
				++indRow;
			}
			if (flag)
			{
				min = sum[i];
				indCol = i - BOARD_SIZE;
				continue;
			}
			
		}
	}
}

void XO::FindIndRow(size_t i, int oldIndRow)
{
	while (arr[BOARD_SIZE * indRow + i - BOARD_SIZE] != ' ')
	{
		if (indRow == 3)
		{
			indRow = oldIndRow;
			while (arr[BOARD_SIZE * indRow + i - BOARD_SIZE] != ' ')
			{
				if (indRow == 0)
				{
					indRow = oldIndRow;
					break;
				}
				--indRow;
			}
			break;
		}
		++indRow;
	}
}

void XO::FindIndCol()
{
	indCol = 0;
	while (arr[BOARD_SIZE * indRow + indCol] != ' ')
	{
		++indCol;
	}
	
}

bool XO::CheckDiagonals()
{
	if (sum[MAIN_DIAG] == -2 || sum[MAIN_DIAG] == 2)
	{
		int i = 0;
		while (arr[i * 4] != ' ')
		{
			++i;
			++indRow;
			++indCol;
		}
		return true;
	}
	else if (sum[LITERAL_DIAG] == -2 || sum[LITERAL_DIAG] == 2)
	{
		indCol = 2;
		int i = 0;
		while (arr[(i * 2) + 2] != ' ')
		{
			++i;
			++indRow;
			--indCol;
		}
		return true;
	}
	else
	{
		return false;
	}
}

void XO::resumDiag()
{
	sum[MAIN_DIAG] = 0;
	sum[LITERAL_DIAG] = 0;
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		if (arr[i * 4] == userMark)
		{
			++sum[MAIN_DIAG];
		}
		else if (arr[i * 4] == computerMark)
		{
			--sum[MAIN_DIAG];
		}

		if (arr[(i * 2) + 2] == userMark)
		{
			++sum[LITERAL_DIAG];
		}
		else if (arr[(i * 2) + 2] == computerMark)
		{
			--sum[LITERAL_DIAG];
		}
	}
}




