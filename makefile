TARGET = AS
SOURCES = AggressiveSquares.c Square.c Joystick.c Bullet.c Pistol.c ataqueEspecial.c inimigo.c menu.c boss.c hud.c
ALLEGRO_FLAGS = $(shell pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_primitives-5 allegro_image-5   allegro_ttf-5 --libs --cflags) -lm


all:
	gcc $(SOURCES) -o $(TARGET) $(ALLEGRO_FLAGS)
# Regra para limpar arquivos gerados
clean:
	@echo "Cleaning up..."
	rm -f $(TARGET) $(SOURCES:.c=.o)

.PHONY: clean