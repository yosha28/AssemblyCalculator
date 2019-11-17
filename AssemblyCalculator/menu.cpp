#include "pch.h"
#include "menu.h"
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <string.h>

//Menu items massive
const char *menuitems[3][3] = {
"Orders","Order input","From file",
"Calculations","By date","By storage",
"Output","To file","Print" };

Menuitm::Menuitm()
{
	itemname = NULL;
	itmposX = 0;
	itmposY = 0;
	itmwidth = 0;
	is_visible = 1;
	ischild = 0;
}

Menuitm::~Menuitm()
{
	free(itemname);
}

Menu::Menu() {

	width = 200;
	height = 3;
	tcolor = clWhite;
	bgcolor = clMagenta;
	posX = 0;
	posY = 0;
}


Menu::~Menu() {

}

void Menu::show_menu_head(Menu *topmenu) {
	/*Menu *topmenu = new Menu;*/
	for (short x = 0; x < topmenu->width; x++) {
		for (short y = 0; y < topmenu->height; y++) {
			consoleSetColors(tcolor, bgcolor);
			posmove(x, y);
			printf(" ");
		}
	}
	topmenu->posX = topmenu->posX + 10;
	topmenu->posY = topmenu->posY + 1;

	posmove(posX, posY);
	consoleSetColors(clWhite, clBlack);
}

void Menu::show_drop_down()
{
}

void Menu::menu_itm_print(pmenu *itemaddr) {
	if (itemaddr->menuitm->is_visible == true) {
		if (itemaddr->menuitm->ischild == true)
		{
			consoleSetColors(clBlack, clYellow);
		}
		else
		{
			consoleSetColors(clBlack, clMagenta);
		}

		for (int w = 0; w <= itemaddr->menuitm->itmwidth; w++) {
			for (int h = 0; h <= 2; h++) {
				posmove(itemaddr->menuitm->itmposX + w, itemaddr->menuitm->itmposY + h);
				printf(" ");
			}
		}
		posmove(itemaddr->menuitm->itmposX + 2, itemaddr->menuitm->itmposY + 1);
		printf("%s", itemaddr->menuitm->itemname);
	}
}

int Menu::menu_navigate()
{
	int keyPressed = _getch();

	switch (keyPressed)
	{
	case KEY_UP:

	default:
		break;
	}
	return 0;
}

pmenu *Menu::menu_create() //Fill menu items
{
	pmenu *startadr = NULL;
	int psize = 0;

	for (int x = 0, y = 0; y <= 2; y++) {              //take max parent menu name as base width
		int pwidth = strlen(menuitems[x][y]);
		if (pwidth > psize)
			psize = pwidth + 4;
	}

	pmenu *curitm = NULL;
	/*pmenu *previtmY = NULL;*/
	pmenu *previtmX = NULL;
	pmenu *ptemp = NULL;

	for (int x = 0; x <= 2; x++) {                       //go right thru menu

		pmenu *previtmY = NULL;

		for (int y = 0; y <= 2; y++) {                   //go down thru menu

			curitm = (pmenu*)malloc(sizeof(pmenu));      //alloc mem for menu itm
			if (curitm->prevY != NULL && curitm->nextY != NULL) {
				curitm->prevY = NULL;
				curitm->nextY = NULL;
				curitm->prevX = NULL;
				curitm->nextX = NULL;
			}

			if (NULL != previtmY) {						//fill pev itm adress
				curitm->prevY = previtmY;
			}

			if (y != 0 && NULL == previtmY->nextY) {     //fill current itm addr into prev itm
				previtmY->nextY = curitm;
			}

			if (x == 0 && y == 0) {  //take  first addr 
				startadr = curitm;

			}


			curitm->menuitm = new Menuitm;
			char *mem = (char*)malloc(100 * (sizeof(char)));
			strcpy_s(mem, 100, menuitems[x][y]);
			curitm->menuitm->itemname = mem;
			curitm->menuitm->itemcode = x + y;

			curitm->menuitm->itmposX = 20 + (x * psize); // x offset
			curitm->menuitm->itmposY = y * 3;            // y offset 
			curitm->menuitm->itmwidth = psize;           // item width
			//curitm->prevX = previtmY;
			if (y > 0) {                                 //check for child include
				curitm->menuitm->ischild = true;
				curitm->menuitm->is_visible = false;

			}

			previtmY = curitm;


			if (x != 0 && y == 0) {
				curitm->prevX = previtmX;

				previtmX->nextX = curitm;
			}

			if (y == 0) {
				previtmX = curitm;
				ptemp = previtmX;
			}
		}

	}
	startadr->prevX = ptemp; //cycle menu  by x
	ptemp->nextX = startadr;

	return startadr;
}


void Menu::menu_print(pmenu *startaddr) {
	pmenu *currentX = startaddr->prevX;
	pmenu *currentY = currentX;
	do {
		currentY = currentX;
		menu_itm_print(currentY);

		do {
			currentY = currentY->nextY;
			menu_itm_print(currentY);

		} while (NULL != currentY->nextY);

		currentX = currentX->nextX;

	} while (currentX->nextX != startaddr);
}



void consoleSetColors(ConsoleColors textColor, ConsoleColors backgroundColor) {  //setting console colors
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCons, (WORD)((backgroundColor << 4) | textColor));
}

void posmove(short x, short y) {
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(hCons, position);
}

