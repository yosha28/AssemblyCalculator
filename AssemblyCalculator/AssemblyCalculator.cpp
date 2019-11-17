#include "pch.h"
#include <iostream>
#include <locale.h>
#include "menu.h"
#include "items.h"

int main()
{
	setlocale(LC_ALL, ".1251");
	consoleSetColors(clWhite, clBlack);

	Menu *topmenu = new Menu;

	pmenu *addr = topmenu->menu_create();
	topmenu->show_menu_head(topmenu);
	topmenu->menu_print(addr);

	switch (topmenu->menu_navigate())
	{
	default:
		break;
	}

	posmove(0, 40);

	return 0;
}

