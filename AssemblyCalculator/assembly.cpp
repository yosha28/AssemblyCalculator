#include "pch.h"
#include "assembly.h"
//#include "items.h"


Order::Order() {
	ordernum = 0;
	camcount=0;
	camtype = NULL;
	cablelenght = 0;
	register_q =0;
	reg_chans = 0;
	boxlenght = 0;
	for (int n = 0;n<= 32;n++){
		switchtype[n]=0;
	}
	pfunc[0] = &Order::Cam_quant_input;
	pfunc[1] = &Order::Cam_type_input;
	pfunc[2] = &Order::Register_input;
	pfunc[3] = &Order::Hdd_input;
	pfunc[4] = &Order::Cable_box_input;
	pfunc[5] = &Order::Switch_input;
	
}

Order::~Order() {

}