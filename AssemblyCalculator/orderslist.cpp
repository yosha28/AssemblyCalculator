#include <iostream>
#include "orderslist.h"
#include "pch.h"
#include "assembly.h"
#include "items.h"

struct orderslist {
	Order *order;
	orderslist *next;
	orderslist *prev;
};

void order_itm_init() {
	orderslist *itm = NULL;
	itm = (orderslist*)malloc(sizeof(struct orderslist));
	itm->order = NULL;
	itm->next = NULL;
	itm->prev = NULL;
	//return (itm);

}
//
//orderslist gotolast() {
//	return (*order_itm_init());
//}
//
//orderslist *order_itm_input() {
//	orderslist *newodr = order_itm_init();
//	newodr->order = new Order;
//	newodr->order->camtype = Camtype.t1;
//	printf("input cam count 1");
//	return nullptr;
//}
