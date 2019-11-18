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
	while (1) {
		switch (int c = topmenu->menu_navigate(addr))
		{

		default:
			posmove(20, 20);
			consoleSetColors(clWhite, clBlack);
			printf("%d", c);
			break;
		}
	}

	posmove(0, 40);

	return 0;
}

