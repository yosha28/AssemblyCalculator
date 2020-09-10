#ifndef TOFILE_H
#define TOFILE_H

#include <stdio.h> 
#include "orderslist.h"




void Write_to_file(orderslist *lastorder, bool *readflg, char *filename);

void Out_to_screen(orderslist * lastorder);

orderslist *Read_from_file(orderslist * lastorder, bool *readflg, char *filename);

void Parse_string(Order * whorder, char *string);

#endif
