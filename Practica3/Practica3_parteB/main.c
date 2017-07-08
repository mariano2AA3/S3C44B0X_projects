#include "s3cev40.h"
#include "common_types.h"
#include "at24c04.h"
#include "44b.h"

extern void sys_init();
extern void iic_init();
extern void D8Led_symbol(int value);


int estado;
uint16 direccion;
uint8 dato;


void Main( void )
{

	estado = 0;
	direccion = 0;
	dato = 0;
    uint8 buffer[AT24C04_DEPTH];
    uint16 i;
    
    sys_init();

    //Inicializamos los botones
    rPCONG = rPCONG & 0xffff0fff;
    rPUPG = 0;

    Eint4567_init();

    keyboard_init();
    iic_init();

    D8Led_init();
    D8Led_symbol(0);

    while( 1 ) {}
}
