#ifndef HUD_H
#define HUD_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "Square.h" 	
#include <stdio.h>

// Defina as constantes para o tamanho da tela
#define X_SCREEN 576*3																																									
#define Y_SCREEN 324*3	

// Declarações das funções para o HUD (Heads-Up Display)
void desenha_time(ALLEGRO_FONT *font, int time_left);

void desenhar_hud(int hp, ALLEGRO_BITMAP *gif_frames);

void desenhar_hud_inimigo(int hp, ALLEGRO_BITMAP *gif_frames);

void atualizar_frame(int *frame_atual, int frame_delay, int *contador, int total_quadros);

void desenharTela1(int *jogo_rodando, ALLEGRO_BITMAP* ken_image, ALLEGRO_BITMAP* barbie_image, ALLEGRO_BITMAP* witch_image, 
                   ALLEGRO_BITMAP* background_image, ALLEGRO_BITMAP* oibarbie, ALLEGRO_BITMAP* oiken, ALLEGRO_BITMAP* barbie_bruxalevouken, 
                   float *tempo_falas_restante, float *ken_x, float *ken_y, int *ken_hit);

void desenharTela2(int *jogo_rodando, ALLEGRO_BITMAP* barbie_image, ALLEGRO_BITMAP* background_image, float *tempo_falas, ALLEGRO_BITMAP* naveBarbie);

void desenharTela3(square* player, ALLEGRO_FONT* font, ALLEGRO_BITMAP* barbie_image, ALLEGRO_BITMAP* background_image, int transicao_em_andamento, 
                   ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_EVENT event, ALLEGRO_BITMAP* pegaBruxa);

void desenharFimBom(ALLEGRO_BITMAP* background_image, ALLEGRO_BITMAP* salvei, ALLEGRO_BITMAP* kenSalvo);

void desenharFimRuim(ALLEGRO_BITMAP* barbie_image, ALLEGRO_BITMAP* finalruim);

#endif // HUD_H
