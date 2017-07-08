/*-------------------------------------------------------------------
**
**  Fichero:
**    lcd.h  10/5/2013
**
**    (c) J.M. Mendias
**    Programación de Sistemas y Dispositivos
**    Facultad de Informática. Universidad Complutense de Madrid
**
**  Propósito:
**    Contiene las definiciones de los prototipos de funciones
**    para el acceso al lcd de la placa de prototipado S3CEV40  
**
**  Notas de diseño:
**
**-----------------------------------------------------------------*/

#ifndef __LCD_H__
#define __LCD_H__

#include "common_types.h"
#include "44b.h"
//#include "s3cev40.h"

#define LCD_WIDTH   (320)
#define LCD_HEIGHT  (240)

#define LCD_BUFFER_SIZE    (LCD_WIDTH*LCD_HEIGHT/2) // en bytes con 2 pixels/byte

#define LCD_BLACK       (0xf)
#define LCD_WHITE       (0x0)
#define LCD_LIGHTGRAY   (0x5)
#define LCD_DARKGRAY    (0xa)
    
#define LCD_OFF     (1)
#define LCD_ON      (0)

/*
** Configura el controlador de lcd según los siguientes parámetros 
**   Resolución: 320x240
**   Modo de barrido: 4 bit single scan
**   Modo del lcd: 16 niveles de gris
**   Paletas de color: no
**   Frecuencia de refresco: 120 Hz
**   Self-refresh: desactivado
**   Polaridad de señales de sincronismo: normal
**   Conmutación de VM: en cada frame
**   Anchura del blanking horizontal: mínima
**   Retardo y anchura de pulso de sincronismo horizontal: mínimos
**   Valores de dithering: por defecto
** Inicializa el estado del lcd y lo apaga
*/
void lcd_init( void );

/* 
** Enciende el lcd
*/
void lcd_on( void );

/* 
** Apaga el lcd
*/
void lcd_off( void );

/*
** Devuelve el estado (LCD_ON/LCD_OFF) del lcd
*/
uint8 lcd_status( void );

/*
** Borra el lcd
*/
void lcd_clear( void );

/*
** Pone el pixel (x,y) en el color indicado
*/
void lcd_putpixel( uint16 x, uint16 y, uint8 color);

/*
** Devuelve el color al que está el pixel (x,y)
*/
uint8 lcd_getpixel( uint16 x, uint16 y );


/*
** Dibuja un rectángulo cuya esquina superior izquierda está en el pixel (xleft,yup) y cuya esquina inferior está en el píxel (xright, ydown) del color y grosor indicados
*/
void lcd_draw_box( uint16 xleft, uint16 yup, uint16 xright, uint16 ydown, uint8 color, uint16 width );
void lcd_pintar_celda(uint16 x, uint16 y, uint8 tam_celda, uint8 color);
void lcd_pintar_cabeza_serpiente_arriba(uint16 x, uint16 y);
void lcd_pintar_cabeza_serpiente_abajo(uint16 x, uint16 y);
void lcd_pintar_cabeza_serpiente_izquierda(uint16 x, uint16 y);
void lcd_pintar_cabeza_serpiente_derecha(uint16 x, uint16 y);
void lcd_pintar_cuerpo_serpiente1(uint16 x, uint16 y, uint8 tam_celda);
void lcd_pintar_cuerpo_serpiente2(uint16 x, uint16 y);
void lcd_pintar_naranja(uint16 x, uint16 y);
void lcd_pintar_platano(uint16 x, uint16 y);
void lcd_pintar_cereza(uint16 x, uint16 y);
void lcd_pintar_muro(uint16 x, uint16 y, uint8 tam_celda);
void lcd_draw_esperar_otro_jugador(void);

#endif 
