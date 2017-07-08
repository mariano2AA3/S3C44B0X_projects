
// VARIABLES

#define FILAS       30
#define COLUMNAS 	40
#define BUFFER_ACT	10
#define CELDA 		8

#define VACIO       0
#define MURO 		1
#define FRUTA   	2
#define CABEZA_J1    3
#define CUERPO_J1    4
#define CABEZA_J2    5
#define CUERPO_J2    6

#define DIRECCION_ARRIBA	'u'
#define DIRECCION_ABAJO  	'd'
#define DIRECCION_DER  		'r'
#define DIRECCION_IZQ 		'l'


int tablero[FILAS][COLUMNAS];

typedef struct {
	int x;
	int y;
} PosJug;

PosJug snake_jug1[FILAS*COLUMNAS];
PosJug snake_jug2[FILAS*COLUMNAS];
int niveljug1;
int niveljug2;
int jug1X, jug1Y;
int jug2X, jug2Y;
char jug1_dir;
char jug2_dir;
int jug1Vivo;		// 1 -> vivo , 0 -> muerto
int jug2Vivo;		// 1 -> vivo , 0 -> muerto
int numAC;
int frutaX, frutaY;

typedef struct {
	int x;
	int y;
	int nuevo_valor;
} ActCelda;

ActCelda ac[BUFFER_ACT];


// FUNCIONES PUBLICAS
void iniciar_snake(char id);
void pintar();
void repintar();
void actualizar();
void enviar_direccion(void);
void recibir_direccion(void);
void enviar_perdido(void);

// FUNCIONES PRIVADAS
void crear_tablero();
void crear_jugadores_tipoA();
void crear_jugadores_tipoB();
void actualizar_pos_tablero(int x, int y, int nuevo_valor);
void generarFruta(void);
