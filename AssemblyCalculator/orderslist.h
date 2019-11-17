#ifndef ORDERSLIST_H
#define ORDERSLIST_H

#include "assembly.h"

struct orderslist {
	Order *order;
	orderslist *next;
	orderslist *prev;
};

void order_itm_init();
//orderslist gotolast();
//orderslist *order_itm_input();


#endif