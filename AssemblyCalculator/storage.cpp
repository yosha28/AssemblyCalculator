#include <stdio.h>
#include <stdlib.h>
#include "pch.h"
#include "storage.h"
#include "menu.h"
#include "orderslist.h"

FILE *fstore = NULL;

Storage::Storage()
{
	domecams = 0;
	bulletcams = 0;
	othercams = 0;
	reg4 = 0;
	reg8 = 0;
	reg16 = 0;
	reg32 = 0;
	switch32 = 0;
	switch16 = 0;
	switch8 = 0;
	switch4 = 0;
	cable = 0;
	box = 0;
	hdd = 0;

};

Storage::~Storage()
{
}

void Storage::Set_domecams(int domecamsQ)
{
	if (domecamsQ != domecams)
		domecams = domecamsQ;

}

void Storage::Set_bulletcams(int bulletcamsQ)
{
	if (bulletcamsQ != bulletcams)
		bulletcams = bulletcamsQ;
}

void Storage::Set_othercams(int othercamsQ)
{
	if (othercamsQ != othercams)
		othercams = othercamsQ;
}

int Storage::Get_domecams()
{
	return domecams;
}

int Storage::Get_bulletcams()
{
	return bulletcams;
}

int Storage::Get_othercams()
{
	return othercams;
}

Storage * Storage::Read_to_storage(const char *sfilename, Storage *pstorage)
{
	if (!fopen_s(&fstore, sfilename, "r")) {

		char *string = (char*)malloc(1024 * sizeof(char));

		while (fgets(string, 1024, fstore) && (!feof(fstore))) {

			Parse_fstorage(pstorage, string);
		}
		fclose(fstore);
	}
	else {
		consoleSetColors(clRed, clBlack);
		printf("                      STORAGE FILE READ ERROR ! error:%d", fopen_s(&fstore, sfilename, "r"));
	}

	return pstorage;
}

void Storage::Parse_fstorage(Storage *pstorage, char *string) {

	//pointers massive create & fill
	const char *p = NULL;
	const char *pmas[14];
	for (int i = 0; i <= 13; i++) {
		p = (char*)malloc(11 * sizeof(char));
		pmas[i] = p;
	}


	//parse thru string
	const char *smover = string;
	int type = 0;
	char *buff = (char*)pmas[type];
	while (*smover != '\n') {

		if (*smover != '|') {
			*buff = *smover;
			buff++;
		}
		else {
			*buff = '\0';
			type++;
			buff = (char*)pmas[type];
		}

		smover++;
	}


	//storage filling
	pstorage->Set_domecams(atoi(pmas[0]));
	pstorage->Set_bulletcams(atoi(pmas[1]));
	pstorage->Set_othercams(atoi(pmas[2]));
	pstorage->reg4 = atoi(pmas[3]);
	pstorage->reg8 = atoi(pmas[4]);
	pstorage->reg16 = atoi(pmas[5]);
	pstorage->reg32 = atoi(pmas[6]);
	pstorage->switch32 = atoi(pmas[7]);
	pstorage->switch16 = atoi(pmas[8]);
	pstorage->switch8 = atoi(pmas[9]);
	pstorage->switch4 = atoi(pmas[10]);
	pstorage->cable = (305 * atoi(pmas[11]));
	pstorage->box = (BOX_L*atoi(pmas[12]));
	pstorage->hdd = atoi(pmas[13]);


	//free buffer
	for (int i = 0; i <= 13; i++) {
		char *p = (char*)realloc((char*)pmas[i], 11);
		free(p);
	}


};

void Storage::Storage_print() {
	int cabb = ceil(this->cable / 305);
	consoleSetColors(clWhite, clBlack);
	posmove(L_FIELD, 15);
	printf("WHAT WE HAVE IN STORAGE:\n\n");

	printf("    %d bullet cams \n\n"
		"    %d dome cams \n\n"
		"    %d other cams \n\n"
		"    %d x 4channel registrators \n\n"
		"    %d x 8channel registrators \n\n"
		"    %d x 16channel registrators \n\n"
		"    %d x 32channel registrators \n\n"
		"    %d Hard disk drives \n\n"
		"    %d 4channel switch \n\n"
		"    %d 8channel switch \n\n"
		"    %d 16channel switch \n\n"
		"    %d 32channel switch \n\n"
		"    %d m. UTP Cat 5e cable in %d boxes \n\n"
		"    %d m. cable box in %d parts \n\n"

		, this->bulletcams
		, this->domecams
		, this->othercams
		, this->reg4
		, this->reg8
		, this->reg16
		, this->reg32
		, this->hdd
		, this->switch4
		, this->switch8
		, this->switch16
		, this->switch32
		,this->cable, cabb
		,this->box, this->box/BOX_L
	);



}

