#ifndef STORAGE_H
#define STORAGE_H

#include <stdlib.h>
#include <stdio.h>
#include "pch.h"

#define BOX_L 2 

class Storage {

private:
	int domecams;
	int bulletcams;
	int othercams;

public:
	Storage();
	~Storage();
	int reg4;
	int reg8;
	int reg16;
	int reg32;
	int switch32;
	int switch16;
	int switch8;
	int switch4;
	int cable;
	int box;
	int hdd;
	void Set_domecams(int);
	void Set_bulletcams(int);
	void Set_othercams(int);
	int Get_domecams();
	int Get_bulletcams();
	int Get_othercams();

	Storage *Read_to_storage(const char*, Storage *);
	void Parse_fstorage(Storage * pstorage, char * string);
	void Storage_print();


protected:
	
};


#endif // !STORAGE_H

