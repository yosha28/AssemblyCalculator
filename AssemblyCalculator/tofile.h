#ifndef TOFILE_H
#define TOFILE_H

#include <stdio.h>
#include "orderslist.h"



void Write_to_file(orderslist *lastorder, int readflg, char *filename);

void Out_to_screen(orderslist * lastorder);

orderslist *Read_from_file(orderslist * lastorder);

#endif
