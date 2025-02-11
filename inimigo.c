#include "inimigo.h"


Inimigo **iniciaInimigo1(int tamanho){
	Inimigo **inimigo =malloc( tamanho * sizeof(Inimigo) );
    for (int i = 0; i < tamanho; i++)
    {
        inimigo[i] = (Inimigo*)malloc( sizeof(Inimigo) );
        inimigo[i]->ID = INIMIGO1;
        inimigo[i]->velocidade = 2;
        inimigo[i]->ativo = 0;
        inimigo[i]->x = 50;
        inimigo[i]->y = 50;
        inimigo[i]->gun = pistol_create();	
        inimigo[i]->side = 20;
        inimigo[i]->face = 0;
        inimigo[i]->hp = 1;																								//Insere o elemento de disparos do quadrado (!)

    }return inimigo;

}
Inimigo **iniciaInimigo2(int tamanho){
	Inimigo **inimigo = malloc( tamanho * sizeof(Inimigo) );
    for (int i = 0; i < tamanho; i++)
    {
        inimigo[i] = (Inimigo*)malloc( sizeof(Inimigo) );
        inimigo[i]->ID = INIMIGO2;
        inimigo[i]->velocidade = 0;
        inimigo[i]->ativo = 0;
        inimigo[i]->x = 50;
        inimigo[i]->y = 50;
        inimigo[i]->gun = pistol_create();	
        inimigo[i]->side = 20;
        inimigo[i]->face = 0;
        inimigo[i]->hp = 1;																								//Insere o elemento de disparos do quadrado (!)

    }return inimigo;

}
Inimigo **iniciaInimigo3(int tamanho){
	Inimigo **inimigo = malloc( tamanho * sizeof(Inimigo) );
    for (int i = 0; i < tamanho; i++)
    {
        inimigo[i] = (Inimigo*)malloc( sizeof(Inimigo) );
        inimigo[i]->ID = INIMIGO3;
        inimigo[i]->velocidade = 2;
        inimigo[i]->ativo = 0;
        inimigo[i]->x = 70;
        inimigo[i]->y = 70;
        inimigo[i]->gun = NULL;	
        inimigo[i]->side = 20;
        inimigo[i]->face = 0;
        inimigo[i]->hp = 1;																								//Insere o elemento de disparos do quadrado (!)

    }return inimigo;

}
Inimigo **iniciaInimigo4(int tamanho){
	Inimigo **inimigo = malloc( tamanho * sizeof(Inimigo) );
    for (int i = 0; i < tamanho; i++)
    {
        inimigo[i] = (Inimigo*)malloc( sizeof(Inimigo) );
        inimigo[i]->ID = INIMIGO4;
        inimigo[i]->velocidade = 1;
        inimigo[i]->ativo = 0;
        inimigo[i]->x = 70;
        inimigo[i]->y = 70;
        inimigo[i]->gun =NULL;
        inimigo[i]->side = 30;
        inimigo[i]->face = 0;
        inimigo[i]->hp = 3;																								

    }return inimigo;

}

void liberaInimigos(Inimigo **inimigos, int tamanho) {
    if (inimigos != NULL) {
        // Primeiro, liberar os recursos de cada inimigo
        for (int i = 0; i < tamanho; i++) {
            if (inimigos[i] != NULL) {
                if (inimigos[i]->gun != NULL) {
                    pistol_destroy(inimigos[i]->gun);																														

                }
                free(inimigos[i]);  // Libere a memória para o inimigo individual
                inimigos[i] = NULL;  //ponteiro para NULL ATERRA
            }
        }
        
        free(inimigos);
        inimigos = NULL;  
    }
}
void inimigo_shot(Inimigo **inimigo, int tamanho){																														

    for (int i = 0; i < tamanho; i++)
    {
        if(inimigo[i]->ID == INIMIGO1 || inimigo[i]->ID == INIMIGO2){
            if (!inimigo[i]->gun->timer && inimigo[i]->gun != NULL) {
            bullet *shot;
            if (!inimigo[i]->face) shot = pistol_shot(inimigo[i]->x - inimigo[i]->side/2, inimigo[i]->y, inimigo[i]->face, inimigo[i]->gun);										
            else if (inimigo[i]->face == 1) shot = pistol_shot(inimigo[i]->x + inimigo[i]->side/2, inimigo[i]->y, inimigo[i]->face, inimigo[i]->gun);								
            if (shot)inimigo[i]->gun->shots = shot;
            inimigo[i]->gun->timer = 100; // Reseta o cooldown da arma
            }
        }
    }
}
void update_bulletsInimigo(Inimigo **player, int tamanho){	
	for(int i = 0 ; i<tamanho ; i++){	
        if(player[i]->gun != NULL ){
            if(player[i]->ID == INIMIGO1 || player[i]->ID == INIMIGO2){																																									
                bullet *previous = NULL;																																												
                for (bullet *index = player[i]->gun->shots; index != NULL;){																																				
                    if (!index->trajectory) index->x -= BULLET_MOVE;																																					
                    else if (index->trajectory == 1) index->x += BULLET_MOVE;																																			
                    
                    if ((index->x < 0) || (index->x > X_SCREEN)){																																						
                        if (previous){																																													
                            previous->next = index->next;
                            //verifica se kja nao foi apagada																																								
                            bullet_destroy(index);																																										
                            index = (bullet*) previous->next;																																							
                        }
                        else {																																															
                            player[i]->gun->shots = (bullet*) index->next;																																					
                            bullet_destroy(index);																																										
                            index = player[i]->gun->shots;																																									
                        }
                    }
                    else{																																																
                        previous = index;																																												
                        index = (bullet*) index->next;																																									
                    }
                }
            }
        }
    }
}

void atualizaInimigo(Inimigo **inimigo, int tamanho, square *victim){
	for (int i = 0; i < tamanho; i++){ 
			if(inimigo[i]->ativo && inimigo[i]->ID == INIMIGO1){
				inimigo[i]->x -= inimigo[i]->velocidade;
				if(inimigo[i]->x < 0 ){
					inimigo[i]->ativo = 0;
				}
			}
            if(inimigo[i]->ativo && inimigo[i]->ID == INIMIGO2){
				//inimigo[i]->x = inimigo[i]->velocidade;
				if(inimigo[i]->x < 0 ){
					inimigo[i]->ativo = 0;
				}
			}
            if(inimigo[i]->ativo && inimigo[i]->ID == INIMIGO3){
				inimigo[i]->y -= inimigo[i]->velocidade;
				if(inimigo[i]->y < 0 ){
					inimigo[i]->ativo = 0;
				}
			}
            if(inimigo[i]->ativo && inimigo[i]->ID == INIMIGO4){
				inimigo[i]->x -= inimigo[i]->velocidade;
				if(inimigo[i]->x < 0 ){
					inimigo[i]->ativo = 0;
				}
			}
		}

}
//QUANDO DESENHA NA TELA
//dentro do evento allegro event timer
void DisparaTiro(Inimigo **inimigo, int tamanho, square *victim){
    
    for (int i = 0; i < tamanho; i++)
    {   
        if(!inimigo[i]->ativo && inimigo[i]->ID == INIMIGO1){
            if(rand() % 500 ==  0){
                inimigo[i]->x = X_SCREEN;
                inimigo[i]->y = 30 + rand() % (Y_SCREEN - 60);
                inimigo[i]->hp = 1;
                inimigo[i]->ativo = true;
                break;
            }
        }
        if(!inimigo[i]->ativo && inimigo[i]->ID == INIMIGO2){
            if(rand() % 500 ==  0){
                inimigo[i]->x = (X_SCREEN / 2) + rand() % (X_SCREEN / 2 - 60); // Meio direito da tela
                inimigo[i]->y = 30 + rand() % (Y_SCREEN - 60);
                inimigo[i]->hp = 1;
                inimigo[i]->ativo = true;
                break;
            }
        }
        if(!inimigo[i]->ativo && inimigo[i]->ID == INIMIGO3){
            if(rand() % 500 ==  0){
                inimigo[i]->x =  30 + rand() % (X_SCREEN - 60);;
                inimigo[i]->y = Y_SCREEN;
                inimigo[i]->hp = 1;
                inimigo[i]->ativo = true;
                break;
            }
        }
        if(!inimigo[i]->ativo && inimigo[i]->ID == INIMIGO4){
            if(rand() % 500 ==  0){
                inimigo[i]->x = X_SCREEN;
                inimigo[i]->y = 30 + rand() % (Y_SCREEN - 60);
                inimigo[i]->hp = 3;
                inimigo[i]->ativo = true;
                break;
            }
        }

    }

    inimigo_shot(inimigo,tamanho); // Dispara
    update_bulletsInimigo(inimigo, tamanho);	

}

unsigned char check_colisao(square *jogador, Inimigo **inimigos, int tamanho) {
    // Verifica se o jogador e os inimigos têm uma colisão
    for (int i = 0; i < tamanho; i++) {
        // Verifica se o jogador colidiu com o inimigo (verifique colisão)
        if(inimigos[i]->hp > 0 && inimigos[i]->ativo){
            if (colisaoJogador(jogador, inimigos[i], tamanho) || colisaoInimigo(inimigos[i], jogador, tamanho)) {
                // Quando ocorre uma colisão, diminui o HP do jogador
                jogador->hp--;
                if (jogador->hp > 0) {
                    // Se ainda tiver HP, retorna 0 (jogador ainda está vivo)
                    return 0;
                } else {
                    // Se não tiver mais HP, o jogador morreu, retorna 1
                    // Destroi as balas ou faz outras ações de final de vida
                    return 1; 
                }  
            }
        }
    }
    // Se não houver colisão, retorna 0 (sem colisão)
    return 0;
}

//ve se o inimigo morreu
unsigned char check_kill_jogador(square *victim, Inimigo **inimigo, int tamanho) {
    for (int i = 0; i < tamanho; i++) {  
            bullet *previous = NULL;
            
            // Para cada projétil do jogador
            for (bullet *index = victim->gun->shots; index != NULL; index = (bullet*)index->next) {
                // Verifique se houve colisão com o inimigo
                if ((index->x >= inimigo[i]->x - inimigo[i]->side) && 
                    (index->x <= inimigo[i]->x + inimigo[i]->side) && 
                    (index->y >= inimigo[i]->y - inimigo[i]->side) && 
                    (index->y <= inimigo[i]->y + inimigo[i]->side) && inimigo[i]->ativo) {
                    
                    // Decrementa o HP do inimigo se colidir
                    inimigo[i]->hp--;
                    
                    if (inimigo[i]->hp > 0 && inimigo[i]->ativo) {
                        // Se o inimigo ainda tiver HP, destrua o projétil e continue
                        if (previous) {
                            previous->next = index->next;  // Remove o projétil da lista
                            bullet_destroy(index);  // Destroi o projétil
                            index = (bullet*)previous->next;  // Avança para o próximo projétil
                        } else {
                            // Caso seja o primeiro projétil da lista
                            victim->gun->shots = (bullet*)index->next;
                            bullet_destroy(index);
                            index = victim->gun->shots;  // Avança para o próximo projétil
                        }
                    } else {
                        // O inimigo morreu
                        inimigo[i]->ativo = 0; 

                        if (previous) {
                            previous->next = index->next;  // Remove o projétil da lista
                            bullet_destroy(index);  // Destroi o projétil
                            index = (bullet*)previous->next;  // Avança para o próximo projétil
                        } else {
                            victim->gun->shots = (bullet*)index->next;
                            bullet_destroy(index);
                            index = victim->gun->shots;
                        }
                        // atualizaInimigo(inimigo, tamanho);
                        return 1;  // Inimigo morreu
                    }
                    return 0;  // Inimigo ainda está vivo
                }
            }
        
    }
    return 0;  // Se não houve colisão com nenhum projétil
}

// se se o jogador morreu
unsigned char check_kill_inimigo(Inimigo **inimigo, square *victim, int tamanho){																																					

    for (int i = 0; i < tamanho; i++){
    if(inimigo[i]->gun != NULL){  
        bullet *previous = NULL;

        for (bullet *index = inimigo[i]->gun->shots; index != NULL; index = (bullet*) index->next){	                                                                                                                    
            if ((index->x > victim->x - victim->side) && 
            (index->x <victim->x + victim->side) && //																										
            (index->y > victim->y - victim->side) && 
            (index->y < victim->y + victim->side)){																											
                victim->hp--;																																													
                if (victim->hp && inimigo[i]->ativo){																																												
                    if (previous){																																												
                        previous->next = index->next;																																							
                        bullet_destroy(index);																																									
                        index = (bullet*) previous->next;																																						
                    }
                    else {																																														
                        inimigo[i]->gun->shots = (bullet*) index->next;																																				
                        bullet_destroy(index);																																									
                        index = inimigo[i]->gun->shots;																																								
                    }
                    return 0;																																													
                }
                else return 1;																																													
            }
            previous = index;																																													
        }
    }
    }
	return 0;																																																
}


void desenhabala(Inimigo ** inimigo, int tamanho,  ALLEGRO_BITMAP *tiro1, ALLEGRO_BITMAP *tiro2){
    float escala_x = 0.5;  // Escala horizontal
    float escala_y = 0.5;
    for (int i = 0; i < tamanho; i++){
		if(inimigo[i]->ativo && inimigo[i]->ID == INIMIGO2){
			for (bullet *index = inimigo[i]->gun->shots; index != NULL; index = (bullet*) index->next) 
				al_draw_scaled_bitmap(tiro2, 0, 0, al_get_bitmap_width(tiro2), al_get_bitmap_height(tiro2),index->x-10, index->y-30,  al_get_bitmap_width(tiro2) * escala_x, al_get_bitmap_height(tiro2) * escala_y, 0);				
				if (inimigo[i]->gun->timer) inimigo[i]->gun->timer--; 		
		}
        if(inimigo[i]->ativo && inimigo[i]->ID == INIMIGO1){
			for (bullet *index = inimigo[i]->gun->shots; index != NULL; index = (bullet*) index->next) 
				al_draw_scaled_bitmap(tiro1, 0, 0, al_get_bitmap_width(tiro1), al_get_bitmap_height(tiro1),index->x-30, index->y-30,  al_get_bitmap_width(tiro1) * escala_x, al_get_bitmap_height(tiro1) * escala_y, 0);				
				if (inimigo[i]->gun->timer) inimigo[i]->gun->timer--; 	
        }
    }
}
void desenha_inimigo(square *player_1,Inimigo **inimigo1,Inimigo **inimigo4, ALLEGRO_BITMAP *framesiNI1[],ALLEGRO_BITMAP *framesiNI2[],ALLEGRO_BITMAP *framesiNI3[],ALLEGRO_BITMAP *framesiNI4[], int frames, int tamanho, int facing_left) {
    int flags = facing_left ? ALLEGRO_FLIP_HORIZONTAL : 0;
    for (int i = 0; i < tamanho; i++){ 
        if(inimigo1[i]->ativo && inimigo1[i]->ID == INIMIGO1){
            float escala_x = 1.2f;
            float escala_y = 1.2f;

            // Desenha a imagem escalada
            al_draw_scaled_bitmap(framesiNI1[frames], 0, 0, al_get_bitmap_width(framesiNI1[frames]), al_get_bitmap_height(framesiNI1[frames]), 
                inimigo1[i]->x - al_get_bitmap_width(framesiNI1[frames]) / 2, inimigo1[i]->y - al_get_bitmap_height(framesiNI1[frames]) / 2, 
                al_get_bitmap_width(framesiNI1[frames]) * escala_x, al_get_bitmap_height(framesiNI1[frames]) * escala_y, flags);
        }

        if(inimigo1[i]->ativo && inimigo1[i]->ID == INIMIGO2){
            al_draw_bitmap(framesiNI2[frames], inimigo1[i]->x - al_get_bitmap_width(framesiNI2[frames]) / 2,
                inimigo1[i]->y - al_get_bitmap_height(framesiNI2[frames]) / 2, flags);
        }
        
        if(inimigo4[i]->ativo && inimigo4[i]->ID == INIMIGO3){
             // Defina o fator de escala que deseja (por exemplo, 1.5 para 150% do tamanho original)
            float escala_x = 1.5f;  // Fator de escala para largura
            float escala_y = 1.5f;  // Fator de escala para altura

            // Desenha a imagem escalada
            al_draw_scaled_bitmap(framesiNI3[frames], 0, 0, al_get_bitmap_width(framesiNI3[frames]), al_get_bitmap_height(framesiNI3[frames]), inimigo4[i]->x - al_get_bitmap_width(framesiNI3[frames]) / 2, 
                inimigo4[i]->y - al_get_bitmap_height(framesiNI3[frames]) / 2, al_get_bitmap_width(framesiNI3[frames]) * escala_x, al_get_bitmap_height(framesiNI3[frames]) * escala_y, flags);
        }

        if(inimigo4[i]->ativo && inimigo4[i]->ID == INIMIGO4){
        
        // Defina os fatores de escala que você deseja (por exemplo, 1.5 para 150% do tamanho original)
            float escala_x = 1.2f;  // Fator de escala para largura
            float escala_y = 1.2f;  // Fator de escala para altura

            if(inimigo4[i]->hp == 3 && player_1->face == 1){
                al_draw_scaled_bitmap(framesiNI4[frames], 0, 0, al_get_bitmap_width(framesiNI4[frames]), al_get_bitmap_height(framesiNI4[frames]),
                    inimigo4[i]->x + 50 - al_get_bitmap_width(framesiNI4[frames]) / 2,inimigo4[i]->y - al_get_bitmap_height(framesiNI4[frames]) / 2,
                    al_get_bitmap_width(framesiNI4[frames]) * escala_x, al_get_bitmap_height(framesiNI4[frames]) * escala_y, flags);
                    al_draw_scaled_bitmap(framesiNI4[frames],0, 0, al_get_bitmap_width(framesiNI4[frames]), al_get_bitmap_height(framesiNI4[frames]),
                    inimigo4[i]->x - al_get_bitmap_width(framesiNI4[frames]) / 2,inimigo4[i]->y - al_get_bitmap_height(framesiNI4[frames]) / 2,
                    al_get_bitmap_width(framesiNI4[frames]) * escala_x, al_get_bitmap_height(framesiNI4[frames]) * escala_y, flags);
                    al_draw_scaled_bitmap(framesiNI4[frames],0, 0, al_get_bitmap_width(framesiNI4[frames]), al_get_bitmap_height(framesiNI4[frames]),
                    inimigo4[i]->x + 100 - al_get_bitmap_width(framesiNI4[frames]) / 2,inimigo4[i]->y - al_get_bitmap_height(framesiNI4[frames]) / 2,
                    al_get_bitmap_width(framesiNI4[frames]) * escala_x,al_get_bitmap_height(framesiNI4[frames]) * escala_y, flags);
            }
            
            if(inimigo4[i]->hp == 2 && player_1->face == 1){
                al_draw_scaled_bitmap(framesiNI4[frames],0, 0, al_get_bitmap_width(framesiNI4[frames]), al_get_bitmap_height(framesiNI4[frames]),
                    inimigo4[i]->x + 50 - al_get_bitmap_width(framesiNI4[frames]) / 2,inimigo4[i]->y - al_get_bitmap_height(framesiNI4[frames]) / 2,
                    al_get_bitmap_width(framesiNI4[frames]) * escala_x, al_get_bitmap_height(framesiNI4[frames]) * escala_y, flags);
                    al_draw_scaled_bitmap(framesiNI4[frames], 0, 0, al_get_bitmap_width(framesiNI4[frames]), al_get_bitmap_height(framesiNI4[frames]),
                    inimigo4[i]->x + 100 - al_get_bitmap_width(framesiNI4[frames]) / 2,inimigo4[i]->y - al_get_bitmap_height(framesiNI4[frames]) / 2,
                    al_get_bitmap_width(framesiNI4[frames]) * escala_x, al_get_bitmap_height(framesiNI4[frames]) * escala_y,  flags);
            }
            
            if(inimigo4[i]->hp == 1 && player_1->face == 1){
                al_draw_scaled_bitmap(framesiNI4[frames], 0, 0, al_get_bitmap_width(framesiNI4[frames]), al_get_bitmap_height(framesiNI4[frames]),
                    inimigo4[i]->x + 100 - al_get_bitmap_width(framesiNI4[frames]) / 2,inimigo4[i]->y - al_get_bitmap_height(framesiNI4[frames]) / 2,
                    al_get_bitmap_width(framesiNI4[frames]) * escala_x, al_get_bitmap_height(framesiNI4[frames]) * escala_y, flags);
            }
        }
    }
}


unsigned char colisaoInimigo(Inimigo *inimigo, square *jogador, int tamanho){
	
		if ((((inimigo->y+inimigo->side/2 >= jogador->y-jogador->side/2) && 
			(jogador->y-jogador->side/2 >= inimigo->y-inimigo->side/2)) || 	//						
			((jogador->y+jogador->side/2 >= inimigo->y-inimigo->side/2) &&
			 (inimigo->y-inimigo->side/2 >= jogador->y-jogador->side/2))) && 	//			
			(((inimigo->x+inimigo->side/2 >= jogador->x-jogador->side/2) &&
			 (jogador->x-jogador->side/2 >= inimigo->x-inimigo->side/2)) || 	//			
			((jogador->x+jogador->side/2 >= inimigo->x-inimigo->side/2) && 
			(inimigo->x-inimigo->side/2 >= jogador->x-jogador->side/2)))) 
			return 1;		
		else return 0;
	
}
unsigned char colisaoJogador( square *jogador,Inimigo *inimigo, int tamanho){
	if ((((jogador->y+jogador->side/2 >= inimigo->y-inimigo->side/2) &&
		(inimigo->y-inimigo->side/2 >= jogador->y-jogador->side/2)) || 						
		((inimigo->y+inimigo->side/2 >= jogador->y-jogador->side/2) &&
		(jogador->y-jogador->side/2 >= inimigo->y-inimigo->side/2))) && 		
		(((jogador->x+jogador->side/2 >= inimigo->x-inimigo->side/2) && 
		(inimigo->x-inimigo->side/2 >= jogador->x-jogador->side/2)) || 		
		((inimigo->x+inimigo->side/2 >= jogador->x-jogador->side/2) &&
		(jogador->x-jogador->side/2 >= inimigo->x-inimigo->side/2)))) 
		return 1;		
	else return 0;
	
}
unsigned char colisaoInimicoInimigo( Inimigo **jogador,Inimigo **inimigo, int tamanho){
    for (int i = 0; i < tamanho; i++)
    {
    if ((((jogador[i]->y+jogador[i]->side/2 >= inimigo[i]->y-inimigo[i]->side/2) &&
		(inimigo[i]->y-inimigo[i]->side/2 >= jogador[i]->y-jogador[i]->side/2)) || 						
		((inimigo[i]->y+inimigo[i]->side/2 >= jogador[i]->y-jogador[i]->side/2) &&
		(jogador[i]->y-jogador[i]->side/2 >= inimigo[i]->y-inimigo[i]->side/2))) && 		
		(((jogador[i]->x+jogador[i]->side/2 >= inimigo[i]->x-inimigo[i]->side/2) && 
		(inimigo[i]->x-inimigo[i]->side/2 >= jogador[i]->x-jogador[i]->side/2)) || 		
		((inimigo[i]->x+inimigo[i]->side/2 >= jogador[i]->x-jogador[i]->side/2) &&
		(jogador[i]->x-jogador[i]->side/2 >= inimigo[i]->x-inimigo[i]->side/2)))) 
		return 1;		
	else return 0;
    }
    
	return 0;
	
}

