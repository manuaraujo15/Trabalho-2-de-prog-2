#ifndef __INIMIGO__ 																																	//Guardas de inclusão
#define __INIMIGO__	
#include "Pistol.h" 
#include "Square.h" 	

#include <stdio.h>																																														
#include <time.h>
#include <allegro5/allegro5.h>																																											
#include <allegro5/allegro_font.h>																																										
#include <allegro5/allegro_primitives.h>																																								
#include <allegro5/allegro_image.h> // Biblioteca 

#define X_SCREEN 576*3																																									
#define Y_SCREEN 324*3	
#define INIMIGO1 1
#define INIMIGO2 2
#define INIMIGO3 3
#define INIMIGO4 4
#define ENEMY_SIZE 20
/*
INIMIGO1 == movimentacao na horizontal e atira hp == 1

INIMIGO2 == imovel hp 5 atira?

INIMIGO3 ==  movimentacao na vertical, hp == 1

INIMIGO4 ==movimentacao na horizontal, mas sao tres INIMIGOS SEGUIDOS e fica invisivel hp == 3


*/
typedef struct {																																	//Definição da estrutura de um quadrado
	unsigned char side;																																//Tamanmho da lateral de um quadrado
	unsigned char face;																																//A face principal do quadrado, algo como a sua "frente" (!)
	unsigned short x;																																//Posição X do centro do quadrado
	unsigned short y;	
	unsigned char hp;	
	//int frame;
	int vida;
	int ID;																	//Quantidade de vida do quadrado, em unidades (!)
	pistol *gun;	
    int velocidade;
    int ativo;																																//Elemento para realizar disparos no jogo (!)
} Inimigo;
Inimigo **iniciaInimigo1(int tamanho);
void DisparaTiro(Inimigo **inimigo, int tamanho, square *victim);
void atualizaInimigo(Inimigo **inimigo, int tamanho, square *victim);
void inimigo_shot(Inimigo** inimigo, int tamanho);																														//Implementação da função "square_shot" (!)
void update_bulletsInimigo(Inimigo **inimigo, int tamanho);																																											
void desenhabala(Inimigo** inimigo, int tamanho,  ALLEGRO_BITMAP *tiro1, ALLEGRO_BITMAP *tiro2);
unsigned char check_kill_inimigo(Inimigo** inimigo, square *victim, int tamanho);																																				//Implementação da função que verifica se um projétil acertou um jogador
//void libera_inimigos(Inimigo* inimigos) ;
void liberaInimigos(Inimigo **element,int tamanho);																													//Implementação da função "square_destroy"
unsigned char check_kill_jogador(square *victim,Inimigo **inimigo, int tamanho);																																					//Implementação da função que verifica se um projétil acertou um jogador
unsigned char colisaoInimigo(Inimigo *inimigo, square *jogador, int tamanho);
unsigned char colisaoJogador( square *jogador,Inimigo *inimigo, int tamanho);
unsigned char check_colisao(square *jogador,Inimigo **inimigo, int tamanho);																																					//Implementação da função que verifica se um projétil acertou um jogador
void DisparaAtivo(Inimigo *inimigo);
unsigned char colisaoInimicoInimigo( Inimigo **jogador,Inimigo **inimigo, int tamanho);
void desenha_inimigo(square *player_1,Inimigo **inimigo1,Inimigo **inimigo2, ALLEGRO_BITMAP *frames1[], ALLEGRO_BITMAP *frames2[], ALLEGRO_BITMAP *frames3[], ALLEGRO_BITMAP *frames4[],int frame, int tamanho, int facing_left) ;
Inimigo **iniciaInimigo2(int tamanho);
Inimigo **iniciaInimigo3(int tamanho);
Inimigo **iniciaInimigo4(int tamanho);

#endif																																				//Guardas de inclusão