#ifndef __ATAQUEESPECIAL__ 																																
#define __ATAQUEESPECIAL__																																
#define LASER_DURACAO 5.0 // 5 segundos de laser
#define FIRE_DURACAO 5.0 // 5 segundos para aumento de disparo
#include "Pistol.h" 	
#include <allegro5/allegro5.h>																																											
#include <allegro5/allegro_font.h>																																										
#include <allegro5/allegro_primitives.h>																																								
#include <allegro5/allegro_image.h> // Biblioteca para carregar imagens
#include "Square.h"

// Estrutura para os AtaqueEsp
typedef struct {
    float x, y;
    int ativo;  // Indica se o ataque especial está ativo

    int type; // 1 para laser, 2 para aumento de disparo
} AtaqueEsp;

void check_collisao_ataque_especial(square* player, AtaqueEsp* ataqueEsp) ;
void shot_laser(square* player, ALLEGRO_BITMAP *tiros);
void update_tiro(double time,square* player);
void update_laser(double time, square* player) ;
void inicia_ataque_especial(square* player, AtaqueEsp* ataqueEsp);
void shot_tiro_rapido(double current_time,bullet* player1, square * player);
void desenhaAtaque(square *player, AtaqueEsp ataqueEsp[2],  ALLEGRO_BITMAP *ataque1_bitmap , ALLEGRO_BITMAP *ataque2_bitmap );

void atualizaAtaque(AtaqueEsp* ataqueEsp, square* player);

#endif