#include <stdlib.h>
#include "Square.h"

square* square_create(unsigned char side, unsigned char face, unsigned short x, unsigned short y, unsigned short max_x, unsigned short max_y){			

	if ((x - side/2 < 0) || (x + side/2 > max_x) || (y - side/2 < 0) || (y + side/2 > max_y)) ;												
	if (face > 3) ;																															

	square *new_square = (square*) malloc(sizeof(square));																								
	if (!new_square) return NULL;																																											
	new_square->side = side;																															
	new_square->face = face;																															
	new_square->x = x;																																	
	new_square->y = y;	
	new_square->hp = HPJOGADOR;		
	new_square->fr_tiro = BULLET_MOVE;																											
	new_square->disparo_ativo = false; 
	new_square->laser_ativo = false;
	new_square->disparos = 0;
	new_square->fire_termino = 0;
	new_square->last_shot_time = 0	;
	new_square->laser_Termino = 0;
	new_square->frame = 0;
	new_square->control = joystick_create();																											
	new_square->gun = pistol_create();																													
	return new_square;																																	
}


void square_move(square *element, char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y){									

	if (!trajectory){ if ((element->x - steps*SQUARE_STEP) - element->side/2 >= 0) element->x = element->x - steps*SQUARE_STEP;} 						
	else if (trajectory == 1){ if ((element->x + steps*SQUARE_STEP) + element->side/2 <= max_x) element->x = element->x + steps*SQUARE_STEP;}			
	else if (trajectory == 2){ if ((element->y - steps*SQUARE_STEP) - element->side/2 >= 0) element->y = element->y - steps*SQUARE_STEP;}				
	else if (trajectory == 3){ if ((element->y + steps*SQUARE_STEP) + element->side/2 <= max_y) element->y = element->y + steps*SQUARE_STEP;}			
}

void square_shot(square *element){																														
	bullet *shot;

	if (!element->face) shot = pistol_shot(element->x - element->side/2, element->y, element->face, element->gun);										
	else if (element->face == 1) shot = pistol_shot(element->x + element->side/2, element->y, element->face, element->gun);								
	if (shot) element->gun->shots = shot;
}
void desenha_player(square *player_1, ALLEGRO_BITMAP *frames[], int frame, int facing_left) {
    int flags = facing_left ? ALLEGRO_FLIP_HORIZONTAL : 0;
    al_draw_bitmap(frames[frame], player_1->x - al_get_bitmap_width(frames[frame]) / 2,
    player_1->y - al_get_bitmap_height(frames[frame]) / 2, flags);
}
void square_destroy(square *element){																													
	
	pistol_destroy(element->gun);																														
	joystick_destroy(element->control);																													
	free(element);																																		
}
void update_bullets(square *player){																																											
	bullet *previous = NULL;																																												
	for (bullet *index = player->gun->shots; index != NULL;){																																				
		if (!index->trajectory) index->x -= BULLET_MOVE;																																					
		else if (index->trajectory == 1) index->x += BULLET_MOVE;																																			
		
		if ((index->x < 0) || (index->x > X_SCREEN)){																																						
			if (previous){																																													
				previous->next = index->next;																																								
				bullet_destroy(index);																																										
				index = (bullet*) previous->next;																																							
			}
			else {																																															
				player->gun->shots = (bullet*) index->next;																																					
				bullet_destroy(index);																																										
				index = player->gun->shots;																																									
			}
		}
		else{																																																
			previous = index;																																												
			index = (bullet*) index->next;																																									
		}
	}
}

unsigned char collision_2D(square *element_first, square *element_second){

	if ((((element_first->y+element_first->side/2 >= element_second->y-element_second->side/2) && (element_second->y-element_second->side/2 >= element_first->y-element_first->side/2)) || 	//						
		((element_second->y+element_second->side/2 >= element_first->y-element_first->side/2) && (element_first->y-element_first->side/2 >= element_second->y-element_second->side/2))) && 	//			
		(((element_first->x+element_first->side/2 >= element_second->x-element_second->side/2) && (element_second->x-element_second->side/2 >= element_first->x-element_first->side/2)) || 	//			
		((element_second->x+element_second->side/2 >= element_first->x-element_first->side/2) && (element_first->x-element_first->side/2 >= element_second->x-element_second->side/2)))) return 1;		
	else return 0;
}

void update_position(square *player_1, int frame,ALLEGRO_BITMAP *frames[7]){																																					

	if (player_1->control->left){	
	
		square_move(player_1, 1, 0, X_SCREEN, Y_SCREEN);																																					
		
		player_1->face = 0;																										
	}else player_1->face = 1;

	if (player_1->control->right){
		square_move(player_1, 1, 1, X_SCREEN, Y_SCREEN);																																					//Move o quadrado do primeiro jogador para a direta
		
		player_1->face = 1;																										//Se o movimento causou uma colisão entre quadrados, desfaça o mesmo
	}
	if (player_1->control->up) {																																											//Se o botão de movimentação para cima do controle do primeiro jogador está ativado...
		square_move(player_1, 1, 2, X_SCREEN, Y_SCREEN);																																					//Move o quadrado do primeiro jogador para cima
	}
	if (player_1->control->down){																																											//Se o botão de movimentação para baixo do controle do primeiro jogador está ativado...
		square_move(player_1, 1, 3, X_SCREEN, Y_SCREEN);																																					//Move o quadrado do primeiro jogador para a baixo
																												//Se o movimento causou uma colisão entre quadrados, desfaça o mesmo
	}

	
		if(player_1->control->fire)																																									//Verifica se o primeiro jogador está atirando (!)
			if (!player_1->gun->timer){																																											//Verifica se a arma do primeiro jogador não está em cooldown (!)
				square_shot(player_1); 																																											//Se não estiver, faz um disparo (!)
				player_1->gun->timer = PISTOL_COOLDOWN;																																							//Inicia o cooldown da arma (!)
			} 
	
	update_bullets(player_1);																																												//Atualiza os disparos do primeiro jogador (!)
}

void desenha_bala(square* players[], int num_players){
    for (int i = 0; i < num_players; i++) {
        for (bullet* index = players[i]->gun->shots; index != NULL;) {
            // Desenha o tiro de cada jogador
            al_draw_filled_circle(index->x, index->y, 2, al_map_rgb(0, 0, 255));
        }	if ( players[i]->gun->timer) players[i]->gun->timer--; 	

    }
}
unsigned char check_kill(square *killer, square *victim){																																					//Implementação da função que verifica se um projétil acertou um jogador

	bullet *previous = NULL;
	for (bullet *index = killer->gun->shots; index != NULL; index = (bullet*) index->next){	
																														//Para todos os projéteis do atirador
		if ((index->x >= victim->x - victim->side) && (index->x <= victim->x + victim->side) && //																										//Verique se houve colisão com a vítima no eixo X
		   (index->y >= victim->y - victim->side) && (index->y <= victim->y + victim->side) || collision_2D(victim,killer)){																											//Verifique se houve colisão com a vítima no eixo Y
			victim->hp--;																																													//Reduz o HP da vítima em uma unidade (!)
			if (victim->hp){																																												//Verifica se a vítima ainda tem HP (!)
				if (previous){																																												//Verifica se não é o primeiro elemento da lista de projéteis (!)
					previous->next = index->next;																																							//Se não for, salva o próximo projétil (!)
					bullet_destroy(index);																																									//Chama o destrutor para o projétil atual (!)
					index = (bullet*) previous->next;																																						//Atualiza para o próximo projétil (!)
				}
				else {																																														//Se for o primeiro projétil da lista (!)
					killer->gun->shots = (bullet*) index->next;																																				//Atualiza o projétil no início da lista (!)
					bullet_destroy(index);																																									//Chama o destrutor para o projétil atual (!)
					index = killer->gun->shots;																																								//Atualiza para o próximo projétil (!)
				}
				return 0;																																													//A vítima sofreu dano, mas ainda não morre (!)
			}
			else return 1;																																													//A vítima sofreu dano e morreu (!)
		}
		previous = index;																																													//Atualiza a variável de controle do projétil anterior (!)
	}
	return 0;																																																//Se não houver nenhum projétil que acertou a vítima, retorne falso
}
unsigned char check_killcollision_2D(square *killer, square *victim){																																					//Implementação da função que verifica se um projétil acertou um jogador

		if (collision_2D(victim,killer)||collision_2D(killer,victim)){														//Verifique se houve colisão com a vítima no eixo Y
			victim->hp--;																																													//Reduz o HP da vítima em uma unidade (!)
			if (victim->hp == 0){
																																																	//Verifica se a vítima ainda tem HP (!)
						return 1 ;																															//Chama o destrutor para o projétil atual (!)
																																								//Atualiza para o próximo projétil (!)
				}else return 0;
																																																	//A vítima sofreu dano, mas ainda não morre (!)
			} 
			
}
