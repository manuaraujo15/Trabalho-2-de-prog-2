#include "boss.h" 	
#define BULLET_RADIUS 5
#define BULLET_COLOR al_map_rgb(255, 0, 0) // Cor vermelha

Boss* iniciaBoss1(){
  	Boss *boss = (Boss*) malloc(sizeof(Boss));																								//Aloca memória na heap para um novo quadrado

        boss = (Boss*)malloc( sizeof(Boss) );
        boss->ID = BOSS1;
        boss->velocidade = 2;
        boss->ativo = 0;
        boss->x = 1500;
        boss->y = 500;
        boss->gun1 = pistol_create();	
        boss->gun2 = pistol_create();	
        boss->velocidade_vertical = 2;     // Velocidade vertical (zig-zag)
        boss->indo_para_metade =1;      
        boss->side = 220;
        boss->face = 0;
        boss->hp = HP_BOSS1;																								//Insere o elemento de disparos do quadrado (!)
        boss->duplicado == 0;
        return boss;

}
Boss *iniciaBoss2(){
  	Boss *boss = (Boss*) malloc(sizeof(Boss));																								//Aloca memória na heap para um novo quadrado
        boss->ID = BOSS2;
        boss->velocidade = 0;
        boss->ativo = 0;
        boss->x = 1500;
        boss->y = 500;
        boss->gun1 = pistol_create();	
        boss->gun2 = pistol_create();	
        boss->velocidade_vertical = 2;     // Velocidade vertical (zig-zag)
        boss->indo_para_metade =1; 
        boss->side = 200;
        boss->face = 0;
        boss->hp = 10;																								//Insere o elemento de disparos do quadrado (!)
        boss->duplicado == 0;
    return boss;

}
Boss *iniciaBoss2_2(){
  	Boss *boss = (Boss*) malloc(sizeof(Boss));																								//Aloca memória na heap para um novo quadrado
        boss->ID = BOSS2;
        boss->velocidade = 0;
        boss->ativo = 0;
        boss->x = 1200;
        boss->y = 300;
        boss->gun1 = pistol_create();	
        boss->gun2 = pistol_create();	
        boss->velocidade_vertical = 2;     // Velocidade vertical (zig-zag)
        boss->indo_para_metade =1; 
        boss->side = 200;
        boss->face = 0;
        boss->hp = 2;																								//Insere o elemento de disparos do quadrado (!)
        boss->duplicado == 0;
    return boss;

}
bullet *pistol_shot_segue(unsigned short x, unsigned short y, square *player, pistol *gun) {
    bullet *new_bullet = bullet_create(x, y, 0, gun->shots); // Cria o projétil

    if (!new_bullet) return NULL;

    return new_bullet;
}
#define BULLET_SPEED 2// Velocidade reduzida para o movimento

void update_bulletsSegue(Boss *boss, pistol *gun, square *player) {
    int velocidade = BULLET_SPEED;
    if(boss->hp <= 6){
        velocidade = 4;
    }
    if (boss->ID == BOSS2) {

        if (gun != NULL) {
            bullet *previous = NULL;
            for (bullet *index = gun->shots; index != NULL;) {
                // Calcula o vetor direção para o jogador
                float dx = player->x - index->x;
                float dy = player->y - index->y;

                // Calcula a distância para limitar o seguimento
                float distance = sqrt(dx * dx + dy * dy);

            
                // Se ainda estiver longe o suficiente, move na direção do jogador
                if (distance > 50 && (dx != 0 || dy != 0)) { // Apenas move se não tiver parado
                    dx /= distance;  // Normaliza o vetor
                    dy /= distance;

                    // Multiplica pela velocidade ajustada
                    index->x += dx * velocidade;
                    index->y += dy * velocidade;
                } 
                
                // Remove tiros fora da tela
                if (index->x < 0 || index->x > X_SCREEN || index->y < 0 || index->y > Y_SCREEN) {
                    if (previous) {
                        previous->next = index->next;
                        bullet_destroy(index);
                        index = (bullet *)previous->next;
                    } else {
                        gun->shots = (bullet *)index->next;
                        bullet_destroy(index);
                        index = gun->shots;
                    }
                } else {
                    previous = index;
                    index = (bullet *)index->next;
                }
            }
        }
    }
}
void update_bulletsBoss(Boss *player, pistol *gun){	
	if(gun != NULL ){
        if(player->ID == BOSS1 || (player->ID == BOSS2 && player->hp>=1)){																																									
            bullet *previous = NULL;																																												
            for (bullet *index = gun->shots; index != NULL;){																																				
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
                        gun->shots = (bullet*) index->next;																																					
                        bullet_destroy(index);																																										
                        index =gun->shots;																																									
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
void liberaBoss(Boss *boss) {
    if (boss != NULL) {
        // Primeiro, liberar os recursos de cada inimigo
            if (boss!= NULL) {
                if (boss->gun1 != NULL) {

                    pistol_destroy(boss->gun1);
                }
                if (boss->gun2 !=NULL) {
                    pistol_destroy(boss->gun2);  // Supondo que pistol_create aloque memória para a arma
                }
                free(boss);  // Libere a memória para o inimigo individual
               boss = NULL;  // Opcional: define o ponteiro para NULL para evitar dangling pointers
            }
        // Agora, liberar o array de ponteiros de inimigos
        free(boss);
        boss = NULL;  // Opcional: define o ponteiro para NULL para evitar dangling pointer
    }
}

void boss_shot(Boss *boss, square * player){																													
    if(boss->ID == BOSS1 ){
        if (!boss->gun1->timer && boss->gun1 != NULL) {
            bullet *shot1;
            bullet *shot2;
            if (!boss->face) {
                //shot1 = pistol_shot(boss->x-150, boss->y+100, boss->face, boss->gun1);	
                shot1 = pistol_shot(boss->x-150, boss->y+100,  boss->face, boss->gun1);
                shot2 = pistol_shot(boss->x-150, boss->y-200, boss->face, boss->gun2);
            }											//Quadrado atira para a esquerda (!)
            else if (boss->face == 1) 
                shot1 = pistol_shot(boss->x-150, boss->y+100,  boss->face, boss->gun1);
                shot2 = pistol_shot(boss->x-150, boss->y-200, boss->face, boss->gun2);						//Quadrado atira para a direita (!)
            if (shot1) 
                boss->gun1->shots = shot1;
            if (shot2) 
                boss->gun2->shots = shot2;
            boss->gun1->timer = 70; // Re
            boss->gun2->timer = 70; // Reseta o cooldown da arma
        }
    }  
    if(boss->ID == BOSS2 ){
        if (!boss->gun1->timer && boss->gun1 != NULL) {
            bullet *shot1;
            bullet *shot2;
            if (!boss->face && boss->duplicado) {
                shot1 = pistol_shot_segue(boss->x-50, boss->y-40,player, boss->gun1);	
                shot2 = pistol_shot(boss->x-150, boss->y-200, boss->face, boss->gun2);
            }
            else if (boss->face == 1) 
                shot1 = pistol_shot(boss->x + boss->side/2, boss->y, boss->face, boss->gun1);								//Quadrado atira para a direita (!)
            if (shot1) 
                boss->gun1->shots = shot1;
            if (shot2) 
                boss->gun2->shots = shot2;
            boss->gun1->timer = 50; // Re
            boss->gun2->timer = 70; // Reseta o cooldown da arma
        }
    }  
    
}


void atualizaBoss(Boss *boss, square *victim){
	if(boss->ativo && boss->ID == BOSS1){
        int local = 0;
        if(boss->hp <= HP_BOSS1/2){
            local = 200;
            boss->velocidade = 4;
        }else{
            local = X_SCREEN /2;
            boss->velocidade = 2;

		}    // Movimento horizontal (zig-zag para a metade da tela)
        if (boss->indo_para_metade) {
            boss->x -= boss->velocidade;

            // Se atingir a metade da tela, inverte a direção
            if (boss->x <= local) {
                boss->indo_para_metade = 0; // Agora, voltará ao ponto inicial
            }
        } else {
            // Retorna ao ponto de origem
            boss->x += boss->velocidade;

            // Se atingir o ponto inicial
            if (boss->x >= X_SCREEN-300) {
                boss->indo_para_metade = 1;
            }
        }

        // Movimento vertical (zig-zag)
        if (boss->y <= 200 || boss->y >= Y_SCREEN - 300) {
            boss->velocidade_vertical *= -1; // Inverta a direção vertical
        }
        boss->y += boss->velocidade_vertical;
    }


    //BOSS 2
    if(boss->ativo && boss->ID == BOSS2){
		//boss->x = boss->velocidade;
		if(boss->x < 0 ){
			boss->ativo = 0;
		}
	}

}
//QUANDO DESENHA NA TELA
//dentro do evento allegro event timer
void DisparaTiroBoss(Boss *boss, square *victim,pistol *gun){
    
    
    if(!boss->ativo && boss->ID == BOSS1){
        if(rand() % 500 ==  0){
            boss->x = X_SCREEN;
            boss->y = 30 + rand() % (Y_SCREEN - 60);
            boss->hp = HP_BOSS1;
            boss->ativo = true;
            boss->indo_para_metade = 1;             // Começa indo para a metade
            boss->velocidade_vertical = 2 + rand() % 3;
    
        }
    }
    if(!boss->ativo && boss->ID == BOSS2){
        if(rand() % 500 ==  0){
          //  boss->x = 30 + rand() % (X_SCREEN - 60);;
          //  boss->y = 30 + rand() % (Y_SCREEN - 60);
            boss->hp = 10;
            boss->ativo = true;
        
        }
    }
    
    boss_shot(boss,victim); // Dispara
    update_bulletsSegue(boss, boss->gun1, victim);
    update_bulletsBoss(boss,gun);	

}

unsigned char check_colisaoBoss(square *jogador, Boss *boss) {
    // Verifica se o jogador e os inimigos têm uma colisão
    
    // Verifica se o jogador colidiu com o inimigo (verifique colisão)
    if(boss->hp > 0 && boss->ativo){
        if (colisaoJogadorBoss(jogador,boss) || colisaoBoss(boss, jogador)) {
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
    
    // Se não houver colisão, retorna 0 (sem colisão)
    return 0;
}
// Função para duplicar o boss

//ve se o inimigo morreu
unsigned char check_kill_jogadorBoss(square *victim, Boss *boss) {
    bullet *previous = NULL;
    int escala =5;
    // Para cada projétil do jogador
    for (bullet *index = victim->gun->shots; index != NULL; index = (bullet*)index->next) {
        // Verifique se houve colisão com o inimigo
        if ((index->x >= boss->x - boss->side) && 
            (index->x <= boss->x + boss->side) && 
            (index->y >= boss->y - boss->side) && 
            (index->y <= boss->y + boss->side) && boss->ativo) {
            
            // Decrementa o HP do inimigo se colidir
            boss->hp--;
            
            if (boss->hp > 0 && boss->ativo) {
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
                boss->ativo = 0;
                victim->hp = HPJOGADOR;		

               // DisparaAtivo(inimigo[i]);
                if (previous) {
                    previous->next = index->next;  // Remove o projétil da lista
                    bullet_destroy(index);  // Destroi o projétil
                    index = (bullet*)previous->next;  // Avança para o próximo projétil
                } else {
                    victim->gun->shots = (bullet*)index->next;
                    bullet_destroy(index);
                    index = victim->gun->shots;
                }
                // atualizaBoss(inimigo, tamanho);
                return 1;  // BossBoss morreu
            }
            return 0;  // Boss ainda está vivo
        }
    }

    
    return 0;  // Se não houve colisão com nenhum projétil
}

// se se o jogador morreu
unsigned char check_kill_boss(Boss *boss, square *victim,pistol *gun){																																					
    if(gun != NULL){  
        bullet *previous = NULL;

        for (bullet *index = gun->shots; index != NULL; index = (bullet*) index->next){	                                                                                                                    
            if ((index->x >= victim->x - victim->side) && (index->x <= victim->x + victim->side) && //																										
            (index->y >= victim->y - victim->side) && (index->y <= victim->y + victim->side)){	
                if(boss->ID == BOSS1 && victim->hp % 2 == 0){																									
                    victim->hp = victim->hp - 2;

                }
                if(boss->ID == BOSS1 && victim->hp % 2 != 0)	{																									
                    victim->hp = victim->hp - 1;
                }
                else  if(boss->ID == BOSS2)	 {

                    victim->hp--;			
                }																																										 
                if (boss->ativo){																																												 
                    if (previous){	
                        previous->next = index->next;																																							
                        bullet_destroy(index);																																									
                        index = (bullet*) previous->next;																																						
                    }
                    else {		
                        gun->shots = (bullet*) index->next;																																				
                        bullet_destroy(index);																																									 
                        index = gun->shots;																																								 
                    }
                    return 0;																																													
                }
                else return 1;																																													
            }
            previous = index;																																													 
        }
    }
	return 0;																																																
}

void desenhabalaBoss(Boss * boss, ALLEGRO_BITMAP *tiro1 ,ALLEGRO_BITMAP *tiro2){
   

    float escala_x = 1;  // Escala horizontal
    float escala_y =  1;
    int escala = 4;
	if(boss->ativo && boss->ID == BOSS1){
		for (bullet *index =boss->gun1->shots; index != NULL; index = (bullet*) index->next){ 
            al_draw_scaled_bitmap(tiro1, 0, 0, al_get_bitmap_width(tiro1), al_get_bitmap_height(tiro1), index->x, index->y, al_get_bitmap_width(tiro1) * escala_x, al_get_bitmap_height(tiro1) * escala_y, 0);
            al_draw_scaled_bitmap(tiro1, 0, 0, al_get_bitmap_width(tiro1), al_get_bitmap_height(tiro1), index->x, index->y-30, al_get_bitmap_width(tiro1) * escala_x, al_get_bitmap_height(tiro1) * escala_y, 0);
            al_draw_scaled_bitmap(tiro1, 0, 0, al_get_bitmap_width(tiro1), al_get_bitmap_height(tiro1), index->x-5, index->y-13, al_get_bitmap_width(tiro1) * escala_x, al_get_bitmap_height(tiro1) * escala_y, 0);
            al_draw_scaled_bitmap(tiro1, 0, 0, al_get_bitmap_width(tiro1), al_get_bitmap_height(tiro1), index->x+10, index->y-13, al_get_bitmap_width(tiro1) * escala_x, al_get_bitmap_height(tiro1) * escala_y, 0);

    }  
    if (boss->gun1->timer) boss->gun1->timer--; 	      
            // Desenha novamente o tiro com a mesma esvcala
        for (bullet *index =boss->gun2->shots; index != NULL; index = (bullet*) index->next) {
            al_draw_scaled_bitmap(tiro1, 0, 0, al_get_bitmap_width(tiro1), al_get_bitmap_height(tiro1), index->x, index->y, al_get_bitmap_width(tiro1) * escala_x,al_get_bitmap_height(tiro1) * escala_y, 0); 
            al_draw_scaled_bitmap(tiro1, 0, 0, al_get_bitmap_width(tiro1), al_get_bitmap_height(tiro1), index->x, index->y-30, al_get_bitmap_width(tiro1) * escala_x, al_get_bitmap_height(tiro1) * escala_y, 0);
            al_draw_scaled_bitmap(tiro1, 0, 0, al_get_bitmap_width(tiro1), al_get_bitmap_height(tiro1), index->x-5, index->y-13, al_get_bitmap_width(tiro1) * escala_x, al_get_bitmap_height(tiro1) * escala_y, 0);
            al_draw_scaled_bitmap(tiro1, 0, 0, al_get_bitmap_width(tiro1), al_get_bitmap_height(tiro1), index->x+10, index->y-13, al_get_bitmap_width(tiro1) * escala_x, al_get_bitmap_height(tiro1) * escala_y, 0);			
        }
        if (boss->gun2->timer) boss->gun2->timer--; 	

	}
    if(boss->ativo && boss->ID == BOSS2){
		for (bullet *index = boss->gun1->shots; index != NULL; index = (bullet*) index->next) 
			al_draw_scaled_bitmap(tiro2, 0, 0, al_get_bitmap_width(tiro2), al_get_bitmap_height(tiro2),index->x, index->y,  al_get_bitmap_width(tiro2) * escala, al_get_bitmap_height(tiro2) * escala, 0);				
			if (boss->gun1->timer) boss->gun1->timer--; 	
    }
}


void desenhabalaBoss22(Boss * boss,ALLEGRO_BITMAP *tiro2){
    int escala = 4;

    if(boss->ativo && boss->ID == BOSS2){
		for (bullet *index = boss->gun1->shots; index != NULL; index = (bullet*) index->next) 
			al_draw_scaled_bitmap(tiro2, 0, 0, al_get_bitmap_width(tiro2), al_get_bitmap_height(tiro2),index->x, index->y,  al_get_bitmap_width(tiro2) * escala, al_get_bitmap_height(tiro2) * escala, 0);				
			if (boss->gun1->timer) boss->gun1->timer--; 	
    }
}

void desenha_boss(Boss *boss1, Boss *boss2, ALLEGRO_BITMAP *framesiNI1[], ALLEGRO_BITMAP *framesiNI2[], int frames, int frames2, int facing_left, float scale) {
    int flags = facing_left ? ALLEGRO_FLIP_HORIZONTAL : 0;


   // Para o boss1
    if (boss1->ativo && boss1->ID == BOSS1) {
       // Obtém a largura e altura da imagem do boss1
        int width1 = al_get_bitmap_width(framesiNI1[frames]);
        int height1 = al_get_bitmap_height(framesiNI1[frames]);

        // Aplica o redimensionamento com base no fator de escala
        al_draw_scaled_bitmap(framesiNI1[frames], 0, 0, width1, height1,
                            boss1->x - width1 * scale / 2, boss1->y - height1 * scale / 2,
                            width1 * scale, height1 * scale, flags);
    }
   // Para o boss2
    int escala =5;
    if (boss2->ativo && boss2->ID == BOSS2) {
       // Obtém a largura e altura da imagem do boss2
        int width2 = al_get_bitmap_width(framesiNI2[frames2]);
        int height2 = al_get_bitmap_height(framesiNI2[frames2]);

       // Aplica o redimensionamento com base no fator de escala
       al_draw_scaled_bitmap(framesiNI2[frames2], 0, 0, width2, height2,boss2->x - width2 * escala / 2, boss2->y - height2 * escala / 2,width2 * escala, height2 * escala, flags);

    }
}

void desenha_boss2(Boss *boss1, Boss *boss2, ALLEGRO_BITMAP *framesiNI1[], ALLEGRO_BITMAP *framesiNI2[], int frames, int frames2, int facing_left, float scale) {
    int flags = facing_left ? ALLEGRO_FLIP_HORIZONTAL : 0;

    int escala =5;
    if (boss2->ativo && boss2->ID == BOSS2) {
        // Obtém a largura e altura da imagem do boss2
        int width2 = al_get_bitmap_width(framesiNI2[frames2]);
        int height2 = al_get_bitmap_height(framesiNI2[frames2]);
        al_draw_scaled_bitmap(framesiNI2[frames2], 0, 0, width2, height2,
                              boss2->x - width2 * escala / 2 , boss2->y - height2 * escala / 2,
                              width2 * escala, height2 * escala, flags);
    }
}

unsigned char colisaoBoss(Boss *inimigo, square *jogador){
	
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
unsigned char colisaoJogadorBoss( square *jogador,Boss *inimigo){
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
/*
unsigned char colisaoInimicoBoss( Boss **jogador,Boss **inimigo, int tamanho){
    for (int i = 0; i < tamanho; i++)
    {check_colisaoboss
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
	
}*/
void move_boss(Boss *boss, char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y){									//Implementação da função "square_move"
        if (!trajectory){ if ((boss->x - steps*SQUARE_STEP) - boss->side/2 >= 0) 
            boss->x = boss->x - steps*SQUARE_STEP;
        } 						//Verifica se a movimentação para a esquerda é desejada e possível; se sim, efetiva a mesma
        else if (trajectory == 1){ 
            if ((boss->x + steps*SQUARE_STEP) + boss->side/2 <= max_x) 
                boss->x = boss->x + steps*SQUARE_STEP;
            }			//Verifica se a movimentação para a direita é desejada e possível; se sim, efetiva a mesma
        else if (trajectory == 2){ 
            if ((boss->y - steps*SQUARE_STEP) - boss->side/2 >= 0) 
                boss->y = boss->y - steps*SQUARE_STEP;
            }				//Verifica se a movimentação para cima é desejada e possível; se sim, efetiva a mesma
        else if (trajectory == 3){ 
            if ((boss->y + steps*SQUARE_STEP) + boss->side/2 <= max_y) 
            boss->y = boss->y + steps*SQUARE_STEP;
            }			//Verifica se a movimentação para baixo é desejada e possível; se sim, efetiva a mesma

}
