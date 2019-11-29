#include <stdio.h>
#include "pch.h"
#include "tofile.h"
#include "menu.h"
#include <xtgmath.h>
//#include "items.h"


FILE *forder = NULL;


void Write_to_file(orderslist * lastorder, bool *readflg, char *filename) {
	int v = 20;

	posmove(L_FIELD, 15);
	consoleSetColors(clWhite, clBlack);

	const char *mode = NULL;  //check if file have once readen - rewrite all file 
	if (*readflg == true) {
		mode = "w";
	}
	else {
		mode = "a";
	}

	if (NULL != lastorder) {
		orderslist *start = Orders_goto_first(lastorder);
		if (!fopen_s(&forder, filename, mode)) {
			do {


				//fwrite(start->order->camtype, sizeof(start->order), 1, forder);
				Order *p = start->order;
				fprintf_s(forder, "%d|%d|%s|%d|%d|%d|%d|%d|%d|%d|%d|%d|\n", p->ordernum, p->camcount, p->camtype, p->register_q, p->reg_chans
					, p->cablelenght, p->boxlenght, p->hddq, p->switchtype[3], p->switchtype[7], p->switchtype[15], p->switchtype[31]);
				
				posmove(L_FIELD, v);
				printf("Order # %d written\n", start->order->ordernum);
				start = start->next;
				v = v + 2;

			} while (start != NULL);
			
			posmove(L_FIELD, v);
			printf("FILE SAVED !");
		}
		else {
			printf("FILE SAVING ERROR ! error:%d", fopen_s(&forder, filename, mode));
			
		}
		fclose(forder);
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
				, p->hddq, p->cablelenght, p->boxlenght);
			for (int x = 4; x <= 32; ) {
				if (p->switchtype[x - 1] != 0) {
					printf("%d x %d channels ", p->switchtype[x - 1], x);
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

orderslist *Read_from_file(orderslist * lastorder, bool *readflg, char *filename) {
	int v = 20;

	if (!fopen_s(&forder, filename, "r")) { //file opened

		char *string = (char*)malloc(1024 * sizeof(char));

		while (fgets(string, 1024, forder) && (!feof(forder)))
		{
			orderslist *newodr = Order_itm_init();
			Order *porder = new Order;
			newodr->order = porder;

			Parse_string(porder, string);


			if (lastorder != NULL) {

				int isexist = 0;     //initiate existing check
				
				orderslist *check = lastorder;
				while (check != NULL) {
					if (check->order->ordernum == newodr->order->ordernum) {
						isexist = 1;
						consoleSetColors(clWhite, clBlack);
						posmove(L_FIELD, v);
						printf("Order # %d exist - skipping", check->order->ordernum);
						v = v + 4;
					}
					check = check->prev;
				} 

				if (isexist == 0) {
					consoleSetColors(clWhite, clBlack);
					posmove(L_FIELD, v);
					printf("Order # %d loaded", lastorder->order->ordernum);
					v = v + 4;
					lastorder->next = newodr;
					newodr->prev = lastorder;
					lastorder = newodr;
					
				}
				else {
					delete porder;
					order_itm_delete(newodr);
				}

			}else {
				lastorder = newodr;
				lastorder->prev = NULL;
				lastorder->next = NULL;
			}

		}


		
		free(string);

	}
	else {
		consoleSetColors(clRed, clBlack);
		printf("                         FILE READ ERROR ! error:%d", fopen_s(&forder, filename, "r"));
	}

	fclose(forder);
	*readflg = true;
	return lastorder;
}

void Parse_string(Order * whorder, char *string) {

	//pointers massive create & fill
	const char *p = NULL;
	const char *pmas[13];
	for (int i = 0; i <= 12; i++) {
		p = (char*)malloc(11 * sizeof(char));
		pmas[i] = p;
	}


	//parse thru string
	const char *smover = string;
	int type = 1;
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


	//order filling
	whorder->ordernum = atoi(pmas[1]);
	whorder->camcount = atoi(pmas[2]);

	Camtype_fill(whorder, pmas[3]);

	whorder->register_q = atoi(pmas[4]);
	whorder->reg_chans = atoi(pmas[5]);
	whorder->cablelenght = atoi(pmas[6]);
	whorder->boxlenght = atoi(pmas[7]);
	whorder->hddq = atoi(pmas[8]);
	whorder->switchtype[3] = atoi(pmas[9]);
	whorder->switchtype[7] = atoi(pmas[10]);
	whorder->switchtype[15] = atoi(pmas[11]);
	whorder->switchtype[31] = atoi(pmas[12]);

	//free buffer
	for (int i = 0; i <= 12; i++) {
		char *p = (char*)realloc((char*)pmas[i], 11);
		free(p);
	}


}
