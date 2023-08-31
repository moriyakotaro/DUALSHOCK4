#ifndef __PS4__H__
#define __PS4__H__

#define DEAD_BAND	10

extern int PS4_right;
extern int PS4_down;
extern int PS4_up;
extern int PS4_left;

extern int PS4_square;
extern int PS4_cross;
extern int PS4_circle;
extern int PS4_triangle;

extern int PS4_l1;
extern int PS4_r1;

extern int PS4_share;
extern int PS4_options;
extern int PS4_l3;
extern int PS4_r3;

extern int PS4_PSbutton;
extern int PS4_touchpad;

extern int PS4_l2;
extern int PS4_r2;

extern int PS4_Rstickx;
extern int PS4_Rsticky;
extern int PS4_Lstickx;
extern int PS4_Lsticky;

void PS4_resetArray(char *array,int arraycount);
int PS4_updataState(int *rcv);
void PS4_updataButtonState(int button_state1, int button_state2, int button_state3);
void PS4_updataJoyStickState(int js_state1, int js_state2, int js_state3, int js_state4, int js_state5, int js_state6, int js_state7, int js_state8);
int PS4_JoyStick_DeadBand(int js);
int PS4_checkSum(int *rcv);
void PS4_controller_data_receive(char data_);

#endif