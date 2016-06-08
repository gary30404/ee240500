/*
This is the code for final project
to control Boe-Bot moving and shooting 
*/

#include "simpletools.h"
#include "servo.h"
#include "servodiffdrive.h"
#include "fdserial.h"
#include "talk.h"
#include "ping.h"   

#define PIN_SOUND       26 // pin for the speaker, default=26
#define PIN_XBEE_RX      0
#define PIN_XBEE_TX      1
#define PIN_SERVO_LEFT  14
#define PIN_SERVO_RIGHT 15

char char2lowercase (char c);
int distance, setPoint, errorVal, kp, speed;  // Navigation variables

int main (void) {

   setPoint = 10;                              // Desired cm distance
   kp = -10;                                   // Proportional control
	fdserial *xbee;
	xbee = fdserial_open(PIN_XBEE_RX, PIN_XBEE_TX, 0, 9600);
	drive_pins(PIN_SERVO_LEFT, PIN_SERVO_RIGHT);

	pause(1000);
	putchar(CLS);
	fdserial_rxFlush(xbee);

	while (1) {
		int ch = fdserial_rxChar(xbee);
		ch = char2lowercase(ch);
		fdserial_rxFlush(xbee);
		switch ((char) ch) {
			case 's':
				print("Stop\n");
          servo_speed(14,0);
          servo_speed(16,0);
          break;
        case 'f':
				print("Forward\n");
          servo_speed(14,50);
          servo_speed(16,-50);
				pause(1000);
          servo_speed(14,0);
          servo_speed(16,0);	
          break;
			case 'b':
				print("Backward\n");
          servo_speed(14,-50);
          servo_speed(16,50);
				pause(1000);
				servo_speed(14,0);
          servo_speed(16,0);
				break;
			case 'r':
				print("Right\n");
          servo_speed(14,50);
          servo_speed(16,-20);
				pause(700);
				servo_speed(14,0);
          servo_speed(16,0);
				break;
			case 'l':
				print("Left\n");
          servo_speed(14,20);
          servo_speed(16,-50);
				pause(700);
				servo_speed(14,0);
          servo_speed(16,0);
				break;
       case 'x':
				print("Forward\n");
          servo_speed(14,-50);
          servo_speed(16,20);
				pause(700);
          servo_speed(14,0);
          servo_speed(16,0);	
          break;
       case 'z':
				print("Forward\n");
          servo_speed(14,-20);
          servo_speed(16,50);
				pause(700);
          servo_speed(14,0);
          servo_speed(16,0);	
          break;
       case 't':
				print("Forward\n");
          servo_speed(15,-100);
				pause(150);
          servo_speed(15,0);
          pause(1000);
          servo_speed(15,100);
          pause(151);
          servo_speed(15,0);
          break;
       case 'a':
				while(1)                                    // main loop
          {
            distance = ping_cm(19);                    // Measure distance
            if (distance < 15){
              servo_speed(14,-50);
              servo_speed(16,50);
				    pause(1500);
              servo_speed(14,50);
              servo_speed(16,-20);
				    pause(2000);
            }
            else{
              servo_speed(14,50);
              servo_speed(16,-50);
            }                          
          }
          break;     
		  default:
				print("Invalid Command\n");
				pause(700);
				break;
		}
		print("%c", (char) ch);
		pause(100);
		fdserial_txChar(xbee, ch);
		fdserial_txFlush(xbee);
	}

}

char char2lowercase (char c) {
	return 'A'<=c && c<='Z' ? c+32 : c;
}
