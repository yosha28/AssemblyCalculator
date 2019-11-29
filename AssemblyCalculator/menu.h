#ifndef MENU_H
#define MENU_H

#define KEY_UP        72
#define KEY_DOWN      80
#define KEY_LEFT      75
#define KEY_RIGHT     77
#define KEY_ENTER     13  
#define KEY_ESCAPE    27

enum ConsoleColors {      // LRGB LRGB    Light Reg Green Blue 
	clBlack = 0  // 0000 0000
	, clBlue = 1  // 0000 0001
	, clGreen = 2  // 0000 0010
	, clCyan = 3  // 0000 0011
	, clRed = 4  // 0000 0100
	, clMagenta = 5  // 0000 0101
	, clBrown = 6  // 0000 0110
	, clLightGrey = 7  // 0000 0111
	, clDarkGrey = 8  // 0000 1000 
	, clLightBlue = 9  // 0000 1001
	, clLightGreen = 10  // 0000 1010
	, clLightCyan = 11  // 0000 1011
	, clLightRed = 12  // 0000 1100
	, clLightMagenta = 13  // 0000 1101
	, clYellow = 14  // 0000 1110
	, clWhite = 15  // 0000 1111
};



class Menuitm {
private:
public:
	Menuitm();
	~Menuitm();
	char *itemname;
	int itemcode;
	short itmposX;
	short itmposY;
	short itmwidth;
	bool is_visible;
	bool ischild;
	bool is_active;

protected:
}; 

struct pmenu {            //menu item list example
	Menuitm *menuitm;
	pmenu *prevX;
	pmenu *nextX;
	pmenu *prevY;
	pmenu *nextY;
};

class Menu {
private:
	short width;
	short height;
	ConsoleColors tcolor;
	ConsoleColors bgcolor;
public:
	Menu();
	~Menu();
	void Show_menu_head(Menu*);
	void Show_drop_down(pmenu *, pmenu *);
	void Hide_drop_down(pmenu *, pmenu *);
	void Burn_current(pmenu * position);
	short posX;
	short posY;
	pmenu *Menu_create();
	void Menu_print(pmenu *);
	void menu_print_startsuggestions();
	void menu_print_name();
	void Menu_itm_print(pmenu *);
	int Menu_navigate(pmenu *, bool*);
	void Free_menu(pmenu*);

protected:

};

void posmove(short x, short y);
void consoleSetColors(ConsoleColors textColor, ConsoleColors backgroundColor);

#endif
