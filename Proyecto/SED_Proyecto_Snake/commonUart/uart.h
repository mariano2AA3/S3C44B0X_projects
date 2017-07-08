/*********************************************************************************************
* Fichero:	uart.h
* Autor:	
* Descrip:	cabecera de las funciones de UART
* Version: <P5-ARM-simple>	
*********************************************************************************************/

#ifndef __UART_H__
#define __UART_H__

#ifdef __cplusplus
extern "C" {
#endif

/*--- definicón de constantes ---*/
#define LF_char 0x0A	/* Caracter de salto de línea */
#define CR_char 0x0D    /* Caracter de retorno de carro */

#define CR_LEFT 'L'
#define CR_RIGHT 'R'
#define CR_0 '0'
#define CR_1 '1'
#define CR_2 '2'
#define CR_3 '3'
#define CR_4 '4'
#define CR_5 '5'
#define CR_6 '6'
#define CR_7 '7'
#define CR_8 '8'
#define CR_9 '9'
#define CR_A 'A'
#define CR_B 'B'
#define CR_C 'C'
#define CR_D 'D'
#define CR_E 'E'
#define CR_F 'F'

/*--- prototipos de funciones ---*/
void Uart_Init(int baud);
void Uart_Config(void);
void Uart0_TxEmpty(void);
char Uart0_Getch(void);
void Uart0_SendByte(int data);
void Uart0_SendString(char *pt);
void Uart0_Printf(char *fmt,...);

void Uart1_TxEmpty(void);
char Uart1_Getch(void);
void Uart1_SendByte(int data);
void Uart1_SendString(char *pt);


#ifdef __cplusplus
}
#endif

#endif /* __UART_H__ */
