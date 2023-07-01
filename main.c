#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define PECA_TAM 2

#define QUADRO_TAM 5
#define SLOTS_TAM 3

#define ANUNCIOS_TAM 10
#define ANUNCIOS_TEXTO_TAM 100

#define RECORDES_TAM 10

#define DADOS_NUM 7
#define CORES_NUM 6

#define BALOES_NUM 4

#define COLAPSO_FRAMES_NUM 8
#define COLAPSO_FRAME_PERIODO 2
#define COLAPSO_ATRASO (3 * COLAPSO_FRAME_PERIODO)

#define EXPLOSAO_FRAMES_NUM 10
#define EXPLOSAO_FRAME_PERIODO 2

#define SOMAS_TAM (2 * QUADRO_TAM)

#define RESERVA_AUDIO 128

#define ROTACAO_CICLO 4

#define MARGEM_PEQUENA 8
#define MARGEM_MEDIA 16
#define MARGEM_GRANDE 24

#define INICIO_BOTOES_ESPACO 2

#define PLACAR_CONTEUDO_ESPACO 1
#define PLACAR_COLUNAS_ESPACO 16

#define AJUDA_CONTROLES_ESPACO 4

#define PAUSA_TITULO_ESPACO 12
#define PAUSA_BOTOES_ESPACO 1

#define GAME_OVER_TITULO_ESPACO 12
#define GAME_OVER_MENU_ESPACO 24

#define HABILIDADE_PROGRESSO_ESPACO 2
#define HABILIDADE_QUANTIDADE_ESPACO 4

#define HABILIDADES_ESPACO 4

#define DADOS_ESPACO 1
#define BALAO_ESPACO 1
#define SLOTS_ESPACO 1

#define ANUNCIO_BONUS_ESPACO 3
#define ANUNCIO_BONUS_PREENCHIMENTO 2

#define ANUNCIO_BONUS_RAIO 2

#define LARGURA_ORIGINAL 320
#define ALTURA_ORIGINAL 180

#define DECORACAO_CENTRO_L 126
#define DECORACAO_PADRAO_L 91
#define DECORACAO_H 11

#define BOTAO_VOLTAR_L 22
#define BOTAO_VOLTAR_H 18

#define INICIO_TITULO_L 140
#define INICIO_TITULO_H 32

#define INICIO_BOTAO_MENU_L 70
#define INICIO_BOTAO_MENU_H 23

#define INICIO_BOTAO_MARCADOR_L 23
#define INICIO_BOTAO_MARCADOR_H 19

#define PLACAR_TITULO_L 80
#define PLACAR_TITULO_H 14

#define PLACAR_RELOGIO_L 25
#define PLACAR_RELOGIO_H 13

#define AJUDA_TITULO_L 66
#define AJUDA_TITULO_H 14

#define AJUDA_SETA_L 19
#define AJUDA_SETA_H 9

#define PAUSA_TITULO_L 80
#define PAUSA_TITULO_H 20

#define PAUSA_BOTAO_MENU_L 73
#define PAUSA_BOTAO_MENU_H 14

#define PAUSA_H (PAUSA_TITULO_H + PAUSA_TITULO_ESPACO + 4 * PAUSA_BOTAO_MENU_H + 3 * PAUSA_BOTOES_ESPACO)

#define GAME_OVER_TITULO_L 138
#define GAME_OVER_TITULO_H 20

#define GAME_OVER_BOTAO_L 85
#define GAME_OVER_BOTAO_H 14

#define GAME_OVER_INFORMACAO_H 12

#define GAME_OVER_L GAME_OVER_TITULO_L
#define GAME_OVER_H (GAME_OVER_TITULO_H + GAME_OVER_TITULO_ESPACO + 2 * GAME_OVER_INFORMACAO_H + GAME_OVER_MENU_ESPACO)

#define HABILIDADE_BOTAO_L 16
#define HABILIDADE_BOTAO_H 17

#define FUNDO_PROGRESSO_L 3
#define FUNDO_PROGRESSO_H 17

#define DADO_L 24
#define DADO_H 25

#define SLOT_L 51
#define SLOT_H 53

#define BOTAO_ROTACIONAR_L 14
#define BOTAO_ROTACIONAR_H 15

#define QUADRO_L (QUADRO_TAM * (DADO_L + DADOS_ESPACO))
#define QUADRO_H (QUADRO_TAM * (DADO_H + DADOS_ESPACO))

#define BALAO_HORIZONTAL_L 19
#define BALAO_HORIZONTAL_H 11

#define BALAO_VERTICAL_L 17
#define BALAO_VERTICAL_H 14

#define BOTAO_PAUSAR_L 16
#define BOTAO_PAUSAR_H 16

#define BOTAO_VOLTAR_OFFSET_CIMA 14

#define INICIO_BOTOES_OFFSET_CIMA (MARGEM_MEDIA + INICIO_TITULO_H + 20)

#define HABILIDADE_PROGRESSO_ALTURA 15
#define HABILIDADE_PROGRESSO_OFFSET_DIREITA 2
#define HABILIDADE_PROGRESSO_OFFSET_CIMA 15

#define QUADRO_OFFSET_DIREITA 24

#define BALAO_HORIZONTAL_OFFSET_DIREITA 1
#define BALAO_HORIZONTAL_OFFSET_CIMA 12

#define BALAO_VERTICAL_OFFSET_DIREITA 9
#define BALAO_VERTICAL_OFFSET_CIMA 1

#define BOTAO_ROTACIONAR_OFFSET_DIREITA 8
#define BOTAO_PAUSAR_OFFSET_CIMA (MARGEM_PEQUENA + 30)

#define ESCORE_OFFSET_CIMA 3
#define TEMPO_OFFSET_CIMA 26

#define PLACAR_LISTA_MARGEM_CIMA (2 * MARGEM_MEDIA + PLACAR_TITULO_H)
#define PLACAR_LISTA_MARGEM_BAIXO MARGEM_GRANDE

#define PLACAR_LINHAS 5
#define PLACAR_COLUNAS 2

#define PLACAR_LINHA_GROSSURA 1

#define BALAO_0_LIMITE 6
#define BALAO_1_LIMITE 9
#define BALAO_2_LIMITE 10

#define CENA_INICIO 0
#define CENA_PLACAR 1
#define CENA_AJUDA 2
#define CENA_JOGO 3

#define ESTADO_RODANDO 0
#define ESTADO_PAUSADO 1
#define ESTADO_GAME_OVER 2

#define SEM_DIRECAO -1
#define DIRECAO_LINHA 0
#define DIRECAO_COLUNA 1

#define DIRECOES_NUM 2

#define ANIMACAO_PARADO 0
#define ANIMACAO_COLAPSO 1
#define ANIMACAO_EXPLOSAO 2

#define SOMA_ALVO 10

#define PONTOS_DADO 1
#define PONTOS_COMBO 5
#define PONTOS_MULTILINHA 7
#define PONTOS_TABULEIRO_CONCLUIDO 10

#define DESFAZER_TABULEIROS_CONCLUIDOS 5
#define BOMBA_COMBINACOES 10
#define ROTACAO_PONTOS 50

#define PREMIO_MULTILINHA 0
#define PREMIO_COMBO 1
#define PREMIO_TABULEIRO_CONCLUIDO 2

#define ANUNCIO_DURACAO_TOTAL 200
#define ANUNCIO_DURACAO_FADE 10

#define COR_PRETO al_map_rgb(0, 0, 0)
#define COR_BRANCO al_map_rgb(255, 255, 255)
#define COR_TRANSPARENTE al_map_rgba(0, 0, 0, 0)
#define COR_PLACAR_LINHA al_map_rgb(255, 185, 185)
#define COR_PLACAR_TEMPO al_map_rgb(32, 232, 32)
#define COR_HABILIDADE_PROGRESSO al_map_rgb(121, 240, 8)
#define COR_ANUNCIO al_map_rgb(112, 0, 255)
#define COR_SOBREPOSICAO al_map_rgba(0, 0, 0, 210)

#define ARQUIVO_RECORDES "data/recordes.txt"
#define ARQUIVO_SAVE "data/save.txt"

#define DADO_VAZIO -1

#define PERIODO_TICK (1.0 / 60.0)

const char *PAGINAS_AJUDA[] = {
	"Como jogar?\n"
	"- Arraste os dados para o tabuleiro utilizando o mouse.\n"
	"- Forme somas de 10 em linhas ou em colunas para limpar e ganhar pontos.\n"
	"- O jogo acaba quando nao ha mais nenhum movimento possivel.\n",

	"Pontos:\n"
	"- +1 ponto para cada dado eliminado.\n\n"
	"- combo: +5 pontos por eliminacao de linhas ou de colunas em sequencia devido a eliminacao de uma anterior.\n\n"
	"- multilinha: +7 pontos por eliminacao de varias linhas ou colunas simultaneamente ao posicionar os dados.\n\n"
	"- tabuleiro concluido: +10 pontos sempre que todo o tabuleiro for limpo.\n\n",

	"Habilidades:\n"
	"- rotacao: gire os dados de um cojunto duplo ou triplo\n"
	"(cada 50 pontos).\n\n"
	"- bomba: exploda 2 linhas ou colunas aleatoriamente\n"
	"(cada 5 combinacoes).\n\n"
	"- desfazer: reverta o seu ultimo movimento\n"
	"(apos 5 tabuleiros concluidos).\n\n"
};

#define NUM_PAGINAS_AJUDA (int)(sizeof(PAGINAS_AJUDA) / sizeof(char *))

struct Fontes {
	ALLEGRO_FONT *fipps_12;
	ALLEGRO_FONT *pixelmix_8;
	ALLEGRO_FONT *smallestpixel7_10;
};

struct Sprites {
	ALLEGRO_BITMAP *sheet;

	ALLEGRO_BITMAP *decoracao_centro;
	ALLEGRO_BITMAP *decoracao_padrao;

	ALLEGRO_BITMAP *botao_voltar;

	ALLEGRO_BITMAP *inicio_titulo;

	ALLEGRO_BITMAP *inicio_botao_continuar_jogo_padrao;
	ALLEGRO_BITMAP *inicio_botao_continuar_jogo_desabilitado;

	ALLEGRO_BITMAP *inicio_botao_novo_jogo_padrao;
	ALLEGRO_BITMAP *inicio_botao_sair_padrao;

	ALLEGRO_BITMAP *inicio_botao_placar_padrao;
	ALLEGRO_BITMAP *inicio_botao_placar_sobre;

	ALLEGRO_BITMAP *inicio_botao_ajuda_padrao;
	ALLEGRO_BITMAP *inicio_botao_ajuda_sobre;

	ALLEGRO_BITMAP *placar_titulo;
	ALLEGRO_BITMAP *placar_relogio;

	ALLEGRO_BITMAP *ajuda_titulo;
	ALLEGRO_BITMAP *ajuda_seta_direita;
	ALLEGRO_BITMAP *ajuda_seta_esquerda;

	ALLEGRO_BITMAP *pausa_titulo;

	ALLEGRO_BITMAP *pausa_botao_resumir_padrao;
	ALLEGRO_BITMAP *pausa_botao_resumir_sobre;

	ALLEGRO_BITMAP *pausa_botao_reiniciar_padrao;
	ALLEGRO_BITMAP *pausa_botao_reiniciar_sobre;

	ALLEGRO_BITMAP *pausa_botao_abandonar_padrao;
	ALLEGRO_BITMAP *pausa_botao_abandonar_sobre;

	ALLEGRO_BITMAP *pausa_botao_sair_e_salvar_padrao;
	ALLEGRO_BITMAP *pausa_botao_sair_e_salvar_sobre;

	ALLEGRO_BITMAP *game_over_titulo;

	ALLEGRO_BITMAP *game_over_botao_sair_padrao;
	ALLEGRO_BITMAP *game_over_botao_sair_sobre;

	ALLEGRO_BITMAP *game_over_botao_jogar_novamente_padrao;
	ALLEGRO_BITMAP *game_over_botao_jogar_novamente_sobre;

	ALLEGRO_BITMAP *moldura;
	ALLEGRO_BITMAP *slot;

	ALLEGRO_BITMAP *botao_pausar_padrao;
	ALLEGRO_BITMAP *botao_pausar_sobre;

	ALLEGRO_BITMAP *habilidade_desfazer_padrao;
	ALLEGRO_BITMAP *habilidade_desfazer_pressionado;
	ALLEGRO_BITMAP *habilidade_desfazer_desabilitado;

	ALLEGRO_BITMAP *habilidade_bomba_padrao;
	ALLEGRO_BITMAP *habilidade_bomba_pressionado;
	ALLEGRO_BITMAP *habilidade_bomba_desabilitado;
	
	ALLEGRO_BITMAP *habilidade_rotacao_padrao;

	ALLEGRO_BITMAP *botao_rotacionar_padrao;
	ALLEGRO_BITMAP *botao_rotacionar_desabilitado;

	ALLEGRO_BITMAP *botao_rotacionar_ativo_padrao;
	ALLEGRO_BITMAP *botao_rotacionar_ativo_pressionado;

	ALLEGRO_BITMAP *fundo_progresso;

	ALLEGRO_BITMAP *dados[CORES_NUM][DADOS_NUM];

	ALLEGRO_BITMAP *baloes_horizontais[BALOES_NUM];
	ALLEGRO_BITMAP *baloes_verticais[BALOES_NUM];

	ALLEGRO_BITMAP *colapso_linha[COLAPSO_FRAMES_NUM];
	ALLEGRO_BITMAP *colapso_coluna[COLAPSO_FRAMES_NUM];

	ALLEGRO_BITMAP *explosao[EXPLOSAO_FRAMES_NUM];
};

struct Sons {
	ALLEGRO_SAMPLE *elefante;

	ALLEGRO_SAMPLE *pop;
	ALLEGRO_SAMPLE *snap;
	ALLEGRO_SAMPLE *pluck;

	ALLEGRO_SAMPLE *impacto;

	ALLEGRO_SAMPLE *botao_sobre;
	ALLEGRO_SAMPLE *botao_selecionar;
	ALLEGRO_SAMPLE *botao_bloqueado;
};

struct Tela {
	bool cheia;

	int escala;

	int largura;
	int altura;

	ALLEGRO_DISPLAY *display;
	ALLEGRO_BITMAP *canvas;

	struct Fontes fontes;
	struct Sprites sprites;
	struct Sons sons;
};

struct Botao {
	int x, y;
	int largura, altura;

	bool sobre;
	bool pressionado;

	bool desabilitado;

	ALLEGRO_BITMAP *sprite_padrao;
	ALLEGRO_BITMAP *sprite_sobre;
	ALLEGRO_BITMAP *sprite_pressionado;
	ALLEGRO_BITMAP *sprite_desabilitado;

	ALLEGRO_SAMPLE *som_sobre;
	ALLEGRO_SAMPLE *som_pressionar;
	ALLEGRO_SAMPLE *som_desabilitado;
};

struct Inicio {
	struct Botao botao_continuar_jogo;
	struct Botao botao_novo_jogo;
	struct Botao botao_sair;

	struct Botao botao_placar;
	struct Botao botao_ajuda;
};

struct Placar {
	struct Botao botao_voltar;
};

struct Ajuda {
	int pagina;

	struct Botao botao_voltar;
	struct Botao botao_pagina_seguinte;
	struct Botao botao_pagina_anterior;

};

struct Pausa {
	struct Botao botao_resumir;
	struct Botao botao_reiniciar;
	struct Botao botao_abandonar;
	struct Botao botao_sair_e_salvar;
};

struct GameOver {
	int tempo;
	int escore;

	struct Botao botao_sair;
	struct Botao botao_jogar_novamente;
};

struct Recorde
{
	bool vago;

	int escore;
	int tempo;
};

struct Habilidade
{
	int x, y;

	bool cumulativo;
	bool bloqueado;

	int custo;
	int progresso;

	int quantidade;

	struct Botao botao;
};

struct Dado {
	bool livre;

	int animacao;
	
	int ticks;
	int atraso;
	int direcao;

	int cor;
	int valor;
};

struct Quadro {
	int x, y;

	bool concluido;

	int soma_linhas[QUADRO_TAM];
	int soma_colunas[QUADRO_TAM];

	struct Dado dados[QUADRO_TAM][QUADRO_TAM];
};

struct Soma
{
	int indice;
	int direcao;
};

struct Arranjos
{
	int origem;
	int sequencia;
};

struct Peca
{
	int x, y;

	int cor;
	int linhas;
	int colunas;

	int dados[PECA_TAM][PECA_TAM];
};

struct Slot {
	int x, y;
	int arraste_x, arraste_y;

	bool ocupado;
	bool arrastando;
	bool rotacionando;

	struct Peca peca;

	struct Botao botao_rotacionar;
};

struct Jogada {
	int indice_origem;

	int linha;
	int coluna;

	struct Peca peca;
};

struct Anuncio
{
	bool usado;

	int premio;

	int pontos;
	int combo;

	int ticks;
};

struct Jogo {
	int estado;

	int escore;
	int tempo;

	int slot_selecionado;

	struct Habilidade desfazer;
	struct Habilidade bomba;
	struct Habilidade rotacao;

	struct Quadro quadro;
	struct Slot slots[SLOTS_TAM];

	struct Jogada jogada;

	struct Anuncio anuncios[ANUNCIOS_TAM];

	struct Botao botao_pausar;

	struct Pausa pausa;
	struct GameOver game_over;
};

struct Sistema {
	int cena;

	bool encerrar;
	bool redesenhar;
	bool reposicionar;

	struct Inicio inicio;
	struct Placar placar;
	struct Ajuda ajuda;

	struct Recorde recordes[RECORDES_TAM];

	struct Jogo jogo;
};

void verificar_init(bool teste, char *descricao)
{
	if (teste)
		return;

	printf("falha ao inicializar %s\n", descricao);
	exit(1);
}

ALLEGRO_BITMAP *recortar_sprite(struct Sprites *sprites, int x, int y, int largura, int altura)
{
	ALLEGRO_BITMAP *sprite = al_create_sub_bitmap(sprites->sheet, x, y, largura, altura);
	verificar_init(sprite, "recortar_sprite");
	return sprite;
}

void carregar_fontes(struct Fontes *fontes)
{
	fontes->fipps_12 = al_load_font("assets/fonts/Fipps-Regular.otf", 12, ALLEGRO_TTF_MONOCHROME);
	verificar_init(fontes->fipps_12, "fipps 12");

	fontes->pixelmix_8 = al_load_font("assets/fonts/pixelmix.ttf", 8, ALLEGRO_TTF_MONOCHROME);
	verificar_init(fontes->pixelmix_8, "pixelmix 8");

	fontes->smallestpixel7_10 = al_load_font("assets/fonts/smallest_pixel-7.ttf", 10, ALLEGRO_TTF_MONOCHROME);
	verificar_init(fontes->smallestpixel7_10, "smallestpixel7 10");
}

void carregar_sprites(struct Sprites *sprites)
{
	sprites->sheet = al_load_bitmap("assets/sprites/spritesheet.png");
	verificar_init(sprites->sheet, "spritesheet.png");

	sprites->decoracao_centro = recortar_sprite(sprites, 192, 155, DECORACAO_CENTRO_L, DECORACAO_H);
	sprites->decoracao_padrao = recortar_sprite(sprites, 318, 155, DECORACAO_PADRAO_L, DECORACAO_H);

	sprites->botao_voltar = recortar_sprite(sprites, 440, 0, BOTAO_VOLTAR_L, BOTAO_VOLTAR_H);

	sprites->inicio_titulo = recortar_sprite(sprites, 300, 0, INICIO_TITULO_L, INICIO_TITULO_H);

	sprites->inicio_botao_continuar_jogo_padrao = recortar_sprite(sprites, 370, 52, INICIO_BOTAO_MENU_L, INICIO_BOTAO_MENU_H);
	sprites->inicio_botao_continuar_jogo_desabilitado = recortar_sprite(sprites, 440, 52, INICIO_BOTAO_MENU_L, INICIO_BOTAO_MENU_H);

	sprites->inicio_botao_novo_jogo_padrao = recortar_sprite(sprites, 370, 75, INICIO_BOTAO_MENU_L, INICIO_BOTAO_MENU_H);
	sprites->inicio_botao_sair_padrao = recortar_sprite(sprites, 440, 75, INICIO_BOTAO_MENU_L, INICIO_BOTAO_MENU_H);

	sprites->inicio_botao_placar_padrao = recortar_sprite(sprites, 466, 0, INICIO_BOTAO_MARCADOR_L, INICIO_BOTAO_MARCADOR_H);
	sprites->inicio_botao_placar_sobre = recortar_sprite(sprites, 489, 0, INICIO_BOTAO_MARCADOR_L, INICIO_BOTAO_MARCADOR_H);

	sprites->inicio_botao_ajuda_padrao = recortar_sprite(sprites, 466, 19, INICIO_BOTAO_MARCADOR_L, INICIO_BOTAO_MARCADOR_H);
	sprites->inicio_botao_ajuda_sobre = recortar_sprite(sprites, 489, 19, INICIO_BOTAO_MARCADOR_L, INICIO_BOTAO_MARCADOR_H);

	sprites->placar_titulo = recortar_sprite(sprites, 364, 38, PLACAR_TITULO_L, PLACAR_TITULO_H);
	sprites->placar_relogio = recortar_sprite(sprites, 338, 32, PLACAR_RELOGIO_L, PLACAR_RELOGIO_H);

	sprites->ajuda_titulo = recortar_sprite(sprites, 446, 38, AJUDA_TITULO_L, AJUDA_TITULO_H);
	sprites->ajuda_seta_esquerda = recortar_sprite(sprites, 299, 32, AJUDA_SETA_L, AJUDA_SETA_H);
	sprites->ajuda_seta_direita = recortar_sprite(sprites, 318, 32, AJUDA_SETA_L, AJUDA_SETA_H);

	sprites->pausa_titulo = recortar_sprite(sprites, 219, 25, PAUSA_TITULO_L, PAUSA_TITULO_H);

	sprites->pausa_botao_resumir_padrao = recortar_sprite(sprites, 224, 65, PAUSA_BOTAO_MENU_L, PAUSA_BOTAO_MENU_H);
	sprites->pausa_botao_resumir_sobre = recortar_sprite(sprites, 297, 65, PAUSA_BOTAO_MENU_L, PAUSA_BOTAO_MENU_H);

	sprites->pausa_botao_reiniciar_padrao = recortar_sprite(sprites, 224, 79, PAUSA_BOTAO_MENU_L, PAUSA_BOTAO_MENU_H);
	sprites->pausa_botao_reiniciar_sobre = recortar_sprite(sprites, 297, 79, PAUSA_BOTAO_MENU_L, PAUSA_BOTAO_MENU_H);

	sprites->pausa_botao_abandonar_padrao = recortar_sprite(sprites, 224, 93, PAUSA_BOTAO_MENU_L, PAUSA_BOTAO_MENU_H);
	sprites->pausa_botao_abandonar_sobre = recortar_sprite(sprites, 297, 93, PAUSA_BOTAO_MENU_L, PAUSA_BOTAO_MENU_H);

	sprites->pausa_botao_sair_e_salvar_padrao = recortar_sprite(sprites, 224, 107, PAUSA_BOTAO_MENU_L, PAUSA_BOTAO_MENU_H);
	sprites->pausa_botao_sair_e_salvar_sobre = recortar_sprite(sprites, 297, 107, PAUSA_BOTAO_MENU_L, PAUSA_BOTAO_MENU_H);

	sprites->game_over_titulo = recortar_sprite(sprites, 219, 45, GAME_OVER_TITULO_L, GAME_OVER_TITULO_H);

	sprites->game_over_botao_sair_padrao = recortar_sprite(sprites, 192, 127, GAME_OVER_BOTAO_L, GAME_OVER_BOTAO_H);
	sprites->game_over_botao_sair_sobre = recortar_sprite(sprites, 277, 127, GAME_OVER_BOTAO_L, GAME_OVER_BOTAO_H);

	sprites->game_over_botao_jogar_novamente_padrao = recortar_sprite(sprites, 192, 141, GAME_OVER_BOTAO_L, GAME_OVER_BOTAO_H);
	sprites->game_over_botao_jogar_novamente_sobre = recortar_sprite(sprites, 277, 141, GAME_OVER_BOTAO_L, GAME_OVER_BOTAO_H);

	sprites->moldura = recortar_sprite(sprites, 168, 0, DADO_L, DADO_H);
	sprites->slot = recortar_sprite(sprites, 168, 25, SLOT_L, SLOT_H);

	sprites->botao_pausar_padrao = recortar_sprite(sprites, 268, 0, BOTAO_PAUSAR_L, BOTAO_PAUSAR_H);
	sprites->botao_pausar_sobre = recortar_sprite(sprites, 284, 0, BOTAO_PAUSAR_L, BOTAO_PAUSAR_H);

	sprites->habilidade_desfazer_padrao = recortar_sprite(sprites, 168, 93, HABILIDADE_BOTAO_L, HABILIDADE_BOTAO_H);
	sprites->habilidade_desfazer_pressionado = recortar_sprite(sprites, 184, 93, HABILIDADE_BOTAO_L, HABILIDADE_BOTAO_H);
	sprites->habilidade_desfazer_desabilitado = recortar_sprite(sprites, 200, 93, HABILIDADE_BOTAO_L, HABILIDADE_BOTAO_H);

	sprites->habilidade_bomba_padrao = recortar_sprite(sprites, 168, 110, HABILIDADE_BOTAO_L, HABILIDADE_BOTAO_H);
	sprites->habilidade_bomba_pressionado = recortar_sprite(sprites, 184, 110, HABILIDADE_BOTAO_L, HABILIDADE_BOTAO_H);
	sprites->habilidade_bomba_desabilitado = recortar_sprite(sprites, 200, 110, HABILIDADE_BOTAO_L, HABILIDADE_BOTAO_H);

	sprites->habilidade_rotacao_padrao = recortar_sprite(sprites, 171, 127, HABILIDADE_BOTAO_L, HABILIDADE_BOTAO_H);

	sprites->fundo_progresso = recortar_sprite(sprites, 168, 127, FUNDO_PROGRESSO_L, FUNDO_PROGRESSO_H);

	sprites->botao_rotacionar_padrao = recortar_sprite(sprites, 168, 78, BOTAO_ROTACIONAR_L, BOTAO_ROTACIONAR_H);
	sprites->botao_rotacionar_desabilitado = recortar_sprite(sprites, 182, 78, BOTAO_ROTACIONAR_L, BOTAO_ROTACIONAR_H);
	sprites->botao_rotacionar_ativo_padrao = recortar_sprite(sprites, 196, 78, BOTAO_ROTACIONAR_L, BOTAO_ROTACIONAR_H);
	sprites->botao_rotacionar_ativo_pressionado = recortar_sprite(sprites, 210, 78, BOTAO_ROTACIONAR_L, BOTAO_ROTACIONAR_H);

	for (int i = 0; i < CORES_NUM; i++)
	{
		for (int j = 0; j < DADOS_NUM; j++)
		{
			sprites->dados[i][j] = recortar_sprite(sprites, j * DADO_L, i * DADO_H, DADO_L, DADO_H);
		}
	}

	for (int i = 0; i < BALOES_NUM; i++)
	{
		int x = 192 + i * BALAO_HORIZONTAL_L;
		int y = 0;

		sprites->baloes_horizontais[i] = recortar_sprite(sprites, x, y, BALAO_HORIZONTAL_L, BALAO_HORIZONTAL_H);
	}

	for (int j = 0; j < BALOES_NUM; j++)
	{
		int x = 192 + j * BALAO_VERTICAL_L;
		int y = 11;

		sprites->baloes_verticais[j] = recortar_sprite(sprites, x, y, BALAO_VERTICAL_L, BALAO_VERTICAL_H);
	}

	for (int i = 0; i < COLAPSO_FRAMES_NUM; i++)
	{
		sprites->colapso_linha[i] = recortar_sprite(sprites, i * DADO_L, 150, DADO_L, DADO_H);;
		sprites->colapso_coluna[i] = recortar_sprite(sprites, i * DADO_L, 175, DADO_L, DADO_H);;
	}

	for (int i = 0; i < EXPLOSAO_FRAMES_NUM; i++)
	{
		sprites->explosao[i] = recortar_sprite(sprites, 192 + i * DADO_L, 176, DADO_L, DADO_H);
	}
}

void carregar_sons(struct Sons *sons)
{
	sons->elefante = al_load_sample("assets/sounds/elephant.wav");
	verificar_init(sons->elefante, "elephant.wav");

	sons->pop = al_load_sample("assets/sounds/pop.wav");
	verificar_init(sons->pop, "pop.wav");

	sons->snap = al_load_sample("assets/sounds/snap.wav");
	verificar_init(sons->snap, "snap.wav");

	sons->impacto = al_load_sample("assets/sounds/impact.wav");
	verificar_init(sons->impacto, "impact.wav");

	sons->botao_sobre = al_load_sample("assets/sounds/hover.wav");
	verificar_init(sons->botao_sobre, "hover.wav");

	sons->botao_selecionar = al_load_sample("assets/sounds/select.wav");
	verificar_init(sons->botao_selecionar, "select.wav");

	sons->botao_bloqueado = al_load_sample("assets/sounds/blocked.wav");
	verificar_init(sons->botao_sobre, "blocked.wav");
}

int inteiro_aleatorio(int minimo, int maximo)
{
	int intervalo = maximo - minimo;
	return rand() % intervalo + minimo;
}

double fracao_aleatoria(double minimo, double maximo)
{
	double intervalo = maximo - minimo;
	double fracao = (double)rand() / RAND_MAX;

	return fracao * intervalo + minimo;
}

int centro(int referencia, int maior, int menor)
{
	return referencia + (maior - menor) / 2;
}

bool colisao_retangulo(int x, int y, int largura, int altura, int px, int py)
{
	int delta_x = px - x;
	int delta_y = py - y;

	return delta_x >= 0 && delta_x < largura && delta_y >= 0 && delta_y < altura;
}

void criar_display(struct Tela *tela)
{
	al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);

	tela->display = al_create_display(1280, 720);
	verificar_init(tela->display, "display");
}

void criar_canvas(struct Tela *tela)
{
	ALLEGRO_TRANSFORM transform;

	float largura_janela = al_get_display_width(tela->display);
	float altura_janela = al_get_display_height(tela->display);

	float razao_x = floor(largura_janela / LARGURA_ORIGINAL);
	float razao_y = floor(altura_janela / ALTURA_ORIGINAL);

	tela->escala = razao_x < razao_y ? razao_x : razao_y;

	if (tela->escala < 1)
	{
		tela->escala = 1;
	}

	tela->largura = ceil(largura_janela / tela->escala);
	tela->altura = ceil(altura_janela / tela->escala);

	tela->canvas = al_create_bitmap(tela->largura, tela->altura);
	verificar_init(tela->canvas, "canvas");

	al_identity_transform(&transform);
	al_scale_transform(&transform, tela->escala, tela->escala);

	al_use_transform(&transform);
}

void alternar_tela_cheia(struct Tela *tela)
{
	tela->cheia = !tela->cheia;
	al_toggle_display_flag(tela->display, ALLEGRO_FULLSCREEN_WINDOW, tela->cheia);
}

void redimensionar_canvas(struct Tela *tela)
{
	al_destroy_bitmap(tela->canvas);
	criar_canvas(tela);
}

void preparar_desenho(struct Tela *tela)
{
	al_set_target_bitmap(tela->canvas);
	al_clear_to_color(COR_TRANSPARENTE);
}

void finalizar_desenho(struct Tela *tela)
{
	al_set_target_backbuffer(tela->display);
	al_clear_to_color(COR_BRANCO);
	al_draw_bitmap(tela->canvas, 0, 0, 0);
	al_flip_display();
}

void detectar_sobre_botao(struct Botao *botao, int px, int py)
{
	bool dentro = colisao_retangulo(botao->x, botao->y, botao->largura, botao->altura, px, py);

	if (dentro)
	{
		if (!botao->sobre && botao->som_sobre)
		{
			al_play_sample(botao->som_sobre, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}

		botao->sobre = true;
	}
	else
	{
		botao->sobre = false;
	}
}

bool pressionar_botao(struct Botao *botao)
{
	if (botao->sobre)
	{
		if (!botao->desabilitado)
		{
			botao->pressionado = true;

			if (botao->som_pressionar)
			{
				al_play_sample(botao->som_pressionar, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
		}
		else
		{
			if (botao->som_desabilitado)
			{
				al_play_sample(botao->som_desabilitado, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
		}
		
	}

	return botao->pressionado;
}

bool soltar_botao(struct Botao *botao)
{
	if (botao->pressionado)
	{
		botao->pressionado = false;
		return true;
	}

	return false;
}

void resetar_botao(struct Botao *botao)
{
	botao->desabilitado = false;
	botao->sobre = false;
	botao->pressionado = false;
}

void inicializar_botao(struct Botao *botao, int largura, int altura)
{
	botao->x = 0;
	botao->y = 0;

	botao->largura = largura;
	botao->altura = altura;

	botao->sprite_padrao = NULL;
	botao->sprite_sobre = NULL;
	botao->sprite_pressionado = NULL;
	botao->sprite_desabilitado = NULL;

	botao->som_sobre = NULL;
	botao->som_pressionar = NULL;
	botao->som_desabilitado = NULL;

	resetar_botao(botao);
}

void desenhar_botao(struct Botao *botao)
{
	ALLEGRO_BITMAP *sprite;

	if (botao->pressionado)
	{
		sprite = botao->sprite_pressionado;
	}
	else if (botao->desabilitado)
	{
		sprite = botao->sprite_desabilitado;
	}
	else if (botao->sobre)
	{
		sprite = botao->sprite_sobre;
	}
	else
	{
		sprite = botao->sprite_padrao;
	}

	al_draw_bitmap(sprite, botao->x, botao->y, 0);
}

bool comparar_recorde(struct Recorde *recorde, int escore, int tempo)
{
	return recorde->vago || escore > recorde->escore || escore == recorde->escore && tempo < recorde->tempo;
}

void carregar_recordes(struct Recorde recordes[RECORDES_TAM])
{
	FILE *arquivo = fopen(ARQUIVO_RECORDES, "r");

	if (arquivo)
	{
		for (int i = 0; i < RECORDES_TAM; i++)
		{
			int vago, escore, tempo;
			int resultado = fscanf(arquivo, "%d %d %d\n", &vago, &escore, &tempo);

			if (resultado == 3)
			{
				recordes[i].vago = vago;
				recordes[i].escore = escore;
				recordes[i].tempo = tempo;
			}
		}

		fclose(arquivo);
	}
}

void salvar_recordes(struct Recorde recordes[RECORDES_TAM])
{
	FILE *arquivo = fopen(ARQUIVO_RECORDES, "w");

	if (arquivo)
	{
		for (int i = 0; i < RECORDES_TAM; i++)
		{
			fprintf(arquivo, "%d %d %d\n", recordes[i].vago, recordes[i].escore, recordes[i].tempo);
		}

		fclose(arquivo);
	}
}

void inserir_recorde(struct Recorde recordes[RECORDES_TAM], int escore, int tempo)
{
	for (int i = 0; i < RECORDES_TAM; i++)
	{
		if (comparar_recorde(&recordes[i], escore, tempo))
		{
			for (int j = RECORDES_TAM - 1; j > i; j--)
			{
				recordes[j] = recordes[j - 1];
			}

			recordes[i].vago = false;
			recordes[i].escore = escore;
			recordes[i].tempo = tempo;

			break;
		}
	}
}

void inicializar_recordes(struct Recorde recordes[RECORDES_TAM])
{
	for (int i = 0; i < RECORDES_TAM; i++)
	{
		recordes[i].vago = true;
		recordes[i].escore = 0;
		recordes[i].tempo = 0;
	}

	carregar_recordes(recordes);
}

void acumular_habilidade(struct Habilidade *habilidade, int parte)
{
	habilidade->progresso += parte;

	if (habilidade->cumulativo)
	{
		habilidade->quantidade += habilidade->progresso / habilidade->custo;
		habilidade->progresso %= habilidade->custo;
	}
	else
	{
		if (habilidade->progresso >= habilidade->custo)
		{
			habilidade->progresso = habilidade->custo;
			habilidade->quantidade = 1;
		}
	}
}

bool pode_usar_habilidade(struct Habilidade *habilidade)
{
	return !habilidade->bloqueado && habilidade->quantidade > 0;
}

bool usar_habilidade(struct Habilidade *habilidade)
{
	if (pode_usar_habilidade(habilidade))
	{
		habilidade->quantidade--;

		if (!habilidade->cumulativo)
		{
			habilidade->progresso = 0;
		}

		return true;
	}

	return false;
}		

void resetar_habilidade(struct Habilidade *habilidade)
{
	habilidade->bloqueado = false;

	habilidade->quantidade = 0;
	habilidade->progresso = 0;
}

void inicializar_habilidade(struct Habilidade *habilidade, int custo, bool cumulativo)
{
	habilidade->custo = custo;
	habilidade->cumulativo = cumulativo;

	inicializar_botao(&habilidade->botao, HABILIDADE_BOTAO_L, HABILIDADE_BOTAO_H);

	resetar_habilidade(habilidade);
}

void posicionar_habilidade(struct Habilidade *habilidade, int x, int y)
{
	habilidade->x = x;
	habilidade->y = y;
	habilidade->botao.x = x + FUNDO_PROGRESSO_L + HABILIDADE_PROGRESSO_ESPACO;
	habilidade->botao.y = y;
}

void atualizar_habilidade(struct Habilidade *habilidade)
{
	habilidade->botao.desabilitado = !pode_usar_habilidade(habilidade);
}

void desenhar_habilidade(struct Habilidade *habilidade, struct Tela *tela)
{
	float porcentagem = (float)habilidade->progresso / habilidade->custo;
	int altura = porcentagem * HABILIDADE_PROGRESSO_ALTURA;

	int progresso_x = habilidade->x + HABILIDADE_PROGRESSO_OFFSET_DIREITA;

	int progresso_y1 = habilidade->y + HABILIDADE_PROGRESSO_OFFSET_CIMA + 1;
	int progresso_y2 = progresso_y1 - altura;

	int quantidade_x = habilidade->botao.x + HABILIDADE_BOTAO_L + HABILIDADE_QUANTIDADE_ESPACO;
	int quantidade_y = centro(habilidade->botao.y, HABILIDADE_BOTAO_H, al_get_font_line_height(tela->fontes.pixelmix_8));

	al_draw_bitmap(tela->sprites.fundo_progresso, habilidade->x, habilidade->y, 0);
	al_draw_line(progresso_x, progresso_y1, progresso_x, progresso_y2, COR_HABILIDADE_PROGRESSO, 1);

	if (habilidade->cumulativo)
	{
		al_draw_textf(tela->fontes.pixelmix_8, COR_PRETO, quantidade_x, quantidade_y, ALLEGRO_ALIGN_LEFT, "%d", habilidade->quantidade);
	}

	desenhar_botao(&habilidade->botao);
}

bool colisao_quadro(struct Quadro *quadro, int px, int py)
{
	return colisao_retangulo(quadro->x, quadro->y, QUADRO_L, QUADRO_H, px, py);
}

void zerar_dado(struct Quadro *quadro, int linha, int coluna)
{
	if (quadro->dados[linha][coluna].valor != DADO_VAZIO)
	{
		quadro->soma_linhas[linha] -= quadro->dados[linha][coluna].valor;
		quadro->soma_colunas[coluna] -= quadro->dados[linha][coluna].valor;

		quadro->dados[linha][coluna].valor = DADO_VAZIO;
	}

	quadro->dados[linha][coluna].animacao = ANIMACAO_PARADO;
}

void preencher_dado(struct Quadro *quadro, int linha, int coluna, int cor, int valor)
{
	quadro->concluido = false;

	quadro->soma_linhas[linha] += valor;
	quadro->soma_colunas[coluna] += valor;

	quadro->dados[linha][coluna].livre = false;

	quadro->dados[linha][coluna].animacao = ANIMACAO_PARADO;
	quadro->dados[linha][coluna].direcao = SEM_DIRECAO;
	quadro->dados[linha][coluna].atraso = 0;
	quadro->dados[linha][coluna].ticks = 0;

	quadro->dados[linha][coluna].cor = cor;
	quadro->dados[linha][coluna].valor = valor;
}

void remover_dado(struct Quadro *quadro, int linha, int coluna)
{
	quadro->dados[linha][coluna].livre = true;
	zerar_dado(quadro, linha, coluna);
}

void animar_dado(struct Dado *dado, int animacao, int atraso, int direcao)
{
	dado->animacao = animacao;
	dado->ticks = 0;
	dado->atraso = atraso;
	dado->direcao = direcao;
}

void explodir_quadro(struct Quadro *quadro, int indice, int direcao)
{
	for (int i = 0; i < QUADRO_TAM; i++)
	{
		int linha = direcao == DIRECAO_LINHA ? indice : i;
		int coluna = direcao == DIRECAO_LINHA ? i : indice;

		quadro->dados[linha][coluna].livre = true;
		animar_dado(&quadro->dados[linha][coluna], ANIMACAO_EXPLOSAO, direcao, 0);
	}
}

int somar_dados_em_linha(struct Quadro *quadro, int linha)
{
	int soma = 0;

	for (int j = 0; j < QUADRO_TAM; j++)
	{
		if (!quadro->dados[linha][j].livre)
		{
			soma += quadro->dados[linha][j].valor;
		}
	}

	return soma;
}

int somar_dados_em_coluna(struct Quadro *quadro, int coluna)
{
	int soma = 0;

	for (int i = 0; i < QUADRO_TAM; i++)
	{
		if (!quadro->dados[i][coluna].livre)
		{
			soma += quadro->dados[i][coluna].valor;
		}
	}

	return soma;
}

int resolver_somas(struct Quadro *quadro, struct Soma somas[SOMAS_TAM])
{
	int n = 0;

	for (int i = 0; i < QUADRO_TAM; i++)
	{
		if (somar_dados_em_linha(quadro, i) == SOMA_ALVO)
		{
			somas[n].indice = i;
			somas[n].direcao = DIRECAO_LINHA;
			n++;
		}

		if (somar_dados_em_coluna(quadro, i) == SOMA_ALVO)
		{
			somas[n].indice = i;
			somas[n].direcao = DIRECAO_COLUNA;
			n++;
		}
	}

	return n;
}

int colapsar_somas(struct Quadro *quadro, struct Soma somas[SOMAS_TAM], int n, int atraso_inicial)
{
	int atraso_maximo = atraso_inicial;

	for (int k = 0; k < n; k++)
	{
		int atraso = atraso_inicial;

		for (int i = 0; i < QUADRO_TAM; i++)
		{
			int linha = somas[k].direcao == DIRECAO_LINHA ? somas[k].indice : i;
			int coluna = somas[k].direcao == DIRECAO_LINHA ? i : somas[k].indice;

			if (!quadro->dados[linha][coluna].livre)
			{
				quadro->dados[linha][coluna].livre = true;
				animar_dado(&quadro->dados[linha][coluna], ANIMACAO_COLAPSO, atraso, somas[k].direcao);
				
				atraso += COLAPSO_ATRASO;
			}
		}

		if (atraso > atraso_maximo)
		{
			atraso_maximo = atraso;
		}
	}

	return atraso_maximo;
}

struct Arranjos formar_arranjos(struct Quadro *quadro)
{
	struct Arranjos arranjos;
	struct Soma somas[SOMAS_TAM];

	int n = resolver_somas(quadro, somas);

	arranjos.origem = n;
	arranjos.sequencia = 0;

	int atraso = 0;

	while (n > 0) {
		arranjos.sequencia++;

		atraso = colapsar_somas(quadro, somas, n, atraso);
		n = resolver_somas(quadro, somas);
	}

	return arranjos;
}

bool quadro_limpo(struct Quadro *quadro)
{
	for (int i = 0; i < QUADRO_TAM; i++)
	{
		for (int j = 0; j < QUADRO_TAM; j++)
		{
			if (!quadro->dados[i][j].livre)
			{
				return false;
			}
		}
	}

	return true;
}

bool verificar_quadro_concluido(struct Quadro *quadro)
{
	if (!quadro->concluido && quadro_limpo(quadro))
	{
		quadro->concluido = true;
		return true;
	}

	return false;
}

bool verificar_colapso(struct Dado *dado)
{
	return dado->animacao == ANIMACAO_COLAPSO && dado->ticks - dado->atraso >= COLAPSO_FRAME_PERIODO * COLAPSO_FRAMES_NUM;
}

bool verificar_explosao(struct Dado *dado)
{
	return dado->animacao == ANIMACAO_EXPLOSAO && dado->ticks - dado->atraso >= EXPLOSAO_FRAME_PERIODO * EXPLOSAO_FRAMES_NUM;
}

int determinar_balao(int soma)
{
	if (soma <= BALAO_0_LIMITE)
	{
		return 0;
	}
	else if (soma <= BALAO_1_LIMITE)
	{
		return 1;
	}
	else if (soma <= BALAO_2_LIMITE)
	{
		return 2;
	}
	else
	{
		return 3;
	}
}

void posicionar_quadro(struct Quadro *quadro, struct Tela *tela)
{
	quadro->x = centro(0, tela->largura, QUADRO_L) - QUADRO_OFFSET_DIREITA;
	quadro->y = tela->altura - QUADRO_H - MARGEM_PEQUENA;
}

void resetar_quadro(struct Quadro *quadro)
{
	quadro->concluido = true;

	for (int i = 0; i < QUADRO_TAM; i++)
	{
		quadro->soma_colunas[i] = 0;
		quadro->soma_linhas[i] = 0;
	}

	for (int i = 0; i < QUADRO_TAM; i++)
	{
		for (int j = 0; j < QUADRO_TAM; j++)
		{
			quadro->dados[i][j].livre = true;
			quadro->dados[i][j].animacao = ANIMACAO_PARADO;
			quadro->dados[i][j].ticks = 0;
			quadro->dados[i][j].atraso = 0;
			quadro->dados[i][j].direcao = SEM_DIRECAO;
			quadro->dados[i][j].cor = 0;
			quadro->dados[i][j].valor = DADO_VAZIO;
		}
	}
}

void inicializar_quadro(struct Quadro *quadro)
{
	quadro->x = 0;
	quadro->y = 0;

	resetar_quadro(quadro);
}

void desenhar_baloes_horizontais(struct Quadro *quadro, struct Tela *tela)
{
	for (int i = 0; i < QUADRO_TAM; i++)
	{
		int x = quadro->x + QUADRO_L + BALAO_ESPACO;
		int y = centro(quadro->y + i * (DADO_H + DADOS_ESPACO), DADO_H, BALAO_HORIZONTAL_H);

		int texto_x = x + BALAO_HORIZONTAL_OFFSET_CIMA;
		int texto_y = y + BALAO_HORIZONTAL_OFFSET_DIREITA;
	
		int soma = quadro->soma_linhas[i];
		int balao = determinar_balao(soma);

		al_draw_bitmap(tela->sprites.baloes_horizontais[balao], x, y, 0);
		al_draw_textf(tela->fontes.pixelmix_8, COR_BRANCO, texto_x, texto_y, ALLEGRO_ALIGN_CENTER, "%d", soma);
	}
}

void desenhar_baloes_verticais(struct Quadro *quadro, struct Tela *tela)
{
	for (int j = 0; j < QUADRO_TAM; j++)
	{
		int x = centro(quadro->x + j * (DADO_L + DADOS_ESPACO), DADO_L, BALAO_VERTICAL_L);
		int y = quadro->y - BALAO_ESPACO - BALAO_VERTICAL_H;

		int texto_x = x + BALAO_VERTICAL_OFFSET_DIREITA;
		int texto_y = y + BALAO_VERTICAL_OFFSET_CIMA;

		int soma = quadro->soma_colunas[j];
		int balao = determinar_balao(soma);

		al_draw_bitmap(tela->sprites.baloes_verticais[balao], x, y, 0);
		al_draw_textf(tela->fontes.pixelmix_8, COR_BRANCO, texto_x, texto_y, ALLEGRO_ALIGN_CENTER, "%d", soma);
	}
}

void desenhar_animacao_colapso(struct Dado *dado, struct Tela *tela, int x, int y)
{
	if (dado->ticks < dado->atraso)
	{
		return;
	}

	int frame = ((dado->ticks - dado->atraso) / COLAPSO_FRAME_PERIODO) % COLAPSO_FRAMES_NUM;

	if (dado->direcao == DIRECAO_LINHA)
	{
		al_draw_bitmap(tela->sprites.colapso_linha[frame], x, y, 0);
	}
	else
	{
		al_draw_bitmap(tela->sprites.colapso_coluna[frame], x, y, 0);
	}
}

void desenhar_animacao_explosao(struct Dado *dado, struct Tela *tela, int x, int y)
{
	int frame = (dado->ticks / EXPLOSAO_FRAME_PERIODO) % EXPLOSAO_FRAMES_NUM;

	al_draw_bitmap(tela->sprites.explosao[frame], x, y, 0);
}

void desenhar_quadro(struct Quadro *quadro, struct Tela *tela)
{
	for (int i = 0; i < QUADRO_TAM; i++)
	{
		for (int j = 0; j < QUADRO_TAM; j++)
		{
			struct Dado *dado = &quadro->dados[i][j];

			int dado_x = quadro->x + j * (DADO_L + DADOS_ESPACO);
			int dado_y = quadro->y + i * (DADO_H + DADOS_ESPACO);

			al_draw_bitmap(tela->sprites.moldura, dado_x, dado_y, 0);

			if (dado->valor != DADO_VAZIO)
			{
				al_draw_bitmap(tela->sprites.dados[dado->cor][dado->valor], dado_x, dado_y, 0);
			}

			switch (dado->animacao)
			{
				case ANIMACAO_COLAPSO:
					desenhar_animacao_colapso(dado, tela, dado_x, dado_y);
					break;
				case ANIMACAO_EXPLOSAO:
					desenhar_animacao_explosao(dado, tela, dado_x, dado_y);
					break;
			}
		}
	}

	desenhar_baloes_horizontais(quadro, tela);
	desenhar_baloes_verticais(quadro, tela);
}

void desenhar_borda_decorativa(struct Tela *tela)
{
	int x1 = centro(0, tela->largura, DECORACAO_CENTRO_L);
	int x2 = x1 + DECORACAO_CENTRO_L;

	int y = tela->altura - DECORACAO_H;

	al_draw_bitmap(tela->sprites.decoracao_centro, x1, y, 0);

	for (int distancia = 0; distancia < tela->largura; distancia += DECORACAO_PADRAO_L)
	{
		al_draw_bitmap(tela->sprites.decoracao_padrao, x2 + distancia, y, 0);
		al_draw_bitmap(tela->sprites.decoracao_padrao, x1 - DECORACAO_PADRAO_L - distancia, y, 0);
	}
}

int largura_peca(struct Peca *peca)
{
	return DADO_L * peca->colunas + DADOS_ESPACO * (peca->colunas - 1);
}

int altura_peca(struct Peca *peca)
{
	return DADO_H * peca->linhas + DADOS_ESPACO * (peca->linhas - 1);
}

struct Peca gerar_peca(int x, int y)
{
	struct Peca peca;

	peca.x = x;
	peca.y = y;

	peca.cor = inteiro_aleatorio(0, CORES_NUM);
	peca.linhas = inteiro_aleatorio(1, PECA_TAM + 1);
	peca.colunas = inteiro_aleatorio(1, PECA_TAM + 1);

	for (int i = 0; i < PECA_TAM; i++)
	{
		for (int j = 0; j < PECA_TAM; j++)
		{
			peca.dados[i][j] = inteiro_aleatorio(0, DADOS_NUM);
		}
	}

	if (peca.linhas == PECA_TAM && peca.colunas == PECA_TAM)
	{
		int i = inteiro_aleatorio(0, PECA_TAM);
		int j = inteiro_aleatorio(0, PECA_TAM);

		peca.dados[i][j] = DADO_VAZIO;
	}

	return peca;
}

bool pode_rotacionar_peca(struct Peca *peca)
{
	return peca->linhas != 1 || peca->colunas != 1;
}

struct Peca rotacionar_peca(struct Peca *peca)
{
	struct Peca copia;

	copia.x = peca->x;
	copia.y = peca->y;

	copia.cor = peca->cor;
	copia.linhas = peca->colunas;
	copia.colunas = peca->linhas;

	for (int i = 0; i < peca->linhas; i++)
	{
		for (int j = 0; j < peca->colunas; j++)
		{
			copia.dados[j][peca->linhas - i - 1] = peca->dados[i][j];
		}
	}

	return copia;
}

bool aceita_peca(struct Quadro *quadro, struct Peca *peca, int linha, int coluna)
{
	if (linha + peca->linhas > QUADRO_TAM || coluna + peca->colunas > QUADRO_TAM)
	{
		return false;
	}

	for (int i = 0; i < peca->linhas; i++)
	{
		for (int j = 0; j < peca->colunas; j++)
		{
			if (peca->dados[i][j] != DADO_VAZIO && !quadro->dados[linha + i][coluna + j].livre)
			{
				return false;
			}
		}
	}

	return true;
}

void inserir_peca(struct Quadro *quadro, struct Peca *peca, int linha, int coluna)
{
	for (int i = 0; i < peca->linhas; i++)
	{
		for (int j = 0; j < peca->colunas; j++)
		{
			if (peca->dados[i][j] != DADO_VAZIO)
			{
				preencher_dado(quadro, linha + i, coluna + j, peca->cor, peca->dados[i][j]);
			}
		}
	}
}

void retirar_peca(struct Quadro *quadro, struct Peca *peca, int linha, int coluna)
{
	for (int i = 0; i < peca->linhas; i++)
	{
		for (int j = 0; j < peca->colunas; j++)
		{
			if (peca->dados[i][j] != DADO_VAZIO)
			{
				remover_dado(quadro, linha + i, coluna + j);
			}
		}
	}
}

bool existe_espaco_disponivel_para_peca(struct Quadro *quadro, struct Peca *peca)
{
	for (int i = 0; i < QUADRO_TAM; i++)
	{
		for (int j = 0; j < QUADRO_TAM; j++)
		{
			if (aceita_peca(quadro, peca, i, j))
			{
				return true;
			}
		}
	}

	return false;
}

void desenhar_peca(struct Peca *peca, struct Tela *tela)
{
	for (int i = 0; i < peca->linhas; i++)
	{
		for (int j = 0; j < peca->colunas; j++)
		{
			int dado_x = peca->x + j * (DADO_L + DADOS_ESPACO);
			int dado_y = peca->y + i * (DADO_H + DADOS_ESPACO);

			if (peca->dados[i][j] != DADO_VAZIO)
			{
				al_draw_bitmap(tela->sprites.dados[peca->cor][peca->dados[i][j]], dado_x, dado_y, 0);
			}
		}
	}
}

bool colisao_slot(struct Slot *slot, int x, int y)
{
	return colisao_retangulo(slot->x, slot->y, SLOT_L, SLOT_H, x, y);
}

void gerar_slot(struct Slot *slot)
{
	slot->ocupado = true;
	slot->peca = gerar_peca(slot->peca.x, slot->peca.y);
}

bool pegar_slot(struct Slot *slot, int x, int y)
{
	if (!slot->ocupado)
	{
		return false;
	}

	slot->arrastando = true;
	slot->arraste_x = slot->peca.x - x;
	slot->arraste_y = slot->peca.y - y;

	return true;
}

void arrastar_slot(struct Slot *slot, int x, int y)
{
	slot->peca.x = slot->arraste_x + x;
	slot->peca.y = slot->arraste_y + y;
}

void rotacionar_slot(struct Slot *slot)
{
	slot->rotacionando = true;
	slot->peca = rotacionar_peca(&slot->peca);
}

bool aceita_slot(struct Quadro *quadro, struct Slot *slot, int linha, int coluna)
{
	return aceita_peca(quadro, &slot->peca, linha, coluna);
}

void inserir_slot(struct Quadro *quadro, struct Slot *slot, int linha, int coluna)
{
	slot->ocupado = false;
	slot->rotacionando = false;
	
	inserir_peca(quadro, &slot->peca, linha, coluna);
}

bool largar_slot(struct Quadro *quadro, struct Slot *slot, int *linha, int *coluna)
{
	slot->arrastando = false;

	int referencia_x = DADO_L / 2 + slot->peca.x;
	int referencia_y = DADO_H / 2 + slot->peca.y;

	if (colisao_quadro(quadro, referencia_x, referencia_y))
	{
		*coluna = (referencia_x - quadro->x) / (DADO_L + DADOS_ESPACO);
		*linha = (referencia_y - quadro->y) / (DADO_H + DADOS_ESPACO);

		if (aceita_slot(quadro, slot, *linha, *coluna))
		{
			inserir_slot(quadro, slot, *linha, *coluna);
			return true;
		}
	}

	return false;
}

void resetar_slot(struct Slot *slot)
{
	slot->ocupado = true;
	slot->arrastando = false;
	slot->rotacionando = false;

	gerar_slot(slot);
}

void inicializar_slot(struct Slot *slot, struct Sprites *sprites, struct Sons *sons)
{
	slot->x = 0;
	slot->y = 0;

	slot->arraste_x = 0;
	slot->arraste_y = 0;

	inicializar_botao(&slot->botao_rotacionar, BOTAO_ROTACIONAR_L, BOTAO_ROTACIONAR_H);

	slot->botao_rotacionar.sprite_desabilitado = sprites->botao_rotacionar_desabilitado;
	slot->botao_rotacionar.sprite_pressionado = sprites->botao_rotacionar_ativo_pressionado;

	slot->botao_rotacionar.som_desabilitado = sons->botao_bloqueado;

	resetar_slot(slot);
}

void desenhar_slot(struct Slot *slot, struct Tela *tela)
{
	al_draw_bitmap(tela->sprites.slot, slot->x, slot->y, 0);

	if (slot->rotacionando)
	{
		slot->botao_rotacionar.sprite_padrao = tela->sprites.botao_rotacionar_ativo_padrao;
		slot->botao_rotacionar.sprite_sobre = tela->sprites.botao_rotacionar_ativo_padrao;
	}
	else
	{
		slot->botao_rotacionar.sprite_padrao = tela->sprites.botao_rotacionar_padrao;
		slot->botao_rotacionar.sprite_sobre = tela->sprites.botao_rotacionar_padrao;
	}

	desenhar_botao(&slot->botao_rotacionar);

	if (slot->ocupado && !slot->arrastando)
	{
		desenhar_peca(&slot->peca, tela);
	}
}

void gerar_slots(struct Slot slots[SLOTS_TAM])
{
	for (int i = 0; i < SLOTS_TAM; i++)
	{
		gerar_slot(&slots[i]);
	}
}

bool slot_vazios(struct Slot slots[SLOTS_TAM])
{
	for (int i = 0; i < SLOTS_TAM; i++)
	{
		if (slots[i].ocupado)
			return false;
	}

	return true;
}

void resetar_slots(struct Slot slots[SLOTS_TAM])
{
	for (int i = 0; i < SLOTS_TAM; i++)
	{
		resetar_slot(&slots[i]);
	}
}

void inicializar_slots(struct Slot slots[SLOTS_TAM], struct Sprites *sprites, struct Sons *sons)
{
	for (int i = 0; i < SLOTS_TAM; i++)
	{
		inicializar_slot(&slots[i], sprites, sons);
	}
}

void posicionar_slots(struct Slot slots[SLOTS_TAM], struct Tela *tela)
{
	for (int i = 0; i < SLOTS_TAM; i++)
	{
		slots[i].x = tela->largura - SLOT_L - MARGEM_PEQUENA;
		slots[i].y = tela->altura - SLOT_H - MARGEM_PEQUENA - (SLOT_H + SLOTS_ESPACO) * i;

		slots[i].botao_rotacionar.x = slots[i].x - BOTAO_ROTACIONAR_L - BOTAO_ROTACIONAR_OFFSET_DIREITA;
		slots[i].botao_rotacionar.y = centro(slots[i].y, SLOT_H, BOTAO_ROTACIONAR_H);
	}
}

void desenhar_slots(struct Slot slots[SLOTS_TAM], struct Tela *tela)
{
	for (int i = 0; i < SLOTS_TAM; i++)
	{
		desenhar_slot(&slots[i], tela);
	}
}

void criar_anuncio(struct Anuncio anuncios[ANUNCIOS_TAM], int bonus, int pontos, int combo)
{
	for (int i = 0; i < ANUNCIOS_TAM; i++)
	{
		if (!anuncios[i].usado)
		{
			anuncios[i].usado = true;

			anuncios[i].premio = bonus;

			anuncios[i].pontos = pontos;
			anuncios[i].combo = combo;

			anuncios[i].ticks = 0;

			return;
		}
	}
}

void remover_anuncio_do_topo(struct Anuncio anuncios[ANUNCIOS_TAM])
{
	for (int i = 0; i < ANUNCIOS_TAM - 1; i++)
	{
		anuncios[i] = anuncios[i + 1];
	}

	anuncios[ANUNCIOS_TAM - 1].usado = false;
}

void resetar_anuncios(struct Anuncio anuncios[ANUNCIOS_TAM])
{
	for (int i = 0; i < ANUNCIOS_TAM; i++)
	{
		anuncios[i].usado = false;
		anuncios[i].premio = -1;

		anuncios[i].pontos = 0;
		anuncios[i].combo = 0;

		anuncios[i].ticks = 0;
	}
}

void inicializar_anuncios(struct Anuncio anuncios[ANUNCIOS_TAM])
{
	resetar_anuncios(anuncios);
}

void desenhar_anuncios(struct Anuncio anuncios[ANUNCIOS_TAM], struct Tela *tela)
{
	struct Anuncio *anuncio = &anuncios[0];

	if (!anuncio->usado)
	{
		return;
	}

	char texto_pontos[ANUNCIOS_TEXTO_TAM] = { 0 };
	char texto_bonus[ANUNCIOS_TEXTO_TAM] = { 0 };

	sprintf(texto_pontos, "+%d pontos", anuncio->pontos);

	switch (anuncio->premio)
	{
		case PREMIO_MULTILINHA:
			sprintf(texto_bonus, "multilinha");
			break;
		case PREMIO_COMBO:
			sprintf(texto_bonus, "%dx combo", anuncio->combo);
			break;
		case PREMIO_TABULEIRO_CONCLUIDO:
			sprintf(texto_bonus, "tabuleiro concluido");
			break;
	}

	float opacidade = 1.0;

	int altura_texto = al_get_font_line_height(tela->fontes.smallestpixel7_10);

	int largura_pontos = al_get_text_width(tela->fontes.smallestpixel7_10, texto_pontos);
	int largura_bonus = al_get_text_width(tela->fontes.smallestpixel7_10, texto_bonus);
	
	int altura_caixa = altura_texto + 2 * ANUNCIO_BONUS_PREENCHIMENTO;
	int largura_caixa = largura_bonus + 2 * ANUNCIO_BONUS_PREENCHIMENTO;

	int largura_total = largura_pontos + largura_caixa + ANUNCIO_BONUS_ESPACO;

	int inicio_x = centro(0, tela->largura, largura_total);
	int inicio_y = MARGEM_PEQUENA;

	int centro_y = inicio_y + altura_texto / 2;

	int pontos_x = inicio_x;
	int pontos_y = inicio_y;

	int caixa_x1 = pontos_x + largura_pontos + ANUNCIO_BONUS_ESPACO;
	int caixa_y1 = centro_y - altura_caixa / 2;

	int caixa_x2 = caixa_x1 + largura_caixa;
	int caixa_y2 = centro_y + altura_caixa / 2;

	int bonus_x = (caixa_x1 + caixa_x2) / 2;
	int bonus_y = inicio_y;

	if (anuncio->ticks < ANUNCIO_DURACAO_FADE)
	{
		opacidade = (float)anuncio->ticks / ANUNCIO_DURACAO_FADE;
	}

	if (anuncio->ticks > ANUNCIO_DURACAO_TOTAL - ANUNCIO_DURACAO_FADE)
	{
		opacidade = (float)(ANUNCIO_DURACAO_TOTAL - anuncio->ticks) / ANUNCIO_DURACAO_FADE;
	}

	ALLEGRO_COLOR cor_preto = COR_PRETO;
	ALLEGRO_COLOR cor_branco = COR_BRANCO;
	ALLEGRO_COLOR cor_anuncio = COR_ANUNCIO;

	cor_preto.a = opacidade;
	cor_branco.a = opacidade;
	cor_anuncio.a = opacidade;

	al_draw_text(tela->fontes.smallestpixel7_10, cor_preto, pontos_x, pontos_y, ALLEGRO_ALIGN_LEFT, texto_pontos);

	al_draw_filled_rounded_rectangle(caixa_x1, caixa_y1, caixa_x2, caixa_y2, ANUNCIO_BONUS_RAIO, ANUNCIO_BONUS_RAIO, cor_anuncio);
	al_draw_text(tela->fontes.smallestpixel7_10, cor_branco, bonus_x, bonus_y, ALLEGRO_ALIGN_CENTER, texto_bonus);
}

bool existe_jogo_salvo()
{
	FILE *arquivo = fopen(ARQUIVO_SAVE, "r");

	if (arquivo != NULL)
	{
		fclose(arquivo);
		return true;
	}

	return false;
}

void escrever_habilidade(FILE *arquivo, struct Habilidade *habilidade)
{
	fprintf(arquivo, "%d %d %d\n", habilidade->bloqueado, habilidade->progresso, habilidade->quantidade);
}

bool ler_habilidade(FILE *arquivo, struct Habilidade *habilidade)
{
	int bloqueado, progresso, quantidade;

	if (fscanf(arquivo, "%d %d %d", &bloqueado, &progresso, &quantidade) != 3)
	{
		return false;
	}

	habilidade->bloqueado = bloqueado;
	habilidade->progresso = progresso;
	habilidade->quantidade = quantidade;

	return true;
}

void escrever_quadro(FILE *arquivo, struct Quadro *quadro)
{
	fprintf(arquivo, "%d\n", quadro->concluido);

	for (int i = 0; i < QUADRO_TAM; i++)
	{
		for (int j = 0; j < QUADRO_TAM; j++)
		{
			struct Dado *dado = &quadro->dados[i][j];

			fprintf(
				arquivo,
				"%d %d %d %d %d %d %d\n",
				dado->livre,
				dado->animacao,
				dado->ticks,
				dado->atraso,
				dado->direcao,
				dado->cor,
				dado->valor
			);
		}
	}
}

bool ler_quadro(FILE *arquivo, struct Quadro *quadro)
{
	int concluido;

	if (fscanf(arquivo, "%d\n", &concluido) != 1)
	{
		return false;
	}

	quadro->concluido = concluido;

	for (int i = 0; i < QUADRO_TAM; i++)
	{
		quadro->soma_linhas[i] = 0;
		quadro->soma_colunas[i] = 0;
	}

	for (int i = 0; i < QUADRO_TAM; i++)
	{
		for (int j = 0; j < QUADRO_TAM; j++)
		{
			int livre, animacao, ticks, atraso, direcao, cor, valor;
			
			if (fscanf(arquivo, "%d %d %d %d %d %d %d\n", &livre, &animacao, &ticks, &atraso, &direcao, &cor, &valor) != 7)
			{
				return false;
			}

			quadro->dados[i][j].livre = livre;
			quadro->dados[i][j].animacao = animacao;
			quadro->dados[i][j].ticks = ticks;
			quadro->dados[i][j].atraso = atraso;
			quadro->dados[i][j].direcao = direcao;
			quadro->dados[i][j].cor = cor;
			quadro->dados[i][j].valor = valor;

			if (valor != DADO_VAZIO)
			{
				quadro->soma_linhas[i] += valor;
				quadro->soma_colunas[j] += valor;
			}
		}
	}

	return true;
}

void escrever_peca(FILE *arquivo, struct Peca *peca)
{
	fprintf(arquivo, "%d %d %d", peca->cor, peca->linhas, peca->colunas);

	for (int i = 0; i < peca->linhas; i++)
	{
		for (int j = 0; j < peca->colunas; j++)
		{
			fprintf(arquivo, " %d", peca->dados[i][j]);
		}
	}

	fprintf(arquivo, "\n");
}

bool ler_peca(FILE *arquivo, struct Peca *peca)
{
	if (fscanf(arquivo, "%d %d %d", &peca->cor, &peca->linhas, &peca->colunas) != 3)
	{
		return false;
	}

	for (int i = 0; i < peca->linhas; i++)
	{
		for (int j = 0; j < peca->colunas; j++)
		{
			if (fscanf(arquivo, " %d", &peca->dados[i][j]) != 1)
			{
				return false;
			}
		}
	}

	return true;
}

void escrever_slot(FILE *arquivo, struct Slot *slot)
{
	fprintf(arquivo, "%d %d ", slot->ocupado, slot->rotacionando);
	escrever_peca(arquivo, &slot->peca);
}

bool ler_slot(FILE *arquivo, struct Slot *slot)
{
	int ocupado, rotacionando;
	
	if (fscanf(arquivo, "%d %d ", &ocupado, &rotacionando) != 2)
	{
		return false;
	}

	slot->ocupado = ocupado;
	slot->rotacionando = rotacionando;

	if (!ler_peca(arquivo, &slot->peca))
	{
		return false;
	}

	return true;
}

void escrever_jogada(FILE *arquivo, struct Jogada *jogada)
{
	fprintf(arquivo, "%d %d %d ", jogada->indice_origem, jogada->linha, jogada->coluna);
	escrever_peca(arquivo, &jogada->peca);
}

bool ler_jogada(FILE *arquivo, struct Jogada *jogada)
{
	if (fscanf(arquivo, "%d %d %d ", &jogada->indice_origem, &jogada->linha, &jogada->coluna) != 3)
	{
		return false;
	}

	ler_peca(arquivo, &jogada->peca);

	return true;
}

void escrever_jogo(FILE *arquivo, struct Jogo *jogo)
{
	fprintf(arquivo, "%d %d\n\n", jogo->escore, jogo->tempo);

	escrever_habilidade(arquivo, &jogo->desfazer);
	escrever_habilidade(arquivo, &jogo->bomba);
	escrever_habilidade(arquivo, &jogo->rotacao);
	fprintf(arquivo, "\n");

	escrever_quadro(arquivo, &jogo->quadro);
	fprintf(arquivo, "\n");

	for (int i = 0; i < SLOTS_TAM; i++)
	{
		escrever_slot(arquivo, &jogo->slots[i]);
	}

	fprintf(arquivo, "\n");

	escrever_jogada(arquivo, &jogo->jogada);

	fclose(arquivo);
}

bool ler_jogo(FILE *arquivo, struct Jogo *jogo)
{
	jogo->estado = ESTADO_RODANDO;
	jogo->slot_selecionado = -1;

	if (fscanf(arquivo, "%d %d\n\n", &jogo->escore, &jogo->tempo) != 2)
	{
		return false;
	}

	if (!ler_habilidade(arquivo, &jogo->desfazer))
	{
		return false;
	}
	
	if (!ler_habilidade(arquivo, &jogo->bomba))
	{
		return false;
	}

	if (!ler_habilidade(arquivo, &jogo->rotacao))
	{
		return false;
	}
	
	if (!ler_quadro(arquivo, &jogo->quadro))
	{
		return false;
	}

	for (int i = 0; i < SLOTS_TAM; i++)
	{
		if (!ler_slot(arquivo, &jogo->slots[i]))
		{
			return false;
		}
	}

	if (!ler_jogada(arquivo, &jogo->jogada))
	{
		return false;
	}

	return true;
}

bool carregar_jogo(struct Jogo *jogo)
{
	FILE *arquivo = fopen(ARQUIVO_SAVE, "r");
	bool sucesso = false;

	if (arquivo != NULL)
	{
		sucesso = ler_jogo(arquivo, jogo);
		fclose(arquivo);
	}

	return sucesso;
}

void salvar_jogo(struct Jogo *jogo)
{
	FILE *arquivo = fopen(ARQUIVO_SAVE, "w");

	if (arquivo != NULL)
	{
		escrever_jogo(arquivo, jogo);
		fclose(arquivo);
	}
}

void mudar_estado(struct Jogo *jogo, int estado)
{
	jogo->estado = estado;
}

void incrementar_score(struct Jogo *jogo, int pontos)
{
	jogo->escore += pontos;
	acumular_habilidade(&jogo->rotacao, pontos);
}

void pontuar_dado(struct Jogo *jogo)
{
	incrementar_score(jogo, PONTOS_DADO);
}

void pontuar_tabuleiro_concluido(struct Jogo *jogo)
{
	acumular_habilidade(&jogo->desfazer, 1);
	criar_anuncio(jogo->anuncios, PREMIO_TABULEIRO_CONCLUIDO, PONTOS_TABULEIRO_CONCLUIDO, 0);

	incrementar_score(jogo, PONTOS_TABULEIRO_CONCLUIDO);
}

void pontuar_multilinha(struct Jogo *jogo, int simultaneos)
{
	int pontos = PONTOS_MULTILINHA * (simultaneos - 1);

	acumular_habilidade(&jogo->bomba, 1);
	criar_anuncio(jogo->anuncios, PREMIO_MULTILINHA, pontos, 0);

	incrementar_score(jogo, pontos);
}

void pontuar_combo(struct Jogo *jogo, int sequencia)
{
	int pontos = PONTOS_COMBO * (sequencia - 1);

	acumular_habilidade(&jogo->bomba, 1);
	criar_anuncio(jogo->anuncios, PREMIO_COMBO, pontos, sequencia);

	incrementar_score(jogo, pontos);
}

void registrar_jogada(struct Jogo *jogo, int slot_origem, int linha, int coluna)
{
	jogo->desfazer.bloqueado = false;

	jogo->jogada.indice_origem = slot_origem;
	jogo->jogada.linha = linha;
	jogo->jogada.coluna = coluna;
	jogo->jogada.peca = jogo->slots[slot_origem].peca;
}

void desfazer_jogada(struct Jogo *jogo)
{
	jogo->desfazer.bloqueado = true;

	retirar_peca(&jogo->quadro, &jogo->jogada.peca, jogo->jogada.linha, jogo->jogada.coluna);
	verificar_quadro_concluido(&jogo->quadro);

	jogo->slots[jogo->jogada.indice_origem].ocupado = true;
	jogo->slots[jogo->jogada.indice_origem].peca = jogo->jogada.peca;
}

void analisar_consequencias(struct Jogo *jogo)
{
	struct Arranjos arranjos = formar_arranjos(&jogo->quadro);

	if (arranjos.origem > 0)
	{
		jogo->desfazer.bloqueado = true;
	}

	if (arranjos.origem > 1)
	{
		pontuar_multilinha(jogo, arranjos.origem);
	}

	if (arranjos.sequencia > 1)
	{
		pontuar_combo(jogo, arranjos.sequencia);
	}
}

bool pode_usar_rotacao(struct Jogo *jogo, struct Slot *slot)
{
	return slot->rotacionando || slot->ocupado && pode_usar_habilidade(&jogo->rotacao) && pode_rotacionar_peca(&slot->peca);
}

void usar_desfazer(struct Jogo *jogo)
{
	if (usar_habilidade(&jogo->desfazer))
	{
		desfazer_jogada(jogo);
	}
}

void usar_bomba(struct Jogo *jogo)
{
	if (usar_habilidade(&jogo->bomba))
	{
		int indice_a = inteiro_aleatorio(0, QUADRO_TAM);
		int direcao_a = inteiro_aleatorio(0, DIRECOES_NUM);

		int indice_b;
		int direcao_b;

		do {
			indice_b = inteiro_aleatorio(0, QUADRO_TAM);
			direcao_b = inteiro_aleatorio(0, DIRECOES_NUM);
		} while (direcao_a == direcao_b && indice_a == indice_b);

		explodir_quadro(&jogo->quadro, indice_a, direcao_a);
		explodir_quadro(&jogo->quadro, indice_b, direcao_b);

		analisar_consequencias(jogo);

		jogo->desfazer.bloqueado = true;
	}
}

void usar_rotacao(struct Jogo *jogo, struct Slot *slot)
{
	if (slot->rotacionando || usar_habilidade(&jogo->rotacao))
	{
		rotacionar_slot(slot);
	}
}

bool existe_espaco_disponivel_para_slot(struct Jogo *jogo, struct Slot *slot)
{
	struct Peca peca = slot->peca;

	if (existe_espaco_disponivel_para_peca(&jogo->quadro, &peca))
	{
		return true;
	}

	if (pode_usar_rotacao(jogo, slot))
	{
		for (int i = 1; i < ROTACAO_CICLO; i++)
		{
			peca = rotacionar_peca(&peca);

			if (existe_espaco_disponivel_para_peca(&jogo->quadro, &peca))
			{
				return true;
			}
		}
	}

	return false;
}

bool verificar_fim_de_jogo(struct Jogo *jogo)
{
	if (pode_usar_habilidade(&jogo->desfazer))
	{
		return false;
	}

	if (pode_usar_habilidade(&jogo->bomba))
	{
		return false;
	}

	for (int i = 0; i < SLOTS_TAM; i++)
	{
		if (jogo->slots[i].ocupado)
		{
			if (existe_espaco_disponivel_para_slot(jogo, &jogo->slots[i]))
			{
				return false;
			}
		}
	}
	
	return true;
}

void preparar_inicio(struct Sistema *sistema)
{
	sistema->inicio.botao_continuar_jogo.desabilitado = !existe_jogo_salvo();
}

void transicionar_para_cena(struct Sistema *sistema, int cena)
{
	if (cena == CENA_INICIO)
	{
		preparar_inicio(sistema);
	}

	sistema->cena = cena;
}

void acabar_jogo(struct Jogo *jogo)
{
	jogo->game_over.escore = jogo->escore;
	jogo->game_over.tempo = jogo->tempo;

	mudar_estado(jogo, ESTADO_GAME_OVER);
}

void pausar_jogo(struct Jogo *jogo)
{
	mudar_estado(jogo, ESTADO_PAUSADO);
}

void resumir_jogo(struct Jogo *jogo)
{
	mudar_estado(jogo, ESTADO_RODANDO);
}

void sair_do_jogo(struct Sistema *sistema)
{
	transicionar_para_cena(sistema, CENA_INICIO);
}

void resetar_habilidades(struct Jogo *jogo)
{
	resetar_habilidade(&jogo->desfazer);
	resetar_habilidade(&jogo->bomba);
	resetar_habilidade(&jogo->rotacao);

	jogo->desfazer.bloqueado = true;
}

void resetar_jogo(struct Jogo *jogo)
{
	jogo->estado = ESTADO_RODANDO;

	jogo->escore = 0;
	jogo->tempo = 0;

	jogo->slot_selecionado = 1;

	resetar_quadro(&jogo->quadro);
	resetar_slots(jogo->slots);
	resetar_habilidades(jogo);
}

void inicializar_desfazer(struct Habilidade *desfazer, struct Sprites *sprites, struct Sons *sons)
{
	inicializar_habilidade(desfazer, DESFAZER_TABULEIROS_CONCLUIDOS, false);

	desfazer->bloqueado = true;

	desfazer->botao.sprite_padrao = sprites->habilidade_desfazer_padrao;
	desfazer->botao.sprite_sobre = sprites->habilidade_desfazer_padrao;
	desfazer->botao.sprite_pressionado = sprites->habilidade_desfazer_pressionado;
	desfazer->botao.sprite_desabilitado = sprites->habilidade_desfazer_desabilitado;

	desfazer->botao.som_desabilitado = sons->botao_bloqueado;
}

void inicializar_bomba(struct Habilidade *bomba, struct Sprites *sprites, struct Sons *sons)
{
	inicializar_habilidade(bomba, BOMBA_COMBINACOES, true);

	bomba->botao.sprite_padrao = sprites->habilidade_bomba_padrao;
	bomba->botao.sprite_sobre = sprites->habilidade_bomba_padrao;
	bomba->botao.sprite_pressionado = sprites->habilidade_bomba_pressionado;
	bomba->botao.sprite_desabilitado = sprites->habilidade_bomba_desabilitado;

	bomba->botao.som_pressionar = sons->impacto;
	bomba->botao.som_desabilitado = sons->botao_bloqueado;
}

void inicializar_rotacao(struct Habilidade *rotacao, struct Sprites *sprites)
{
	inicializar_habilidade(rotacao, ROTACAO_PONTOS, true);

	rotacao->botao.sprite_padrao = sprites->habilidade_rotacao_padrao;
	rotacao->botao.sprite_sobre = sprites->habilidade_rotacao_padrao;
	rotacao->botao.sprite_pressionado = sprites->habilidade_rotacao_padrao;
	rotacao->botao.sprite_desabilitado = sprites->habilidade_rotacao_padrao;
}

void inicializar_habilidades(struct Jogo *jogo, struct Sprites *sprites, struct Sons *sons)
{
	inicializar_desfazer(&jogo->desfazer, sprites, sons);
	inicializar_bomba(&jogo->bomba, sprites, sons);
	inicializar_rotacao(&jogo->rotacao, sprites);
}

void inicializar_pausa(struct Pausa *pausa, struct Sprites *sprites, struct Sons *sons)
{
	inicializar_botao(&pausa->botao_resumir, PAUSA_BOTAO_MENU_L, PAUSA_BOTAO_MENU_H);
	inicializar_botao(&pausa->botao_reiniciar, PAUSA_BOTAO_MENU_L, PAUSA_BOTAO_MENU_H);
	inicializar_botao(&pausa->botao_abandonar, PAUSA_BOTAO_MENU_L, PAUSA_BOTAO_MENU_H);
	inicializar_botao(&pausa->botao_sair_e_salvar, PAUSA_BOTAO_MENU_L, PAUSA_BOTAO_MENU_H);

	pausa->botao_resumir.sprite_padrao = sprites->pausa_botao_resumir_padrao;
	pausa->botao_resumir.sprite_sobre = sprites->pausa_botao_resumir_sobre;
	pausa->botao_resumir.sprite_pressionado = sprites->pausa_botao_resumir_padrao;
	pausa->botao_resumir.sprite_desabilitado = sprites->pausa_botao_resumir_padrao;

	pausa->botao_resumir.som_sobre = sons->botao_sobre;
	pausa->botao_resumir.som_pressionar = sons->botao_selecionar;

	pausa->botao_reiniciar.sprite_padrao = sprites->pausa_botao_reiniciar_padrao;
	pausa->botao_reiniciar.sprite_sobre = sprites->pausa_botao_reiniciar_sobre;
	pausa->botao_reiniciar.sprite_pressionado = sprites->pausa_botao_reiniciar_padrao;
	pausa->botao_reiniciar.sprite_desabilitado = sprites->pausa_botao_reiniciar_padrao;

	pausa->botao_reiniciar.som_sobre = sons->botao_sobre;
	pausa->botao_reiniciar.som_pressionar = sons->botao_selecionar;

	pausa->botao_abandonar.sprite_padrao = sprites->pausa_botao_abandonar_padrao;
	pausa->botao_abandonar.sprite_sobre = sprites->pausa_botao_abandonar_sobre;
	pausa->botao_abandonar.sprite_pressionado = sprites->pausa_botao_abandonar_padrao;
	pausa->botao_abandonar.sprite_desabilitado = sprites->pausa_botao_abandonar_padrao;

	pausa->botao_abandonar.som_sobre = sons->botao_sobre;
	pausa->botao_abandonar.som_pressionar = sons->botao_selecionar;

	pausa->botao_sair_e_salvar.sprite_padrao = sprites->pausa_botao_sair_e_salvar_padrao;
	pausa->botao_sair_e_salvar.sprite_sobre = sprites->pausa_botao_sair_e_salvar_sobre;
	pausa->botao_sair_e_salvar.sprite_pressionado = sprites->pausa_botao_sair_e_salvar_padrao;
	pausa->botao_sair_e_salvar.sprite_desabilitado = sprites->pausa_botao_sair_e_salvar_padrao;

	pausa->botao_sair_e_salvar.som_sobre = sons->botao_sobre;
	pausa->botao_sair_e_salvar.som_pressionar = sons->botao_selecionar;
}

void inicializar_game_over(struct GameOver *game_over, struct Sprites *sprites, struct Sons *sons)
{
	game_over->tempo = 0;
	game_over->escore = 0;

	inicializar_botao(&game_over->botao_sair, GAME_OVER_BOTAO_L, GAME_OVER_BOTAO_H);
	inicializar_botao(&game_over->botao_jogar_novamente, GAME_OVER_BOTAO_L, GAME_OVER_BOTAO_H);

	game_over->botao_sair.sprite_padrao = sprites->game_over_botao_sair_padrao;
	game_over->botao_sair.sprite_sobre = sprites->game_over_botao_sair_sobre;
	game_over->botao_sair.sprite_pressionado = sprites->game_over_botao_sair_padrao;
	game_over->botao_sair.sprite_desabilitado = sprites->game_over_botao_sair_padrao;

	game_over->botao_sair.som_sobre = sons->botao_sobre;
	game_over->botao_sair.som_pressionar = sons->botao_selecionar;

	game_over->botao_jogar_novamente.sprite_padrao = sprites->game_over_botao_jogar_novamente_padrao;
	game_over->botao_jogar_novamente.sprite_sobre = sprites->game_over_botao_jogar_novamente_sobre;
	game_over->botao_jogar_novamente.sprite_pressionado = sprites->game_over_botao_jogar_novamente_padrao;
	game_over->botao_jogar_novamente.sprite_desabilitado = sprites->game_over_botao_jogar_novamente_padrao;

	game_over->botao_jogar_novamente.som_sobre = sons->botao_sobre;
	game_over->botao_jogar_novamente.som_pressionar = sons->botao_selecionar;
}

void inicializar_jogo(struct Jogo *jogo, struct Sprites *sprites, struct Sons *sons)
{
	jogo->estado = ESTADO_RODANDO;

	jogo->escore = 0;
	jogo->tempo = 0;

	jogo->slot_selecionado = 1;

	inicializar_quadro(&jogo->quadro);
	inicializar_slots(jogo->slots, sprites, sons);
	inicializar_habilidades(jogo, sprites, sons);
	inicializar_anuncios(jogo->anuncios);
	inicializar_pausa(&jogo->pausa, sprites, sons);
	inicializar_game_over(&jogo->game_over, sprites, sons);

	inicializar_botao(&jogo->botao_pausar, BOTAO_PAUSAR_L, BOTAO_PAUSAR_L);

	jogo->botao_pausar.sprite_padrao = sprites->botao_pausar_padrao;
	jogo->botao_pausar.sprite_sobre = sprites->botao_pausar_sobre;
	jogo->botao_pausar.sprite_pressionado = sprites->botao_pausar_padrao;
	jogo->botao_pausar.sprite_desabilitado = sprites->botao_pausar_padrao;
}

void posicionar_habilidades(struct Jogo *jogo, struct Tela *tela)
{
	int espaco_y = HABILIDADE_BOTAO_H + HABILIDADES_ESPACO;

	int x = MARGEM_PEQUENA;
	int y = tela->altura - MARGEM_PEQUENA - HABILIDADE_BOTAO_H;

	posicionar_habilidade(&jogo->rotacao, x, y);

	y -= espaco_y;
	posicionar_habilidade(&jogo->bomba, x, y);

	y -= espaco_y;
	posicionar_habilidade(&jogo->desfazer, x, y);
}

void posicionar_pausa(struct Pausa *pausa, struct Tela *tela)
{
	int menu_x = centro(0, tela->largura, PAUSA_BOTAO_MENU_L);
	int menu_y = centro(0, tela->altura, PAUSA_H);

	menu_y += PAUSA_TITULO_H;
	menu_y += PAUSA_TITULO_ESPACO;

	pausa->botao_resumir.x = menu_x;
	pausa->botao_resumir.y = menu_y;

	menu_y += PAUSA_BOTAO_MENU_H;
	menu_y += PAUSA_BOTOES_ESPACO;

	pausa->botao_reiniciar.x = menu_x;
	pausa->botao_reiniciar.y = menu_y;

	menu_y += PAUSA_BOTAO_MENU_H;
	menu_y += PAUSA_BOTOES_ESPACO;

	pausa->botao_abandonar.x = menu_x;
	pausa->botao_abandonar.y = menu_y;

	menu_y += PAUSA_BOTAO_MENU_H;
	menu_y += PAUSA_BOTOES_ESPACO;

	pausa->botao_sair_e_salvar.x = menu_x;
	pausa->botao_sair_e_salvar.y = menu_y;
}

void posicionar_game_over(struct GameOver *game_over, struct Tela *tela)
{
	int menu_x = centro(0, tela->largura, 2 * GAME_OVER_BOTAO_L);
	int menu_y = centro(0, tela->altura, GAME_OVER_H);

	menu_y += GAME_OVER_TITULO_H;
	menu_y += GAME_OVER_TITULO_ESPACO;
	menu_y += 2 * GAME_OVER_INFORMACAO_H;
	menu_y += GAME_OVER_MENU_ESPACO;

	game_over->botao_sair.x = menu_x;
	game_over->botao_sair.y = menu_y;

	menu_x += GAME_OVER_BOTAO_L;

	game_over->botao_jogar_novamente.x = menu_x;
	game_over->botao_jogar_novamente.y = menu_y;
}

void posicionar_jogo(struct Jogo *jogo, struct Tela *tela)
{
	posicionar_quadro(&jogo->quadro, tela);
	posicionar_slots(jogo->slots, tela);
	posicionar_habilidades(jogo, tela);
	posicionar_pausa(&jogo->pausa, tela);
	posicionar_game_over(&jogo->game_over, tela);

	jogo->botao_pausar.x = MARGEM_PEQUENA;
	jogo->botao_pausar.y = BOTAO_PAUSAR_OFFSET_CIMA;
}

void atualizar_habilidades(struct Jogo *jogo)
{
	atualizar_habilidade(&jogo->rotacao);
	atualizar_habilidade(&jogo->bomba);
	atualizar_habilidade(&jogo->desfazer);
}

void atualizar_slots(struct Jogo *jogo)
{
	for (int i = 0; i < SLOTS_TAM; i++)
	{
		struct Slot *slot = &jogo->slots[i];

		slot->botao_rotacionar.desabilitado = false;

		if (!slot->arrastando)
		{
			slot->peca.x = centro(slot->x, SLOT_L, largura_peca(&slot->peca));
			slot->peca.y = centro(slot->y, SLOT_H, altura_peca(&slot->peca));
		}

		slot->botao_rotacionar.desabilitado = !pode_usar_rotacao(jogo, slot);
	}
}

void atualizar_quadro(struct Jogo *jogo, struct Sons *sons)
{
	for (int i = 0; i < QUADRO_TAM; i++)
	{
		for (int j = 0; j < QUADRO_TAM; j++)
		{
			struct Dado *dado = &jogo->quadro.dados[i][j];

			dado->ticks++;

			if (dado->ticks > dado->atraso)
			{
				int duracao = dado->ticks - dado->atraso;

				switch (dado->animacao)
				{
					case ANIMACAO_COLAPSO:
						if (duracao == 1)
						{
							al_play_sample(sons->pop, 1.0, 0.0, fracao_aleatoria(0.7, 1.3), ALLEGRO_PLAYMODE_ONCE, NULL);
						}

						if (duracao == COLAPSO_FRAMES_NUM * COLAPSO_FRAME_PERIODO)
						{
							zerar_dado(&jogo->quadro, i, j);
							pontuar_dado(jogo);
						}
						break;	
					case ANIMACAO_EXPLOSAO:
						if (duracao == EXPLOSAO_FRAMES_NUM * EXPLOSAO_FRAME_PERIODO)
						{
							zerar_dado(&jogo->quadro, i, j);
						}
						break;
				}
			}
		}
	}

	if (verificar_quadro_concluido(&jogo->quadro))
	{
		pontuar_tabuleiro_concluido(jogo);
	}
}

void atualizar_anuncios(struct Jogo *jogo)
{
	struct Anuncio *topo = &jogo->anuncios[0];

	if (topo->usado)
	{
		topo->ticks++;

		if (topo->ticks >= ANUNCIO_DURACAO_TOTAL)
		{
			remover_anuncio_do_topo(jogo->anuncios);
		}
	}
}

void desenhar_pontuacao(struct Jogo *jogo, struct Tela *tela)
{
	int total_segundos = jogo->tempo * PERIODO_TICK;

	int minutos = total_segundos / 60;
	int segundos = total_segundos % 60;

	al_draw_textf(tela->fontes.fipps_12, COR_PRETO, MARGEM_PEQUENA, ESCORE_OFFSET_CIMA, ALLEGRO_ALIGN_LEFT, "%03d", jogo->escore);
	al_draw_textf(tela->fontes.pixelmix_8, COR_PRETO, MARGEM_PEQUENA, TEMPO_OFFSET_CIMA, ALLEGRO_ALIGN_LEFT, "%02d:%02d", minutos, segundos);
}

void desenhar_habilidades(struct Jogo *jogo, struct Tela *tela)
{
	desenhar_habilidade(&jogo->rotacao, tela);
	desenhar_habilidade(&jogo->bomba, tela);
	desenhar_habilidade(&jogo->desfazer, tela);
}

void desenhar_pausa(struct Pausa *pausa, struct Tela *tela)
{
	int container_x = centro(0, tela->largura, PAUSA_TITULO_L);
	int container_y = centro(0, tela->altura, PAUSA_H);

	al_draw_bitmap(tela->sprites.pausa_titulo, container_x, container_y, 0);

	desenhar_botao(&pausa->botao_resumir);
	desenhar_botao(&pausa->botao_reiniciar);
	desenhar_botao(&pausa->botao_abandonar);
	desenhar_botao(&pausa->botao_sair_e_salvar);
}

void desenhar_game_over(struct GameOver *game_over, struct Tela *tela)
{
	int total_segundos = game_over->tempo * PERIODO_TICK;

	int minutos = total_segundos / 60;
	int segundos = total_segundos % 60;

	int container_x = centro(0, tela->largura, GAME_OVER_TITULO_L);
	int container_y = centro(0, tela->altura, GAME_OVER_H);

	int informacao_x = container_x;
	int informacao_y = container_y + GAME_OVER_TITULO_H + GAME_OVER_TITULO_ESPACO;

	al_draw_bitmap(tela->sprites.game_over_titulo, container_x, container_y, 0);

	al_draw_textf(tela->fontes.pixelmix_8, COR_BRANCO, informacao_x, informacao_y, ALLEGRO_ALIGN_LEFT, "pontos:");
	al_draw_textf(tela->fontes.pixelmix_8, COR_BRANCO, informacao_x + GAME_OVER_L, informacao_y, ALLEGRO_ALIGN_RIGHT, "%d", game_over->escore);

	informacao_y += GAME_OVER_INFORMACAO_H;

	al_draw_textf(tela->fontes.pixelmix_8, COR_BRANCO, informacao_x, informacao_y, ALLEGRO_ALIGN_LEFT, "tempo:");
	al_draw_textf(tela->fontes.pixelmix_8, COR_BRANCO, informacao_x + GAME_OVER_L, informacao_y, ALLEGRO_ALIGN_RIGHT, "%02d:%02d", minutos, segundos);

	desenhar_botao(&game_over->botao_sair);
	desenhar_botao(&game_over->botao_jogar_novamente);
}

void controlar_jogo_rodando(struct Tela *tela, struct Sistema *sistema, ALLEGRO_EVENT *evento)
{
	switch (evento->type)
	{
		case ALLEGRO_EVENT_TIMER:
			atualizar_quadro(&sistema->jogo, &tela->sons);
			atualizar_slots(&sistema->jogo);
			atualizar_anuncios(&sistema->jogo);
			atualizar_habilidades(&sistema->jogo);

			if (verificar_fim_de_jogo(&sistema->jogo))
			{
				acabar_jogo(&sistema->jogo);

				inserir_recorde(sistema->recordes, sistema->jogo.escore, sistema->jogo.tempo);
				salvar_recordes(sistema->recordes);
			}

			sistema->jogo.tempo++;
			break;
		case ALLEGRO_EVENT_MOUSE_AXES:
		{
			int mouse_x = evento->mouse.x / tela->escala;
			int mouse_y = evento->mouse.y / tela->escala;

			detectar_sobre_botao(&sistema->jogo.desfazer.botao, mouse_x, mouse_y);
			detectar_sobre_botao(&sistema->jogo.bomba.botao, mouse_x, mouse_y);
			detectar_sobre_botao(&sistema->jogo.rotacao.botao, mouse_x, mouse_y);
			
			detectar_sobre_botao(&sistema->jogo.botao_pausar, mouse_x, mouse_y);

			for (int i = 0; i < SLOTS_TAM; i++)
			{
				detectar_sobre_botao(&sistema->jogo.slots[i].botao_rotacionar, mouse_x, mouse_y);
			}

			if (sistema->jogo.slot_selecionado != -1)
			{
				arrastar_slot(&sistema->jogo.slots[sistema->jogo.slot_selecionado], mouse_x, mouse_y);
			}

			break;
		}
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		{
			int mouse_x = evento->mouse.x / tela->escala;
			int mouse_y = evento->mouse.y / tela->escala;

			if (evento->mouse.button & 1)
			{
				if (pressionar_botao(&sistema->jogo.desfazer.botao))
				{
					usar_desfazer(&sistema->jogo);
				}

				if (pressionar_botao(&sistema->jogo.bomba.botao))
				{
					usar_bomba(&sistema->jogo);
				}

				if (pressionar_botao(&sistema->jogo.botao_pausar))
				{
					pausar_jogo(&sistema->jogo);
					resetar_botao(&sistema->jogo.botao_pausar);
				}

				for (int i = 0; i < SLOTS_TAM; i++)
				{
					if (pressionar_botao(&sistema->jogo.slots[i].botao_rotacionar))
					{
						usar_rotacao(&sistema->jogo, &sistema->jogo.slots[i]);
					}
				}

				for (int i = 0; i < SLOTS_TAM; i++)
				{
					if (colisao_slot(&sistema->jogo.slots[i], mouse_x, mouse_y))
					{
						if (pegar_slot(&sistema->jogo.slots[i], mouse_x, mouse_y))
						{
							sistema->jogo.slot_selecionado = i;
						}
					}
				}
			}

			break;
		}
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			if (evento->mouse.button & 1)
			{
				soltar_botao(&sistema->jogo.desfazer.botao);
				soltar_botao(&sistema->jogo.bomba.botao);
				soltar_botao(&sistema->jogo.rotacao.botao);

				for (int i = 0; i < SLOTS_TAM; i++)
				{
					soltar_botao(&sistema->jogo.slots[i].botao_rotacionar);
				}

				if (sistema->jogo.slot_selecionado != -1)
				{
					struct Slot *slot = &sistema->jogo.slots[sistema->jogo.slot_selecionado];

					int linha;
					int coluna;

					if (largar_slot(&sistema->jogo.quadro, slot, &linha, &coluna))
					{
						registrar_jogada(&sistema->jogo, sistema->jogo.slot_selecionado, linha, coluna);
						analisar_consequencias(&sistema->jogo);

						al_play_sample(tela->sons.snap, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

						if (slot_vazios(sistema->jogo.slots))
						{
							gerar_slots(sistema->jogo.slots);
						}
					}

					sistema->jogo.slot_selecionado = -1;;
				}
			}
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			if (evento->keyboard.keycode == ALLEGRO_KEY_B)
			{
				pontuar_tabuleiro_concluido(&sistema->jogo);
			}

			if (sistema->jogo.slot_selecionado != -1)
			{
				if (evento->keyboard.keycode == ALLEGRO_KEY_SPACE)
				{
					gerar_slot(&sistema->jogo.slots[sistema->jogo.slot_selecionado]);
				}

				if (evento->keyboard.keycode == ALLEGRO_KEY_R)
				{
					rotacionar_slot(&sistema->jogo.slots[sistema->jogo.slot_selecionado]);
				}
			}

			if (evento->keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				pausar_jogo(&sistema->jogo);
			}
			break;
	}

}

void controlar_jogo_pausado(struct Tela *tela, struct Sistema *sistema, ALLEGRO_EVENT *evento)
{
	switch (evento->type)
	{
		case ALLEGRO_EVENT_MOUSE_AXES:
		{
			int mouse_x = evento->mouse.x / tela->escala;
			int mouse_y = evento->mouse.y / tela->escala;

			detectar_sobre_botao(&sistema->jogo.pausa.botao_resumir, mouse_x, mouse_y);
			detectar_sobre_botao(&sistema->jogo.pausa.botao_reiniciar, mouse_x, mouse_y);
			detectar_sobre_botao(&sistema->jogo.pausa.botao_abandonar, mouse_x, mouse_y);
			detectar_sobre_botao(&sistema->jogo.pausa.botao_sair_e_salvar, mouse_x, mouse_y);

			break;
		}
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			if (evento->mouse.button & 1)
			{
				if (pressionar_botao(&sistema->jogo.pausa.botao_resumir))
				{
					resumir_jogo(&sistema->jogo);
					resetar_botao(&sistema->jogo.pausa.botao_resumir);
				}

				if (pressionar_botao(&sistema->jogo.pausa.botao_reiniciar))
				{
					resetar_jogo(&sistema->jogo);
					resetar_botao(&sistema->jogo.pausa.botao_reiniciar);
				}

				if (pressionar_botao(&sistema->jogo.pausa.botao_abandonar))
				{
					sair_do_jogo(sistema);
					resetar_botao(&sistema->jogo.pausa.botao_abandonar);
				}

				if (pressionar_botao(&sistema->jogo.pausa.botao_sair_e_salvar))
				{
					salvar_jogo(&sistema->jogo);
					sair_do_jogo(sistema);
					resetar_botao(&sistema->jogo.pausa.botao_sair_e_salvar);
				}
			}
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			if (evento->keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				resumir_jogo(&sistema->jogo);
			}
			break;
	}
}

void controlar_jogo_game_over(struct Tela *tela, struct Sistema *sistema, ALLEGRO_EVENT *evento)
{
	switch (evento->type)
	{
		case ALLEGRO_EVENT_MOUSE_AXES:
		{
			int mouse_x = evento->mouse.x / tela->escala;
			int mouse_y = evento->mouse.y / tela->escala;

			detectar_sobre_botao(&sistema->jogo.game_over.botao_sair, mouse_x, mouse_y);
			detectar_sobre_botao(&sistema->jogo.game_over.botao_jogar_novamente, mouse_x, mouse_y);

			break;
		}
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			if (evento->mouse.button & 1)
			{
				if (pressionar_botao(&sistema->jogo.game_over.botao_sair))
				{
					sair_do_jogo(sistema);
					resetar_botao(&sistema->jogo.game_over.botao_sair);
				}

				if (pressionar_botao(&sistema->jogo.game_over.botao_jogar_novamente))
				{
					resetar_jogo(&sistema->jogo);
					resetar_botao(&sistema->jogo.game_over.botao_jogar_novamente);
				}
			}

			break;
	}
}

void cena_jogo(struct Tela *tela, struct Sistema *sistema, ALLEGRO_EVENT *evento)
{
	switch (sistema->jogo.estado)
	{
		case ESTADO_RODANDO:
			controlar_jogo_rodando(tela, sistema, evento);
			break;
		case ESTADO_PAUSADO:
			controlar_jogo_pausado(tela, sistema, evento);
			break;
		case ESTADO_GAME_OVER:
			controlar_jogo_game_over(tela, sistema, evento);
			break;
	}

	if (sistema->redesenhar)
	{
		preparar_desenho(tela);

		desenhar_quadro(&sistema->jogo.quadro, tela);
		desenhar_slots(sistema->jogo.slots, tela);
		desenhar_anuncios(sistema->jogo.anuncios, tela);
		desenhar_habilidades(&sistema->jogo, tela);
		desenhar_pontuacao(&sistema->jogo, tela);

		desenhar_botao(&sistema->jogo.botao_pausar);

		if (sistema->jogo.slot_selecionado != -1)
		{
			desenhar_peca(&sistema->jogo.slots[sistema->jogo.slot_selecionado].peca, tela);
		}

		if (sistema->jogo.estado == ESTADO_PAUSADO || sistema->jogo.estado == ESTADO_GAME_OVER)
		{
			al_draw_filled_rectangle(0, 0, tela->largura, tela->altura, COR_SOBREPOSICAO);

			switch (sistema->jogo.estado)
			{
				case ESTADO_PAUSADO:
					desenhar_pausa(&sistema->jogo.pausa, tela);
					break;
				case ESTADO_GAME_OVER:
					desenhar_game_over(&sistema->jogo.game_over, tela);
					break;
			}
		}

		finalizar_desenho(tela);
	}
}

void inicializar_inicio(struct Inicio *inicio, struct Sprites *sprites, struct Sons *sons)
{
	inicializar_botao(&inicio->botao_continuar_jogo, INICIO_BOTAO_MENU_L, INICIO_BOTAO_MENU_H);
	inicializar_botao(&inicio->botao_novo_jogo, INICIO_BOTAO_MENU_L, INICIO_BOTAO_MENU_H);
	inicializar_botao(&inicio->botao_sair, INICIO_BOTAO_MENU_L, INICIO_BOTAO_MENU_H);
	inicializar_botao(&inicio->botao_placar, INICIO_BOTAO_MARCADOR_L, INICIO_BOTAO_MARCADOR_H);
	inicializar_botao(&inicio->botao_ajuda, INICIO_BOTAO_MARCADOR_L, INICIO_BOTAO_MARCADOR_H);

	inicio->botao_continuar_jogo.sprite_padrao = sprites->inicio_botao_continuar_jogo_padrao;
	inicio->botao_continuar_jogo.sprite_sobre = sprites->inicio_botao_continuar_jogo_padrao;
	inicio->botao_continuar_jogo.sprite_pressionado = sprites->inicio_botao_continuar_jogo_padrao;
	inicio->botao_continuar_jogo.sprite_desabilitado = sprites->inicio_botao_continuar_jogo_desabilitado;

	inicio->botao_continuar_jogo.som_pressionar = sons->botao_selecionar;

	inicio->botao_novo_jogo.sprite_padrao = sprites->inicio_botao_novo_jogo_padrao;
	inicio->botao_novo_jogo.sprite_sobre = sprites->inicio_botao_novo_jogo_padrao;
	inicio->botao_novo_jogo.sprite_pressionado = sprites->inicio_botao_novo_jogo_padrao;
	inicio->botao_novo_jogo.sprite_desabilitado = sprites->inicio_botao_novo_jogo_padrao;

	inicio->botao_novo_jogo.som_pressionar = sons->botao_selecionar;

	inicio->botao_sair.sprite_padrao = sprites->inicio_botao_sair_padrao;
	inicio->botao_sair.sprite_sobre = sprites->inicio_botao_sair_padrao;
	inicio->botao_sair.sprite_pressionado = sprites->inicio_botao_sair_padrao;
	inicio->botao_sair.sprite_desabilitado = sprites->inicio_botao_sair_padrao;

	inicio->botao_sair.som_pressionar = sons->botao_selecionar;

	inicio->botao_placar.sprite_padrao = sprites->inicio_botao_placar_padrao;
	inicio->botao_placar.sprite_sobre = sprites->inicio_botao_placar_sobre;
	inicio->botao_placar.sprite_pressionado = sprites->inicio_botao_placar_padrao;
	inicio->botao_placar.sprite_desabilitado = sprites->inicio_botao_placar_padrao;

	inicio->botao_placar.som_pressionar = sons->botao_selecionar;

	inicio->botao_ajuda.sprite_padrao = sprites->inicio_botao_ajuda_padrao;
	inicio->botao_ajuda.sprite_sobre = sprites->inicio_botao_ajuda_sobre;
	inicio->botao_ajuda.sprite_pressionado = sprites->inicio_botao_ajuda_padrao;
	inicio->botao_ajuda.sprite_desabilitado = sprites->inicio_botao_ajuda_padrao;

	inicio->botao_ajuda.som_pressionar = sons->botao_selecionar;
}

void posicionar_inicio(struct Inicio *inicio, struct Tela *tela)
{
	int menu_x = centro(0, tela->largura, INICIO_BOTAO_MENU_L);
	int menu_y = INICIO_BOTOES_OFFSET_CIMA;

	int marcador_x = tela->largura - INICIO_BOTAO_MARCADOR_L;
	int marcador_y = INICIO_BOTOES_OFFSET_CIMA;

	inicio->botao_continuar_jogo.x = menu_x;
	inicio->botao_continuar_jogo.y = menu_y;

	menu_y += INICIO_BOTAO_MENU_H + INICIO_BOTOES_ESPACO;

	inicio->botao_novo_jogo.x = menu_x;
	inicio->botao_novo_jogo.y = menu_y;

	menu_y += INICIO_BOTAO_MENU_H + INICIO_BOTOES_ESPACO;

	inicio->botao_sair.x = menu_x;
	inicio->botao_sair.y = menu_y;

	inicio->botao_placar.x = marcador_x;
	inicio->botao_placar.y = marcador_y;

	marcador_y += INICIO_BOTAO_MARCADOR_H + INICIO_BOTOES_ESPACO;

	inicio->botao_ajuda.x = marcador_x;
	inicio->botao_ajuda.y = marcador_y;
}

void cena_inicio(struct Tela *tela, struct Sistema *sistema, ALLEGRO_EVENT *evento)
{
	switch (evento->type)
	{
		case ALLEGRO_EVENT_MOUSE_AXES:
		{
			int mouse_x = evento->mouse.x / tela->escala;
			int mouse_y = evento->mouse.y / tela->escala;

			detectar_sobre_botao(&sistema->inicio.botao_continuar_jogo, mouse_x, mouse_y);
			detectar_sobre_botao(&sistema->inicio.botao_novo_jogo, mouse_x, mouse_y);
			detectar_sobre_botao(&sistema->inicio.botao_sair, mouse_x, mouse_y);
			detectar_sobre_botao(&sistema->inicio.botao_placar, mouse_x, mouse_y);
			detectar_sobre_botao(&sistema->inicio.botao_ajuda, mouse_x, mouse_y);

			break;
		}
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			if (evento->mouse.button & 1)
			{
				if (pressionar_botao(&sistema->inicio.botao_continuar_jogo))
				{
					if (!carregar_jogo(&sistema->jogo))
					{
						resetar_jogo(&sistema->jogo);
					}

					transicionar_para_cena(sistema, CENA_JOGO);
					resetar_botao(&sistema->inicio.botao_continuar_jogo);
				}

				if (pressionar_botao(&sistema->inicio.botao_novo_jogo))
				{
					resetar_jogo(&sistema->jogo);
					transicionar_para_cena(sistema, CENA_JOGO);
					resetar_botao(&sistema->inicio.botao_novo_jogo);
				}

				if (pressionar_botao(&sistema->inicio.botao_sair))
				{
					sistema->encerrar = true;
					resetar_botao(&sistema->inicio.botao_sair);
				}

				if (pressionar_botao(&sistema->inicio.botao_placar))
				{
					transicionar_para_cena(sistema, CENA_PLACAR);
					resetar_botao(&sistema->inicio.botao_placar);
				}

				if (pressionar_botao(&sistema->inicio.botao_ajuda))
				{
					transicionar_para_cena(sistema, CENA_AJUDA);
					resetar_botao(&sistema->inicio.botao_ajuda);
				}
			}

			break;
	}

	if (sistema->redesenhar)
	{
		preparar_desenho(tela);
		
		al_draw_bitmap(tela->sprites.inicio_titulo, centro(0, tela->largura, INICIO_TITULO_L), MARGEM_MEDIA, 0);

		desenhar_botao(&sistema->inicio.botao_continuar_jogo);
		desenhar_botao(&sistema->inicio.botao_novo_jogo);
		desenhar_botao(&sistema->inicio.botao_sair);
		desenhar_botao(&sistema->inicio.botao_placar);
		desenhar_botao(&sistema->inicio.botao_ajuda);

		desenhar_borda_decorativa(tela);

		finalizar_desenho(tela);
	}
}

void inicializar_placar(struct Placar *placar, struct Sprites *sprites, struct Sons *sons)
{
	inicializar_botao(&placar->botao_voltar, BOTAO_VOLTAR_L, BOTAO_VOLTAR_H);

	placar->botao_voltar.sprite_padrao = sprites->botao_voltar;
	placar->botao_voltar.sprite_sobre = sprites->botao_voltar;
	placar->botao_voltar.sprite_pressionado = sprites->botao_voltar;
	placar->botao_voltar.sprite_desabilitado = sprites->botao_voltar;

	placar->botao_voltar.som_pressionar = sons->botao_selecionar;
}

void posicionar_placar(struct Placar *placar, struct Tela *tela)
{
	placar->botao_voltar.x = MARGEM_GRANDE;
	placar->botao_voltar.y = BOTAO_VOLTAR_OFFSET_CIMA;
}

void desenhar_lista_recordes(struct Recorde recordes[RECORDES_TAM], struct Tela *tela)
{
	int lista_largura = tela->largura - MARGEM_GRANDE * 2;
	int lista_altura = tela->altura - PLACAR_LISTA_MARGEM_CIMA - PLACAR_LISTA_MARGEM_BAIXO;

	int lista_x = centro(0, tela->largura, lista_largura);
	int lista_y = centro(0, tela->altura, lista_altura);

	int item_largura = lista_largura / PLACAR_COLUNAS - (PLACAR_COLUNAS_ESPACO * (PLACAR_COLUNAS - 1)) / PLACAR_COLUNAS;
	int item_altura = lista_altura / PLACAR_LINHAS;

	for (int i = 0; i < PLACAR_LINHAS; i++)
	{
		for (int j = 0; j < PLACAR_COLUNAS; j++)
		{
			int indice = j * PLACAR_LINHAS + i;
			int posicao = indice + 1;

			if (indice < RECORDES_TAM)
			{
				struct Recorde *recorde = &recordes[indice];

				int item_x = lista_x + (item_largura + PLACAR_COLUNAS_ESPACO) * j;
				int item_y = lista_y + item_altura * i;

				int linha_x = item_x;
				int linha_y = item_y + item_altura;

				int conteudo_x = linha_x;
				int conteudo_y = linha_y - PLACAR_LINHA_GROSSURA - PLACAR_CONTEUDO_ESPACO;

				int texto_x = conteudo_x;
				int texto_y = conteudo_y - al_get_font_line_height(tela->fontes.pixelmix_8);

				al_draw_line(linha_x, linha_y, linha_x + item_largura, linha_y, COR_PLACAR_LINHA, PLACAR_LINHA_GROSSURA);

				if (!recorde->vago)
				{
					int total_segundos = recorde->tempo * PERIODO_TICK;

					int minutos = total_segundos / 60;
					int segundos = total_segundos % 60;

					int relogio_x = conteudo_x + item_largura - PLACAR_RELOGIO_L;
					int relogio_y = conteudo_y - PLACAR_RELOGIO_H;

					int tempo_x = relogio_x + PLACAR_RELOGIO_L / 2;
					int tempo_y = centro(relogio_y, PLACAR_RELOGIO_H, al_get_font_line_height(tela->fontes.smallestpixel7_10));

					al_draw_bitmap(tela->sprites.placar_relogio, relogio_x, relogio_y, 0);

					al_draw_textf(tela->fontes.pixelmix_8, COR_PRETO, texto_x, texto_y, ALLEGRO_ALIGN_LEFT, "%d. %d", posicao, recorde->escore);
					al_draw_textf(tela->fontes.smallestpixel7_10, COR_PLACAR_TEMPO, tempo_x + 1, tempo_y, ALLEGRO_ALIGN_CENTER, "%02d:%02d", minutos, segundos);
				}
				else
				{
					al_draw_textf(tela->fontes.pixelmix_8, COR_PRETO, texto_x, texto_y, ALLEGRO_ALIGN_LEFT, "%d.", posicao);
				}
			}
		}
	}
}

void cena_placar(struct Tela *tela, struct Sistema *sistema, ALLEGRO_EVENT *evento)
{
	switch (evento->type)
	{
		case ALLEGRO_EVENT_MOUSE_AXES:
		{
			int mouse_x = evento->mouse.x / tela->escala;
			int mouse_y = evento->mouse.y / tela->escala;

			detectar_sobre_botao(&sistema->placar.botao_voltar, mouse_x, mouse_y);

			break;
		}
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			if (evento->mouse.button & 1)
			{
				if (pressionar_botao(&sistema->placar.botao_voltar))
				{
					transicionar_para_cena(sistema, CENA_INICIO);
					resetar_botao(&sistema->placar.botao_voltar);
				}
			}

			break;
	}

	if (sistema->redesenhar)
	{
		preparar_desenho(tela);

		al_draw_bitmap(tela->sprites.placar_titulo, centro(0, tela->largura, PLACAR_TITULO_L), MARGEM_MEDIA, 0);
		desenhar_botao(&sistema->placar.botao_voltar);
		desenhar_lista_recordes(sistema->recordes, tela);
		desenhar_borda_decorativa(tela);

		finalizar_desenho(tela);
	}
}

void avancar_pagina_ajuda(struct Ajuda *ajuda)
{
	ajuda->pagina = (ajuda->pagina + 1) % NUM_PAGINAS_AJUDA;
}

void voltar_pagina_ajuda(struct Ajuda *ajuda)
{
	ajuda->pagina = (NUM_PAGINAS_AJUDA + ajuda->pagina - 1) % NUM_PAGINAS_AJUDA;
}

void inicializar_ajuda(struct Ajuda *ajuda, struct Sprites *sprites, struct Sons *sons)
{
	ajuda->pagina = 0;

	inicializar_botao(&ajuda->botao_voltar, BOTAO_VOLTAR_L, BOTAO_VOLTAR_H);
	inicializar_botao(&ajuda->botao_pagina_seguinte, AJUDA_SETA_L, AJUDA_SETA_H);
	inicializar_botao(&ajuda->botao_pagina_anterior, AJUDA_SETA_L, AJUDA_SETA_H);


	ajuda->botao_voltar.sprite_padrao = sprites->botao_voltar;
	ajuda->botao_voltar.sprite_sobre = sprites->botao_voltar;
	ajuda->botao_voltar.sprite_pressionado = sprites->botao_voltar;
	ajuda->botao_voltar.sprite_desabilitado = sprites->botao_voltar;

	ajuda->botao_voltar.som_pressionar = sons->botao_selecionar;

	ajuda->botao_pagina_seguinte.sprite_padrao = sprites->ajuda_seta_direita;
	ajuda->botao_pagina_seguinte.sprite_sobre = sprites->ajuda_seta_direita;
	ajuda->botao_pagina_seguinte.sprite_pressionado = sprites->ajuda_seta_direita;
	ajuda->botao_pagina_seguinte.sprite_desabilitado = sprites->ajuda_seta_direita;

	ajuda->botao_pagina_anterior.sprite_padrao = sprites->ajuda_seta_esquerda;
	ajuda->botao_pagina_anterior.sprite_sobre = sprites->ajuda_seta_esquerda;
	ajuda->botao_pagina_anterior.sprite_pressionado = sprites->ajuda_seta_esquerda;
	ajuda->botao_pagina_anterior.sprite_desabilitado = sprites->ajuda_seta_esquerda;
}

void posicionar_ajuda(struct Ajuda *ajuda, struct Tela *tela)
{
	int controles_y = tela->altura - AJUDA_SETA_H - MARGEM_MEDIA;

	ajuda->botao_voltar.x = MARGEM_GRANDE;
	ajuda->botao_voltar.y = BOTAO_VOLTAR_OFFSET_CIMA;

	ajuda->botao_pagina_seguinte.x = tela->largura - MARGEM_MEDIA - AJUDA_SETA_L;
	ajuda->botao_pagina_seguinte.y = controles_y;

	ajuda->botao_pagina_anterior.x = ajuda->botao_pagina_seguinte.x - AJUDA_CONTROLES_ESPACO - AJUDA_SETA_L;
	ajuda->botao_pagina_anterior.y = controles_y;
}

void cena_ajuda(struct Tela *tela, struct Sistema *sistema, ALLEGRO_EVENT *evento)
{
	switch (evento->type)
	{
		case ALLEGRO_EVENT_MOUSE_AXES:
		{
			int mouse_x = evento->mouse.x / tela->escala;
			int mouse_y = evento->mouse.y / tela->escala;

			detectar_sobre_botao(&sistema->ajuda.botao_voltar, mouse_x, mouse_y);
			detectar_sobre_botao(&sistema->ajuda.botao_pagina_seguinte, mouse_x, mouse_y);
			detectar_sobre_botao(&sistema->ajuda.botao_pagina_anterior, mouse_x, mouse_y);
			
			break;
		}
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			if (evento->mouse.button & 1)
			{
				if (pressionar_botao(&sistema->ajuda.botao_voltar))
				{
					transicionar_para_cena(sistema, CENA_INICIO);
					resetar_botao(&sistema->ajuda.botao_voltar);
				}

				if (pressionar_botao(&sistema->ajuda.botao_pagina_seguinte))
				{
					avancar_pagina_ajuda(&sistema->ajuda);
				}

				if (pressionar_botao(&sistema->ajuda.botao_pagina_anterior))
				{
					voltar_pagina_ajuda(&sistema->ajuda);
				}
			}

			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			if (evento->mouse.button & 1)
			{
				soltar_botao(&sistema->ajuda.botao_pagina_seguinte);
				soltar_botao(&sistema->ajuda.botao_pagina_anterior);
			}
			
			break;
		case ALLEGRO_EVENT_KEY_CHAR:
			switch (evento->keyboard.keycode)
			{
				case ALLEGRO_KEY_RIGHT:
					avancar_pagina_ajuda(&sistema->ajuda);
					break;
				case ALLEGRO_KEY_LEFT:
					voltar_pagina_ajuda(&sistema->ajuda);
					break;
			}
			break;
	}

	if (sistema->redesenhar)
	{
		int texto_largura = tela->largura - 2 * MARGEM_GRANDE;
		int texto_linha = al_get_font_line_height(tela->fontes.smallestpixel7_10);

		int texto_x = centro(0, tela->largura, texto_largura);
		int texto_y = MARGEM_MEDIA + AJUDA_TITULO_H + MARGEM_PEQUENA;

		int pagina_x = sistema->ajuda.botao_pagina_anterior.x - AJUDA_CONTROLES_ESPACO;
		int pagina_y = centro(sistema->ajuda.botao_pagina_anterior.y, AJUDA_SETA_H, texto_linha);

		preparar_desenho(tela);

		al_draw_bitmap(tela->sprites.ajuda_titulo, centro(0, tela->largura, AJUDA_TITULO_L), MARGEM_MEDIA, 0);

		al_draw_multiline_text(
			tela->fontes.smallestpixel7_10,
			COR_PRETO,
			texto_x,
			texto_y,
			texto_largura,
			texto_linha,
			ALLEGRO_ALIGN_LEFT,
			PAGINAS_AJUDA[sistema->ajuda.pagina]
		);

		al_draw_textf(
			tela->fontes.smallestpixel7_10,
			COR_PRETO,
			pagina_x,
			pagina_y,
			ALLEGRO_ALIGN_RIGHT,
			"%d/%d",
			sistema->ajuda.pagina + 1,
			NUM_PAGINAS_AJUDA
		);

		desenhar_botao(&sistema->ajuda.botao_voltar);
		desenhar_botao(&sistema->ajuda.botao_pagina_seguinte);
		desenhar_botao(&sistema->ajuda.botao_pagina_anterior);

		desenhar_borda_decorativa(tela);

		finalizar_desenho(tela);
	}
}

int main()
{
	srand(time(NULL));

	verificar_init(al_init(), "allegro");
	verificar_init(al_init_primitives_addon(), "primitives");
	verificar_init(al_init_font_addon(), "font");
	verificar_init(al_init_ttf_addon(), "ttf");
	verificar_init(al_init_image_addon(), "image");
	verificar_init(al_init_acodec_addon(), "audio codec");

	verificar_init(al_install_keyboard(), "keyboard");
	verificar_init(al_install_mouse(), "mouse");
	verificar_init(al_install_audio(), "audio");

	verificar_init(al_reserve_samples(RESERVA_AUDIO), "samples");

	struct Tela tela;

	tela.cheia = false;

	criar_display(&tela);
	criar_canvas(&tela);

	ALLEGRO_TIMER *timer = al_create_timer(PERIODO_TICK);
	verificar_init(timer, "timer");

	ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
	verificar_init(queue, "queue");

	carregar_fontes(&tela.fontes);
	carregar_sprites(&tela.sprites);
	carregar_sons(&tela.sons);

	al_register_event_source(queue, al_get_display_event_source(tela.display));
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));

	ALLEGRO_EVENT evento;
	bool redesenhar = false;

	struct Sistema sistema;

	sistema.cena = -1;

	sistema.encerrar = false;
	sistema.reposicionar = true;
	sistema.redesenhar = false;

	inicializar_recordes(sistema.recordes);
	inicializar_inicio(&sistema.inicio, &tela.sprites, &tela.sons);
	inicializar_placar(&sistema.placar, &tela.sprites, &tela.sons);
	inicializar_ajuda(&sistema.ajuda, &tela.sprites, &tela.sons);
	inicializar_jogo(&sistema.jogo, &tela.sprites, &tela.sons);

	transicionar_para_cena(&sistema, CENA_INICIO);

	al_start_timer(timer);

	while (true)
	{
		al_wait_for_event(queue, &evento);

		switch (evento.type)
		{
			case ALLEGRO_EVENT_TIMER:
				redesenhar = true;
				break;
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				sistema.encerrar = true;
				break;
			case ALLEGRO_EVENT_DISPLAY_RESIZE:
				al_acknowledge_resize(tela.display);
				redimensionar_canvas(&tela);

				sistema.reposicionar = true;
				break;
			case ALLEGRO_EVENT_KEY_DOWN:
				if (evento.keyboard.keycode == ALLEGRO_KEY_F11)
				{
					alternar_tela_cheia(&tela);
					redimensionar_canvas(&tela);

					sistema.reposicionar = true;
				}
				break;
		}

		if (sistema.encerrar)
		{
			break;
		}

		if (sistema.reposicionar)
		{
			posicionar_inicio(&sistema.inicio, &tela);
			posicionar_placar(&sistema.placar, &tela);
			posicionar_ajuda(&sistema.ajuda, &tela);
			posicionar_jogo(&sistema.jogo, &tela);
		}

		sistema.redesenhar = redesenhar && al_event_queue_is_empty(queue);

		if (sistema.redesenhar)
		{
			redesenhar = false;
		}

		switch (sistema.cena)
		{
			case CENA_INICIO:
				cena_inicio(&tela, &sistema, &evento);
				break;
			case CENA_PLACAR:
				cena_placar(&tela, &sistema, &evento);
				break;
			case CENA_AJUDA:
				cena_ajuda(&tela, &sistema, &evento);
				break;
			case CENA_JOGO:
				cena_jogo(&tela, &sistema, &evento);
				break;
		}
	}
}