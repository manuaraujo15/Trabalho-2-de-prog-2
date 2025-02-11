#ifndef MENU_H
#define MENU_H
#include <allegro5/allegro5.h>																																											
#include <allegro5/allegro_font.h>																																										
#include <allegro5/allegro_primitives.h>																																								
#include <allegro5/allegro_image.h> // Biblioteca para carregar imagens
#include <allegro5/allegro_ttf.h>
#define X_SCREEN 576*3																																									
#define Y_SCREEN 324*3	
// Enum para representar as opções do menu
typedef enum {
    MENU_START_GAME,
    MENU_EXIT_GAME
} MenuOption;

// Declaração da função do menu
MenuOption display_menu(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font,ALLEGRO_EVENT event,ALLEGRO_EVENT_QUEUE* queue,ALLEGRO_BITMAP* fundoMenu,ALLEGRO_BITMAP* logoJogo );

#endif