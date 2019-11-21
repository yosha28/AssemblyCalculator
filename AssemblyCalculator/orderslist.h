#ifndef ORDERSLIST_H
#define ORDERSLIST_H

#include "assembly.h"
//#include "items.h"

struct orderslist {
	Order *order;
	orderslist *next;
	orderslist *prev;
};


orderslist *order_itm_init(orderslist*);
orderslist *order_itm_input(orderslist * lastorder);
//orderslist gotolast();
//orderslist *order_itm_input();

#endif