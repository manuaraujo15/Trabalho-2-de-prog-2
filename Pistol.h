#ifndef __PISTOL__ 																												
#define __PISTOL__																												

#include "Bullet.h"

#define PISTOL_COOLDOWN 20																									

typedef struct {																												//Definição da estrutura de uma pistola 
	unsigned char timer;																										//Relógio de intervalo entre tiros
	bullet *shots;																												//Lista de balas ativas no campo disparadas pelas arma	
} pistol;																														//Definição do nome da estrutura 

pistol* pistol_create();																										
bullet* pistol_shot(unsigned short x, unsigned short y, unsigned char trajectory, pistol *gun);									
void pistol_destroy(pistol *element);																							


#endif																															