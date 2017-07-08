/*--- ficheros de cabecera ---*/
#include "44blib.h"
#include "44b.h"
#include "stdio.h"
/*--- funciones externas ---*/
extern void leds_off();
extern void led1_on();
extern void timer_init();
/*--- declaracion de funciones ---*/
void Main(void);
/*--- codigo de funciones ---*/
void Main(void)
{
	/* Inicializar controladores */
	sys_init(); // Inicializacion de la placa, interrupciones y puertos
	//timer_init(); // Inicializacion del temporizador
	keyboard_init();

	/* Establecer valor inicial de los LEDs */
	leds_off();
	led1_on();

	D8Led_init();
	D8Led_symbol(0);

	while (1); // espera
}
