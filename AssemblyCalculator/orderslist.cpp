#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include "pch.h"
#include "orderslist.h"
#include "assembly.h"
#include "items.h"
#include "menu.h"
#include <time.h>




orderslist *Order_itm_init() {
	orderslist *itm = NULL;
	itm = (orderslist*)malloc(sizeof(struct orderslist));
	itm->order = NULL;
	itm->next = NULL;
	itm->prev = NULL;
	return (itm);

}

void order_itm_delete(orderslist *newodr) {
	free(newodr);
}

orderslist *Order_itm_input(orderslist * lastorder) {
	int h = L_FIELD;
	int v = 20;
	posmove(L_FIELD, 15);
	consoleSetColors(clWhite, clBlack);
	
	orderslist *newodr = Order_itm_init();

	Order *porder = new Order;
	newodr->order = porder;

	newodr->order->ordernum = porder->Order_number_gen();
	printf("ORDER INPUT  # %d", newodr->order->ordernum);

	for (int i = 0; i <= 5; i++) {

		(porder->*porder->pfunc[i])(porder, h, 20 + (i * 2));

	}


	do {
		posmove(R_FIELD, 20 + (6 * 2));
		printf("Save order? y/n - ");
		char yesno = ' ';
		scanf_s("%c", &yesno);

		if (yesno == 'y' || yesno == 'Y') {
			if (NULL != lastorder) {
				newodr->prev = lastorder;
				lastorder->next = newodr;

			}
			return newodr;
		}
		else if (yesno == 'n' || yesno == 'N') {
			delete porder;
			order_itm_delete(newodr);
			return lastorder;

		}
	} while (1);

}

void Order::Cam_quant_input(Order* noaddr, int h, int v) {
	posmove(h, v);
	printf("Input cam quantity - ");
	int camq = 0;
	scanf_s("%d", &camq);
	noaddr->camcount = camq;
	posmove(h + R_FIELD, v);
	printf("Order cam quantity - %d", noaddr->camcount);
}

void Order::Cam_type_input(Order* noaddr, int h, int v) {
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

void Order::Register_input(Order* noaddr, int h, int v)
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

void Order::Hdd_input(Order *noaddr, int h, int v)
{
	posmove(h, v);
	printf("Input HDD quantity - ");
	int hddq = 0;
	scanf_s("%d", &hddq);
	noaddr->hddq = hddq;
	posmove(h + R_FIELD, v);
	printf("Order HDD quantity - %d", noaddr->hddq);

}

void Order::Cable_box_input(Order *noaddr, int h, int v) {

	int box_lenght = 0;
	int cab_lenght = 0;
	int bratio = 0;

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

void Order::Switch_input(Order* noaddr, int h, int v)
{
	float sw_q = (noaddr->register_q + noaddr->camcount + 1); //suggest switch config
	int  switch_chan_q = (ceil(sw_q / 4) * 4);

	for (int a = 32; a >= 4; ) {
		while (switch_chan_q >= a) {
			(noaddr->switchtype[a - 1])++;
			switch_chan_q = switch_chan_q - a;
		}
		a = a / 2;
	}
	

	posmove(h, v);
	printf("Suggested Poe switch config: ");                    //print suggestion

	for (int a = 32; a >= 4; ) {
		if (switchtype[a - 1] != 0) {
			printf("%d x %dch , ", switchtype[a - 1], a);
		}
		a = a / 2;
	}

	int yesno = 0;
	int exit = 0;

	while (1) {
		posmove(h + C_FIELD, v);
		printf("Is it right? - y/n ? - ");

		scanf_s("%c", &yesno);
		if (yesno == 'n' || yesno == 'N') {
			posmove(h + C_FIELD, v);

			for (int a = 32; a >= 4; ) {
				posmove(h + C_FIELD, v);
				printf("                                           ", a);
				posmove(h + C_FIELD, v);
				printf("How many %d channels switch You need? - ", a);
				int nvrq = 0;
				scanf_s("%d", &nvrq);
				noaddr->switchtype[a - 1] = nvrq;
				a = a / 2;
			}


		}
		else if (yesno == 'y' || yesno == 'y') {
			break;
		}
		else {
			posmove(h + R_FIELD, v);
			printf("Answer Y  or  N !!!               ");
		}
	}

	posmove(h + R_FIELD, v);
	printf("Order will include ");
	for (int a = 32; a >= 4; ) {
		if (switchtype[a - 1] != 0) {
			printf("%d x %dch , ", switchtype[a - 1], a);
		}
		a = a / 2;
	}
	printf("switch");

}

long Order::Order_number_gen() {
	char *gen = (char*)malloc(16 * sizeof(char));
	char *pf = gen;
	int i = 17;  //cut of genersted num
	char buff[26];
	time_t sec = time(NULL);
	ctime_s(buff, sizeof(buff), &sec);
	
	while (buff[i] != '\n') {
		char c = buff[i];
		if (c >= 48 && c <= 57) {

			*gen = buff[i];
			gen++;
			
		}
		*gen = '\0';
		i++;
	}
	long nummer = atoi(pf);
	return nummer;
}

orderslist *Orders_goto_first(orderslist* lastord) {
	orderslist *result = lastord;
	while (result->prev != NULL) {
		result = result->prev;
	}
	return result;
}

void Camtype_fill(Order* whord, const char *pword) {
	for (int g = 0; g <= 2; g++) {
		if (strcmp(pword, camtypes[g]) == 0) {
			whord->camtype = camtypes[g];
		}
	}
}