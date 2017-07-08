#include "44b.h"
#include "iic.h"

extern uint32 mclk;			   // Frecuencia actual del reloj (Hz)

extern void DelayMs(int ms_time);

void iic_init( void ) {
	// Enable IIC & GPIO & BDMA blocks (si no se activa BDMA, el controlador IIC no es accesible)
	rCLKCON |= (1<<13) | (1<<10) | (1<<7);
	
	// PF[1] = IICSDA, PF[0] = IICSCL
	rPCONF = 0xA; // 1010 --> últimos 4 bits del registro.
	
	// Pull-up enable
	rPUPF &= ~(1<<1) & ~(1<<0);
	
    //Configurar la dirección del slave
	// IICADD [7:0] -> slave address = [7-1], Not Mapped = [0]
	rIICADD = S3C44B0X_SLAVE_ADDRESS<<1;

    //Generación ACK habilitada, interrupciones habilitadas
    rIICCON = rIICCON | ((mclk / 4000000 - 1) & 0xf); 	//Valor de preescalado, PREESCALER = mclk/16/250000 -1
    rIICCON = rIICCON | (1<<7) | (1<<5); //Habilitado ACK e interrupciones

    // Activa Tx/Rx
    rIICSTAT = (1<<4); // (Se recomienda NO realizar operaciones lógica sobre este registro)
}

void iic_putByte_start( uint8 byte ) { // OK
	// Escribe el dato
	rIICDS = byte;

	// Máster Tx, start condition, Tx/Rx habilitada
	rIICSTAT = 0xF0;

	// Comienza la transmisión (borrando pending bit del IICCON)
	rIICCON &= ~(1<<4);

    // Espera la recepción de ACK
	while((rIICCON & (1<<4)) == 0x0){}
}

void iic_putByte( uint8 byte ) {
    // Escribe el dato
	rIICDS = byte;

	// Comienza la transmisión del dato (borrando pending bit del IICCON)
	rIICCON &= ~(1<<4);

    // Espera la recepción de ACK
	while((rIICCON & (1<<4)) == 0x0){}
};

void iic_putByte_stop( uint8 byte ) {
    // Escribe el dato
	rIICDS = byte;

	// Comienza la trasmisión del dato (borrando pending bit del IICCON)
	rIICCON &= ~(1<<4);

    // Espera la recepción de ACK
	while((rIICCON & (1<<4)) == 0x0){}
    
    // Máster Tx, stop condition, Tx/Rx habilitada
	rIICSTAT = 0xD0;

    // Comienza la trasmisión de STOP (borrando pending bit del IICCON)
	rIICCON &= ~(1<<4);

    // Espera a que la stop condition tenga efecto (5 ms para la at24c04)
	DelayMs(5);

}

void iic_getByte_start( uint8 byte ) {
	// Escribe el dato
	rIICDS = byte;

    // Máster Rx, start condition, Tx/Rx habilitada
	rIICSTAT = 0xB0;

    // Comienza la transmisión (borrando pending bit del IICCON)
	rIICCON &= ~(1<<4);

    // Espera la rececpión de ACK
	while((rIICCON & (1<<4)) == 0x0){}
}

uint8 iic_getByte( void ) {
    // Reanuda la recepción (borrando pending bit del IICCON)
	rIICCON &= ~(1<<4);

	// Espera la recepción del dato
	while((rIICCON & (1<<4)) == 0x0){}

    return rIICDS;// Lee el dato
}

uint8 iic_getByte_stop( int8 ack ) {
	uint8 byte;

    rIICCON = (rIICCON & ~(1 << 7)) | (ack << 7); // Habilita/deshabilita la generación de ACK

    // Reanuda la recepción (borrando pending bit del IICCON)
    rIICCON &= ~(1<<4);
	
	// Espera la recepción del dato
    while((rIICCON & (1<<4)) == 0x0){}
	
    byte = rIICDS;	// Lee el dato

   	// Máster Rx, stop condition, Tx/Rx habilitada
    rIICSTAT = 0x90;

   	// Comienza la trasmisión de STOP (borrando pending bit del IICCON)
    rIICCON &= ~(1<<4);

   	// Espera a que la stop condition tenga efecto (5 ms para la at24c04)
    DelayMs(5);

	rIICCON |= (1<<7); // Habilita la generación de ACK
   	return byte;
}
