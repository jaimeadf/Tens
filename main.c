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

#define PI 3.14159265358979323846

#define PECA_TAM 2

#define QUADRO_TAM 5
#define SLOTS_TAM 3

#define RECORDES_TAM 10

#define DADOS_NUM 7
#define CORES_NUM 6

#define BALOES_NUM 4

#define COLAPSO_FRAMES_NUM 8
#define COLAPSO_FRAME_PERIODO 2
#define COLAPSO_ATRASO (3 * COLAPSO_FRAME_PERIODO)

#define SOMA_TAM (2 * QUADRO_TAM)

#define DIRECAO_LINHA 0
#define DIRECAO_COLUNA 1

#define DIRECOES_NUM 2

#define ANIMACAO_PARADO 0
#define ANIMACAO_COLAPSO 1
#define ANIMACAO_EXPLOSAO 2

#define LIMITE_BALAO_0 6
#define LIMITE_BALAO_1 9
#define LIMITE_BALAO_2 10

#define PONTOS_DADO 1
#define PONTOS_COMBO 5
#define PONTOS_MULTILINHA 7
#define PONTOS_TABULEIRO_CONCLUIDO 10

#define DESFAZER_TABULEIROS_CONCLUIDOS 1
#define BOMBA_COMBINACOES 5
#define ROTACAO_PONTOS 50

#define DADO_VAZIO -1

#define PERIODO_TICK (1.0 / 60.0)

#define ESPACO_ENTRE_DADOS 1
#define ESPACO_ENTRE_SLOTS 1
#define ESPACO_ENTRE_HABILIDADES 4
#define ESPACO_BALAO 1
#define ESPACO_PROGRESSO_HABILIDADE 2
#define ESPACO_QUANTIDADE_HABILIDADE 4

#define LARGURA_ORIGINAL 320
#define ALTURA_ORIGINAL 180

#define DADO_L 24
#define DADO_H 25

#define SLOT_L 51
#define SLOT_H 53

#define BALAO_HORIZONTAL_L 19
#define BALAO_HORIZONTAL_H 11

#define BALAO_HORIZONTAL_OFFSET_DIREITA 1
#define BALAO_HORIZONTAL_OFFSET_CIMA 12

#define BALAO_VERTICAL_L 17
#define BALAO_VERTICAL_H 14

#define BALAO_VERTICAL_OFFSET_DIREITA 9
#define BALAO_VERTICAL_OFFSET_CIMA 1

#define QUADRO_L (QUADRO_TAM * (DADO_L + ESPACO_ENTRE_DADOS))
#define QUADRO_H (QUADRO_TAM * (DADO_H + ESPACO_ENTRE_DADOS))

#define BOTAO_ROTACIONAR_L 14
#define BOTAO_ROTACIONAR_H 15

#define BOTAO_HABILIDADE_L 16
#define BOTAO_HABILIDADE_H 17

#define FUNDO_PROGRESSO_L 3
#define FUNDO_PROGRESSO_H 17

#define PROGRESSO_OFFSET_DIREITA 2
#define PROGRESSO_OFFSET_CIMA 15

#define PROGRESSO_ALTURA 15

#define MARGEM_PEQUENA 8

#define ESCORE_OFFSET_CIMA 3
#define TEMPO_OFFSET_CIMA 26

#define QUADRO_OFFSET_DIREITA 24

#define BOTAO_ROTACIONAR_OFFSET_DIREITA 8

#define COR_PRETO al_map_rgb(0, 0, 0)
#define COR_BRANCO al_map_rgb(255, 255, 255)
#define COR_PROGRESSO al_map_rgb(121, 240, 8)

struct Fontes {
	ALLEGRO_FONT *fipps_12;
	ALLEGRO_FONT *pixelmix_8;
};

struct Sprites {
	ALLEGRO_BITMAP *sheet;

	ALLEGRO_BITMAP *titulo_tens;
	
	ALLEGRO_BITMAP *botao_continuar_jogo_padrao;
	ALLEGRO_BITMAP *botao_continuar_jogo_sobre;
	ALLEGRO_BITMAP *botao_continuar_jogo_desativado;

	ALLEGRO_BITMAP *botao_novo_jogo_padrao;
	ALLEGRO_BITMAP *botao_novo_jogo_sobre;

	ALLEGRO_BITMAP *botao_sair_padrao;
	ALLEGRO_BITMAP *botao_sair_sobre;

	ALLEGRO_BITMAP *botao_placar_padrao;
	ALLEGRO_BITMAP *botao_placar_sobre;

	ALLEGRO_BITMAP *botao_ajuda_padrao;
	ALLEGRO_BITMAP *botao_ajuda_sobre;

	ALLEGRO_BITMAP *moldura;
	ALLEGRO_BITMAP *slot;

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
};

struct Tela {
	int escala;

	int largura;
	int altura;

	ALLEGRO_DISPLAY *display;
	ALLEGRO_BITMAP *canvas;

	struct Fontes fontes;
	struct Sprites sprites;
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
};

struct Inicio {
	int a;
};

struct Placar {
	int b;
};

struct Ajuda {
	int c;
};

struct Recorde
{
	bool vago;

	int score;
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

struct Jogo {
	int escore;
	int tempo;

	int combo;

	int slot_selecionado;

	struct Habilidade desfazer;
	struct Habilidade bomba;
	struct Habilidade rotacao;

	struct Quadro quadro;
	struct Slot slots[SLOTS_TAM];

	struct Jogada jogada;

	struct Recorde recordes[RECORDES_TAM];
};

struct Sistema {
	int cena;

	bool redesenhar;

	struct Inicio inicio;
	struct Placar placar;
	struct Ajuda ajuda;

	struct Jogo jogo;
};

void verificar_init(bool teste, char *descricao)
{
	if (teste)
		return;

	printf("falha ao inicializar %s\n", descricao);
	exit(1);
}

ALLEGRO_BITMAP *selecionar_sprite(struct Sprites *sprites, int x, int y, int largura, int altura)
{
	ALLEGRO_BITMAP *sprite = al_create_sub_bitmap(sprites->sheet, x, y, largura, altura);
	verificar_init(sprite, "selecionar_sprite");
	return sprite;
}

void carregar_fontes(struct Fontes *fontes)
{
	fontes->fipps_12 = al_load_font("assets/fonts/Fipps-Regular.otf", 12, ALLEGRO_TTF_MONOCHROME);
	verificar_init(fontes->fipps_12, "fipps 12");

	fontes->pixelmix_8 = al_load_font("assets/fonts/pixelmix.ttf", 8, ALLEGRO_TTF_MONOCHROME);
	verificar_init(fontes->pixelmix_8, "pixelmix 8");
}

void carregar_sprites(struct Sprites *sprites)
{
	sprites->sheet = al_load_bitmap("assets/sprites/spritesheet.bmp");
	verificar_init(sprites->sheet, "spritesheet.bmp");

	sprites->moldura = selecionar_sprite(sprites, 168, 0, DADO_L, DADO_H);
	sprites->slot = selecionar_sprite(sprites, 168, 25, SLOT_L, SLOT_H);

	sprites->botao_rotacionar_padrao = selecionar_sprite(sprites, 168, 78, BOTAO_ROTACIONAR_L, BOTAO_ROTACIONAR_H);
	sprites->botao_rotacionar_desabilitado = selecionar_sprite(sprites, 182, 78, BOTAO_ROTACIONAR_L, BOTAO_ROTACIONAR_H);
	sprites->botao_rotacionar_ativo_padrao = selecionar_sprite(sprites, 196, 78, BOTAO_ROTACIONAR_L, BOTAO_ROTACIONAR_H);
	sprites->botao_rotacionar_ativo_pressionado = selecionar_sprite(sprites, 210, 78, BOTAO_ROTACIONAR_L, BOTAO_ROTACIONAR_H);

	sprites->habilidade_desfazer_padrao = selecionar_sprite(sprites, 168, 93, BOTAO_HABILIDADE_L, BOTAO_HABILIDADE_H);
	sprites->habilidade_desfazer_pressionado = selecionar_sprite(sprites, 184, 93, BOTAO_HABILIDADE_L, BOTAO_HABILIDADE_H);
	sprites->habilidade_desfazer_desabilitado = selecionar_sprite(sprites, 200, 93, BOTAO_HABILIDADE_L, BOTAO_HABILIDADE_H);

	sprites->habilidade_bomba_padrao = selecionar_sprite(sprites, 168, 110, BOTAO_HABILIDADE_L, BOTAO_HABILIDADE_H);
	sprites->habilidade_bomba_pressionado = selecionar_sprite(sprites, 184, 110, BOTAO_HABILIDADE_L, BOTAO_HABILIDADE_H);
	sprites->habilidade_bomba_desabilitado = selecionar_sprite(sprites, 200, 110, BOTAO_HABILIDADE_L, BOTAO_HABILIDADE_H);

	sprites->habilidade_rotacao_padrao = selecionar_sprite(sprites, 216, 93, BOTAO_HABILIDADE_L, BOTAO_HABILIDADE_H);

	sprites->fundo_progresso = selecionar_sprite(sprites, 168, 127, FUNDO_PROGRESSO_L, FUNDO_PROGRESSO_H);

	for (int i = 0; i < CORES_NUM; i++)
	{
		for (int j = 0; j < DADOS_NUM; j++)
		{
			sprites->dados[i][j] = selecionar_sprite(sprites, j * DADO_L, i * DADO_H, DADO_L, DADO_H);
		}
	}

	for (int i = 0; i < BALOES_NUM; i++)
	{
		int x = 192 + i * BALAO_HORIZONTAL_L;
		int y = 0;

		sprites->baloes_horizontais[i] = selecionar_sprite(sprites, x, y, BALAO_HORIZONTAL_L, BALAO_HORIZONTAL_H);
	}

	for (int j = 0; j < BALOES_NUM; j++)
	{
		int x = 192 + j * BALAO_VERTICAL_L;
		int y = 11;

		sprites->baloes_verticais[j] = selecionar_sprite(sprites, x, y, BALAO_VERTICAL_L, BALAO_VERTICAL_H);
	}

	for (int i = 0; i < COLAPSO_FRAMES_NUM; i++)
	{
		sprites->colapso_linha[i] = selecionar_sprite(sprites, i * DADO_L, 150, DADO_L, DADO_H);;
		sprites->colapso_coluna[i] = selecionar_sprite(sprites, i * DADO_L, 175, DADO_L, DADO_H);;
	}
}

int aleatorio(int minimo, int maximo)
{
	int intervalo = maximo - minimo;
	return rand() % intervalo + minimo;
}

int centro(int referencia, int maior, int menor)
{
	return referencia + (maior - menor) / 2;
}

bool colisao_area(int x1, int y1, int x2, int y2, int px, int py)
{
	return px >= x1 && px <= x2 && py >= y1 && py <= y2;
}

bool colisao_retangulo(int x, int y, int largura, int altura, int px, int py)
{
	return colisao_area(x, y, x + largura, y + altura, px, py);
}

void redimensionar_tela(struct Tela *tela)
{
	ALLEGRO_TRANSFORM transform;

	al_destroy_bitmap(tela->canvas);

	float largura_janela = al_get_display_width(tela->display);
	float altura_janela = al_get_display_height(tela->display);

	float razao_x = floor(largura_janela / LARGURA_ORIGINAL);
	float razao_y = floor(altura_janela / ALTURA_ORIGINAL);

	tela->escala = razao_x < razao_y ? razao_x : razao_y;

	if (tela->escala < 1)
		tela->escala = 1;

	tela->largura = largura_janela / tela->escala;
	tela->altura = altura_janela / tela->escala;

	tela->canvas = al_create_bitmap(tela->largura, tela->altura);

	al_identity_transform(&transform);
	al_scale_transform(&transform, tela->escala, tela->escala);
	al_use_transform(&transform);
}

void inicializar_botao(struct Botao *botao, int largura, int altura)
{
	botao->x = 0;
	botao->y = 0;

	botao->largura = largura;
	botao->altura = altura;

	botao->desabilitado = false;
	botao->sobre = false;
	botao->pressionado = false;

	botao->sprite_padrao = NULL;
	botao->sprite_sobre = NULL;
	botao->sprite_pressionado = NULL;
	botao->sprite_desabilitado = NULL;
}

bool pressionar_botao(struct Botao *botao)
{
	if (botao->sobre && !botao->desabilitado)
	{
		botao->pressionado = true;
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

void detectar_sobreposicao_botao(struct Botao *botao, int px, int py)
{
	botao->sobre = colisao_retangulo(botao->x, botao->y, botao->largura, botao->altura, px, py);
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

void posicionar_habilidade(struct Habilidade *habilidade, int x, int y)
{
	habilidade->x = x;
	habilidade->y = y;
	habilidade->botao.x = x + FUNDO_PROGRESSO_L + ESPACO_PROGRESSO_HABILIDADE;
	habilidade->botao.y = y;
}

void inicializar_habilidade(struct Habilidade *habilidade, int custo, bool cumulativo)
{
	habilidade->custo = custo;
	habilidade->cumulativo = cumulativo;

	habilidade->bloqueado = false;

	habilidade->quantidade = 0;
	habilidade->progresso = 0;

	inicializar_botao(&habilidade->botao, BOTAO_HABILIDADE_L, BOTAO_HABILIDADE_H);
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

void atualizar_habilidade(struct Habilidade *habilidade)
{
	habilidade->botao.desabilitado = !pode_usar_habilidade(habilidade);
}

void desenhar_habilidade(struct Tela *tela, struct Habilidade *habilidade)
{
	float porcentagem = (float)habilidade->progresso / habilidade->custo;
	int altura = porcentagem * PROGRESSO_ALTURA;

	int progresso_x = habilidade->x + PROGRESSO_OFFSET_DIREITA;

	int progresso_y1 = habilidade->y + PROGRESSO_OFFSET_CIMA + 1;
	int progresso_y2 = progresso_y1 - altura;

	int quantidade_x = habilidade->botao.x + BOTAO_HABILIDADE_L + ESPACO_QUANTIDADE_HABILIDADE;
	int quantidade_y = centro(habilidade->botao.y, BOTAO_HABILIDADE_H, al_get_font_line_height(tela->fontes.pixelmix_8));

	al_draw_bitmap(tela->sprites.fundo_progresso, habilidade->x, habilidade->y, 0);
	al_draw_line(progresso_x, progresso_y1, progresso_x, progresso_y2, COR_PROGRESSO, 1);

	if (habilidade->cumulativo)
		al_draw_textf(tela->fontes.pixelmix_8, COR_PRETO, quantidade_x, quantidade_y, ALLEGRO_ALIGN_LEFT, "%d", habilidade->quantidade);

	desenhar_botao(&habilidade->botao);
}

void inicializar_desfazer(struct Sprites *sprites, struct Habilidade *desfazer)
{
	inicializar_habilidade(desfazer, DESFAZER_TABULEIROS_CONCLUIDOS, false);

	desfazer->bloqueado = true;

	desfazer->botao.sprite_padrao = sprites->habilidade_desfazer_padrao;
	desfazer->botao.sprite_sobre = sprites->habilidade_desfazer_padrao;
	desfazer->botao.sprite_pressionado = sprites->habilidade_desfazer_pressionado;
	desfazer->botao.sprite_desabilitado = sprites->habilidade_desfazer_desabilitado;
}

void inicializar_bomba(struct Sprites *sprites, struct Habilidade *bomba)
{
	inicializar_habilidade(bomba, BOMBA_COMBINACOES, true);

	bomba->botao.sprite_padrao = sprites->habilidade_bomba_padrao;
	bomba->botao.sprite_sobre = sprites->habilidade_bomba_padrao;
	bomba->botao.sprite_pressionado = sprites->habilidade_bomba_pressionado;
	bomba->botao.sprite_desabilitado = sprites->habilidade_bomba_desabilitado;
}

void inicializar_rotacao(struct Sprites *sprites, struct Habilidade *rotacao)
{
	inicializar_habilidade(rotacao, ROTACAO_PONTOS, true);

	rotacao->botao.sprite_padrao = sprites->habilidade_rotacao_padrao;
	rotacao->botao.sprite_sobre = sprites->habilidade_rotacao_padrao;
	rotacao->botao.sprite_pressionado = sprites->habilidade_rotacao_padrao;
	rotacao->botao.sprite_desabilitado = sprites->habilidade_rotacao_padrao;
}

void posicionar_habilidades(struct Tela *tela, struct Jogo *jogo)
{
	int espaco_y = BOTAO_HABILIDADE_H + ESPACO_ENTRE_HABILIDADES;

	int x = MARGEM_PEQUENA;
	int y = tela->altura - MARGEM_PEQUENA - BOTAO_HABILIDADE_H;

	posicionar_habilidade(&jogo->rotacao, x, y);

	y -= espaco_y;
	posicionar_habilidade(&jogo->bomba, x, y);

	y -= espaco_y;
	posicionar_habilidade(&jogo->desfazer, x, y);
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
	incrementar_score(jogo, PONTOS_TABULEIRO_CONCLUIDO);
}

void pontuar_multilinha(struct Jogo *jogo, int linhas)
{
	acumular_habilidade(&jogo->bomba, 1);
	incrementar_score(jogo, PONTOS_MULTILINHA * (linhas - 1));
}

void pontuar_combo(struct Jogo *jogo, int linhas)
{
	if (jogo->combo == 1)
		acumular_habilidade(&jogo->bomba, 1);

	incrementar_score(jogo, PONTOS_COMBO * linhas);
}

void resetar_combo(struct Jogo *jogo)
{
	jogo->combo = 1;
}

bool colisao_quadro(struct Quadro *quadro, int px, int py)
{
	return colisao_retangulo(quadro->x, quadro->y, QUADRO_L, QUADRO_H, px, py);
}

void posicionar_quadro(struct Tela *tela, struct Quadro *quadro)
{
	quadro->x = centro(0, tela->largura, QUADRO_L) - QUADRO_OFFSET_DIREITA;
	quadro->y = tela->altura - QUADRO_H - MARGEM_PEQUENA;
}

void remover_dado(struct Quadro *quadro, int linha, int coluna)
{
	quadro->soma_linhas[linha] -= quadro->dados[linha][coluna].valor;
	quadro->soma_colunas[coluna] -= quadro->dados[linha][coluna].valor;

	quadro->dados[linha][coluna].valor = DADO_VAZIO;
}

void preencher_dado(struct Quadro *quadro, int linha, int coluna, int cor, int valor)
{
	quadro->concluido = false;

	quadro->soma_linhas[linha] += valor;
	quadro->soma_colunas[coluna] += valor;

	quadro->dados[linha][coluna].cor = cor;
	quadro->dados[linha][coluna].valor = valor;
}

void animar_dado(struct Dado *dado, int animacao, int atraso, int direcao)
{
	dado->animacao = animacao;
	dado->ticks = 0;
	dado->atraso = atraso;
	dado->direcao = direcao;
}

bool verificar_colapso(struct Dado *dado)
{
	return dado->animacao == ANIMACAO_COLAPSO && dado->ticks - dado->atraso >= COLAPSO_FRAME_PERIODO * COLAPSO_FRAMES_NUM;
}

bool verificar_explosao(struct Dado *dado)
{
	return dado->animacao == ANIMACAO_EXPLOSAO;
}

bool linha_destruida(struct Quadro *quadro, int linha)
{
	for (int j = 0; j < QUADRO_TAM; j++)
	{
		if (quadro->dados[linha][j].animacao == ANIMACAO_COLAPSO)
			return true;
	}

	return false;
}

bool coluna_destruida(struct Quadro *quadro, int coluna)
{
	for (int i = 0; i < QUADRO_TAM; i++)
	{
		if (quadro->dados[i][coluna].animacao == ANIMACAO_COLAPSO)
			return true;
	}

	return false;
}

int encontrar_tens(struct Quadro *quadro, struct Soma somas[])
{
	int n = 0;

	for (int i = 0; i < QUADRO_TAM; i++)
	{
		if (!linha_destruida(quadro, i) && quadro->soma_linhas[i] == 10)
		{
			somas[n].direcao = DIRECAO_LINHA;
			somas[n].indice = i;

			n++;
		}
	}

	for (int j = 0; j < QUADRO_TAM; j++)
	{
		if (!coluna_destruida(quadro, j) && quadro->soma_colunas[j] == 10)
		{
			somas[n].direcao = DIRECAO_COLUNA;
			somas[n].indice = j;

			n++;
		}
	}

	return n;
}

void destruir_tens(struct Quadro *quadro, struct Soma somas[SOMA_TAM], int n)
{
	for (int k = 0; k < n; k++)
	{
		int atraso = 0;

		for (int i = 0; i < QUADRO_TAM; i++)
		{
			struct Dado *dado = somas[k].direcao == DIRECAO_LINHA
				? &quadro->dados[somas[k].indice][i]
				: &quadro->dados[i][somas[k].indice];

			if (dado->valor != DADO_VAZIO)
			{
				animar_dado(dado, ANIMACAO_COLAPSO, atraso, somas[k].direcao);
				atraso += COLAPSO_ATRASO;
			}
		}
	}
}

int formar_tens(struct Quadro *quadro)
{
	struct Soma somas[SOMA_TAM];
	int n = encontrar_tens(quadro, somas);

	destruir_tens(quadro, somas, n);

	return n;
}

void explodir(struct Quadro *quadro, int indice, int direcao)
{
	for (int i = 0; i < QUADRO_TAM; i++)
	{
		int linha = direcao == DIRECAO_LINHA ? indice : i;
		int coluna = direcao == DIRECAO_LINHA ? i : indice;

		if (quadro->dados[linha][coluna].valor != DADO_VAZIO)
		{
			remover_dado(quadro, linha, coluna);
		}

		animar_dado(&quadro->dados[linha][coluna], ANIMACAO_EXPLOSAO, 0, direcao);
	}
}

bool quadro_limpo(struct Quadro *quadro)
{
	for (int i = 0; i < QUADRO_TAM; i++)
	{
		for (int j = 0; j < QUADRO_TAM; j++)
		{
			if (quadro->dados[i][j].valor != DADO_VAZIO)
			{
				return false;
			}
		}
	}

	return true;
}

bool restaurar_quadro_concluido(struct Quadro *quadro)
{
	if (!quadro->concluido && quadro_limpo(quadro))
	{
		quadro->concluido = true;
		return true;
	}

	return false;
}

int determinar_balao(int soma)
{
	if (soma <= LIMITE_BALAO_0)
		return 0;
	else if (soma <= LIMITE_BALAO_1)
		return 1;
	else if (soma <= LIMITE_BALAO_2)
		return 2;
	else
		return 3;
}

void inicializar_quadro(struct Quadro *quadro)
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
			quadro->dados[i][j].animacao = ANIMACAO_PARADO;
			quadro->dados[i][j].ticks = 0;
			quadro->dados[i][j].atraso = 0;
			quadro->dados[i][j].cor = 0;
			quadro->dados[i][j].valor = DADO_VAZIO;
		}
	}
}

void desenhar_quadro(struct Tela *tela, struct Quadro *quadro)
{
	for (int i = 0; i < QUADRO_TAM; i++)
	{
		for (int j = 0; j < QUADRO_TAM; j++)
		{
			struct Dado *dado = &quadro->dados[i][j];

			int dado_x = quadro->x + j * (DADO_L + ESPACO_ENTRE_DADOS);
			int dado_y = quadro->y + i * (DADO_H + ESPACO_ENTRE_DADOS);

			al_draw_bitmap(tela->sprites.moldura, dado_x, dado_y, 0);

			if (dado->valor != DADO_VAZIO)
				al_draw_bitmap(tela->sprites.dados[dado->cor][dado->valor], dado_x, dado_y, 0);

			if (dado->animacao == ANIMACAO_COLAPSO && dado->ticks > dado->atraso)
			{
				int frame = ((dado->ticks - dado->atraso) / COLAPSO_FRAME_PERIODO) % COLAPSO_FRAMES_NUM;

				if (dado->direcao == DIRECAO_LINHA)
					al_draw_bitmap(tela->sprites.colapso_linha[frame], dado_x, dado_y, 0);
				else
					al_draw_bitmap(tela->sprites.colapso_coluna[frame], dado_x, dado_y, 0);
			}
		}
	}

	for (int i = 0; i < QUADRO_TAM; i++)
	{
		int x = quadro->x + QUADRO_L + ESPACO_BALAO;
		int y = centro(quadro->y + i * (DADO_H + ESPACO_ENTRE_DADOS), DADO_H, BALAO_HORIZONTAL_H);

		int texto_x = x + BALAO_HORIZONTAL_OFFSET_CIMA;
		int texto_y = y + BALAO_HORIZONTAL_OFFSET_DIREITA;
	
		int soma = quadro->soma_linhas[i];
		int balao = determinar_balao(soma);

		al_draw_bitmap(tela->sprites.baloes_horizontais[balao], x, y, 0);
		al_draw_textf(tela->fontes.pixelmix_8, COR_BRANCO, texto_x, texto_y, ALLEGRO_ALIGN_CENTER, "%d", soma);
	}

	for (int j = 0; j < QUADRO_TAM; j++)
	{
		int x = centro(quadro->x + j * (DADO_L + ESPACO_ENTRE_DADOS), DADO_L, BALAO_VERTICAL_L);
		int y = quadro->y - ESPACO_BALAO - BALAO_VERTICAL_H;

		int texto_x = x + BALAO_VERTICAL_OFFSET_DIREITA;
		int texto_y = y + BALAO_VERTICAL_OFFSET_CIMA;

		int soma = quadro->soma_colunas[j];
		int balao = determinar_balao(soma);

		al_draw_bitmap(tela->sprites.baloes_verticais[balao], x, y, 0);
		al_draw_textf(tela->fontes.pixelmix_8, COR_BRANCO, texto_x, texto_y, ALLEGRO_ALIGN_CENTER, "%d", soma);
	}
}

int largura_peca(struct Peca *peca)
{
	return DADO_L * peca->colunas + ESPACO_ENTRE_DADOS * (peca->colunas - 1);
}

int altura_peca(struct Peca *peca)
{
	return DADO_H * peca->linhas + ESPACO_ENTRE_DADOS * (peca->linhas - 1);
}

struct Peca gerar_peca(int x, int y)
{
	struct Peca peca;

	peca.x = x;
	peca.y = y;

	peca.cor = aleatorio(0, CORES_NUM);
	peca.linhas = aleatorio(1, PECA_TAM + 1);
	peca.colunas = aleatorio(1, PECA_TAM + 1);

	for (int i = 0; i < PECA_TAM; i++)
	{
		for (int j = 0; j < PECA_TAM; j++)
		{
			peca.dados[i][j] = aleatorio(0, DADOS_NUM);
		}
	}

	if (peca.linhas == PECA_TAM && peca.colunas == PECA_TAM)
	{
		int i = aleatorio(0, PECA_TAM);
		int j = aleatorio(0, PECA_TAM);

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
			if (peca->dados[i][j] != DADO_VAZIO && quadro->dados[linha + i][coluna + j].valor != DADO_VAZIO)
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

void desenhar_peca(struct Tela *tela, struct Peca *peca)
{
	for (int i = 0; i < peca->linhas; i++)
	{
		for (int j = 0; j < peca->colunas; j++)
		{
			int dado_x = peca->x + j * (DADO_L + ESPACO_ENTRE_DADOS);
			int dado_y = peca->y + i * (DADO_H + ESPACO_ENTRE_DADOS);

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

void posicionar_slots(struct Tela *tela, struct Slot slots[SLOTS_TAM])
{
	for (int i = 0; i < SLOTS_TAM; i++)
	{
		slots[i].x = tela->largura - SLOT_L - MARGEM_PEQUENA;
		slots[i].y = tela->altura - SLOT_H - MARGEM_PEQUENA - (SLOT_H + ESPACO_ENTRE_SLOTS) * i;

		slots[i].botao_rotacionar.x = slots[i].x - BOTAO_ROTACIONAR_L - BOTAO_ROTACIONAR_OFFSET_DIREITA;
		slots[i].botao_rotacionar.y = centro(slots[i].y, SLOT_H, BOTAO_ROTACIONAR_H);
	}
}

void gerar_slot(struct Slot *slot)
{
	slot->ocupado = true;
	slot->peca = gerar_peca(slot->peca.x, slot->peca.y);
}

void rotacionar_slot(struct Slot *slot)
{
	slot->rotacionando = true;
	slot->peca = rotacionar_peca(&slot->peca);
}

void pegar_slot(struct Slot *slot, int x, int y)
{
	slot->arrastando = true;
	slot->arraste_x = slot->x - x;
	slot->arraste_y = slot->y - y;
}

void arrastar_slot(struct Slot *slot, int x, int y)
{
	slot->peca.x = slot->arraste_x + x;
	slot->peca.y = slot->arraste_y + y;
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
		*coluna = (referencia_x - quadro->x) / (DADO_L + ESPACO_ENTRE_DADOS);
		*linha = (referencia_y - quadro->y) / (DADO_H + ESPACO_ENTRE_DADOS);

		if (aceita_slot(quadro, slot, *linha, *coluna))
		{
			inserir_slot(quadro, slot, *linha, *coluna);
			return true;
		}
	}

	return false;
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

void gerar_slots(struct Slot slots[SLOTS_TAM])
{
	for (int i = 0; i < SLOTS_TAM; i++)
	{
		gerar_slot(&slots[i]);
	}
}

void inicializar_slots(struct Sprites *sprites, struct Slot slots[SLOTS_TAM])
{
	for (int i = 0; i < SLOTS_TAM; i++)
	{
		slots[i].ocupado = false;
		slots[i].arrastando = false;
		slots[i].rotacionando = false;
		
		inicializar_botao(&slots[i].botao_rotacionar, BOTAO_ROTACIONAR_L, BOTAO_ROTACIONAR_H);

		slots[i].botao_rotacionar.sprite_desabilitado = sprites->botao_rotacionar_desabilitado;
		slots[i].botao_rotacionar.sprite_pressionado = sprites->botao_rotacionar_ativo_pressionado;
	}
}

void desenhar_slot(struct Tela *tela, struct Slot *slot)
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
		desenhar_peca(tela, &slot->peca);
	}
}

void desenhar_pontuacao(struct Tela *tela, struct Jogo *jogo)
{
	int total_segundos = jogo->tempo * PERIODO_TICK;

	int minutos = total_segundos / 60;
	int segundos = total_segundos % 60;

	al_draw_textf(tela->fontes.fipps_12, COR_PRETO, MARGEM_PEQUENA, ESCORE_OFFSET_CIMA, ALLEGRO_ALIGN_LEFT, "%03d", jogo->escore);
	al_draw_textf(tela->fontes.pixelmix_8, COR_PRETO, MARGEM_PEQUENA, TEMPO_OFFSET_CIMA, ALLEGRO_ALIGN_LEFT, "%02d:%02d", minutos, segundos);
}

void analisar_tabuleiro_concluido(struct Jogo *jogo)
{
	if (restaurar_quadro_concluido(&jogo->quadro))
	{
		pontuar_tabuleiro_concluido(jogo);
	}
}

void analisar_consequencias(struct Jogo *jogo)
{
	int linhas = formar_tens(&jogo->quadro);

	if (linhas > 0)
	{
		jogo->desfazer.bloqueado = true;
	}

	if (linhas > 1)
	{
		pontuar_multilinha(jogo, linhas);
	}

	resetar_combo(jogo);
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
	restaurar_quadro_concluido(&jogo->quadro);

	jogo->slots[jogo->jogada.indice_origem].ocupado = true;
	jogo->slots[jogo->jogada.indice_origem].peca = jogo->jogada.peca;
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
		int indice_a = aleatorio(0, QUADRO_TAM);
		int direcao_a = aleatorio(0, DIRECOES_NUM);

		int indice_b;
		int direcao_b;

		do {
			indice_b = aleatorio(0, QUADRO_TAM);
			direcao_b = aleatorio(0, DIRECOES_NUM);
		} while (direcao_a == direcao_b && indice_a == indice_b);

		explodir(&jogo->quadro, indice_a, direcao_a);
		explodir(&jogo->quadro, indice_b, direcao_b);

		analisar_tabuleiro_concluido(jogo);
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

		if (!slot->rotacionando)
		{
			slot->botao_rotacionar.desabilitado = !pode_rotacionar_peca(&slot->peca) || !pode_usar_habilidade(&jogo->rotacao);
		}
	}
}

void atualizar_quadro(struct Jogo *jogo)
{
	bool modificado = false;

	for (int i = 0; i < QUADRO_TAM; i++)
	{
		for (int j = 0; j < QUADRO_TAM; j++)
		{
			struct Dado *dado = &jogo->quadro.dados[i][j];

			dado->ticks++;

			if (verificar_explosao(dado))
			{
				dado->animacao = ANIMACAO_PARADO;
			}

			if (verificar_colapso(dado))
			{
				remover_dado(&jogo->quadro, i, j);
				pontuar_dado(jogo);

				dado->animacao = ANIMACAO_PARADO;

				modificado = true;
			}
		}
	}

	if (modificado)
	{
		int linhas = formar_tens(&jogo->quadro);

		if (linhas > 0)
		{
			pontuar_combo(jogo, linhas);
		}

		analisar_tabuleiro_concluido(jogo);
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

	verificar_init(al_install_keyboard(), "keyboard");
	verificar_init(al_install_mouse(), "mouse");

	al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);

	struct Tela tela;

	tela.display = al_create_display(1280, 720);
	verificar_init(tela.display, "display");

	tela.canvas = NULL;

	ALLEGRO_TIMER *timer = al_create_timer(PERIODO_TICK);
	verificar_init(timer, "timer");

	ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
	verificar_init(queue, "queue");

	carregar_fontes(&tela.fontes);
	carregar_sprites(&tela.sprites);

	al_register_event_source(queue, al_get_display_event_source(tela.display));
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));

	bool finalizar = false;
	bool desenhar = true;

	ALLEGRO_EVENT event;

	struct Jogo jogo;

	jogo.slot_selecionado = -1;

	jogo.escore = 0;
	jogo.tempo = 0;

	redimensionar_tela(&tela);

	inicializar_quadro(&jogo.quadro);
	inicializar_slots(&tela.sprites, jogo.slots);
	inicializar_desfazer(&tela.sprites, &jogo.desfazer);
	inicializar_bomba(&tela.sprites, &jogo.bomba);
	inicializar_rotacao(&tela.sprites, &jogo.rotacao);

	posicionar_quadro(&tela, &jogo.quadro);
	posicionar_slots(&tela, jogo.slots);
	posicionar_habilidades(&tela, &jogo);

	gerar_slots(jogo.slots);

	jogo.desfazer.quantidade = 1;
	jogo.bomba.quantidade = 10;
	jogo.rotacao.quantidade = 1;

	al_start_timer(timer);

	while(true) {
		al_wait_for_event(queue, &event);

		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:
			atualizar_quadro(&jogo);
			atualizar_slots(&jogo);
			atualizar_habilidade(&jogo.desfazer);
			atualizar_habilidade(&jogo.bomba);
			atualizar_habilidade(&jogo.rotacao);

			jogo.tempo++;

			desenhar = true;
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			finalizar = true;
			break;
		case ALLEGRO_EVENT_DISPLAY_RESIZE:
			al_acknowledge_resize(tela.display);
			redimensionar_tela(&tela);
			posicionar_quadro(&tela, &jogo.quadro);
			posicionar_slots(&tela, jogo.slots);
			break;
		case ALLEGRO_EVENT_MOUSE_AXES:
		{
			int mouse_x = event.mouse.x / tela.escala;
			int mouse_y = event.mouse.y / tela.escala;

			if (jogo.slot_selecionado != -1)
				arrastar_slot(&jogo.slots[jogo.slot_selecionado], mouse_x, mouse_y);

			detectar_sobreposicao_botao(&jogo.desfazer.botao, mouse_x, mouse_y);
			detectar_sobreposicao_botao(&jogo.bomba.botao, mouse_x, mouse_y);
			detectar_sobreposicao_botao(&jogo.rotacao.botao, mouse_x, mouse_y);


			for (int i = 0; i < SLOTS_TAM; i++)
				detectar_sobreposicao_botao(&jogo.slots[i].botao_rotacionar, mouse_x, mouse_y);
				
			 
			break;
		}
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		{
			int mouse_x = event.mouse.x / tela.escala;
			int mouse_y = event.mouse.y / tela.escala;

			if (event.mouse.button & 1)
			{
				if (pressionar_botao(&jogo.desfazer.botao))
				{
					usar_desfazer(&jogo);
				}

				if (pressionar_botao(&jogo.bomba.botao))
				{
					usar_bomba(&jogo);
				}

				for (int i = 0; i < SLOTS_TAM; i++)
				{
					if (pressionar_botao(&jogo.slots[i].botao_rotacionar))
					{
						usar_rotacao(&jogo, &jogo.slots[i]);
					}
				}

				for (int i = 0; i < SLOTS_TAM; i++)
				{
					if (colisao_slot(&jogo.slots[i], mouse_x, mouse_y))
					{
						jogo.slot_selecionado = i;
						pegar_slot(&jogo.slots[i], mouse_x, mouse_y);
					}
				}
			}
			
			break;
		}
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			if (event.mouse.button & 1)
			{
				soltar_botao(&jogo.desfazer.botao);
				soltar_botao(&jogo.bomba.botao);
				soltar_botao(&jogo.rotacao.botao);

				for (int i = 0; i < SLOTS_TAM; i++)
				{
					soltar_botao(&jogo.slots[i].botao_rotacionar);
				}

				if (jogo.slot_selecionado != -1)
				{
					struct Slot *slot = &jogo.slots[jogo.slot_selecionado];

					int linha;
					int coluna;

					if (largar_slot(&jogo.quadro, slot, &linha, &coluna))
					{
						registrar_jogada(&jogo, jogo.slot_selecionado, linha, coluna);
						analisar_consequencias(&jogo);

						if (slot_vazios(jogo.slots))
						{
							gerar_slots(jogo.slots);
						}
					}

					jogo.slot_selecionado = -1;;
				}
			}
			break;
		case ALLEGRO_EVENT_KEY_DOWN:

			if (jogo.slot_selecionado != -1)
			{
				if (event.keyboard.keycode == ALLEGRO_KEY_SPACE)
				{
					gerar_slot(&jogo.slots[jogo.slot_selecionado]);
				}

				if (event.keyboard.keycode == ALLEGRO_KEY_R)
				{
					rotacionar_slot(&jogo.slots[jogo.slot_selecionado]);
				}
			}

			break;
		}

		if (finalizar)
			break;

		if (desenhar && al_event_queue_is_empty(queue))
		{
			al_set_target_bitmap(tela.canvas);
			al_clear_to_color(al_map_rgba(0, 0, 0, 0));

			desenhar_quadro(&tela, &jogo.quadro);

			for (int i = 0; i < SLOTS_TAM; i++)
			{
				desenhar_slot(&tela, &jogo.slots[i]);
			}

			if (jogo.slot_selecionado != -1)
			{
				desenhar_peca(&tela, &jogo.slots[jogo.slot_selecionado].peca);
			}

			desenhar_pontuacao(&tela, &jogo);
			desenhar_habilidade(&tela, &jogo.desfazer);
			desenhar_habilidade(&tela, &jogo.bomba);
			desenhar_habilidade(&tela, &jogo.rotacao);

			al_set_target_backbuffer(tela.display);
			al_clear_to_color(al_map_rgb(255, 255, 255));
			al_draw_bitmap(tela.canvas, 0, 0, 0);
			al_flip_display();

			desenhar = false;
		}
	}
}