/*--- ficheros de cabecera ---*/
#include "44blib.h"
#include "44b.h"
#include "uart.h"
#include "lcd.h"
#include "snake.h"

/*--- Externas ---*/
 extern void Eint4567_init(void);
 extern void keyboard_init();
 extern void D8Led_init(void);
 extern void D8Led_symbol(int value);
/*--- declaracion de funciones ---*/
int Main(void);




/*--- codigo de la funcion ---*/
int Main(void){

	sys_init(); // inicializacion de la placa, interrupciones, puertos

    //Inicializamos los botones
    rPCONG = rPCONG & 0xffff0fff;
    rPUPG = 0;

    lcd_init();

    Eint4567_init();

    keyboard_init();

    timer_init(); // Inicializacion del temporizador

    D8Led_init();
    D8Led_symbol(0);


	Uart_Init(115200); 		// inicializacion de la Uart
	Uart_Config(); 			// configuración de interrupciones y buffers


	D8Led_symbol(0);
	Uart1_TxEmpty();

	lcd_draw_esperar_otro_jugador();

	// Esperamos a recibir el id del jugador (1 o 2)
	char id = Uart1_Getch();
	char dir = '\0';

    while(1) {

    	lcd_clear();

    	if ( id == '1' ) {
    		D8Led_symbol(1);
    		while( !(rPDATG & 0x00000040) == 0 ) {}
    		Uart1_SendByte('E');
    	}
    	else if ( id == '2'){
    		D8Led_symbol(2);

//    		lcd_draw_esperar_otro_jugador();

    		dir = Uart1_Getch();
    		while( dir != 'E') {
    			dir = Uart1_Getch();
    		}
    	}


		iniciar_snake(id);
		pintar();
		enciende_timer0();

		while (jug1Vivo && jug2_dir != 'F') {


			if ( id == '1' ) {
				enviar_direccion();
				recibir_direccion();
			}
			else if ( id == '2' ) {
				recibir_direccion();
				enviar_direccion();
			}


			actualizar();

			repintar();

			DelayMs(80);
		}

		// Si pierde un maletin...
		if (jug1Vivo == 0) {
			enviar_perdido();
		}


		apagar_timers();

    }


	return 0;

}
