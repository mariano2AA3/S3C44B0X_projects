/*--- ficheros de cabecera ---*/
#include "44b.h"
#include "44blib.h"
/*--- funciones externas ---*/
extern void leds_switch();
/*--- declaracion de funciones ---*/
void timer0_juego(void) __attribute__ ((interrupt ("IRQ")));
void timer2_mostrar_mensaje(void) __attribute__ ((interrupt ("IRQ")));
void timer4_tiempo_juego(void) __attribute__ ((interrupt ("IRQ")));
void timer_init(void);
void enciende_timer0(void);
void enciende_timer2(void);
void enciende_timer4(void);

/*-- Variables --*/
extern int secuencia_maquina[100];
extern int pierde;
extern int indice;
extern int nivel;
extern int turno;
extern int switchLed;
int apagado;

/*--- codigo de las funciones ---*/
void led_jugador(void);
void led_maquina(void);
void led_preparado(void);
void led_jugadorPierde(void);


void timer_init(void) {

	apagado = 0;

	/* Configuracion del controlador de interrupciones */
		// Configurar las lineas como de tipo IRQ
		rINTMOD=0x0;
		// Habilitar int. vectorizadas y la linea IRQ (FIQ no)
		rINTCON=0x1;

		// Enmascarar todas las lineas excepto Timer0 y el bit global
		// rINTMSK = rINTMSK & ~(BIT_TIMER0 | BIT_GLOBAL);
		rINTMSK = rINTMSK & ~(BIT_TIMER0 | BIT_TIMER2 | BIT_TIMER4 | BIT_GLOBAL);

	/* Establece la rutina de servicio para TIMER0 */
		pISR_TIMER0 = (unsigned)timer0_juego;
		pISR_TIMER2 = (unsigned)timer2_mostrar_mensaje;
		pISR_TIMER4 = (unsigned)timer4_tiempo_juego;

	/* Configurar los Timer{0,2,4} (el resto de los timers se dejan a la configuración por defecto) */
		// Capitulo 9 ~244)
		rTCFG0 = 0xFFFFFF; // pre-escalado = 255 a los 3 timers

		/*
		    0000 = 1/2 0001 = 1/4 0010 = 1/8
			0011 = 1/16 01xx = 1/32
		*/
		rTCFG1 = 0xF7F0F0; // divisor = 1/2

		rTCNTB0 = 65535;
		rTCMPB0 = 12800;

		rTCNTB2 = 65535/2;
		rTCMPB2 = 12800;

		rTCNTB4 = 65535;
		rTCMPB4 = 12800;


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

void timer0_juego(void) {

	// Turno maquina
	if ( turno == 0 && indice < nivel) {
		D8Led_symbol(secuencia_maquina[indice]);
		indice++;
	}
	else {
		turno = 1;
		D8Led_symbol(18);
		enciende_timer4();
	}

	rI_ISPC = BIT_TIMER0;
}




// Muestra los mensajes L (listo) o P (pierde)
void timer2_mostrar_mensaje(void) {

	// Esta listo
	if ( pierde == 0) {
		if ( apagado == 0){
			D8Led_symbol(16);
			apagado = 1;
		}
		else {
			D8Led_symbol(18);
			apagado = 0;
		}

	}
	else {
		if ( apagado == 0){
			D8Led_symbol(17);
			apagado = 1;
		}
		else {
			D8Led_symbol(18);
			apagado = 0;
		}
	}

	rI_ISPC = BIT_TIMER2;

}

//
void timer4_tiempo_juego(void) {

	if ( turno == 1 ) {
		led_jugadorPierde();
		pierde = 1;
	}

	enciende_timer2();
	rI_ISPC = BIT_TIMER4;

}

// LED derecho
void led_jugador(void){
	leds_off();
	led1_on();
}

// LED izquierdo
void led_maquina(void){
	leds_off();
	led2_on();
}

// Ambos apagados
void led_preparado(void) {
	leds_off();
}

// Ambos encendidos
void led_jugadorPierde(void) {
	led1_on();
	led2_on();
}
