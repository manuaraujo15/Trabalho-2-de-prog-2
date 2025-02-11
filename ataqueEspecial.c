#include <allegro5/allegro5.h>																																											
#include <allegro5/allegro_font.h>																																										
#include <allegro5/allegro_primitives.h>																																								
#include <allegro5/allegro_image.h> // Bibliotec
#include <stdlib.h>
#include <stdio.h>																																														
#include "Square.h"
#include "ataqueEspecial.h"

#define X_SCREEN 576*3																																									
#define Y_SCREEN 324*3	
void inicia_ataque_especial(square* player, AtaqueEsp* ataqueEsp) {      //  tipo_ataque_especial = rand() % 2 + 1; // 1 ou 2 para escolher entre laser ou aumento de disparo

    if(!ataqueEsp[1].ativo && !ataqueEsp[2].ativo){

    // ataqueEsp do laser
    ataqueEsp[1].x = (rand() % (X_SCREEN - 40))*0.5;
    ataqueEsp[1].y = rand() % (Y_SCREEN - 200);
    ataqueEsp[1].type = 1;  // Laser
    ataqueEsp[1].ativo = 1; 
    // ataqueEspde aumento de disparo
    ataqueEsp[2].x = rand() % (X_SCREEN - 40);
    ataqueEsp[2].y = rand() % (Y_SCREEN - 200);
    ataqueEsp[2].type = 2;  // Aumento de disparo
    ataqueEsp[2].ativo = 1; 
        }
}

void atualizaAtaque(AtaqueEsp* ataqueEsp, square* player) {
    for (int i = 1; i <= 2; i++) { 
        if(ataqueEsp[i].ativo) {
            if (ataqueEsp[i].x < 0) {
                ataqueEsp[i].ativo = 0;  // Desativa o ataqueEsp quando sai da tela
            }
            
            // Verifica se o ataqueEsp é de laser ou aumento de disparo
            if (ataqueEsp[i].type == 1 && player->laser_ativo) { 
                // Atualiza o tempo de ativação do laser
                if (al_get_time() > player->laser_Termino) {
                    player->laser_ativo = false;  // Desativa o laser após o tempo
                }
            } 
            else if (ataqueEsp[i].type == 2 && player->disparo_ativo) { 
                // Atualiza o tempo de aumento de disparo
                if (al_get_time() > player->fire_termino) {
                    player->disparo_ativo = false;  // Desativa o aumento de disparo
                }
            }
        }
    }
}
// Função para atualizar o laser
void update_laser(double time, square* player) {
    if (player->laser_ativo && time > player->laser_Termino) {
        player->laser_ativo = false; // Desativa o laser após 5 segundos
    }
}

// Função para atualizar a velocidade de disparo
void update_tiro(double time,square* player) {
    if (player->disparo_ativo && time > player->fire_termino) {
        player->disparo_ativo = false;  // Desativa o aumento de velocidade de disparo
         // Velocidade normal de disparo
    }
}

// Função para disparar laser
void shot_laser(square* player, ALLEGRO_BITMAP *tiros) {
    // Verifica se o laser está ativo e se o jogador está disparando
    if (player->control->fire && player->laser_ativo) {
        square_shot(player); // Dispara o laser
    }

    if (player->laser_ativo) {
        bullet *prev = NULL;
        bullet *current = player->gun->shots;

        while (current != NULL) {
            // Verifique se o tiro saiu da tela
            if (current->x < 0 || current->x > X_SCREEN ) {
                // Se for o primeiro tiro da lista, atualize diretamente a cabeça da lista
                if (prev){	
                    prev->next = current->next;  // Desconecta o tiro da lista
                    bullet_destroy(current);																																										
                    // Avançar para o próximo tiro
                    current = (bullet*) prev->next;  // Libera a memória do tiro removido
            } else {
                // Caso contrário, 
                player->gun->shots = (bullet*) current->next;																																					
                bullet_destroy(current);																																										
                current = player->gun->shots;		

                }
                }else {																																															
                    al_draw_scaled_bitmap(tiros, 0, 0, al_get_bitmap_width(tiros), al_get_bitmap_height(tiros),
                                      current->x - 55, current->y - 5, al_get_bitmap_width(tiros) * 0.5,
                                      al_get_bitmap_height(tiros) * 0.5, 0);

                // Se você quiser desenhar dois lasers, pode duplicar a linha de desenho aqui
                    al_draw_scaled_bitmap(tiros, 0, 0, al_get_bitmap_width(tiros), al_get_bitmap_height(tiros),
                                      current->x - 55, current->y - 50, al_get_bitmap_width(tiros) * 0.5,
                                      al_get_bitmap_height(tiros) * 0.5, 0);
                // Avança na lista de tiros
                    prev = current;
                    current = (bullet*) current->next;  // Avança para o próximo tiro
            }
        }
    }
}


void shot_tiro_rapido(double current_time,bullet* player1, square * player) {

    if ( player->disparo_ativo && !player->laser_ativo ) {	
        	
       	if (player->control->fire){																																											//Verifica se o primeiro jogador está atirando (!)
			if (!player->gun->timer){																																											//Verifica se a arma do primeiro jogador não está em cooldown (!)
				square_shot(player); 																																														//Se não estiver, faz um disparo (!)
				player->gun->timer = 5;																																							//Inicia o cooldown da arma (!)
			} 
		}
	}
} 

// Função para verificar colisão com ataqueEsps
void check_collisao_ataque_especial(square* player, AtaqueEsp* ataqueEsp) {

    for (int i = 1; i <=2; i++) {
        // Verifica se o jogador colidiu com o ataqueEsp
        if (player->x >= ataqueEsp[i].x && player->x <= ataqueEsp[i].x + 75 && player->y >= ataqueEsp[i].y && player->y <= ataqueEsp[i].y + 75 && !player->laser_ativo && !player->disparo_ativo) {
            if (ataqueEsp[i].type == 1) {  // Power-up de Laser
                player->laser_ativo = true;
                ataqueEsp[i].ativo = 0;
                player->laser_Termino = al_get_time() + LASER_DURACAO;
            } else if (ataqueEsp[i].type == 2) {  // Power-up de Aumento de Disparo
                player->disparo_ativo = true;
                ataqueEsp[i].ativo = 0;

                player->fire_termino = al_get_time() + FIRE_DURACAO;
                //player->fr_tiro = 0.1; // Aumenta a velocidade de disparo
            }
            ataqueEsp[i].x = -100;  // Remove o ataqueEsp do mapa após ser coletado
            ataqueEsp[i].y = -100;  // Remove o ataqueEsp do mapa após ser coletadoe
        }
    }
}


void desenhaAtaque(square *player, AtaqueEsp ataqueEsp[2],  ALLEGRO_BITMAP *ataque1_bitmap , ALLEGRO_BITMAP *ataque2_bitmap ) {
    float escala_x = 1.2f;  // Fator de escala horizontal
    float escala_y = 1.2f;
    // Desenhar os ataques no lugar dos ataq, se o ataq foi coletado ou usado
    for (int i = 1; i <= 2; i++) {
        if (ataqueEsp[i].x >= 0 && ataqueEsp[i].x < X_SCREEN && ataqueEsp[i].y >= 0 && ataqueEsp[i].y < Y_SCREEN) {
            if (ataqueEsp[i].type == 1) {  // Power-up de laser foi coletado
                // Desenhar o ataque laser no lugar ataq
                if (ataque1_bitmap) {  // Verifique se o bitmap não é NULL
                     // Fator de escala vertical

                    // Desenha a imagem com a escala aplicada
                    al_draw_scaled_bitmap(ataque1_bitmap, 0, 0, al_get_bitmap_width(ataque1_bitmap), al_get_bitmap_height(ataque1_bitmap), 
                    ataqueEsp[i].x, ataqueEsp[i].y, al_get_bitmap_width(ataque1_bitmap) * escala_x, al_get_bitmap_height(ataque1_bitmap) * escala_y, 0);
                }
            } else if (ataqueEsp[i].type == 2) {  // ataq de aumento de disparo foi coletado
                // Desenhar o ataque de aumento de disparo no lugar do ataq
                if (ataque2_bitmap) {  // Verifique se o bitmap não é NULL
                        al_draw_scaled_bitmap(ataque2_bitmap, 0, 0, al_get_bitmap_width(ataque2_bitmap), al_get_bitmap_height(ataque2_bitmap), ataqueEsp[i].x, ataqueEsp[i].y, 
                        al_get_bitmap_width(ataque2_bitmap) * escala_x, al_get_bitmap_height(ataque2_bitmap) * escala_y, 0);
                }
            }
        }
    }

}
