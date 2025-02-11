#include "menu.h"


MenuOption display_menu(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE* event_queue,ALLEGRO_BITMAP* fundoMenu,ALLEGRO_BITMAP* logoJogo ) {
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    MenuOption option = MENU_START_GAME;
    int rodando = 1;
    int largura_imagem = al_get_bitmap_width(fundoMenu);
    int altura_imagem = al_get_bitmap_height(fundoMenu);
    while (rodando) {
        // Desenhar o menu
        

        if (option == MENU_START_GAME) {
            al_draw_scaled_bitmap(fundoMenu, 0, 0, largura_imagem, altura_imagem, 0, 0, X_SCREEN, Y_SCREEN, 0);
            al_draw_bitmap(logoJogo, 400, 100, 0);

            al_draw_text(font, al_map_rgb(255, 255, 255), X_SCREEN/2, Y_SCREEN/2, ALLEGRO_ALIGN_CENTER, "-> Iniciar Jogo");
            al_draw_text(font, al_map_rgb(150, 150, 150), X_SCREEN/2, Y_SCREEN/2+100, ALLEGRO_ALIGN_CENTER, "Sair");
        } else {
            al_draw_scaled_bitmap(fundoMenu, 0, 0, largura_imagem, altura_imagem, 0, 0, X_SCREEN, Y_SCREEN, 0);
            al_draw_bitmap(logoJogo, 400, 100, 0);

            al_draw_text(font, al_map_rgb(150, 150, 150), X_SCREEN/2, Y_SCREEN/2, ALLEGRO_ALIGN_CENTER, "Iniciar Jogo");
            al_draw_text(font, al_map_rgb(255, 255, 255), X_SCREEN/2, Y_SCREEN/2+100, ALLEGRO_ALIGN_CENTER, "-> Sair");
        }

        al_flip_display();

        // Processar eventos
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    option = MENU_START_GAME;
                    break;

                case ALLEGRO_KEY_DOWN:
                    option = MENU_EXIT_GAME;
                    break;

                case ALLEGRO_KEY_ENTER:
                    rodando = 0;
                    event.type = 42;
                    break;

                case ALLEGRO_KEY_ESCAPE:
                    option = MENU_EXIT_GAME;
                    event.type = 42;
                    rodando = 0;
                    break;
            }
        }
    }

    return option;
}