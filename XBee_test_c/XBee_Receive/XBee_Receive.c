#include "simpletools.h"
#include "fdserial.h"

//int fdserial_txChars (fdserial *term, char *str);

int RX = 0, TX = 1; // XBEE connected pins

int main () {
	fdserial *xbee;
	xbee = fdserial_open(RX, TX, 0, 9600);
	putchar(CLS); // Clear terminal screen
	fdserial_rxFlush(xbee);
	pause(100);

	/*
	char str[] = "Test";
	while(1) {
		fdserial_txChars (xbee, str); // send string
		fdserial_txChar(xbee, 'a'); // send a char
	}
	*/
	
	while (1) {
		int ch = fdserial_rxChar(xbee);
		fdserial_rxFlush(xbee);
		print("%c", (char) ch);
		fdserial_txChar(xbee, ch);
		fdserial_txFlush(xbee);
		pause(100);
	}
}
/*
int fdserial_txChars (fdserial *term, char *str) {
	int rc = 0;
	for (; *str!='\0'; str++)
		rc = fdserial_txChar(term, *str);
	return rc;
}
*/
