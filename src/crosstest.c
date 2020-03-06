#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#include <lcd.h>

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>




//USE WIRINGPI PIN NUMBERS
#define LCD_RS  25               //Register select pin
#define LCD_E   24               //Enable Pin
#define LCD_D0  29               //Data pin D0
#define LCD_D1  28               //Data pin D1
#define LCD_D2  27               //Data pin D2
#define LCD_D3  26               //Data pin D3
#define LCD_D4  23               //Data pin D4
#define LCD_D5  22               //Data pin D5
#define LCD_D6  21               //Data pin D6
#define LCD_D7  14               //Data pin D7
 
int main()
{

    int lcd;
    wiringPiSetup();
    lcd = lcdInit (2, 16, 8, LCD_RS, LCD_E, LCD_D0, LCD_D1, LCD_D2, LCD_D3, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

    int n;
    struct ifreq ifr;
    char iface[] = "wlan0";
    while(1){
        n = socket(AF_INET, SOCK_DGRAM, 0);
        ifr.ifr_addr.sa_family = AF_INET;
        strncpy(ifr.ifr_name, iface, IFNAMSIZ -1);
        ioctl(n, SIOCGIFADDR, &ifr);
        close(n);
	sleep(1);
        lcdPosition(lcd, 0, 0);
        lcdPrintf(lcd, "Hello Joe: ");
        lcdPosition(lcd, 0, 1);
	lcdPrintf(lcd, "Finally WORKS..");

	/*lcdPrintf(lcd, ("%s - %s\n", iface, inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr)));*/
    }
    return 0;
    
}






 /*   while(1){ 
    	lcdPuts(lcd, "Hello, Finally works!! ");
    	sleep(2);
    	lcdClear(lcd);
    	sleep(2);

    }
}
*/
