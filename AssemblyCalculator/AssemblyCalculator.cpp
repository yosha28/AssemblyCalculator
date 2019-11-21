#include "pch.h"
#include <iostream>
#include <locale.h>
#include "menu.h"
//#include "items.h"
#include "orderslist.h"
#include "assembly.h"

int main()
{ 
	
	setlocale(LC_ALL, ".1251");
	consoleSetColors(clWhite, clBlack);

	Menu *topmenu = new Menu;

	orderslist *lastorder = NULL;
	pmenu *addr = topmenu->menu_create();
	topmenu->show_menu_head(topmenu);
	topmenu->menu_print(addr);

	while (1) {
		switch (int c = topmenu->menu_navigate(addr))
		{
		case 1:
			lastorder = order_itm_input(lastorder);
			break;
		default:
			posmove(20, 20);
			consoleSetColors(clWhite, clBlack);
			/*printf("%d", c);*/
			break;
		}
	}

	posmove(0, 40);

	return 0;
}

