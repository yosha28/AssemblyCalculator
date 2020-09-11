#include <stdio.h>
#include <stdlib.h>
#include "pch.h"
#include "orderslist.h"
#include "calculator.h"
#include "storage.h"
#include "menu.h"




Iter::Iter()
{
	ordpassed = 0;
	maxfnd = 0;
	start = (collection*)malloc(sizeof(collection));
	start->next = NULL; 
}

Iter::~Iter()
{
	free(start);
}

packs *Bruteforce(orderslist *lastorder, Storage *ms) {

	posmove(0, 15);
	consoleSetColors(clWhite, clBlack);

	packs *packexample = NULL;
	packs *startpack = NULL;
	int numpassed = 1; //1 cos first order is allways in
	int maxfound = 0;

	orderslist *orderfirst = NULL; //cos "potentially uninitialized local pointer variable 'orderfirst' used	" says release
	orderfirst = Orders_goto_first(lastorder);

	while (orderfirst != NULL) {


		orderslist *base = orderfirst;                      //next base order
		Storage *om = new Storage;                         //orders summ matrix
		Iter *newiter = new Iter;

		//creating passed items collection classes list item brrrrrrr...
		if (packexample != NULL) {                   //if packexample exist
			packs *new_pack = (packs*)malloc(sizeof(packs));
			new_pack->nextpack = NULL;
			packexample->nextpack = new_pack;
			packexample = new_pack;
		}
		else {
			packexample = (packs*)malloc(sizeof(packs));
			packexample->nextpack = NULL;
			startpack = packexample;
		}

		//printf("==================================================\n");
		//printf("%d %d %d %d %d %d %d %d %d %d %d %d %d\n\n\n", ms->Get_bulletcams(), ms->Get_domecams(), ms->Get_othercams(), ms->reg4
		//	, ms->reg8, ms->reg16, ms->reg32, ms->switch4, ms->switch8, ms->switch16, ms->switch32, ms->box, ms->cable, ms->hdd);

		packexample->ppack = newiter;
		numpassed = 1;
		newiter->start->po_addr = base;           //writing base order as first in list
		collection *move_addr = newiter->start;   //current adr of last list in struct 

		newiter->Matrxsumm(om, base);
		orderslist *ordermove = orderfirst->next;   //pointer to compared order  

		while (ordermove != NULL) {
			newiter->Matrxsumm(om, ordermove);                    //count summ
			int msb = ms->Get_bulletcams();
			int msd = ms->Get_domecams();
			int mso = ms->Get_othercams();
			int omb = om->Get_bulletcams();
			int omd = om->Get_domecams();
			int omo = om->Get_othercams();

			if (omb > msb  // check if any item of OM (order matrix) is topped out MS storage limit
				|| omd > msd
				|| omo > mso
				|| (om->reg4) > (ms->reg4)
				|| (om->reg8) > (ms->reg8)
				|| (om->reg16) > (ms->reg16)
				|| (om->reg32) > (ms->reg32)
				|| (om->switch4) > (ms->switch4)
				|| (om->switch8) > (ms->switch8)
				|| (om->switch16) > (ms->switch16)
				|| (om->switch32) > (ms->switch32)
				|| (om->box) > (ms->box)
				|| (om->cable) > (ms->cable)
				|| (om->hdd) > (ms->hdd)) {

				//break; //to do: make diff func and jump over topping order to end
				newiter->Matrxdiff(om, ordermove);  //minus current order items from matrix - skip this order
			}
			else {

				collection *pnext = (collection*)malloc(sizeof(collection));    //add current order to list
				pnext->next = NULL;
				move_addr->next = pnext;
				move_addr = pnext;
				move_addr->po_addr = ordermove;
				numpassed++;
			}

			//printf("%d %d %d %d %d %d %d %d %d %d %d %d %d\n\n", om->Get_bulletcams(), om->Get_domecams(), om->Get_othercams(), om->reg4
			//	, om->reg8, om->reg16, om->reg32, om->switch4, om->switch8, om->switch16, om->switch32, om->box, om->cable, om->hdd);

			ordermove = ordermove->next;
		}


		packexample->ppack->ordpassed = numpassed;
		if (numpassed > maxfound) {
			maxfound = numpassed;
		}
		delete om;
		orderfirst = orderfirst->next;  //next order to be base
	}

	startpack->ppack->maxfnd = maxfound;
	return startpack;
};

void Iter::Matrxsumm(Storage *matrix, orderslist *toexpand) {

	if (strcmp(toexpand->order->camtype, "Bullet") == 0) {
		int n = (matrix->Get_bulletcams()) + (toexpand->order->camcount);
		matrix->Set_bulletcams(n);
	}

	if (strcmp(toexpand->order->camtype, "Dome") == 0) {
		int n = (matrix->Get_domecams()) + (toexpand->order->camcount);
		matrix->Set_domecams(n);
	}

	if (strcmp(toexpand->order->camtype, "other") == 0) {
		int n = (matrix->Get_othercams()) + (toexpand->order->camcount);
		matrix->Set_othercams(n);
	}

	if (toexpand->order->reg_chans == 4)
		matrix->reg4 = matrix->reg4 + toexpand->order->register_q;

	if (toexpand->order->reg_chans == 8)
		matrix->reg8 = matrix->reg8 + toexpand->order->register_q;

	if (toexpand->order->reg_chans == 16)
		matrix->reg16 = matrix->reg16 + toexpand->order->register_q;

	if (toexpand->order->reg_chans == 32)
		matrix->reg32 = matrix->reg32 + toexpand->order->register_q;

	if (toexpand->order->reg_chans == 4)
		matrix->reg4 = matrix->reg4 + toexpand->order->register_q;


	if (toexpand->order->switchtype[3] != 0)
		matrix->switch4 = matrix->switch4 + toexpand->order->switchtype[3];

	if (toexpand->order->switchtype[7] != 0)
		matrix->switch8 = matrix->switch8 + toexpand->order->switchtype[7];

	if (toexpand->order->switchtype[15] != 0)
		matrix->switch16 = matrix->switch16 + toexpand->order->switchtype[15];

	if (toexpand->order->switchtype[31] != 0)
		matrix->switch32 = matrix->switch32 + toexpand->order->switchtype[31];

	matrix->cable = matrix->cable + toexpand->order->cablelenght;
	matrix->box = matrix->box + toexpand->order->boxlenght;
	matrix->hdd = matrix->hdd + toexpand->order->hddq;

};

void Iter::Matrxdiff(Storage *matrix, orderslist *toexpand) {

	if (strcmp(toexpand->order->camtype, "Bullet") == 0) {
		int n = (matrix->Get_bulletcams()) - (toexpand->order->camcount);
		matrix->Set_bulletcams(n);
	}

	if (strcmp(toexpand->order->camtype, "Dome") == 0) {
		int n = (matrix->Get_domecams()) - (toexpand->order->camcount);
		matrix->Set_domecams(n);
	}

	if (strcmp(toexpand->order->camtype, "other") == 0) {
		int n = (matrix->Get_othercams()) - (toexpand->order->camcount);
		matrix->Set_othercams(n);
	}

	if (toexpand->order->reg_chans == 4)
		matrix->reg4 = matrix->reg4 - toexpand->order->register_q;

	if (toexpand->order->reg_chans == 8)
		matrix->reg8 = matrix->reg8 - toexpand->order->register_q;

	if (toexpand->order->reg_chans == 16)
		matrix->reg16 = matrix->reg16 - toexpand->order->register_q;

	if (toexpand->order->reg_chans == 32)
		matrix->reg32 = matrix->reg32 - toexpand->order->register_q;

	if (toexpand->order->reg_chans == 4)
		matrix->reg4 = matrix->reg4 - toexpand->order->register_q;


	if (toexpand->order->switchtype[3] != 0)
		matrix->switch4 = matrix->switch4 - toexpand->order->switchtype[3];

	if (toexpand->order->switchtype[7] != 0)
		matrix->switch8 = matrix->switch8 - toexpand->order->switchtype[7];

	if (toexpand->order->switchtype[15] != 0)
		matrix->switch16 = matrix->switch16 - toexpand->order->switchtype[15];

	if (toexpand->order->switchtype[31] != 0)
		matrix->switch32 = matrix->switch32 - toexpand->order->switchtype[31];

	matrix->cable = matrix->cable - toexpand->order->cablelenght;
	matrix->box = matrix->box - toexpand->order->boxlenght;
	matrix->hdd = matrix->hdd - toexpand->order->hddq;

};

void Print_by_storage(orderslist* lastorder, Storage *memstorage) {


	if (lastorder != NULL) {

		packs *start = Bruteforce(lastorder, memstorage);
		int max = start->ppack->maxfnd;
		Resultprint(start);
		Resulclear(start);
	}
	else {
		posmove(4, 15);
		consoleSetColors(clLightGreen, clBlack);
		printf("NO ORDERS IN SYSTEM ! ");
	};


}

void Resultprint(packs *start) {
	int firstprint = 0;
	packs *go = start;
	int maxq = go->ppack->maxfnd;

	while (go != NULL) {
		Iter *pnow = go->ppack;
		if (pnow->ordpassed == maxq && firstprint == 0) {
			int v = 20;
			firstprint = 1;
			posmove(L_FIELD, 15);

			consoleSetColors(clLightGreen, clBlack);
			printf("THOSE %d ORDERS AVIABLE BY STORAGE RESTS:\n\n", start->ppack->maxfnd);
			consoleSetColors(clWhite, clBlack);

			collection *pcol = pnow->start;

			Storage *om = new Storage;
			do {

				posmove(L_FIELD, v);

				Order *p = pcol->po_addr->order;
				int cablebox = ceil((p->cablelenght) / 305);
				printf("Order #%d - \n\n U will need %d cameras %s type,  %d Registrators with %d channels, and %d HDD  %d boxes UTP cat 5e and %d pcs cable box, Switches:  "
					, p->ordernum, p->camcount, p->camtype, p->register_q, p->reg_chans
					, p->hddq, cablebox, ((p->boxlenght) / BOX_L));
				for (int x = 4; x <= 32; ) {
					if (p->switchtype[x - 1] != 0) {
						printf("%d x %d channels ", p->switchtype[x - 1], x);
					}
					x = x * 2;
				}
				printf("\n");

				pnow->Matrxsumm(om, pcol->po_addr);


				pcol = pcol->next;
				v = v + 4;				 
			} while (pcol != NULL);

			int boxc = ceil((om->cable) / 305);
			int pcsb = ((om->box) / 2);

			printf("\n\n    Total to loading: \n\
				\n    Bullet cams = %d \
                \n    Dome cams = %d\
				\n    Other cams = %d\
				\n    4x channel Registr = %d\
				\n    8x channel Registr = %d\
				\n    16x channel Registr = %d\
				\n    32x channel Registr = %d\
				\n    4x channel Poe switch = %d\
				\n    8x channel Poe switch= %d\
				\n    16x channel Poe switch = %d\
				\n    32x channel Poe switch = %d\
				\n    UTP cat 5e cable packs = %d\
				\n    2m cable box pcs = %d"
				,om->Get_bulletcams()
				,om->Get_domecams()
			    ,om->Get_othercams()
				,om->reg4
				,om->reg8
				,om->reg16
				,om->reg32
				,om->switch4
				,om->switch8
				,om->switch16
				,om->switch32
				,boxc
				,pcsb);

					delete (om);
		}


		go = go->nextpack;
	}


}

void Resulclear(packs *start) {
	packs *nextdestr = start;
	while (nextdestr != NULL) {
		nextdestr = start->nextpack;  //remember next pack

		collection *tokill = start->ppack->start->next; //skip start member of Itr cos its clearing by destr
		while (tokill != NULL) {
			collection *nextkill = tokill->next; //remember next collection p
			free(tokill);
			tokill = nextkill;
		};

		delete start->ppack;
		free(start);
		start = nextdestr;
	}
}