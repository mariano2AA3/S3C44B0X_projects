#include "lcd.h"
#include <stdarg.h>
#include <stdio.h>

static uint8 buffer[320*240/2];
void lcd_init( void ){
	rLCDCON1 	= 0x1C021;//
	rLCDCON2 	= 0x13CEF;//
	rLCDSADDR1 	= (2<<27) | ((uint32) buffer >> 1);
	rLCDSADDR2 	= (1<<29) | (((uint32) buffer + LCD_BUFFER_SIZE) & 0x3FFFFF) >> 1;
	rLCDSADDR3 	= 0x50;
	rLCDCON3	= 0x0;
	rREDLUT 	= 0x0;
	rBLUELUT 	= 0x0;
	rGREENLUT 	= 0x0;
	rDITHMODE 	= 0x12210;
	rDP1_2 		= 0xA5A5;
	rDP4_7 		= 0xBA5DA65;
	rDP3_5 		= 0xA5A5F;
	rDP2_3 		= 0xD6B;
	rDP5_7 		= 0xEB7B5ED;
	rDP3_4 		= 0x77DBE;//
	rDP4_5 		= 0x7EBDF;
	rDP6_7 		= 0x7FDFBFE;
}

/*
** Borra el lcd
*/
void lcd_clear( void ){
	int i;
	int j;
	for(i = 0; i < 240; i++)
		for(j = 0; j < 320; j++)
			lcd_putpixel(i, j, LCD_WHITE);
}

/*
** Pone el pixel (x,y) en el color indicado
*/
void lcd_putpixel( uint16 x, uint16 y, uint8 color){
	uint8 byte, bit;
	uint16 i;

	i = y/2 + x*(320/2);
	bit = (1-y%2)*4;
	byte = buffer[i];
	byte &= ~(0xF << bit);
	byte |= color << bit;
	buffer[i] = byte;
}

/*
** Devuelve el color al que está el pixel (x,y)
*/
uint8 lcd_getpixel( uint16 x, uint16 y ){
	uint8 color;
	uint32 word;
	word = buffer[x/8 + y*(320/8)];
	word &= (0xf0000000 >> (x%8)*4);		
	color = (uint32) word >> (7 - x%8)*4; // ver cuanto calcular
	
	return color;
}

/*
** Dibuja una línea horizontal desde el pixel (xleft,y) hasta el pixel (xright,y) del color y grosor indicados
*/
void lcd_draw_hline( uint16 xleft, uint16 xright, uint16 y, uint8 color, uint16 width ){	
	int i;
	int tam;
	for(tam = 0; tam < width; tam++)
		for(i = xleft; i < xright; i++)
				lcd_putpixel(i, y + tam, color);	
}

/*
** Dibuja una línea vertical desde el pixel (x,yup) hasta el pixel (x,ydown) del color y grosor indicados
*/
void lcd_draw_vline( uint16 yup, uint16 ydown, uint16 x, uint8 color, uint16 width ){
	int j;
	int tam;
	for(tam = 0; tam < width; tam++)
		for(j = ydown; j < yup; j++)
				lcd_putpixel(x + tam, j, color);
}

/*
** Dibuja un rectángulo cuya esquina superior izquierda está en el pixel (xleft,yup) y cuya esquina inferior está en el píxel (xright, ydown) del color y grosor indicados
*/
void lcd_draw_box( uint16 xleft, uint16 yup, uint16 xright, uint16 ydown, uint8 color, uint16 width ){
	lcd_draw_hline(xleft+width, xright+width, ydown, color, width);
	lcd_draw_vline(ydown, yup, xright, color, width);
	lcd_draw_hline(xleft, xright, yup, color, width);
	lcd_draw_vline(ydown+width, yup+width, xleft, color, width);
}

void lcd_pintar_celda(uint16 x, uint16 y, uint8 tam_celda, uint8 color) {
	uint16 i, j;
	for (i = x; i < x + tam_celda; ++i)
		for (j = y; j < y + tam_celda; ++j)
			lcd_putpixel( i, j, color);
}

void lcd_pintar_cabeza_serpiente_arriba(uint16 x, uint16 y) {
		lcd_putpixel(x + 0, y + 3, LCD_BLACK);
		lcd_putpixel(x + 0, y + 4, LCD_BLACK);
		lcd_putpixel(x + 1, y + 2, LCD_BLACK);
		lcd_putpixel(x + 1, y + 5, LCD_BLACK);
		lcd_putpixel(x + 2, y + 1, LCD_BLACK);
		lcd_putpixel(x + 2, y + 6, LCD_BLACK);
		lcd_putpixel(x + 3, y + 0, LCD_BLACK);
		lcd_putpixel(x + 3, y + 7, LCD_BLACK);
		lcd_putpixel(x + 4, y + 0, LCD_BLACK);
		lcd_putpixel(x + 4, y + 1, LCD_BLACK);
		lcd_putpixel(x + 4, y + 2, LCD_BLACK);
		lcd_putpixel(x + 4, y + 5, LCD_BLACK);
		lcd_putpixel(x + 4, y + 6, LCD_BLACK);
		lcd_putpixel(x + 4, y + 7, LCD_BLACK);
		lcd_putpixel(x + 5, y + 0, LCD_BLACK);
		lcd_putpixel(x + 5, y + 1, LCD_BLACK);
		lcd_putpixel(x + 5, y + 2, LCD_BLACK);
		lcd_putpixel(x + 5, y + 5, LCD_BLACK);
		lcd_putpixel(x + 5, y + 6, LCD_BLACK);
		lcd_putpixel(x + 5, y + 7, LCD_BLACK);
		lcd_putpixel(x + 6, y + 0, LCD_BLACK);
		lcd_putpixel(x + 6, y + 7, LCD_BLACK);
		lcd_putpixel(x + 7, y + 0, LCD_BLACK);
		lcd_putpixel(x + 7, y + 1, LCD_BLACK);
		lcd_putpixel(x + 7, y + 2, LCD_BLACK);
		lcd_putpixel(x + 7, y + 3, LCD_BLACK);
		lcd_putpixel(x + 7, y + 4, LCD_BLACK);
		lcd_putpixel(x + 7, y + 5, LCD_BLACK);
		lcd_putpixel(x + 7, y + 6, LCD_BLACK);
		lcd_putpixel(x + 7, y + 7, LCD_BLACK);
}

void lcd_pintar_cabeza_serpiente_abajo(uint16 x, uint16 y) {
		lcd_putpixel(x + 0, y + 0, LCD_BLACK);
		lcd_putpixel(x + 0, y + 1, LCD_BLACK);
		lcd_putpixel(x + 0, y + 2, LCD_BLACK);
		lcd_putpixel(x + 0, y + 3, LCD_BLACK);
		lcd_putpixel(x + 0, y + 4, LCD_BLACK);
		lcd_putpixel(x + 0, y + 5, LCD_BLACK);
		lcd_putpixel(x + 0, y + 6, LCD_BLACK);
		lcd_putpixel(x + 0, y + 7, LCD_BLACK);
		lcd_putpixel(x + 1, y + 0, LCD_BLACK);
		lcd_putpixel(x + 1, y + 7, LCD_BLACK);
		lcd_putpixel(x + 2, y + 0, LCD_BLACK);
		lcd_putpixel(x + 2, y + 1, LCD_BLACK);
		lcd_putpixel(x + 2, y + 2, LCD_BLACK);
		lcd_putpixel(x + 2, y + 5, LCD_BLACK);
		lcd_putpixel(x + 2, y + 6, LCD_BLACK);
		lcd_putpixel(x + 2, y + 7, LCD_BLACK);
		lcd_putpixel(x + 3, y + 0, LCD_BLACK);
		lcd_putpixel(x + 3, y + 1, LCD_BLACK);
		lcd_putpixel(x + 3, y + 2, LCD_BLACK);
		lcd_putpixel(x + 3, y + 5, LCD_BLACK);
		lcd_putpixel(x + 3, y + 6, LCD_BLACK);
		lcd_putpixel(x + 3, y + 7, LCD_BLACK);
		lcd_putpixel(x + 4, y + 0, LCD_BLACK);
		lcd_putpixel(x + 4, y + 7, LCD_BLACK);
		lcd_putpixel(x + 5, y + 1, LCD_BLACK);
		lcd_putpixel(x + 5, y + 6, LCD_BLACK);
		lcd_putpixel(x + 6, y + 2, LCD_BLACK);
		lcd_putpixel(x + 6, y + 5, LCD_BLACK);
		lcd_putpixel(x + 7, y + 3, LCD_BLACK);
		lcd_putpixel(x + 7, y + 4, LCD_BLACK);
}

void lcd_pintar_cabeza_serpiente_derecha(uint16 x, uint16 y) {
		lcd_putpixel(x + 0, y + 0, LCD_BLACK);
		lcd_putpixel(x + 1, y + 0, LCD_BLACK);
		lcd_putpixel(x + 2, y + 0, LCD_BLACK);
		lcd_putpixel(x + 3, y + 0, LCD_BLACK);
		lcd_putpixel(x + 4, y + 0, LCD_BLACK);
		lcd_putpixel(x + 5, y + 0, LCD_BLACK);
		lcd_putpixel(x + 6, y + 0, LCD_BLACK);
		lcd_putpixel(x + 7, y + 0, LCD_BLACK);
		lcd_putpixel(x + 0, y + 1, LCD_BLACK);
		lcd_putpixel(x + 7, y + 1, LCD_BLACK);
		lcd_putpixel(x + 0, y + 2, LCD_BLACK);
		lcd_putpixel(x + 1, y + 2, LCD_BLACK);
		lcd_putpixel(x + 2, y + 2, LCD_BLACK);
		lcd_putpixel(x + 5, y + 2, LCD_BLACK);
		lcd_putpixel(x + 6, y + 2, LCD_BLACK);
		lcd_putpixel(x + 7, y + 2, LCD_BLACK);
		lcd_putpixel(x + 0, y + 3, LCD_BLACK);
		lcd_putpixel(x + 1, y + 3, LCD_BLACK);
		lcd_putpixel(x + 2, y + 3, LCD_BLACK);
		lcd_putpixel(x + 5, y + 3, LCD_BLACK);
		lcd_putpixel(x + 6, y + 3, LCD_BLACK);
		lcd_putpixel(x + 7, y + 3, LCD_BLACK);
		lcd_putpixel(x + 0, y + 4, LCD_BLACK);
		lcd_putpixel(x + 7, y + 4, LCD_BLACK);
		lcd_putpixel(x + 1, y + 5, LCD_BLACK);
		lcd_putpixel(x + 6, y + 5, LCD_BLACK);
		lcd_putpixel(x + 2, y + 6, LCD_BLACK);
		lcd_putpixel(x + 5, y + 6, LCD_BLACK);
		lcd_putpixel(x + 3, y + 7, LCD_BLACK);
		lcd_putpixel(x + 4, y + 7, LCD_BLACK);
}

void lcd_pintar_cabeza_serpiente_izquierda(uint16 x, uint16 y) {
		lcd_putpixel(x + 3, y + 0, LCD_BLACK);
		lcd_putpixel(x + 4, y + 0, LCD_BLACK);
		lcd_putpixel(x + 2, y + 1, LCD_BLACK);
		lcd_putpixel(x + 5, y + 1, LCD_BLACK);
		lcd_putpixel(x + 1, y + 2, LCD_BLACK);
		lcd_putpixel(x + 6, y + 2, LCD_BLACK);
		lcd_putpixel(x + 0, y + 3, LCD_BLACK);
		lcd_putpixel(x + 7, y + 3, LCD_BLACK);
		lcd_putpixel(x + 0, y + 4, LCD_BLACK);
		lcd_putpixel(x + 1, y + 4, LCD_BLACK);
		lcd_putpixel(x + 2, y + 4, LCD_BLACK);
		lcd_putpixel(x + 5, y + 4, LCD_BLACK);
		lcd_putpixel(x + 6, y + 4, LCD_BLACK);
		lcd_putpixel(x + 7, y + 4, LCD_BLACK);
		lcd_putpixel(x + 0, y + 5, LCD_BLACK);
		lcd_putpixel(x + 1, y + 5, LCD_BLACK);
		lcd_putpixel(x + 2, y + 5, LCD_BLACK);
		lcd_putpixel(x + 5, y + 5, LCD_BLACK);
		lcd_putpixel(x + 6, y + 5, LCD_BLACK);
		lcd_putpixel(x + 7, y + 5, LCD_BLACK);
		lcd_putpixel(x + 0, y + 6, LCD_BLACK);
		lcd_putpixel(x + 7, y + 6, LCD_BLACK);
		lcd_putpixel(x + 0, y + 7, LCD_BLACK);
		lcd_putpixel(x + 1, y + 7, LCD_BLACK);
		lcd_putpixel(x + 2, y + 7, LCD_BLACK);
		lcd_putpixel(x + 3, y + 7, LCD_BLACK);
		lcd_putpixel(x + 4, y + 7, LCD_BLACK);
		lcd_putpixel(x + 5, y + 7, LCD_BLACK);
		lcd_putpixel(x + 6, y + 7, LCD_BLACK);
		lcd_putpixel(x + 7, y + 7, LCD_BLACK);
}

void lcd_pintar_cuerpo_serpiente1(uint16 x, uint16 y, uint8 tam_celda) {
	uint16 i, j;
	for (i = x; i < x + tam_celda; ++i) {
		for (j = y; j < y + tam_celda; ++j) {
			if ((x + y) % 2 == 0 || i == x || i == x + tam_celda - 1 || j == y || j == y + tam_celda - 1 ) 
				lcd_putpixel( i, j, LCD_BLACK);
			else
				lcd_putpixel( i, j, LCD_LIGHTGRAY);
		}
	}
}

void lcd_pintar_cuerpo_serpiente2(uint16 x, uint16 y) {
	lcd_pintar_naranja(x, y);
}

void lcd_pintar_cereza(uint16 x, uint16 y) {
	lcd_putpixel(x + 0, y + 5, LCD_BLACK);
	lcd_putpixel(x + 0, y + 6, LCD_BLACK);
	lcd_putpixel(x + 1, y + 4, LCD_BLACK);
	lcd_putpixel(x + 1, y + 5, LCD_BLACK);
	lcd_putpixel(x + 2, y + 3, LCD_BLACK);
	lcd_putpixel(x + 2, y + 4, LCD_BLACK);
	lcd_putpixel(x + 3, y + 1, LCD_BLACK);
	lcd_putpixel(x + 3, y + 2, LCD_BLACK);
	lcd_putpixel(x + 3, y + 3, LCD_BLACK);
	lcd_putpixel(x + 3, y + 4, LCD_BLACK);
	lcd_putpixel(x + 3, y + 5, LCD_BLACK);
	lcd_putpixel(x + 3, y + 6, LCD_BLACK);
	lcd_putpixel(x + 4, y + 0, LCD_BLACK);
	lcd_putpixel(x + 4, y + 3, LCD_BLACK);
	lcd_putpixel(x + 4, y + 7, LCD_BLACK);
	lcd_putpixel(x + 5, y + 0, LCD_BLACK);
	lcd_putpixel(x + 5, y + 3, LCD_BLACK);
	lcd_putpixel(x + 5, y + 7, LCD_BLACK);
	lcd_putpixel(x + 6, y + 0, LCD_BLACK);
	lcd_putpixel(x + 6, y + 3, LCD_BLACK);
	lcd_putpixel(x + 6, y + 7, LCD_BLACK);
	lcd_putpixel(x + 7, y + 1, LCD_BLACK);
	lcd_putpixel(x + 7, y + 2, LCD_BLACK);
	lcd_putpixel(x + 7, y + 4, LCD_BLACK);
	lcd_putpixel(x + 7, y + 5, LCD_BLACK);
	lcd_putpixel(x + 7, y + 6, LCD_BLACK);
}

void lcd_pintar_platano(uint16 x, uint16 y) {
	lcd_putpixel(x + 0, y + 6, LCD_BLACK);
	lcd_putpixel(x + 0, y + 7, LCD_BLACK);
	lcd_putpixel(x + 1, y + 6, LCD_BLACK);
	lcd_putpixel(x + 1, y + 7, LCD_BLACK);
	lcd_putpixel(x + 2, y + 5, LCD_BLACK);
	lcd_putpixel(x + 2, y + 7, LCD_BLACK);
	lcd_putpixel(x + 3, y + 5, LCD_BLACK);
	lcd_putpixel(x + 3, y + 7, LCD_BLACK);
	lcd_putpixel(x + 4, y + 4, LCD_BLACK);
	lcd_putpixel(x + 4, y + 7, LCD_BLACK);
	lcd_putpixel(x + 5, y + 1, LCD_BLACK);
	lcd_putpixel(x + 5, y + 2, LCD_BLACK);
	lcd_putpixel(x + 5, y + 3, LCD_BLACK);
	lcd_putpixel(x + 5, y + 6, LCD_BLACK);
	lcd_putpixel(x + 5, y + 7, LCD_BLACK);
	lcd_putpixel(x + 6, y + 0, LCD_BLACK);
	lcd_putpixel(x + 6, y + 5, LCD_BLACK);
	lcd_putpixel(x + 6, y + 6, LCD_BLACK);
	lcd_putpixel(x + 7, y + 0, LCD_BLACK);
	lcd_putpixel(x + 7, y + 1, LCD_BLACK);
	lcd_putpixel(x + 7, y + 2, LCD_BLACK);
	lcd_putpixel(x + 7, y + 3, LCD_BLACK);
	lcd_putpixel(x + 7, y + 4, LCD_BLACK);
	lcd_putpixel(x + 7, y + 5, LCD_BLACK);
}

void lcd_pintar_naranja(uint16 x, uint16 y) {
	lcd_putpixel(x + 0, y + 2, LCD_BLACK);
	lcd_putpixel(x + 0, y + 3, LCD_BLACK);
	lcd_putpixel(x + 0, y + 4, LCD_BLACK);
	lcd_putpixel(x + 0, y + 5, LCD_BLACK);
	lcd_putpixel(x + 1, y + 1, LCD_BLACK);
	lcd_putpixel(x + 1, y + 6, LCD_BLACK);
	lcd_putpixel(x + 2, y + 0, LCD_BLACK);
	lcd_putpixel(x + 2, y + 2, LCD_BLACK);
	lcd_putpixel(x + 2, y + 7, LCD_BLACK);
	lcd_putpixel(x + 3, y + 0, LCD_BLACK);
	lcd_putpixel(x + 3, y + 5, LCD_BLACK);
	lcd_putpixel(x + 3, y + 7, LCD_BLACK);
	lcd_putpixel(x + 4, y + 0, LCD_BLACK);
	lcd_putpixel(x + 4, y + 2, LCD_BLACK);
	lcd_putpixel(x + 4, y + 7, LCD_BLACK);
	lcd_putpixel(x + 5, y + 0, LCD_BLACK);
	lcd_putpixel(x + 5, y + 4, LCD_BLACK);
	lcd_putpixel(x + 5, y + 7, LCD_BLACK);
	lcd_putpixel(x + 6, y + 1, LCD_BLACK);
	lcd_putpixel(x + 6, y + 6, LCD_BLACK);
	lcd_putpixel(x + 7, y + 2, LCD_BLACK);
	lcd_putpixel(x + 7, y + 3, LCD_BLACK);
	lcd_putpixel(x + 7, y + 4, LCD_BLACK);
	lcd_putpixel(x + 7, y + 5, LCD_BLACK);
}

void lcd_pintar_muro(uint16 x, uint16 y, uint8 tam_celda) {
	uint16 i, j;
	for (i = x; i < x + tam_celda; ++i)
		for (j = y; j < y + tam_celda; ++j)
			lcd_putpixel(i, j, LCD_BLACK);

	lcd_putpixel(x + 3, y + 2, LCD_BLACK);
	lcd_putpixel(x + 3, y + 4, LCD_BLACK);
	lcd_putpixel(x + 3, y + 6, LCD_BLACK);
	lcd_putpixel(x + 4, y + 1, LCD_BLACK);
	lcd_putpixel(x + 4, y + 3, LCD_BLACK);
	lcd_putpixel(x + 4, y + 5, LCD_BLACK);
	lcd_putpixel(x + 5, y + 2, LCD_BLACK);
	lcd_putpixel(x + 5, y + 4, LCD_BLACK);
	lcd_putpixel(x + 5, y + 6, LCD_BLACK);
	lcd_putpixel(x + 6, y + 1, LCD_BLACK);
	lcd_putpixel(x + 6, y + 3, LCD_BLACK);
	lcd_putpixel(x + 6, y + 5, LCD_BLACK);
}


void lcd_draw_esperar_otro_jugador(void) {

	lcd_pintar_celda(0, 0, 8, LCD_BLACK);

}

/*
** Usando una fuente 8x16, escribe un caracter a partir del pixel (x,y) en el color indicado
*/
/*
void lcd_putchar( uint16 x, uint16 y, uint8 color, char ch ){
	uint8 row, line;
	uint8 *bitmap;
	bitmap = font + ch*16;
	for(line = 0; line < 16; line++){
		for(row = 0; row < 8; row++){
			if(bitmap[line] & (0x80>>row))
				lcd_putpixel(x+row, y+line, color);
			else
				lcd_putpixel(x+row, y+line, LCD_WHITE);
		}
	}		
}
*/

/*
** Usando una fuente 8x16, escribe una cadena a partir del pixel (x,y) en el color indicado
*/
/*
void lcd_puts( uint16 x, uint16 y, uint8 color, char *s ){	
	while(*s) {
		lcd_putchar(x, y, color, *s);
		s++;
		x = x + 8;
	}	
}
*/

/*
** Usando una fuente 8x16, escribe texto formateado a partir del pixel (x,y) en el color indicado
*/
/*
uint32 lcd_printf( uint16 x, uint16 y, uint8 color, const char *fmt, ... ){
	va_list arg_p;
	
	char cadena[256];
	int32 charRetorno;
	
	va_start(arg_p, fmt);
	
	charRetorno = vsprintf(cadena, fmt, arg_p);
	
	va_end(arg_p);
	
	lcd_puts(x, y, color, cadena);
	
	return charRetorno;
}
*/

/*
** Usando una fuente 8x16, escribe un caracter a doble tamaño a partir del pixel (x,y) en el color indicado
*/
/*
void lcd_putchar_x2( uint16 x, uint16 y, uint8 color, char ch ){
	uint8 row, line;
	uint8 *bitmap;
	bitmap = font + ch*16;
	for(line = 0; line < 16; line++){
		for(row = 0; row < 8; row++){
			if(bitmap[line] & (0x80>>row)) {
				lcd_putpixel(2*(x+row)-18, 2*(y+line) - y, color);
				lcd_putpixel(2*(x+row)-1-18, 2*(y+line) - y, color);				
				lcd_putpixel(2*(x+row)-18, 2*(y+line)+1 - y, color);				
				lcd_putpixel(2*(x+row)-1-18, 2*(y+line)+1 - y, color);
				
			} else {
				lcd_putpixel(2*(x+row)-18, 2*(y+line) - y, LCD_WHITE);
				lcd_putpixel(2*(x+row)-1-18, 2*(y+line) - y, LCD_WHITE);
				lcd_putpixel(2*(x+row)-18, 2*(y+line)+1 - y, LCD_WHITE);
				lcd_putpixel(2*(x+row)-1-18, 2*(y+line)+1 - y, LCD_WHITE);
			}
		}
	}
}
*/

/*
** Usando una fuente 8x16, escribe una cadena a doble tamaño a partir del pixel (x,y) en el color indicado
*/
/*
void lcd_puts_x2( uint16 x, uint16 y, uint8 color, char *s ){
	while(*s) {
		lcd_putchar_x2(x, y, color, *s);
		s++;
		x = x + 8;
	}
}
*/

/*
** Usando una fuente 8x16, escribe texto formateado a doble tamaño a partir del pixel (x,y) en el color indicado
*/
/*
uint32 lcd_printf_x2( uint16 x, uint16 y, uint8 color, const char *fmt, ... ){
	va_list arg_p;
	
	char cadena[256];
	int32 charRetorno;
	
	va_start(arg_p, fmt);
	
	charRetorno = vsprintf(cadena, fmt, arg_p);
	
	va_end(arg_p);
	
	lcd_puts_x2(x, y, color, cadena);
	
	return charRetorno;
}
*/
