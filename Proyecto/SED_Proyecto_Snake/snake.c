#include "snake.h"
#include "lcd.h"
#include "uart.h"
#include "stdio.h"	// rand

void iniciar_snake(char id) {

	crear_tablero();

	if ( id == '1')
		crear_jugadores_tipoA();

	else if ( id == '2')
		crear_jugadores_tipoB();

	numAC = 0;

	frutaX = 100;	// Pintamos la fruta fuera del tablero.
	frutaY = 100;

	actualizar_pos_tablero(frutaX, frutaY, FRUTA);
}

void crear_tablero() {
	int i = 0;
	int j = 0;

	for (i = 0; i < FILAS;++i) {
		for (j = 0; j < COLUMNAS; ++j) {
			if (i == 0 || i == FILAS-1 || j == 0 || j == COLUMNAS-1)
				tablero[i][j] = MURO;
			else
				tablero[i][j] = VACIO;

		}
	}

	// Muros
	for (i=10;i<30;i++) {
		tablero[20][i] = MURO;
	}


}

void crear_jugadores_tipoA() {
	jug1X 	 = 5;
	jug1Y 	 = 5;
	jug1Vivo = 1;
	niveljug1 = 2;
	snake_jug1[0].x = jug1X;
	snake_jug1[0].y = jug1Y;
	snake_jug1[1].x = jug1X;
	snake_jug1[1].y = jug1Y - 1;

	tablero[jug1X][jug1Y] = CABEZA_J1;
	tablero[jug1X][jug1Y-1] = CUERPO_J1;
	jug1_dir = DIRECCION_DER;

	jug2X 	 = 5;
	jug2Y 	 = COLUMNAS - 5;
	jug2Vivo = 1;
	niveljug2 = 2;
	snake_jug2[0].x = jug2X;
	snake_jug2[0].y = jug2Y;
	snake_jug2[1].x = jug2X;
	snake_jug2[1].y = jug2Y + 1;

	tablero[jug2X][jug2Y] = CABEZA_J2;
	tablero[jug2X][jug2Y+1] = CUERPO_J2;
	jug2_dir = DIRECCION_IZQ;
}

void crear_jugadores_tipoB() {
	jug1X 	 = 5;
	jug1Y 	 = COLUMNAS - 5;
	jug1Vivo = 1;
	niveljug1 = 2;
	snake_jug1[0].x = jug1X;
	snake_jug1[0].y = jug1Y;
	snake_jug1[1].x = jug1X;
	snake_jug1[1].y = jug1Y + 1;

	tablero[jug1X][jug1Y] = CABEZA_J1;
	tablero[jug1X][jug1Y+1] = CUERPO_J1;
	jug1_dir = DIRECCION_IZQ;

	jug2X 	 = 5;
	jug2Y 	 = 5;
	jug2Vivo = 1;
	niveljug2 = 2;
	snake_jug2[0].x = jug2X;
	snake_jug2[0].y = jug2Y;
	snake_jug2[1].x = jug2X;
	snake_jug2[1].y = jug2Y - 1;

	tablero[jug2X][jug2Y] = CABEZA_J2;
	tablero[jug2X][jug2Y-1] = CUERPO_J2;
	jug2_dir = DIRECCION_DER;
}


void pintar() {
	int i = 0;
	int j = 0;

	for (i = 0; i < FILAS; ++i) {
		for (j = 0; j < COLUMNAS; ++j) {
			if ( tablero[i][j] == MURO ) {
				lcd_pintar_muro(i * CELDA, j * CELDA, CELDA);
			}

		}
	}
}

void repintar() {

	int i = 0;

	for (i = 0; i < numAC; ++i) {

		if ( ac[i].nuevo_valor == CABEZA_J1 || ac[i].nuevo_valor == CABEZA_J2 ) {
			if (jug1_dir == DIRECCION_ARRIBA)
				lcd_pintar_cabeza_serpiente_arriba(ac[i].x * CELDA, ac[i].y * CELDA);
			if (jug1_dir == DIRECCION_ABAJO)
				lcd_pintar_cabeza_serpiente_abajo(ac[i].x * CELDA, ac[i].y * CELDA);
			if (jug1_dir == DIRECCION_IZQ)
				lcd_pintar_cabeza_serpiente_izquierda(ac[i].x * CELDA, ac[i].y * CELDA);
			else
				lcd_pintar_cabeza_serpiente_derecha(ac[i].x * CELDA, ac[i].y * CELDA);
		}
		else if ( ac[i].nuevo_valor == CUERPO_J1 ) {
			lcd_pintar_celda(ac[i].x * CELDA, ac[i].y * CELDA, CELDA, LCD_WHITE); //OPTIMIZAR!!!
			lcd_pintar_cuerpo_serpiente1(ac[i].x * CELDA, ac[i].y * CELDA, CELDA);
		}
		else if ( ac[i].nuevo_valor == CUERPO_J2 ) {
			lcd_pintar_celda(ac[i].x * CELDA, ac[i].y * CELDA, CELDA, LCD_WHITE); //OPTIMIZAR!!!
			lcd_pintar_cuerpo_serpiente2(ac[i].x * CELDA, ac[i].y * CELDA);
		}
		else if ( ac[i].nuevo_valor == VACIO ) {
			lcd_pintar_celda(ac[i].x * CELDA, ac[i].y * CELDA, CELDA, LCD_WHITE);
		}
		else if ( ac[i].nuevo_valor == FRUTA ) {
			if (jug1_dir == DIRECCION_ARRIBA)
				lcd_pintar_naranja(ac[i].x * CELDA, ac[i].y * CELDA);
			else if (jug1_dir == DIRECCION_ABAJO)
				lcd_pintar_platano(ac[i].x * CELDA, ac[i].y * CELDA);
			else
				lcd_pintar_cereza(ac[i].x * CELDA, ac[i].y * CELDA);
		}
	}
	numAC = 0;
}

void cambiar_direccion_jugador1(int dir) {

	if ( (dir == DIRECCION_ARRIBA && jug1_dir != DIRECCION_ABAJO) ||
			(dir == DIRECCION_ABAJO && jug1_dir != DIRECCION_ARRIBA) ||
			(dir == DIRECCION_DER && jug1_dir != DIRECCION_IZQ) ||
			(dir == DIRECCION_IZQ && jug1_dir != DIRECCION_DER))

		jug1_dir = dir;
}

void actualizar() {

	switch( jug1_dir ) {
		case DIRECCION_ARRIBA:
			jug1X--;
		break;

		case DIRECCION_ABAJO:
			jug1X++;
		break;

		case DIRECCION_DER:
			jug1Y++;
		break;

		case DIRECCION_IZQ:
			jug1Y--;
		break;
	}


	switch( jug2_dir ) {
		case DIRECCION_ARRIBA:
			jug2X--;
		break;

		case DIRECCION_ABAJO:
			jug2X++;
		break;

		case DIRECCION_DER:
			jug2Y++;
		break;

		case DIRECCION_IZQ:
			jug2Y--;
		break;
	}

	// Comprobamos situaciones de colision, comer o mover la serpiente

	if ( tablero[jug1X][jug1Y] != VACIO && tablero[jug1X][jug1Y] != FRUTA )
		jug1Vivo = 0;
	else if ( tablero[jug2X][jug2Y] != VACIO && tablero[jug2X][jug2Y] != FRUTA )
		jug2Vivo = 0;
	else {

		int i;

		for (i = niveljug1; i > 0; --i)
			snake_jug1[i] = snake_jug1[i-1];

		for (i = niveljug2; i > 0; --i)
			snake_jug2[i] = snake_jug2[i-1];

		snake_jug1[0].x = jug1X;
		snake_jug1[0].y = jug1Y;

		snake_jug2[0].x = jug2X;
		snake_jug2[0].y = jug2Y;


		if ( tablero[jug1X][jug1Y] == FRUTA )
			niveljug1++;
		else
			actualizar_pos_tablero(snake_jug1[niveljug1].x, snake_jug1[niveljug1].y, VACIO); // Mandamos borrar la cola del jugador 1

		if ( tablero[jug2X][jug2Y] == FRUTA )
			niveljug2++;
		else
			actualizar_pos_tablero(snake_jug2[niveljug2].x, snake_jug2[niveljug2].y, VACIO); // Mandamos borrar la cola del jugador 2

		actualizar_pos_tablero(jug1X, jug1Y, CABEZA_J1); // Mandamos pintar la cabeza del jugador 1
		actualizar_pos_tablero(snake_jug1[1].x, snake_jug1[1].y, CUERPO_J1); // Mandamos pintar el cuerpo del jugador 1 que antes era cabeza

		actualizar_pos_tablero(jug2X, jug2Y, CABEZA_J2); // Mandamos pintar la cabeza del jugador 2
		actualizar_pos_tablero(snake_jug2[1].x, snake_jug2[1].y, CUERPO_J2); // Mandamos pintar el cuerpo del jugador 2 que antes era cabeza
	}
}

void actualizar_pos_tablero(int x, int y, int nuevo_valor){
	tablero[x][y] = nuevo_valor;
	ac[numAC].x = x;
	ac[numAC].y = y;
	ac[numAC].nuevo_valor = nuevo_valor;
	numAC++;

}

void generarFruta(void) {
	// Quitamos (si existe) la fruta anterior
	actualizar_pos_tablero(frutaX, frutaY, VACIO);

	// Ponemos la fruta nueva
	do {
		int r = 7;//rand() % COLUMNAS;
		frutaX = ( (r + jug1X + jug2X) % (FILAS - 2)) + 1;
		frutaY = ( (r + jug1Y + jug2Y) % (COLUMNAS - 2)) + 1;
	}while ( tablero[frutaX][frutaY] == MURO || tablero[frutaX][frutaY] == CABEZA_J1 || tablero[frutaX][frutaY] == CUERPO_J1 );

	actualizar_pos_tablero(frutaX, frutaY, FRUTA);
}

void enviar_direccion(void) {
	Uart1_SendByte(jug1_dir);
}

void recibir_direccion(void) {
	jug2_dir = Uart1_Getch();
}

void enviar_perdido(void) {
	Uart1_SendByte('F');
}
