/*--- ficheros de cabecera ---*/
#include "44blib.h"
#include "44b.h"
#include "stdio.h"

/*--- funciones externas ---*/
extern void leds_off();
extern void led1_on();
extern void timer_init();

int secuencia_maquina[100];
int secuencia_jugador[100];
int pierde;
int indice;
int indice_jug;
int nivel;
int turno;
int switchLed;

/*--- declaracion de funciones ---*/
void Main(void);
void generar_secuencia_maquina(void);
void comparar_secuencias(void);
/*--- codigo de funciones ---*/

void Main(void) {
	/* Inicializar controladores */
	sys_init(); // Inicializacion de la placa, interrupciones y puertos

	rPCONG = rPCONG & 0xffff0fff;
	rPUPG = 0;


	keyboard_init();

	D8Led_init();
	D8Led_symbol(18);

	led1_on();
	led2_on();

	pierde = 0;
	turno = 0;
	indice = 0;
	indice_jug = 0;
	nivel = 0;
	switchLed = 0;

	timer_init(); // Inicializacion del temporizador

	enciende_timer2();
	while( !(rPDATG & 0x00000040) == 0 ) {}


	while (pierde == 0) {

		/* Turno maquina */
			leds_off();
			led1_on();
			turno = 0;
			indice = 0;
			generar_secuencia_maquina();
			enciende_timer0();

			while(turno == 0) {}

		/* Turno jugador */
			indice_jug = 0;
			leds_off();
			led2_on();
			while ( !(rPDATG & 0x00000080) == 0 ) {}
			D8Led_symbol(18);
			DelayMs(500);
			comparar_secuencias();

	}


	leds_off();
	enciende_timer2();
	// Ha perdido
	while(1) {}

}

void generar_secuencia_maquina(void) {

	secuencia_maquina[nivel] = (rand() % 15) + 1;
	nivel++;

}

void comparar_secuencias(void) {

	if ( indice_jug > nivel ) {
		pierde = 1;
	}

	int i;
	for(i = 0;i<nivel && pierde == 0;++i) {
		if ( secuencia_jugador[i] != secuencia_maquina[i] ) {
			pierde = 1;
		}
	}

}
