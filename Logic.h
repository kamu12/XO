#ifndef _LOGIC_H_
#define _LOGIC_H_

#define COMPUTER 0
#define USER 1
#define DRAW 2

#define EASY 3
#define MEDIUM 4
#define HARD 5

#define BOARD_SIZE 3
#define SIZE 8

#define MAIN_DIAG 6
#define LITERAL_DIAG 7

#define X 'X'
#define O 'O'

#define TRUE 1
#define FALSE 0

struct XO
{
	char arr[BOARD_SIZE*BOARD_SIZE];
	int sum[SIZE];
	bool isFull[SIZE];
	int indRow;
	int indCol;
	char computerMark = O;
	char userMark = X;
	bool firstMove = USER;
	size_t diffLevel = EASY;
	size_t moveCount;
	typedef void (XO::*PlayPtr)();

	void Init();

	void Play();

	// implement computer move
	void ComputerMoveEasy();
	void ComputerMoveMed();
	void ComputerMoveHard();

	// first move for computer if it moves first
	void FirstMove();

	void SetUserMove(int indRow, int indCol);

	// checks if row is full
	void IsRowFull(int indRow);
	// checks if col is full
	void IsColFull(int indCol);

	// search for most convenient row for next computer move
	int FindMinRow();
	// search for most convenient row for next computer move
	void FindMinCol(int minRow);

	// search for proper row if convenient col is alerady found
	void FindIndRow(size_t i, int oldIndRow);
	void FindIndCol();

	bool CheckDiagonals();
	void resumDiag();

};

#endif /*_LOGIC_H_*/
