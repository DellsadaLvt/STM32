#include "UART.h"





int main( void )
{
	
	/* GPIO INIT */
	GPIO_Init();
	/* USART INIT */
	USART_INIT();
	
	/* VALUE INIT */
	uint8_t result;
	uint8_t chat = 'A';
	int n;
   char str[100];
	
	
	printf("Hello from the other side\r\n");
  //fprintf(stdout, "    test for stdout\r\n");
  //fprintf(stderr, "    test for stderr\r\n");

    while (1) {
        printf("How old are you ?");
        scanf("%d", &n);
        printf("Your age is: %d\r\n", n);
        printf("Enter your first name: ");
        gets(str);
        printf("I like your style: ");
        puts(str);
        printf("\r\n");
    }
}








