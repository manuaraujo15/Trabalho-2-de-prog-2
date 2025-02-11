#include "hud.h"

void desenha_time(ALLEGRO_FONT *font, int time_left) {
    char time_text[32];
    sprintf(time_text, "Tempo: %d", time_left);
    al_draw_text(font, al_map_rgb(255, 255, 255), X_SCREEN / 2, 10, ALLEGRO_ALIGN_CENTER, time_text);
}

void desenhar_hud(int hp, ALLEGRO_BITMAP *gif_frames) {
	if(hp>0){
    for (int i = 0; i <hp; i++) {
        // Desenhe os corações com base no HP restante
     al_draw_scaled_bitmap(gif_frames, 0, 0, al_get_bitmap_width(gif_frames), al_get_bitmap_height(gif_frames),   i * (al_get_bitmap_width(gif_frames) * 1,5 + 35), 0,al_get_bitmap_width(gif_frames) * 0.15+2, al_get_bitmap_height(gif_frames) * 0.15, 0);																					                                                           //Função que captura eventos da fila, inserindo os mesmos na variável de eventos
		}	
    }
}
void desenhar_hud_inimigo(int hp, ALLEGRO_BITMAP *gif_frames) {
    // Definir a margem esquerda para os corações no canto superior direito
    int margin_right =  1.5;  // A distância do canto direito da tela onde os corações começam
    int heart_width = al_get_bitmap_width(gif_frames) * 0.15;  // Largura do coração
    int heart_height = al_get_bitmap_height(gif_frames) * 0.15; // Altura do coração
    int total_width = heart_width * hp + margin_right * (hp - 1); // Largura total necessária para desenhar todos os corações
    
    // Posição do primeiro coração a partir do lado direito
    int start_x = X_SCREEN - total_width; // Coloca os corações no canto superior direito

    // Desenhar os corações com base no HP restante
    for (int i = 0; i < hp; i++) {
        // Desenha o coração com um espaçamento entre eles
        al_draw_scaled_bitmap(gif_frames, 0, 0, al_get_bitmap_width(gif_frames), al_get_bitmap_height(gif_frames), start_x + i * (heart_width + margin_right), 0, heart_width, heart_height, 0);
    }
}
// Tempo de exibição das falas (em segundos)

void atualizar_frame(int *frame_atual, int frame_delay, int *contador, int total_quadros) {
    if (*frame_atual >= frame_delay) {
        *contador = (*contador + 1) % total_quadros; // Avança para o próximo frame
        *frame_atual = 0; // Reseta o contador de frames
    } else {
        (*frame_atual)++; // Incrementa o contador de frames
    }
}
void desenharTela1(int *jogo_rodando, ALLEGRO_BITMAP* ken_image, ALLEGRO_BITMAP* barbie_image, ALLEGRO_BITMAP* witch_image, 
ALLEGRO_BITMAP* background_image, ALLEGRO_BITMAP* oibarbie, ALLEGRO_BITMAP* oiken, ALLEGRO_BITMAP* barbie_bruxalevouken, 
float *tempo_falas_restante, float *ken_x, float *ken_y, int *ken_hit) {

    // Carregar imagens
    int largura_imagem = al_get_bitmap_width(background_image);
    int altura_imagem = al_get_bitmap_height(background_image);
    int width2 = al_get_bitmap_width(witch_image);
    int height2 = al_get_bitmap_height(witch_image);

    // Desenhar fundo
    al_draw_scaled_bitmap(background_image, 0, 0, largura_imagem, altura_imagem, 0, 0, X_SCREEN, Y_SCREEN, 0);

    // Desenhar personagens
    al_draw_bitmap(barbie_image, 1300, 200, 0);
    al_draw_bitmap(ken_image, *ken_x, *ken_y, 0);

    // Inicializa a posição da bruxa
     float witch_x = (X_SCREEN / 2) - (width2 * 2.5);  // Posição inicial da bruxa no meio da tela
     float witch_y = -height2;  // A bruxa começa fora da tela, acima

    // Lógica do jogo
    if (*tempo_falas_restante > 0) {
        *tempo_falas_restante -= 1.0 / 60; // Decrementa temporizador
        al_draw_bitmap(oiken, 900, 100, 0);
        al_draw_bitmap(oibarbie, *ken_x + 100, *ken_y - 100, 0);
        *ken_hit = 1; // Simula Ken atingido
    } else {
        // A bruxa começa a descer até o Ken
        

        // Depois que a bruxa chega no Ken, ela segue com ele
        if (*ken_x + al_get_bitmap_width(ken_image) >= 0) {
            *ken_x -= 2;  // Velocidade horizontal do Ken
            *ken_y += 2;  // Velocidade vertical do Ken
            al_draw_bitmap(barbie_bruxalevouken, 900, 100, 0);
            
            // A bruxa vai seguir o Ken enquanto ele se move
            al_draw_scaled_bitmap(witch_image, 0, 0, width2, height2, *ken_x - 400, *ken_y - 200, width2 * 5, height2 * 5, 0);
        } else {
            *jogo_rodando = 0; // Sinaliza fim do jogo
        }
    }

    // Atualiza tela
    al_flip_display();
}

void desenharTela2( int *jogo_rodando,ALLEGRO_BITMAP* barbie_image, 
ALLEGRO_BITMAP* background_image, float *tempo_falas,ALLEGRO_BITMAP* naveBarbie) {
	int largura_imagem = al_get_bitmap_width(background_image);
    int altura_imagem = al_get_bitmap_height(background_image);

    // Desenhar fundo
	if (*tempo_falas > 0) {
		al_draw_scaled_bitmap(background_image, 0, 0, largura_imagem, altura_imagem, 0, 0, X_SCREEN, Y_SCREEN, 0);
    // Desenhar personagens
    	al_draw_bitmap(barbie_image, 1300, 200, 0);
		al_draw_bitmap(naveBarbie, 800, 0, 0);

        *tempo_falas -= 1.0 / 60; // Decrementa temporizador

	}else
		*jogo_rodando = 1;

	al_flip_display();

}
void desenharTela3(square* player,  ALLEGRO_FONT* font,ALLEGRO_BITMAP* barbie_image, ALLEGRO_BITMAP* background_image, int transicao_em_andamento, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_EVENT event,ALLEGRO_BITMAP* pegaBruxa  ) {
	int largura_imagem = al_get_bitmap_width(background_image);
    int altura_imagem = al_get_bitmap_height(background_image);

    // Desenhar fundo
	al_draw_scaled_bitmap(background_image, 0, 0, largura_imagem, altura_imagem, 0, 0, X_SCREEN, Y_SCREEN, 0);

    // Desenhar personagens
	al_draw_bitmap(barbie_image, 1300, 200, 0);
	al_draw_bitmap(pegaBruxa, 800, 0, 0);
	al_draw_text(font, al_map_rgb(224, 33, 138), X_SCREEN/2, Y_SCREEN/2+300, ALLEGRO_ALIGN_CENTER, "Pressione c para continuar");	
    al_flip_display(); // Exibe a tela de transição

 	// Bloqueia o código aqui até o evento de transição ser concluído
    while (transicao_em_andamento) {
	 	al_wait_for_event(queue, &event);  // Espera por eventos

        // Espera por um evento de tecla para continuar
		if ((event.type == 10) &&  (event.keyboard.keycode == 3))  {
			


			transicao_em_andamento = 0; 
			al_flip_display();
		}
    }
	al_flip_display();
}

void desenharFimBom(ALLEGRO_BITMAP* background_image,ALLEGRO_BITMAP* salvei, ALLEGRO_BITMAP* kenSalvo ) {
	int largura_imagem = al_get_bitmap_width(background_image);
    int altura_imagem = al_get_bitmap_height(background_image);
    // Desenhar fundo
	al_draw_scaled_bitmap(background_image, 0, 0, largura_imagem, altura_imagem, 0, 0, X_SCREEN, Y_SCREEN, 0);

    // Desenhar personagens
    al_draw_bitmap(salvei, 1200, 50, 0);
	al_draw_bitmap(kenSalvo,50, 50, 0);

}


void desenharFimRuim(ALLEGRO_BITMAP* barbie_image, ALLEGRO_BITMAP* finalruim ) {
	int largura_imagem = al_get_bitmap_width(barbie_image);
    int altura_imagem = al_get_bitmap_height(barbie_image);
    // Desenhar fundo
	al_draw_scaled_bitmap(barbie_image, 0, 0, largura_imagem, altura_imagem, 0, 0, X_SCREEN, Y_SCREEN, 0);


    // Desenhar personagens
 	al_draw_bitmap(finalruim, 30, 100, 0);

}
