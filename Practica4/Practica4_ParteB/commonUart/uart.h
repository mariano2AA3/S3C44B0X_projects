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
