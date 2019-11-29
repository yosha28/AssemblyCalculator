#include "pch.h"
#include <iostream>
#include <locale.h>
#include <string.h>
#include "menu.h"
#include "tofile.h"
#include "assembly.h"
#include "storage.h"
#include "calculator.h"



int main(int argc, char* argv[])
{

	//setlocale(LC_ALL, ".1251");
	consoleSetColors(clWhite, clBlack);

	char *abs = argv[0];
	int l = 0;
	while (*abs != '.') {   //count for path symbols
		l++;
		abs++;
	}
	abs = abs - l;
	int k = l - 18;

	char *abspath = (char*)malloc((k+1) * sizeof(char));  //absolute path
	char *ordpath = (char*)malloc((k + 11) * sizeof(char)); //orders path
	char *gdspath = (char*)malloc((k + 10) * sizeof(char)); //goods path

	*(abs + k) = '\0';
	strcpy_s(abspath, k + 1, abs);
	strcpy_s(ordpath, k + 11, abs);
	strcpy_s(gdspath, k + 10, abs);
	strcat_s(ordpath, k + 11, "orders.txt");
	strcat_s(gdspath, k + 10, "goods.txt");

	Storage *memstorage = new Storage;
	memstorage->Read_to_storage(gdspath, memstorage);

	Menu *topmenu = new Menu;
	orderslist *lastorder = NULL;
	pmenu *addr = topmenu->Menu_create();

	topmenu->Show_menu_head(topmenu);
	topmenu->Menu_print(addr);
	topmenu->menu_print_startsuggestions();
	topmenu->menu_print_name();

	bool* readflg = new bool(false); //reading file base flag
	bool* exitflg = new bool(false); 

	while (*exitflg == false) {

		switch (int c = topmenu->Menu_navigate(addr,exitflg))
			{

		case 1:
			system("CLS");
			topmenu->Show_menu_head(topmenu);
			lastorder = Order_itm_input(lastorder);
			break;
		case 2:
			system("CLS");
			topmenu->Show_menu_head(topmenu);
			lastorder = Read_from_file(lastorder, readflg, ordpath);
			break;
		case 4:
			system("CLS");
			topmenu->Show_menu_head(topmenu);
			memstorage->Storage_print();
			break;
		case 5:
			system("CLS");
			topmenu->Show_menu_head(topmenu);
			Print_by_storage(lastorder,memstorage);
			break;
		case 7:
			system("CLS");
			topmenu->Show_menu_head(topmenu);
			Write_to_file(lastorder, readflg, ordpath);
			break;
		case 8:
			system("CLS");
			topmenu->Show_menu_head(topmenu);
			Out_to_screen(lastorder);
			break;
		default:
			posmove(20, 20);
			consoleSetColors(clWhite, clBlack);
			break;
		}
	}

	posmove(0, 40); 

	Free_orders(lastorder);  //clear orders
	topmenu->Free_menu(addr); //clear menus

	delete memstorage;
	free(abspath);
	free(ordpath);
	free(gdspath);


	return 0;
}

