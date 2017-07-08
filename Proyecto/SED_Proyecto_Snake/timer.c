/*--- ficheros de cabecera ---*/
#include "44b.h"
#include "44blib.h"
#include "snake.h"



/*--- declaracion de funciones ---*/
void timer0(void) __attribute__ ((interrupt ("IRQ")));
void timer2(void) __attribute__ ((interrupt ("IRQ")));
//void timer4(void) __attribute__ ((interrupt ("IRQ")));
void timer_init(void);
void apagar_timers(void);
void enciende_timer0(void);
void enciende_timer2(void);
void enciende_timer4(void);



void timer_init(void) {


	/* Configuracion del controlador de interrupciones */
		// Configurar las lineas como de tipo IRQ
		rINTMOD=0x0;
		// Habilitar int. vectorizadas y la linea IRQ (FIQ no)
		rINTCON=0x1;

		// Enmascarar todas las lineas excepto Timer0 y el bit global
		// rINTMSK = rINTMSK & ~(BIT_TIMER0 | BIT_GLOBAL);
		rINTMSK = rINTMSK & ~(BIT_TIMER0 | BIT_TIMER2 | BIT_TIMER4 | BIT_GLOBAL);

	/* Establece la rutina de servicio para TIMER0 */
		pISR_TIMER0 = (unsigned)timer0;
		//pISR_TIMER2 = (unsigned)timer2;
		//pISR_TIMER4 = (unsigned)timer4_tiempo_juego;

	/* Configurar los Timer{0,2,4} (el resto de los timers se dejan a la configuración por defecto) */
		// Capitulo 9 ~244)
		rTCFG0 = 0xFFFFFF; // pre-escalado = 255 a los 3 timers

		/*
		    0000 = 1/2 0001 = 1/4 0010 = 1/8
			0011 = 1/16 01xx = 1/32
		*/
		rTCFG1 = 0xF7F0F7;	// [3:0] -> timer0 / [11:8] -> timer2 / [19:16] -> timer4
		// divisor = 1/2


		rTCNTB0 = 65535;
		rTCMPB0 = 12800;

		rTCNTB2 = 65535/2;
		rTCMPB2 = 12800;

		rTCNTB4 = 65535;
		rTCMPB4 = 12800;


}

void apagar_timers(void) {

	rTCON = rTCON & ~(0x1<<0);
	rTCON = rTCON & ~(0x1<<12);
	rTCON = rTCON & ~(0x1<<20);

}

void enciende_timer0(void) {
	rTCON = rTCON | (0x01<<1);// establecer manual_update
	rTCON = rTCON | (0x01<<3);//activar modo auto-reload

	rTCON = rTCON | (0x1<<0);
	rTCON = rTCON & ~(0x1<<12);
	rTCON = rTCON & ~(0x1<<20);

	rTCON = rTCON & ~(0x01<<1);// DESACTIVA manual_update
}

void enciende_timer2(void) {
	rTCON = rTCON | (0x01<<13);// establecer manual_update
	rTCON = rTCON | (0x01<<15);//activar modo auto-reload

	rTCON = rTCON & ~(0x1<<0);
	rTCON = rTCON | (0x1<<12);
	rTCON = rTCON & ~(0x1<<20);

	rTCON = rTCON & ~(0x01<<13);// DESACTIVA manual_update
}

void enciende_timer4(void) {
	rTCON = rTCON | (0x01<<21);// establecer manual_update
	rTCON = rTCON | (0x01<<23);//activar modo auto-reload

	rTCON = rTCON & ~(0x1<<0);
	rTCON = rTCON & ~(0x1<<12);
	rTCON = rTCON | (0x1<<20);

	rTCON = rTCON & ~(0x01<<21);// DESACTIVA manual_update
}

int a = 1;

void timer0(void) {

	generarFruta();

	rI_ISPC = BIT_TIMER0;
}




// Muestra los mensajes L (listo) o P (pierde)
void timer2(void) {


	rI_ISPC = BIT_TIMER2;

}

/*
void timer4_tiempo_juego(void) {

	if ( turno == 1 ) {
		led_jugadorPierde();
		pierde = 1;
	}

	enciende_timer2();
	rI_ISPC = BIT_TIMER4;

}
*/

