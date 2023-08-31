/*
mainにこれを追加すればDUALSHOCK3と同じ方法で使える
void serialEvent5(){
  PS4_controller_data_receive(Serial5.read());
}
*/

#include <Arduino.h>
#include "PS4.h"

int PS4_monitoring = 0;
int PS4_data[11] = {0};

int PS4_right=0;
int PS4_down=0;
int PS4_up=0;
int PS4_left=0;
int PS4_square=0;
int PS4_cross=0;
int PS4_circle=0;
int PS4_triangle=0;
int PS4_l1=0;
int PS4_r1=0;
int PS4_share=0;
int PS4_options=0;
int PS4_l3=0;
int PS4_r3=0;
int PS4_PSbutton=0;
int PS4_touchpad=0;
int PS4_l2=0;
int PS4_r2=0;
int PS4_Rstickx=0;
int PS4_Rsticky=0;
int PS4_Lstickx=0;
int PS4_Lsticky=0;


int PS4_i_abs(int num){
	return (num>=0) ? num:-num;
}

int PS4_is(int num){
	return !!num;
}

void PS4_resetArray(char *array,int arraycount){
	int i;
	for(i=0;i<arraycount;i++){
		array[i] = 0;
	}
}

int PS4_updataState(int *rcv){
	int err;
	err = PS4_checkSum(rcv);
	if(err!=-1){
		PS4_updataButtonState(rcv[1], rcv[2], rcv[3]);
		PS4_updataJoyStickState(rcv[3], rcv[4], rcv[5], rcv[6], rcv[7], rcv[8], rcv[9], rcv[10]);
	}
	return 0;
}

void PS4_updataButtonState(int button_state1, int button_state2, int button_state3){
	PS4_up   = PS4_is(button_state1 & 0x40);
	PS4_down    = PS4_is(button_state1 & 0x20);
	PS4_left = PS4_is(button_state1 & 0x10);
	PS4_right   = PS4_is(button_state1 & 0x08);
	PS4_circle  = PS4_is(button_state1 & 0x04);
	PS4_cross = PS4_is(button_state1 & 0x02);
	PS4_square    = PS4_is(button_state1 & 0x01);
	PS4_triangle  = PS4_is(button_state2 & 0x40);
	PS4_l1 = PS4_is(button_state2 & 0x20);
	PS4_l3 = PS4_is(button_state2 & 0x10);
	PS4_r1 = PS4_is(button_state2 & 0x08);
	PS4_r3 = PS4_is(button_state2 & 0x04);
	PS4_share = PS4_is(button_state2 & 0x02);
	PS4_options = PS4_is(button_state2 & 0x01);
	PS4_PSbutton = PS4_is(button_state3 & 0x40);
	PS4_touchpad = PS4_is(button_state3 & 0x20);
}

void PS4_updataJoyStickState(int js_state1, int js_state2, int js_state3, int js_state4, int js_state5, int js_state6, int js_state7, int js_state8){
	int L2=0,R2=0,Lx=0,Ly=0,Rx=0,Ry=0;
	L2 = ((js_state1 & 0b00011111)<<3) | ((js_state2 & 0b01110000)>>4);
	R2 = ((js_state2 & 0b00001111)<<4) | ((js_state3 & 0b01111000)>>3);
	Lx = ((js_state3 & 0b00000111)<<5) | ((js_state4 & 0b01111100)>>2);
	Ly = ((js_state4 & 0b00000011)<<6) | ((js_state5 & 0b01111110)>>1);
	Rx = ((js_state5 & 0b00000001)<<7) | (js_state6 & 0b01111111);
	Ry = ((js_state7 & 0b01111111)<<1) | ((js_state8 & 0b01000000)>>6);
	PS4_l2 = L2;
	PS4_r2 = R2;
	PS4_Lstickx = PS4_JoyStick_DeadBand(Lx);
	PS4_Lsticky = PS4_JoyStick_DeadBand(Ly);
	PS4_Rstickx = PS4_JoyStick_DeadBand(Rx);
	PS4_Rsticky = PS4_JoyStick_DeadBand(Ry);
}

int PS4_JoyStick_DeadBand(int js){
	js -= 128;
	if(PS4_i_abs(js)<=DEAD_BAND)	js = 0;
	else 				js += (js<0) ? DEAD_BAND:-DEAD_BAND;
	return js;
}

int PS4_checkSum(int *rcv){
	char sum;
	unsigned int sum_data = 0;
	for(int i=0; i<11; i++){
		sum_data += rcv[i];
	}
	sum=sum_data;
	return (sum==rcv[11]) ? 1:-1;
}

void PS4_controller_data_receive(char data_){
	static int No = 0;
  	int controler_buff = data_;
	PS4_monitoring = 0;
	if(controler_buff == 0x80){
		No = 0;
		PS4_data[No++] = 0x80;
	}else if(No > 0){
		PS4_data[No++] = controler_buff;
		if(No > 11){
			PS4_updataState(PS4_data);
			No = 0;
		}
	}
}