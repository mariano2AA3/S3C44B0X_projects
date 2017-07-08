/*--- ficheros de cabecera ---*/
#include "44blib.h"
#include "44b.h"
#include "stdio.h"
/*--- funciones externas ---*/
extern void leds_off();
extern void led1_on();
extern void leds_switch();


extern void sys_init();
/*--- declaracion de funciones ---*/
void Main(void);
void button_init();


/*--- codigo de funciones ---*/
void Main(void)
{
	/* Inicializar controladores */
	sys_init(); // Inicializacion de la placa, interrupciones y puertos


	button_init();

	/* Establecer valor inicial de los LEDs */
	leds_off();
	led1_on();

	while (1){

		if ( (rPDATG & 0x00000040) == 0 || (rPDATG & 0x00000080) == 0) {

			while ( (rPDATG & 0x00000040) == 0 || (rPDATG & 0x00000080) == 0) {}

			leds_switch();
			DelayMs(100);
		}

	}
}


void button_init() {

	rPCONG = rPCONG & 0xffff0fff;
	rPUPG = 0;

}
