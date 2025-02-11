#ifndef __SQUARE__ 																																	//Guardas de inclusão
#define __SQUARE__																																	//Guardas de inclusão																															//Quantidade de pixels que um quadrado se move por passo
#include <allegro5/allegro5.h>																																											
#include <allegro5/allegro_font.h>																																										
#include <allegro5/allegro_primitives.h>																																								
#include <allegro5/allegro_image.h> // Bibliotec
#include "Joystick.h"																																//Estrutura e procedimentos relacionados ao controle do quadrado
#include "Pistol.h" 	
																			//Estrutura e procedimentos relacionados ao controle da arma (pistola) no jogo (!)
#define SQUARE_STEP 10	
#define X_SCREEN 576*3																																									
#define Y_SCREEN 324*3	
#define HPJOGADOR 6
																											//Tamanho, em pixels, de um passo do quadrado

typedef struct {																																	//Definição da estrutura de um quadrado
	unsigned char side;																																//Tamanmho da lateral de um quadrado
	unsigned char face;																																//A face principal do quadrado, algo como a sua "frente" (!)
	unsigned short x;																																//Posição X do centro do quadrado
	unsigned short y;	
	unsigned char hp;	
	int frame;
	int vida;
	float disparos; // Tempo entre disparos
    float last_shot_time;
    int laser_ativo;  // Ativo se o jogador tiver o laser
    int disparo_ativo;  // Ativo se o jogador tiver a velocidade de disparo aumentada
    double laser_Termino; // Tempo de término do laser
    double fire_termino; // Tempo de término do aumento de disparo
 	double fr_tiro;																											//Quantidade de vida do quadrado, em unidades (!)
	joystick *control;																																//Elemento de controle do quadrado no jogo
	pistol *gun;																																	//Elemento para realizar disparos no jogo (!)
} square;																																			//Definição do nome da estrutura
void desenha_player(square *player_1, ALLEGRO_BITMAP *frames[], int frame, int facing_left);
square* square_create(unsigned char side, unsigned char face, unsigned short x, unsigned short y, unsigned short max_x, unsigned short max_y);		//Protótipo da função de criação de um quadrado
void square_move(square *element, char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y);								//Protótipo da função de movimentação de um quadrado
void square_shot(square *element);																													//Protótipo da função de disparo de um quadrado (!)
void square_destroy(square *element);																												//Protótipo da função de destruição de um quadrado
void update_position(square *player_1, int frame,ALLEGRO_BITMAP *frames[7]);																																				
void update_bullets(square *player);																																											
unsigned char collision_2D(square *element_first, square *element_second);
unsigned char check_kill(square *killer, square *victim);																																				//Implementação da função que verifica se um projétil acertou um jogador
//unsigned char check_kill_inimigo(inimigo *killer, square *victim);
void desenha_bala(square* players[], int num_players);
unsigned char check_killcollision_2D(square *killer, square *victim);																																				//Implementação da função que verifica se um projétil acertou um jogador

#endif																																				//Guardas de inclusão