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
	is_active = 0;
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

void Menu::show_drop_down(pmenu *menuaddr, pmenu *position)
{
	while (NULL != position->nextY) {    //make lower items visible
		position->nextY->menuitm->is_visible = true;
		position = position->nextY;
	}
	menu_print(menuaddr); //reprint menu
}

void Menu::hide_drop_down(pmenu *menuaddr, pmenu *position)
{
	while (NULL != position->prevY) {  //rewind to up
		position = position->prevY;
	}
	while (NULL != position->nextY) {    //make lower items invisible
		position->nextY->menuitm->is_visible = false;
		position = position->nextY;
	}

	menu_print(menuaddr); //reprint menu
}

void Menu::burn_current(pmenu *position) {

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

		if (itemaddr->menuitm->is_active) {
			consoleSetColors(clBlack, clLightRed);
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
	else {
		consoleSetColors(clBlack, clBlack);
		for (int w = 0; w <= itemaddr->menuitm->itmwidth; w++) {
			for (int h = 0; h <= 2; h++) {
				posmove(itemaddr->menuitm->itmposX + w, itemaddr->menuitm->itmposY + h);
				printf(" ");
			}
		}

	}
}

int Menu::menu_navigate(pmenu *menuaddr)
{
	menu_print(menuaddr);
	pmenu *position = menuaddr;
	int goout = 0;

	do {
		posmove(0, 0);
		int keyPressed = _getch();

		switch (keyPressed)
		{
		case KEY_UP:
			if (NULL != position->prevY) {
				position->menuitm->is_active = false;
				menu_itm_print(position);
				position = position->prevY;
				position->menuitm->is_active = true;
				menu_itm_print(position);
				if (NULL == position->prevY)
					hide_drop_down(menuaddr, position);
			}
			break;
		case KEY_DOWN:
			if (NULL != position->nextY) {
				if (NULL == position->prevY) {          // check if upper - expand lower items
					show_drop_down(menuaddr, position);
				}
				position->menuitm->is_active = false;
				menu_itm_print(position);
				position = position->nextY;
				position->menuitm->is_active = true;
				menu_itm_print(position);
			}
			break;
		case KEY_RIGHT:
			
			if (NULL == position->prevY) {
				hide_drop_down(menuaddr, position);
				position->menuitm->is_active = false;
				menu_itm_print(position);
				position = position->nextX;

				if (NULL == position->prevY) {          // check if upper - expand lower items
					show_drop_down(menuaddr, position);
				}
				position->menuitm->is_active = true;
				menu_itm_print(position);
			}
			break;
		case KEY_LEFT:
			
			if (NULL == position->prevY) {
				hide_drop_down(menuaddr, position);
				position->menuitm->is_active = false;
				menu_itm_print(position);
				position = position->prevX;

				if (NULL == position->prevY) {          // check if upper - expand lower items
					show_drop_down(menuaddr, position);
				}
				position->menuitm->is_active = true;
				menu_itm_print(position);
			}
			break;
		case KEY_ENTER:
			hide_drop_down(menuaddr, position);
			goout = 1;
			break;
		default:
			position->menuitm->is_active = true;
			menu_itm_print(position);
			break;
		}
	} while (goout != 1);

	position->menuitm->is_active = false;
	return position->menuitm->itemcode;
}

pmenu *Menu::menu_create() //Fill menu items
{

	pmenu *startadr = NULL;
	int psize = 0;
	int code = 0;

	for (int x = 0, y = 0; y <= 2; y++) {              //take max parent menu name as base width
		int pwidth = strlen(menuitems[x][y]);
		if (pwidth > psize)
			psize = pwidth + 4;
	}

	pmenu *curitm = NULL;
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
			curitm->menuitm->itemcode = code;
			code++;

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

