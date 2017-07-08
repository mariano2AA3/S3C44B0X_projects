/*--- ficheros de cabecera ---*/
#include "44blib.h"
#include "44b.h"
#include "def.h"
/*--- variables globales ---*/
int symbol = 0;
/*--- funciones externas ---*/
//extern void D8Led_Symbol(int value);
/*--- declaracion de funciones ---*/
void Eint4567_ISR(void) __attribute__ ((interrupt ("IRQ")));
void Eint4567_init(void);
extern void leds_switch ();
//extern void D8Led_symbol(int value);

int contador;

/*--- codigo de funciones ---*/
void Eint4567_init(void) {

	contador = 0;

	/* Configuracion del controlador de interrupciones */

		// Borra EXTINTPND escribiendo 1s en el propio registro
		rEXTINTPND = 0xf;

		// Borra INTPND escribiendo 1s en I_ISPC
		rI_ISPC = 0xfffffff;

		// Configura las lineas como de tipo IRQ mediante INTMOD
		rINTMOD = 0x0000000;

		// Habilita int. vectorizadas y la linea IRQ (FIQ no) mediante INTCON
		rINTCON = 0x1;

		// Enmascara todas las lineas excepto Eint4567 y el bit global (INTMSK)
		rINTMSK = 0xffffffff & ~BIT_GLOBAL & ~BIT_EINT4567;

		// Establecer la rutina de servicio para Eint4567
	    pISR_EINT4567 = (unsigned) Eint4567_ISR;

	/* Configuracion del puerto G */
		// Establece la funcion de los pines (EINT7-EINT0)
	    // Bits 6 y 7 a 0, resto a 1´s
	    rPCONG = 0xff3f;

		//Habilita las resistencias de pull-up
		rPUPG = 0;

		// Configura las lineas de int. como de flanco de bajada mediante EXTINT
		// _01x_01x_01x_01x_01x_01x_01x_01x ; x,_ = doesnt care
		rEXTINT = 0x33333333;

	/* Por precaucion, se vuelven a borrar los bits de INTPND y EXTINTPND */
	    rEXTINTPND = 0xf;
	    rI_ISPC = 0xfffffff;
}

/*COMENTAR PARA LA PARTE DEL 8-SEGMENTOS
DESCOMENTAR PARA LA PRIMERA PARTE CON INTERRUPCIONES
*/
void Eint4567_ISR(void) {

	while ( (rPDATG & 0x00000040) == 0 || (rPDATG & 0x00000080) == 0) {}

	//Conmutamos LEDs
	leds_switch();

	//Delay para eliminar rebotes
	DelayMs(100);

	//Borramos EXTINTPND ambas líneas EINT7 y EINT6
	// Ponemos a 1´s los bits de EXTINTPND3(EINT7) y EXTINTPND2(EINT6)
	rEXTINTPND = 0xC;

	//Borramos INTPND usando ISPC
	rI_ISPC = BIT_EINT4567;

}



