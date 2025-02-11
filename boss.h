#ifndef __BOSS__ 																																	
#define __BOSS__	
#include "Pistol.h" 
#include "Square.h" 	
#include "Bullet.h" 

#include <stdio.h>																																														
#include <time.h>
#include <allegro5/allegro5.h>																																											
#include <allegro5/allegro_font.h>																																										
#include <allegro5/allegro_primitives.h>																																								
#include <allegro5/allegro_image.h> // Biblioteca 

#define X_SCREEN 576*3																																									
#define Y_SCREEN 324*3	
#define BOSS1 1
#define BOSS2 2
#define HP_BOSS1 7
#define HP_BOSS2 10

/*
4. Resistência e Vida
O chefe deve ter um número de pontos de vida significativamente maior (ex: 100 a 200, enquanto inimigos normais têm 10-20).
Ao atingir certos níveis de vida (ex: 75%, 50%, 25%), a dificuldade aumenta:
Mais projéteis lançados.
A velocidade do chefe aumenta.
Novo padrão de ataques.x: zig-zag, avançar para o jogador).


3. Ataques Únicos
Cada chefe deve ter dois ataques únicos, sendo um baseado em projéteis.

Ataque 1 (Exemplo: Tiros direcionados ao jogador): boss 2
O chefe lança projéteis na direção da posição atual do jogador.
Ataque 2 (Exemplo: Área de dano ou rajadas múltiplas):
Pode lançar múltiplos projéteis ou criar obstáculos que permanecem na tela.
*/

typedef struct {																																	
	unsigned char side;																																
	unsigned char face;																																
	unsigned short x;																																
	unsigned short y;	
	unsigned char hp;	
	//int frame;
	int vida;
	int ID;																	
	pistol *gun1;	
	pistol *gun2;	
    int velocidade;
	int velocidade_vertical;     // Velocidade vertical (zig-zag)
    int indo_para_metade;  
    int ativo;	
	int duplicado;																														
} Boss;

//int colisao_boss(Boss *a, Boss *b);
Boss* iniciaBoss1();
Boss* iniciaBoss2();
Boss *iniciaBoss2_2();

void desenhabalaBoss22(Boss * boss,ALLEGRO_BITMAP *tiro2);


void DisparaTiroBoss(Boss *boss, square *victim,pistol *gun);
void atualizaBoss(Boss *boss, square *victim);
//void desenhaBoss(Boss* boss, int tamanho, square *player);
void boss_shot(Boss* boss, square *player);																														
void update_bulletsBoss(Boss *player,pistol *gun);
void desenhabalaBoss(Boss* boss, ALLEGRO_BITMAP *tiro1 ,ALLEGRO_BITMAP *tiro2);
unsigned char check_kill_boss(Boss* boss, square *victim,pistol *gun);																																				
//void libera_boss(Boss* boss) ;
void liberaBoss(Boss *element);																													
unsigned char check_kill_jogadorBoss(square *victim,Boss *boss);																																					
unsigned char colisaoBoss(Boss *boss, square *jogador);
unsigned char colisaoJogadorBoss( square *jogador,Boss *boss);
unsigned char check_colisaoBoss(square *jogador,Boss *boss);																																					
void remove_boss(Boss *boss);
//unsigned char colisaoInimicoBoss( Boss *jogador,Boss *boss, int tamanho);
//void updateBoss(Boss *boss1,Boss *boss2, int tamanho);
void desenha_boss(Boss *boss1,Boss *boss2, ALLEGRO_BITMAP *framesiNI1[],ALLEGRO_BITMAP *framesiNI2[], int frames,int frames2, int facing_left,float scale);

//void update_enemy_positions(Boss *boss, int tamanho, int screen_width, int screen_height);
void move_boss(Boss *element, char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y)	;								
void update_bulletsSegue(Boss *boss, pistol *gun, square *player);
bullet *pistol_shot_segue(unsigned short x, unsigned short y, square *player, pistol *gun);


void desenha_boss2(Boss *boss1, Boss *boss2, ALLEGRO_BITMAP *framesiNI1[], ALLEGRO_BITMAP *framesiNI2[], int frames, int frames2, int facing_left, float scale);

#endif	