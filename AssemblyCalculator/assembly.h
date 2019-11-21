#ifndef ASSEMBLY_H
#define ASSEMBLY_H


#include <iostream>
#include "pch.h"


class Order {

private:

public:
	Order();
	~Order();
	int camcount;
	const char *camtype;
	int cablelenght;
	int register_q;
	int reg_chans;
	int hddq;
	int boxlenght;

	void (Order::*pfunc[6])(Order*, int, int);


protected:

	void cam_quant_input(Order*, int, int);
	void cam_type_input(Order*, int, int);

	void register_input(Order*, int, int);
	void hdd_input(Order*, int, int);
	void cable_box_input(Order*, int, int);
	//void cam_type_input(Order*, int, int);
	//void cam_type_input(Order*, int, int);
	//void cam_type_input(Order*, int, int);

};



#endif 

