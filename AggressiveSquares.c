//Compilação:  gcc AggressiveSquares.c Square.c Joystick.c Bullet.c Pistol.c ataqueEspecial.c inimigo.c menu.c boss.c -o AS $(pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_primitives-5 allegro_image-5 --libs --cflags) -lm

#include <allegro5/allegro5.h>																																											
#include <allegro5/allegro_font.h>																																										
#include <allegro5/allegro_primitives.h>																																								
#include <allegro5/allegro_image.h> // Biblioteca para carregar imagens
#include <allegro5/allegro_ttf.h>

#include "Square.h"
#include "ataqueEspecial.h"
#include "inimigo.h"
#include "boss.h"
#include <stdio.h>																																														
#include <time.h>	
#include "menu.h"
#include "hud.h"


#define NUM_INIMIGOS 6

#define NUM_FRAMES 7
#define X_SCREEN 576*3																																									
#define Y_SCREEN 324*3	

	AtaqueEsp ataqueEsp[2];  // Criando dois DESENHOS no mapa



int main(){
	al_init();																																															
	al_init_primitives_addon();																																											
	al_init_image_addon();
	al_init_font_addon();
	al_install_keyboard();	
	al_init_ttf_addon();
 // Inicializa o addon de imagens
    srand(time(NULL));

/*--------------------------------------------------DECLARACAO DE VARIAVEIS-------------------*/
	int jogo_rodando = -1;
	float escala_x = 0.5;  // Escala horizontal
	float escala_y = 0.5;
	int frame_cont1 = 0;
	int frame_delay = 2; // Número de ciclos de loop antes de mudar o frame
	int frame_delay_coracao= 1;
	int frame_delay_inim = 2;
	int frame_delay_boss = 2;
	int frame_delay_boss2 = 3;
	const float TEMPO_FALAS = 3.0f; // 3 segundos
	float tempo_falas_restante = TEMPO_FALAS;
	float tempo_falas = TEMPO_FALAS;
	int ken_hit = 0; // Estado inicial
	float ken_x = 50, ken_y = 100; // Posição inicial
	float ken_velocity = 7; // Velocidade
	int frame_boss1 = 0;
	int frame_boss2 = 0;
	// Número de ciclos de loop antes de mudar o frame
	int frame_nave = 0;
	int coracao_frame = 0;	
	int frame_cont = 0;	
	float bg_x = 0;  // Posição X inicial do background
    float bg_vel = 1.5;  // Velocidade de rolagem do background
 	int fase = 1; // Fase 1 ou 2
    int time_fase = 2000; // Tempo para cada fase                 AUMENTEI PRA TESTE
	int cont_inim1 = 0;
	int cont_boss1 = 0;
	int cont_boss2 = 0;
	int frame_inim1 = 0;
	int frame_barbieTriste= 0;
	int frame_delay_barbieTriste = 2;
	int cont_barbieTriste = 0;
	int transicao_em_andamento = 1;

/*--------------------------------------------------DECLARACAO DE IMAGENS-------------------*/
    ALLEGRO_BITMAP* ken_image = al_load_bitmap("ken.png");
	ALLEGRO_BITMAP* barbie_image = al_load_bitmap("barbie.png");
    ALLEGRO_BITMAP* witch_image = al_load_bitmap("bosscerto.png");
    ALLEGRO_BITMAP* background_image = al_load_bitmap("fundo.png");
    ALLEGRO_BITMAP* oibarbie = al_load_bitmap("OIBARBIE.png");
    ALLEGRO_BITMAP* oiken = al_load_bitmap("OIKEN.png");
	ALLEGRO_BITMAP* barbie_bruxalevouken = al_load_bitmap("barbie_bruxalevouken.png");
	ALLEGRO_BITMAP* babiefeliz = al_load_bitmap("babiefeliz.png");
	ALLEGRO_BITMAP* barbiesad = al_load_bitmap("barbiesad.jpg");
	ALLEGRO_BITMAP* kenSalvo = al_load_bitmap("kenSalvo.png");
	ALLEGRO_BITMAP* salvei = al_load_bitmap("salvei.png");
	ALLEGRO_BITMAP* naveBarbie = al_load_bitmap("naveBarbie.png");
	ALLEGRO_BITMAP* finalruim = al_load_bitmap("finalruim.png");
	ALLEGRO_BITMAP* pegaBruxa = al_load_bitmap("pegaBruxa.png");
	ALLEGRO_BITMAP* logoJogo = al_load_bitmap("logoJogo.png");
	ALLEGRO_BITMAP* fundoMenu = al_load_bitmap("fundoMenu.jpg");
 	ALLEGRO_BITMAP *tiro3 = al_load_bitmap("LaserSprites/08.png");
    ALLEGRO_BITMAP *tiro4 = al_load_bitmap("PROJECTIL1.png");
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);																																					
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();																																				 
	ALLEGRO_FONT* font =  al_load_font("Barbie.ttf", 45, 0);																																					
	ALLEGRO_DISPLAY* disp = al_create_display(X_SCREEN, Y_SCREEN);																																		
 	ALLEGRO_BITMAP *tiro1 = al_load_bitmap("LaserSprites/10.png");
    ALLEGRO_BITMAP *tiro2 = al_load_bitmap("LaserSprites/02.png");
	ALLEGRO_BITMAP *ataque1_bitmap = al_load_bitmap("crystal_01e.png");
    ALLEGRO_BITMAP *ataque2_bitmap = al_load_bitmap("shard_01j.png");
    ALLEGRO_BITMAP *tiro = al_load_bitmap("LaserSprites/06.png");
    ALLEGRO_BITMAP *tiroLaser = al_load_bitmap("LaserSprites/23.png");

// Carregar as imagens de cada frame da animação
    ALLEGRO_BITMAP *frames[NUM_FRAMES];
    for (int i = 0; i < NUM_FRAMES; i++) {
        char filename[50];
        sprintf(filename, "nave/planeK-anim%d.png", i); // Nome dos arquivos dos frames
        frames[i] = al_load_bitmap(filename);
        if (!frames[i]) {
            return -1;
        }
    }
	ALLEGRO_BITMAP *imgInimigo1[4];
	for (int i = 0; i < 4; i++) {
        char filename[50];
        sprintf(filename, "1/wingbot%d.png", i); // Nome dos arquivos dos frames
        imgInimigo1[i] = al_load_bitmap(filename);
        if (!imgInimigo1[i]) {
            return -1;
        }
    }

	ALLEGRO_BITMAP *imgInimigo2[4];
	for (int i = 0; i < 4; i++) {
        char filename[50];
        sprintf(filename, "img-inimigo1/enemy1idle%d.png", i); // Nome dos arquivos dos frames
        imgInimigo2[i] = al_load_bitmap(filename);
        if (!imgInimigo2[i]) {
            return -1;
        }
    }


	ALLEGRO_BITMAP *imgInimigo4[4];
	for (int i = 0; i < 4; i++) {
        char filename[50];
        sprintf(filename, "drone1/drone1-export%d.png", i); // Nome dos arquivos dos frames
        imgInimigo4[i] = al_load_bitmap(filename);
        if (!imgInimigo4[i]) {
            return -1;
        }
    }
	ALLEGRO_BITMAP *imgInimigo3[4];
	for (int i = 0; i < 4; i++) {
        char filename[50];
        sprintf(filename, "drone2/drone2-export%d.png", i); // Nome dos arquivos dos frames
        imgInimigo3[i] = al_load_bitmap(filename);
        if (!imgInimigo3[i]) {
            return -1;
        }
    }
	ALLEGRO_BITMAP *img_boss1[5];
	for (int i = 0; i < 5; i++) {
        char filename[50];
        sprintf(filename, "boss/monster1-export%d.png", i); // Nome dos arquivos dos frames
        img_boss1[i] = al_load_bitmap(filename);
        if (!img_boss1[i]) {
            return -1;
        }
    }


	ALLEGRO_BITMAP *img_boss2anda[6];
		for (int i = 0; i < 6; i++) {
			char filename[50];
			sprintf(filename, "Witch/Sprite/IDLE%d.png", i); // Nome dos arquivos dos frames
			img_boss2anda[i] = al_load_bitmap(filename);
			if (!img_boss2anda[i]) {
				return -1;
			}
		}

	//coracao
	ALLEGRO_BITMAP *gif_frames[12];
    for (int i = 0; i < 11; i++) {
        char filename[50];
        sprintf(filename, "coracao/frame_%d.png", i); // Nome dos arquivos dos frames
        gif_frames[i] = al_load_bitmap(filename);
        if (!gif_frames[i]) {
            return -1;
        }
    }

	
    ALLEGRO_BITMAP* background = al_load_bitmap("8.png");
    if (!background) return -1;
	int background_width = al_get_bitmap_width(background);
    ALLEGRO_BITMAP* background2 = al_load_bitmap("7.png");
	int background_width2 = al_get_bitmap_width(background2);

/*--------------------------------------------------INICIALIZACAO-------------------*/

	al_register_event_source(queue, al_get_keyboard_event_source());																																	
	al_register_event_source(queue, al_get_display_event_source(disp));																																	
	al_register_event_source(queue, al_get_timer_event_source(timer));	
	ALLEGRO_EVENT event;																																												
	al_start_timer(timer);	

	square* player_1 = square_create(70, 1, 20, Y_SCREEN/2, X_SCREEN+20, Y_SCREEN+40);																															
	if (!player_1) return 1;																																												
	
	Boss* boss1 = iniciaBoss1();
	Boss* boss2 = iniciaBoss2();
	Boss* boss2_2 = iniciaBoss2_2();


	Inimigo** inimigo1 = iniciaInimigo1(NUM_INIMIGOS);
	Inimigo** inimigo2 = iniciaInimigo2(NUM_INIMIGOS);
	Inimigo** inimigo3 = iniciaInimigo3(NUM_INIMIGOS);
	Inimigo** inimigo4 = iniciaInimigo4(NUM_INIMIGOS);

	Inimigo** inimigoAux1 = NULL; 
	Inimigo** inimigoAux2 = NULL;


	/*--------------------------------------------------COMECO-------------------*/

	while(jogo_rodando==-1){	
		al_wait_for_event(queue, &event);  // Espera por eventos

		if (event.type == ALLEGRO_EVENT_TIMER) {
			desenharTela1(&jogo_rodando, ken_image ,barbie_image , witch_image ,  background_image ,oibarbie, oiken , barbie_bruxalevouken,&tempo_falas_restante,&ken_x,&ken_y,&ken_hit) ;
		}
	}
   // Chamar o menual_wait_for_event(queue, &event);  // Espera por eventos

	if (event.type == ALLEGRO_EVENT_TIMER) {
		MenuOption selected_option = display_menu(disp, font,event,queue,fundoMenu,logoJogo);

		// Verificar a opção selecionada
		if (selected_option == MENU_START_GAME) {
			//printf("Jogo iniciado!\n");
			// Aqui você implementaria a lógica do jogo
		} else if (selected_option == MENU_EXIT_GAME) {
			jogo_rodando = -2;																																					
		}
	}


	while(jogo_rodando==0){	
		al_wait_for_event(queue, &event);  // Espera por eventos

		if (event.type == ALLEGRO_EVENT_TIMER) {
			desenharTela2(&jogo_rodando,barbie_image,  background_image, &tempo_falas, naveBarbie) ;
		}	
	}
	tempo_falas = TEMPO_FALAS;
/*------------------------------------------------------------------------------JOGO RODANDO-------------------*/

	while(jogo_rodando>0){	

		al_wait_for_event(queue, &event);	
		if(event.type == ALLEGRO_EVENT_TIMER) {
			/*------------------------------------------------------------------------------ORGANIZACAO DO JOGO-------------------*/

			// Atualizar o tempo da fase
			time_fase--;
			// Lógica para fase 1
			if (fase == 1 && time_fase <= 0) {
				boss1->ativo = 1; // Ativa o Boss 1
			}
			if (time_fase <= 0 && fase == 2 ) {
					boss2->ativo = 1; // Ativa o Boss 2 após o intervalo
				} 
			// Verificar se o Boss 2 foi derrotado
			if (boss2->hp <= 0) {
				//jogo_rodando = 0; // Termina o jogo
			}																				
			// Atualize a posição do background para criar efeito de rolagem
			bg_x -= bg_vel;
			if (bg_x <= -al_get_bitmap_width(background)) {
				bg_x = 0;  // Reseta a posição para o efeito contínuo
			}
			// Desenha o background
			if(fase==1){
				al_draw_bitmap(background, bg_x, 0, 0);
				al_draw_bitmap(background, bg_x + al_get_bitmap_width(background), 0, 0);
				inimigoAux1 = inimigo2;
				inimigoAux2 = inimigo4;
			}
			if(fase==2 ){
				al_draw_bitmap(background2, bg_x, 0, 0);
				al_draw_bitmap(background2, bg_x + al_get_bitmap_width(background2), 0, 0);		
		
				inimigoAux1 = inimigo1;
				inimigoAux2 = inimigo3;	
			}
			
			// Atualiza o frame
			atualizar_frame(&frame_nave, frame_delay, &frame_cont1, NUM_FRAMES);
			atualizar_frame(&coracao_frame, frame_delay_coracao, &frame_cont, 11);
			atualizar_frame(&frame_inim1, frame_delay_inim, &cont_inim1, 4);
			atualizar_frame(&frame_boss1, frame_delay_boss, &cont_boss1, 4);
			atualizar_frame(&frame_boss2, frame_delay_boss2, &cont_boss2, 6);
			atualizar_frame(&frame_barbieTriste,frame_delay_barbieTriste, &cont_barbieTriste, 23);


		}
			desenhar_hud(player_1->hp,gif_frames[frame_cont]);
			inicia_ataque_especial(player_1, ataqueEsp);
			check_collisao_ataque_especial(player_1, ataqueEsp);
			double tempo_corrido = al_get_time();
			shot_tiro_rapido(tempo_corrido, player_1->gun->shots, player_1);
			shot_laser(player_1, tiroLaser);
			//atualizaAtaque(ataqueEsp, player_1);
			update_laser(tempo_corrido,player_1);
			update_tiro(tempo_corrido,player_1);
			desenhaAtaque(player_1,ataqueEsp, ataque1_bitmap , ataque2_bitmap );
/*-----------------------------------------------------------------------------tela de ganha ou perde-------------------*/
		if ( player_1->hp <= 0 || boss2->hp<=0 ){																																												 
			al_clear_to_color(al_map_rgb(0, 0, 0));	
			if( player_1->hp <= 0){	
				desenharFimRuim(barbiesad,finalruim);
			
			}if(boss2->hp<=0){
				desenharFimBom(babiefeliz, salvei, kenSalvo ); ///
				
			}	
			
			al_draw_text(font, al_map_rgb(224, 33, 138), X_SCREEN/2, Y_SCREEN/2+300, ALLEGRO_ALIGN_CENTER, "Pressione espaco para sair");																					
			al_flip_display();																																												
					
			if ((event.type == 10) && (event.keyboard.keycode == 75)) break;																																
			else if (event.type == 42) break; 	
		}

		else if (event.type == 30){
			/*------------------------------------------------- ATAQUE ESPECIAL--------------------*/
			
		if (event.type == ALLEGRO_EVENT_TIMER) {
		
			update_position(player_1,frame_cont,frames);	
		if (boss1->ativo) {
			desenhar_hud_inimigo(boss1->hp, gif_frames[frame_cont]) ;
			DisparaTiroBoss(boss1, player_1, boss1->gun1);
			DisparaTiroBoss(boss1, player_1, boss1->gun2);
			atualizaBoss(boss1, player_1);
			check_kill_boss(boss1, player_1 ,boss1->gun1);		
			check_kill_boss(boss1, player_1,boss1->gun2);																																				
			check_kill_jogadorBoss(player_1,boss1);
			desenha_boss(boss1,boss2,img_boss1,img_boss2anda, cont_boss1,cont_boss2, 0,3);
			check_colisaoBoss(player_1,boss1);
			desenhabalaBoss(boss1,tiro3,tiro4);  
			// Verificar se o Boss foi derrotado
			if (boss1->hp <= 0) {
				boss1->ativo = 0;  // Desativar o Boss
				fase++; 
				if(transicao_em_andamento) 
					desenharTela3(player_1,font,barbie_image,background_image,transicao_em_andamento, queue, event, pegaBruxa ); ///
           // Avançar para a próxima fase
					time_fase = 2000;
			}
		}
		if (boss2->ativo) {

			desenhar_hud_inimigo(boss2->hp, gif_frames[frame_cont]) ;
			DisparaTiroBoss(boss2, player_1, boss2->gun1);
			DisparaTiroBoss(boss2, player_1, boss2->gun2);
			atualizaBoss(boss2, player_1);
			check_kill_boss(boss2, player_1 ,boss2->gun1);		
			check_kill_boss(boss2, player_1,boss2->gun2);																																				 
			check_kill_jogadorBoss(player_1,boss2);
			desenha_boss(boss1,boss2,img_boss1,img_boss2anda, cont_boss1,cont_boss2, 0,3);
			check_colisaoBoss(player_1,boss2);
			desenhabalaBoss(boss2,tiro3,tiro4);  
			if(boss2->hp <= 5){
				boss2_2->ativo = 1;
			}
		}
		if (boss2_2->ativo) {
			boss2_2->duplicado = 1;
			DisparaTiroBoss(boss2_2, player_1, boss2_2->gun1);
			DisparaTiroBoss(boss2_2, player_1, boss2_2->gun2);
			atualizaBoss(boss2_2, player_1);
			// Desenhar o Boss 1 na tela
			// Verificar colisões com o Boss
			check_kill_boss(boss2_2, player_1 ,boss2_2->gun1);		
			check_kill_boss(boss2_2, player_1,boss2_2->gun2);																																				
			check_kill_jogadorBoss(player_1,boss2_2);
			desenha_boss2(boss1,boss2_2,img_boss1,img_boss2anda, cont_boss1,cont_boss2, 0,3);
			check_colisaoBoss(player_1,boss2_2);
			desenhabalaBoss22(boss2_2,tiro4);
		}
		if(!boss1->ativo && !boss2->ativo && !boss2_2->ativo){
			check_kill_jogador(player_1,inimigoAux1, NUM_INIMIGOS);	
			check_kill_inimigo(inimigoAux1,player_1, NUM_INIMIGOS);	
			check_kill_jogador(player_1,inimigoAux2, NUM_INIMIGOS);	
			check_kill_inimigo(inimigoAux2, player_1,NUM_INIMIGOS);
			DisparaTiro( inimigoAux1, NUM_INIMIGOS,player_1);
			DisparaTiro( inimigoAux2, NUM_INIMIGOS,player_1);
			//update_enemy_positions(inimigoAux2,NUM_INIMIGOS ,X_SCREEN,Y_SCREEN	);
			atualizaInimigo( inimigoAux1,NUM_INIMIGOS,player_1);
			atualizaInimigo( inimigoAux2,NUM_INIMIGOS,player_1);
			check_colisao(player_1,inimigoAux1, NUM_INIMIGOS);
			check_colisao(player_1,inimigoAux2, NUM_INIMIGOS);	
		}
			
		// Desenha o frame atual na tela
		desenha_player(player_1, frames, frame_cont1, player_1->control->left); // Renderiza a nave
		
		if(!boss1->ativo && !boss2->ativo){
			desenha_inimigo(player_1,inimigoAux1,inimigoAux2, imgInimigo1,imgInimigo2,imgInimigo3,imgInimigo4, cont_inim1,NUM_INIMIGOS,0); // Renderiza a nave
			desenhabala(inimigoAux1,NUM_INIMIGOS, tiro1, tiro2);
		}

		// desenha bala do jogador
		if (!player_1->laser_ativo){
			for (bullet *index = player_1->gun->shots; index != NULL; index = (bullet*) index->next){
				// Desenha o tiro com escala reduzida
				al_draw_scaled_bitmap(tiro, 0, 0, al_get_bitmap_width(tiro), al_get_bitmap_height(tiro), index->x-0.5, index->y-5, al_get_bitmap_width(tiro) * escala_x, al_get_bitmap_height(tiro) * escala_y, 0);
				// Desenha novamente o tiro com a mesma esvcala
				al_draw_scaled_bitmap(tiro, 0, 0, al_get_bitmap_width(tiro), al_get_bitmap_height(tiro), index->x-0.5, index->y - 50, al_get_bitmap_width(tiro) * escala_x,al_get_bitmap_height(tiro) * escala_y, 0); 			
			}	 								
			if (player_1->gun->timer) player_1->gun->timer--;	
		}	
		
		// Desenhar o tempo restante
		
		if(!boss1->ativo &&!boss2->ativo){
			desenha_time(font, time_fase);
		
		}
		al_flip_display();					
			}
		} else if ((event.type == 10) || (event.type == 12)){																																																					
			if (event.keyboard.keycode == 1) joystick_left(player_1->control);																															
			else if (event.keyboard.keycode == 4) joystick_right(player_1->control);																													
			else if (event.keyboard.keycode == 23) joystick_up(player_1->control);																														
			else if (event.keyboard.keycode == 19) joystick_down(player_1->control);																												
			else if (event.keyboard.keycode == 3) joystick_fire(player_1->control);																																		
		
		} else if (event.type == 42) break;	
		// Limpa a tela para o próximo frame																																											
	}
/*----------------------------------------------------------------------------Destrói------------------*/
	for (int i = 0; i < 11; i++) {
        al_destroy_bitmap(gif_frames[i]);
    }
	for (int i = 0; i < NUM_FRAMES; i++) {
        al_destroy_bitmap(frames[i]);
    }
	for (int i = 0; i < 4; i++) {
        al_destroy_bitmap(imgInimigo1[i]);
    }
	for (int i = 0; i < 4; i++) {
        al_destroy_bitmap(imgInimigo2[i]);
    }
	for (int i = 0; i < 4; i++) {
        al_destroy_bitmap(imgInimigo3[i]);
    }
	for (int i = 0; i < 4; i++) {
        al_destroy_bitmap(imgInimigo4[i]);
    }
	for (int i = 0; i < 5; i++) {
        al_destroy_bitmap(img_boss1[i]);
    }
	for (int i = 0; i < 6; i++) {
        al_destroy_bitmap(img_boss2anda[i]);
    }

	square_destroy(player_1);																																												

	liberaBoss(boss1);
	liberaBoss(boss2);
	liberaBoss(boss2_2);
   // finaliza_menu(menu);
	al_destroy_bitmap(kenSalvo);
	al_destroy_bitmap(salvei);
	al_destroy_bitmap(naveBarbie);
	al_destroy_bitmap(finalruim);
	al_destroy_bitmap(logoJogo);
	al_destroy_bitmap(fundoMenu);

	al_destroy_bitmap(tiro);
	al_destroy_bitmap(pegaBruxa);
    al_destroy_bitmap(ataque1_bitmap);
    al_destroy_bitmap(ataque2_bitmap);
    al_destroy_bitmap(background);
    al_destroy_bitmap(background2);
	al_destroy_bitmap(babiefeliz);
	al_destroy_font(font);																																													
	al_destroy_timer(timer);																																												
	al_destroy_event_queue(queue);																																											
	liberaInimigos(inimigo1,NUM_INIMIGOS);																													
	liberaInimigos(inimigo2,NUM_INIMIGOS);																													
	liberaInimigos(inimigo3,NUM_INIMIGOS);																													
	liberaInimigos(inimigo4,NUM_INIMIGOS);																													
	al_destroy_display(disp);																																												
	al_destroy_bitmap(barbie_image);
	al_destroy_bitmap(ken_image);
	al_destroy_bitmap(witch_image);
	al_destroy_bitmap(background_image);
	al_destroy_bitmap(oibarbie);
	al_destroy_bitmap(oiken);
	al_destroy_bitmap(barbie_bruxalevouken);
	al_destroy_bitmap(tiro1);
	al_destroy_bitmap(tiro2);
	al_destroy_bitmap(tiro3);
	al_destroy_bitmap(tiro4);
	al_destroy_bitmap(tiroLaser);


}