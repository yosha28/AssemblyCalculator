#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "orderslist.h"
#include "storage.h"



struct collection {  //structure for link passed orders in class Iter

	orderslist *po_addr;
	collection *next;
};


 
class Iter {
private:
public:
	Iter();
	~Iter();
	int ordpassed;
	int maxfnd;
	collection *start;

	
	void Matrxsumm(Storage *matrix, orderslist *toexpand);
	void Matrxdiff(Storage *matrix, orderslist *toexpand);
	
protected:

};

struct packs {   //structure for list pointers to classes examples of passed items
	Iter *ppack;
	packs *nextpack;
};

void Print_by_storage(orderslist* lastorder, Storage *memstorage);
packs *Bruteforce(orderslist * lastorder, Storage *ms);
void Resultprint(packs *start);
void Resulclear(packs *start);
#endif // !CALCULATOR_H


