#ifndef __BULLET__ 																																
#define __BULLET__																																

#define BULLET_MOVE 20

#include <math.h>
#include <stdlib.h>

typedef struct {																																//Definição da estrutura de um pŕojétil
	unsigned short x;																															//Local, no eixo x, onde se localiza a bala 
	unsigned short y;																															//Local, no eixo y, onde se localiza a bala 
	unsigned char trajectory;																													//Trajetória da bala
	struct bullet *next; 																														//Próxima bala, se houver, formando uma lista encadeada 
} bullet;																																		//Definição do nome da estrutura 

bullet* bullet_create(unsigned short x, unsigned short y, unsigned char trajectory, bullet *next);												
void bullet_move(bullet *elements);																													
void bullet_destroy(bullet *element);																											

#endif																																			