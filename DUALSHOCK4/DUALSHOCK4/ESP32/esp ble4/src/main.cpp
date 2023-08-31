#include <Arduino.h>
#include "PS4Controller.h"

int RX_PIN = 22;
int TX_PIN = 23; 
char Up=0;
char Down=0;
char Left=0;
char Right=0;
char Circle=0;
char Cross=0;
char Square=0;
char Triangle=0;
char L1=0;
char L3=0;
char R1=0;
char R3=0;
char Share=0;
char Options=0;
char PSButton=0;
char Touchpad=0;
char L2Value=0;
char R2Value=0;
int LStickX=0;
int LStickY=0;
int RStickX=0;
int RStickY=0;
char send_data[12]={};

int i_abs(int num){
	return (num>=0) ? num:-num;
}

void button_update(){
  Up=PS4.Up();
  Down=PS4.Down();
  Left=PS4.Left();
  Right=PS4.Right();
  Circle=PS4.Circle();
  Cross=PS4.Cross();
  Square=PS4.Square();
  Triangle=PS4.Triangle();
  L1=PS4.L1();
  L3=PS4.L3();
  R1=PS4.R1();
  R3=PS4.R3();
  Share=PS4.Share();
  Options=PS4.Options();
  PSButton=PS4.PSButton();
  Touchpad=PS4.Touchpad();
  L2Value=PS4.L2Value();
  R2Value=PS4.R2Value();
  LStickX=PS4.LStickX()+128;
  LStickY=PS4.LStickY()+128;
  RStickX=PS4.RStickX()+128;
  RStickY=PS4.RStickY()+128;
}

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
  PS4.begin("8c:4b:14:16:46:5f");
  // PS4.begin("8c:4b:14:16:46:4f");//sixaxisPair ToolでDUALSHOCK4のMACaddを確認して合わせる
  Serial.println("Ready."); 
}

void loop() {
  if (PS4.isConnected()) {
    unsigned int sum_data = 0;
    button_update();
    send_data[0] = 0x80;
    send_data[1] = (Up<<6) + (Down<<5) + (Left<<4) + (Right<<3) + (Circle<<2) + (Cross<<1) + (Square);
    send_data[2] = (Triangle<<6) + (L1<<5) + (L3<<4) + (R1<<3) + (R3<<2) + (Share<<1) + (Options);
    send_data[3] = (PSButton<<6) + (Touchpad<<5) + (L2Value);
    send_data[4] = ((L2Value&0b00000111)<<4) | (R2Value>>4);
    send_data[5] = ((R2Value&0b00001111)<<3) | (LStickX>>5);
    send_data[6] = ((LStickX&0b00011111)<<2) | (LStickY>>6);
    send_data[7] = ((LStickY&0b00111111)<<1) | (RStickX>>7);
    send_data[8] = (RStickX&0b01111111);
    send_data[9] = ((RStickY&0b11111110)>>1);
    send_data[10] = ((RStickY&0b00000001)<<6);
	  for(int i=0; i<11; i++){
		  sum_data += (send_data[i]);
      
	  }
    send_data[11] = sum_data;
    Serial.printf("%d\n",send_data[8]);
    Serial1.write(send_data, 12);
  }

}