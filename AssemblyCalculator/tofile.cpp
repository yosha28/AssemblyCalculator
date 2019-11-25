#include <stdio.h>
#include "pch.h"
#include "tofile.h"
#include "menu.h"

FILE *forder = NULL;


void Write_to_file(orderslist * lastorder, int readflg, char *filename) {

	posmove(L_FIELD, 15);

	const char *mode = NULL;
	if (readflg == 1) {
		mode = "a";
	}
	else {
		mode = "w";
	}

	if (NULL != lastorder) {
		orderslist *start = Orders_goto_first(lastorder);
		if (!fopen_s(&forder, filename, mode)) {
			do {


				//fwrite(start->order->camtype, sizeof(start->order), 1, forder);
				Order *p = start->order;
				fprintf_s(forder, "%d|%d|%s|%d|%d|%d|%d|%d||%d|%d|%d|%d|\n", p->ordernum, p->camcount, p->camtype, p->register_q, p->reg_chans
					, p->cablelenght, p->boxlenght, p->hddq, p->switchtype[3], p->switchtype[7], p->switchtype[15], p->switchtype[31]);

				start = start->next;

			} while (start != NULL);
			fclose(forder);
			printf("FILE SAVED !");
		}
		else {
			printf("FILE SAVING ERROR ! error:%d", fopen_s(&forder, filename, mode));
		}

	}
	else {
		posmove(L_FIELD, 15);
		consoleSetColors(clWhite, clBlack);
		printf("NO ORDERS IN SYSTEM !");
	}

}

void Out_to_screen(orderslist * lastorder) {
	int v = 20;
	posmove(L_FIELD, 15);

	if (NULL != lastorder) {
		consoleSetColors(clWhite, clBlack);
		printf("ORDERS AVIABLE:\n\n");
		orderslist *start = Orders_goto_first(lastorder);

		do {

			posmove(L_FIELD, v);

			Order *p = start->order;
			printf("Order #%d  %d cameras %s type,  %d Registrators with %d channels, and %d HDD  %d m. UTP cat 5e and %d m cable box, Switches:  "
				, p->ordernum, p->camcount, p->camtype, p->register_q, p->reg_chans
				,  p->hddq, p->cablelenght, p->boxlenght);
			for (int x = 4; x <= 32; ) {
				if (p->switchtype[x-1] != 0) {
					printf("%d x %d channels ", p->switchtype[x - 1],x);
				}
				x = x * 2;
			}
			printf("\n");
			start = start->next;
			v = v + 4;
		} while (start != NULL);


	}
	else {
		posmove(L_FIELD, 15);
		consoleSetColors(clWhite, clBlack);
		printf("NO ORDERS IN SYSTEM !");
	}
}

orderslist *Read_from_file(orderslist * lastorder) {

}
