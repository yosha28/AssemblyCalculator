#ifndef ORDERSLIST_H
#define ORDERSLIST_H

#include "assembly.h"


#define L_FIELD 4   //left fileld
#define C_FIELD 50  //central field
#define R_FIELD 100 // right field

struct orderslist {
	Order *order;
	orderslist *next;
	orderslist *prev;
};


orderslist *Order_itm_init();
orderslist *Order_itm_input(orderslist * lastorder);
orderslist *Orders_goto_first(orderslist *lastord);
void order_itm_delete(orderslist *newodr);
void Camtype_fill(Order* whord, const char *pword);
void Free_orders(orderslist * lastorder);

#endif