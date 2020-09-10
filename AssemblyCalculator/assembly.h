#ifndef ASSEMBLY_H
#define ASSEMBLY_H


#include <iostream>
#include "pch.h"


class Order {

private:

public:
	Order();
	~Order();
	long ordernum;
	int camcount;
	const char *camtype;
	int cablelenght;
	int register_q;
	int reg_chans;
	int hddq;
	int boxlenght;
	int switchtype[32];

	void (Order::*pfunc[6])(Order*, int, int);
	long Order_number_gen();
	
	 
protected:

	void Cam_quant_input(Order*, int, int);
	void Cam_type_input(Order*, int, int);
	void Register_input(Order*, int, int);
	void Hdd_input(Order*, int, int);
	void Cable_box_input(Order*, int, int);
	void Switch_input(Order *, int, int);
	
};



#endif 

