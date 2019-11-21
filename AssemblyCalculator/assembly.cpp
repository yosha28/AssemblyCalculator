#include "pch.h"
#include "assembly.h"
//#include "items.h"


Order::Order() {
	camcount=0;
	camtype = NULL;
	cablelenght = 0;
	register_q =0;
	reg_chans = 0;
	boxlenght = 0;
	pfunc[0] = &Order::cam_quant_input;
	pfunc[1] = &Order::cam_type_input;
	pfunc[2] = &Order::register_input;
	pfunc[3] = &Order::hdd_input;
	pfunc[4] = &Order::cable_box_input;
	
}

Order::~Order() {

}