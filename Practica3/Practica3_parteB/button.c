/*--- ficheros de cabecera ---*/
#include "44blib.h"
#include "44b.h"
#include "def.h"
#include "common_types.h"
/*--- variables globales ---*/
int symbol = 0;

/*--- funciones externas ---*/
extern void D8Led_symbol(int value);
/*--- declaracion de funciones ---*/
void Eint4567_ISR(void) __attribute__ ((interrupt ("IRQ")));
void Eint4567_init(void);

extern void at24c04_byteread( uint16 addr, uint8 *data );
extern void at24c04_bytewrite( uint16 addr, uint8 data );

extern int estado;
extern uint16 direccion;
extern uint8 dato;

/*--- codigo de funciones ---*/
void Eint4567_init(void) {


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


void Eint4567_ISR(void) {

	//Delay para eliminar rebotes
	DelayMs(100);

	// IZQ
	if ( (rPDATG & 0x00000040) == 0 ) {
		estado = (estado + 1) % 6;
		D8Led_symbol(estado);
		if(estado == 5){
			at24c04_bytewrite( direccion, dato );
		}
	}
	// DR
	else if ( (rPDATG & 0x00000080) == 0 ) {
		at24c04_byteread( direccion, &dato );
		int parte2 = dato & 0xf;
		//int parte1 = dato >> 4;
		int parte1 = (dato & 0xf0)>>4;
		D8Led_symbol(parte1);
		DelayMs(1000);
		D8Led_symbol(parte2);
	}

	while ( (rPDATG & 0x00000040) == 0 || (rPDATG & 0x00000080) == 0) {}

	//Borramos EXTINTPND ambas líneas EINT7 y EINT6
	// Ponemos a 1´s los bits de EXTINTPND3(EINT7) y EXTINTPND2(EINT6)
	rEXTINTPND = 0xC;

	//Borramos INTPND usando ISPC
	rI_ISPC = BIT_EINT4567;

}



