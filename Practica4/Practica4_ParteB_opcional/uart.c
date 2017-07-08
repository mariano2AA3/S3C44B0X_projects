/*********************************************************************************************
* Fichero:	uart.c
* Autor:	
* Descrip:	funciones de UART
* Version: <P6-ARM-simple>	
*********************************************************************************************/

/*--- ficheros de cabecera ---*/
#include "44b.h"
#include "uart.h"
#include <stdarg.h>
#include <stdio.h>

/*--- implementaci�n de las funciones ---*/
void Uart_Init(int baud) {

    
    /* UART0 */
    rULCON0=0x3;     // Modo normal, no paridad, 1b stop, 8b char
    rUCON0=0x205;    // tx=nivel, rx=flanco, no rx-timeout ni rx-error, normal, int/polling 
    rUBRDIV0=( (int)(MCLK/16./baud + 0.5) -1 ); // formula division de frecuencia
    rUFCON0=0x0;     // Desactivar FIFO
    rUMCON0=0x0;	 // Desactivar control de flujo

    /* UART1 */
    rULCON1=0x3;     // Modo normal, no paridad, 1b stop, 8b char
    rUCON1=0x205;    // tx=nivel, rx=flanco, no rx-timeout ni rx-error, normal, int/polling
    rUBRDIV1=( (int)(MCLK/16./baud + 0.5) -1 ); // formula division de frecuencia
    rUFCON1=0x0;	// Desactivar FIFO
    rUMCON1=0x0;	// Desactivar control de flujo
}

void Uart_Config(void)
{
    // Si no se usan interrupciones, no es necesario hacer nada
}

inline void Uart0_TxEmpty(void) {
    while (!(rUTRSTAT0 & 0x4)); 	     // esperar a que el shifter de TX se vacie
}

inline void Uart1_TxEmpty(void) {
    while (!(rUTRSTAT1 & 0x4)); 	     // esperar a que el shifter de TX se vacie
}


char Uart0_Getch(void)
{
    while (!(rUTRSTAT0 & 0x1));        // esperar a que el buffer contenga datos
	return RdURXH0();		   		   // devolver el caracter
}

char Uart1_Getch(void) {
    while (!(rUTRSTAT1 & 0x1));        // esperar a que el buffer contenga datos
	return RdURXH1();		   		   // devolver el caracter
}

void Uart0_SendByte(int data) {
    char localBuf[2] = {'\0','\0'};

    if(data == '\n')		
	{
	   while (!(rUTRSTAT0 & 0x2));     // esperar a que THR se vacie
	   WrUTXH0('\r');			       // escribir retorno de carro (utilizar macro)
	}
	while (!(rUTRSTAT0 & 0x2)); 	   // esperar a que THR se vacie
	WrUTXH0(data);				       // escribir data (utilizar macro)
}

void Uart1_SendByte(int data) {
    char localBuf[2] = {'\0','\0'};

    if(data == '\n') {
	   while (!(rUTRSTAT1 & 0x2));     // esperar a que THR se vacie
	   WrUTXH1('\r');			       // escribir retorno de carro (utilizar macro)
	}
	while (!(rUTRSTAT1 & 0x2)); 	   // esperar a que THR se vacie
	WrUTXH1(data);				       // escribir data (utilizar macro)
}

void Uart0_SendString(char *pt) {
    while (*pt)						    // mandar byte a byte hasta completar string
	Uart0_SendByte(*pt++);
}

void Uart1_SendString(char *pt) {
    while (*pt)						    // mandar byte a byte hasta completar string
	Uart1_SendByte(*pt++);
}

void Uart0_Printf(char *fmt,...) {
    va_list ap;
    char string[256];

    va_start(ap,fmt);
    vsprintf(string,fmt,ap);
    Uart0_SendString(string);
    va_end(ap);
}



