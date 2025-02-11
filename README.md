O jogo é versão alternativa do Space Impact, particularmente baseada no Space Impact 303
 desenvolvido em C utilizando a biblioteca Allegro 5. O jogo apresenta uma nave controlável pelo jogador, enfrentando inimigos e chefes em um ambiente dinâmico e desafiador. O jogo inclui animações, ataques especiais e um sistema de fases progressivo.
 
Dependências
Para compilar e executar o jogo, é necessário instalar a biblioteca Allegro 5. No Linux, você pode instalar as dependências com o seguinte comando:
sudo apt-get install liballegro5-dev

Compilação
Para compilar o jogo, utilize o seguinte comando:
gcc AggressiveSquares.c Square.c Joystick.c Bullet.c Pistol.c ataqueEspecial.c inimigo.c menu.c boss.c -o AS $(pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_primitives-5 allegro_image-5 --libs --cflags) -lm

Execução
Após compilar, execute o jogo com:
./AS

Controles
Setas direcionais: Movem a nave
Barra de espaço: Atira
Tecla especial c : Ativa o ataque especial
Esc: Sai do jogo

Estrutura do Projeto
O projeto está dividido nos seguintes módulos:
AggressiveSquares.c: Arquivo principal que gerencia o loop do jogo
Square.c: Implementa a lógica do jogador
Joystick.c: Gerencia a entrada do teclado
Bullet.c: Controla os tiros do jogador
Pistol.c: Define as armas e tiros
ataqueEspecial.c: Implementa os ataques especiais
inimigo.c: Gerencia a IA dos inimigos
menu.c: Gerencia o menu inicial
boss.c: Controla os chefes do jogo

Recursos

Gráficos: Imagens de sprites carregadas dinamicamente
Animação: Quadros de animação para naves e inimigos
Som: Suporte para efeitos sonoros (se adicionado futuramente)
Progressão de fases: O jogo avança conforme o jogador elimina inimigos e chefes

Melhorias Futuras

Adição de múltiplos modos de jogo
Implementação de efeitos sonoros
Otimização de desempenho
Novos inimigos e padrões de ataque

Autor
Desenvolvido por Emanuele Fernanda Ferraz de Araújo
