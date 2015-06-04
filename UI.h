#include "Logic.h"
#ifndef _UI_H_
#define _UI_H_

#define ARROW -32
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13
#define ESC 27

// recoment in case of change controls
//#define UP 'w'
//#define DOWN 's'
//#define LEFT 'a'
//#define RIGHT 'd'

#define WHITE 7
#define GREY 8

void Logo();
void GoTo(int x, int y);
int GetColor();
void SetColor(int color);
void HideCursor();
void ShowCursor();

void Start();
void MainMenu(XO& xo);
void OptionsMenu(XO& xo);

void ChooseDiffLevel(XO& xo);
void ChooseFirstMove(XO& xo);
void ChangeSign(XO& xo);

void PrintField();
void Print(XO& currState);

void UserMove(XO& xo);

bool CheckState(XO& xo);

#endif /*_UI_H_*/
