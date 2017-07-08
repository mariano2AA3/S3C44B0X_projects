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

    keyboard_init();

    D8Led_init();
    D8Led_symbol(0);

    leds_off();

	Uart_Init(115200); 		// inicializacion de la Uart
	Uart_Config(); 			// configuración de interrupciones y buffers
	Uart0_Printf(str_send); // mostrar cabecera


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
		else {
			int numero;


			switch(*pt_str) {
				case CR_0: numero = 0; break;
				case CR_1: numero = 1; break;
				case CR_2: numero = 2; break;
				case CR_3: numero = 3; break;
				case CR_4: numero = 4; break;
				case CR_5: numero = 5; break;
				case CR_6: numero = 6; break;
				case CR_7: numero = 7; break;
				case CR_8: numero = 8; break;
				case CR_9: numero = 9; break;
				case CR_A: numero = 10; break;
				case CR_B: numero = 11; break;
				case CR_C: numero = 12; break;
				case CR_D: numero = 13; break;
				case CR_E: numero = 14; break;
				case CR_F: numero = 15; break;
			}

			D8Led_symbol(numero);
		}

	}



	/*
	while(1){
		*pt_str = Uart0_Getch(); // leer caracter
		Uart0_SendByte(*pt_str); // enviar caracter
		if (*pt_str == CR_char){ // retorno de carro?
			if (pt_str != str) { // si cadena no vacia, mostrar
				*(++pt_str) = '\0'; // terminar cadena antes
				Uart0_Printf("\n");
				Uart0_Printf(str);
			}
			Uart0_Printf(str_send); // preparar siguiente
			pt_str = str;
		}
		else if (++pt_str == str + 255){ // desbordamiento?
			Uart0_Printf(str_error); // avisar del desbordamiento
			pt_str = str;
		}
	}*/

	return 0;

}
