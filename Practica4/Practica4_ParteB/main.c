/*--- ficheros de cabecera ---*/
#include "44blib.h"
#include "44b.h"
#include "uart.h"
/*--- Externas ---*/
 extern void Eint4567_init(void);
 extern void keyboard_init();
 extern void D8Led_init(void);
 extern void D8Led_symbol(int value);
/*--- declaracion de funciones ---*/
int Main(void);

/*--- variables globales ---*/
char str_send[10] = "\nSED-P4 >\0";
char str_error[50] = "\nSe ha producido un desbordamiento!\n\0";
char str[256];

/*--- codigo de la funcion ---*/
int Main(void){

	char *pt_str = str;

	sys_init(); // inicializacion de la placa, interrupciones, puertos

    //Inicializamos los botones
    rPCONG = rPCONG & 0xffff0fff;
    rPUPG = 0;

    Eint4567_init();

    //keyboard_init();

    D8Led_init();
    D8Led_symbol(0);

    leds_off();

	Uart_Init(115200); 		// inicializacion de la Uart
	Uart_Config(); 			// configuración de interrupciones y buffers


	while( 1 ) {

		*pt_str = Uart1_Getch(); // leer caracter del pc

		if ( *pt_str == CR_LEFT) {
			leds_off();
			led1_on();
		}
		else if ( *pt_str == CR_RIGHT) {
			leds_off();
			led2_on();
		}

		Uart0_Printf(*pt_str);

	}


	return 0;

}
