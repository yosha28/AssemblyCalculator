#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include "pch.h"
#include "orderslist.h"
#include "assembly.h"
#include "items.h"
#include "menu.h"

#define L_FIELD 4
#define C_FIELD 50
#define R_FIELD 100

//struct orderslist {
//	Order *order;
//	orderslist *next;
//	orderslist *prev;
//};

orderslist *order_itm_init() {
	orderslist *itm = NULL;
	itm = (orderslist*)malloc(sizeof(struct orderslist));
	itm->order = NULL;
	itm->next = NULL;
	itm->prev = NULL;
	return (itm);

}
//
//orderslist gotolast() {
//	return (*order_itm_init());
//}
//

orderslist *order_itm_input(orderslist * lastorder) {
	int h = L_FIELD;
	int v = 20;
	posmove(4, 15);
	consoleSetColors(clWhite, clBlack);
	printf("ORDER INPUT");

	orderslist *newodr = order_itm_init();

	Order *porder = new Order;
	newodr->order = porder;

	if (NULL != lastorder) {
		newodr->prev = lastorder;
		lastorder->next = newodr;
	}

	

	for (int i = 0; i <= 4; i++) {

		(porder->*porder->pfunc[i])(porder, h, 20 + (i * 2));

	}

	return newodr;
}

void Order::cam_quant_input(Order* noaddr, int h, int v) {
	posmove(h, v);
	printf("Input cam quantity - ");
	int camq = 0;
	scanf_s("%d", &camq);
	noaddr->camcount = camq;
	posmove(h + R_FIELD, v);
	printf("Order cam quantity - %d", noaddr->camcount);
}

void Order::cam_type_input(Order* noaddr, int h, int v) {
	int camt = 0;                  //input cam type
	do {
		posmove(h, v);
		printf("Input cam type (1-Bullet 2-Dome 3-other) - ");
		scanf_s("%d", &camt);

		posmove(h + R_FIELD, v);
		if (camt > 3 || camt < 0) {
			printf("Wrong cam type !!!               ");
		}
	} while (camt > 3 || camt < 0);
	noaddr->camtype = camtypes[camt - 1];
	printf("Order cam type - %s", noaddr->camtype);
}

void Order::register_input(Order* noaddr, int h, int v)
{
	int exit = 0;
	int regq_c = 0;
	int chnum = 0;
	char yesno;

	do {

		while (1) {
			posmove(h, v);
			printf("                                             ");
			posmove(h, v);
			printf("Input number of NVR channels (4,8,16 or 32) - ");
			scanf_s("%d", &chnum);
			if (chnum <= 32 && (chnum % 4) == 0) {
				noaddr->reg_chans = chnum;
				break;
			}
			else {
				posmove(h + R_FIELD, v);
				printf("Wrong channels number !!!               ");
			}

		}

		regq_c = ceil((float)(noaddr->camcount) / (float)chnum);  //ceil cams to registers

		while (1) {                                               //registrator quantization or input logic
			posmove(h + C_FIELD, v);
			printf("You will need %d NVR - y/n ? - ", regq_c);

			scanf_s("%c", &yesno);
			if (yesno == 'n' || yesno == 'N') {
				posmove(h + C_FIELD, v);
				printf("How many %d channels NVR You need? - ", chnum);
				int nvrq = 0;
				scanf_s("%d", &nvrq);
				posmove(h + R_FIELD, v);
				printf("Order will include %d %d-channel NVR  ", nvrq, chnum);
				noaddr->register_q = nvrq;
				exit = 1;
				break;

			}
			else if (yesno == 'y' || yesno == 'y') {
				posmove(h + R_FIELD, v);
				printf("Order will include %d %d-channel NVR  ", regq_c, chnum);
				noaddr->register_q = regq_c;
				exit = 1;
				break;
			}
			else {
				posmove(h + R_FIELD, v);
				printf("Answer Y  or  N !!!               ");
			}
		}

	} while (exit != 1);  //not nessesary logic but i will leave it here)
}

void Order::hdd_input(Order *noaddr, int h, int v)
{
	posmove(h, v);
	printf("Input HDD quantity - ");
	int hddq = 0;
	scanf_s("%d", &hddq);
	noaddr->hddq = hddq;
	posmove(h + R_FIELD, v);
	printf("Order HDD quantity - %d", noaddr->hddq);

}

void Order::cable_box_input(Order *noaddr, int h, int v) {

	int box_lenght = 0;
	int cab_lenght = 0;
	int bratio =0;

	posmove(h, v);
	printf("Input cable lenght in m.- ");
	scanf_s("%d", &cab_lenght);

	posmove(h + C_FIELD, v);
	printf("What is box lenght ratio to cable in %% ? - ");
	scanf_s("%d", &bratio);

	box_lenght = (cab_lenght / 100) * bratio;

	posmove(h + 100, v);
	printf("Order cable lenght %d m. and box lenght %d m. ", cab_lenght, box_lenght);
	noaddr->cablelenght = cab_lenght;
	noaddr->boxlenght = box_lenght;
	
}
