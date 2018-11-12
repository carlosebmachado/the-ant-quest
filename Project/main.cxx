/*
 * DESCRI��O: Jogo criado para a disciplina de Algoritmos e Programa��o.
 * AUTORES:
 * Carlos Eduardo de Borba Machado
 * Caio Gonzaga Bernils
 * Mateus Luis Ropke Lauer
 */

// BIBLIOTECAS
//
#include "graphics.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>         
#include <list>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <vector>
//

// CONSTANTES
//
#define TEMPO_MAXIMO 45.0

#define TECLA_ACIMA 119
#define TECLA_ABAIXO 115
#define TECLA_DIREITA 97
#define TECLA_ESQUERDA 100
#define TECLA_PAUSE 27
#define	TECLA_SELECIONA 32

#define PAREDE 0
#define CAMINHO 1
#define ARMAZEM_1 6
#define ARMAZEM_2 7
#define ARMAZEM_3 8
#define PERSONAGEM_VAZIO 9
#define PERSONAGEM_CHEIO 10

#define SEM_COMIDA 0
//

enum armazens {ARMAZEM_LOCAL_1, ARMAZEM_LOCAL_2, ARMAZEM_LOCAL_3};

using namespace std;

/*-------------------------------- STRUCTS ------------------------------------*/

typedef struct Controle {
	bool menu = false, jogar = true, pausa = false, sair = false, facil = true;
	clock_t tempoInicial = 0, tempoFinal = 0;
	double tempoTotal = TEMPO_MAXIMO, tempoExecucao = 0;
	int mapaAtual = 0;
};

typedef struct Formiga {
	int comidaAtual = 0;
	bool vazio = true;
	int velocidade = 0;
	int x = 1, y = 1;
};

typedef struct Mapa {
	int armazem[3][4];
	int **mapa;
	int x, y;
};

/*-----------------------------------------------------------------------------*/




// PARTE DO C�DIGO ESCRITA POR CAIO
//
// Apresenta a tela de menu ao jogador
void menu(Controle &c)
{
	static bool opcao = false;
	char tecla;

	tecla = _getch();

	switch (tecla)
	{
	case 'w': //cima
		if (opcao)
			opcao = false;
		break;
	case 's': //baixo
		if (!opcao)
			opcao = true;
		break;
	case 27: // sair
		c.sair = true;
		break;
	case 32: // seleciona
		if (opcao)
			c.facil = false;
		else
			c.facil = true;
		c.menu = false;
		break;
	}
	//----------------- MENU --------------------- //

	//L�GICA MENU

	//-------------------------------------------- //
}
//
// FIM DA PARTE DE C�DIGO ESCRITA POR CAIO



/*---------------------------------------------------------------------------------------------------*/



// PARTE DO C�DIGO ESCRITA POR CARLOS
//
// Verifica se a formiga est� ou n�o com comida
void formigaAtual(Mapa &m, Formiga f) {
	if (f.vazio)
		m.mapa[f.x][f.y] = PERSONAGEM_VAZIO;
	else
		m.mapa[f.x][f.y] = PERSONAGEM_CHEIO;
}

// Inicializa os armazens
void iniciarArmazem(int a[3][4]) {
	int i, j, aux = 4;

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 4; j++) {
			if (i == 0) {
				a[i][j] = aux;
				aux--;
			} else {
				a[i][j] = 0;
			}
		}
	}
}

// Cria um novo mapa
void novoMapa(Mapa &m) {
	srand(time(0));
	m.x = 30 + (rand() % 20);
	m.y = (m.x / 3) * 2;
	list <pair <int, int> > drillers;

	m.mapa = new int *[m.y];
	for (size_t y = 0; y < m.y; y++)
		m.mapa[y] = new int[m.x];

	for (size_t x = 0; x < m.x; x++)
		for (size_t y = 0; y < m.y; y++)
			m.mapa[y][x] = 0;

	drillers.push_back(make_pair(m.x / 2, m.y / 2));

	while (drillers.size() > 0) {
		list <pair <int, int> >::iterator n, _n, temp;
		n = drillers.begin();
		_n = drillers.end();
		while (n != _n) {
			bool remove_driller = false;
			switch (rand() % 4)
			{
			case 0:
				(*n).second -= 2;
				if ((*n).second < 0 || m.mapa[(*n).second][(*n).first]) {
					remove_driller = true;
					break;
				}
				m.mapa[(*n).second + 1][(*n).first] = 1;
				break;
			case 1:
				(*n).second += 2;
				if ((*n).second >= m.y || m.mapa[(*n).second][(*n).first]) {
					remove_driller = true;
					break;
				}
				m.mapa[(*n).second - 1][(*n).first] = 1;
				break;
			case 2:
				(*n).first -= 2;
				if ((*n).first < 0 || m.mapa[(*n).second][(*n).first]) {
					remove_driller = true;
					break;
				}
				m.mapa[(*n).second][(*n).first + 1] = 1;
				break;
			case 3:
				(*n).first += 2;
				if ((*n).first >= m.x || m.mapa[(*n).second][(*n).first]) {
					remove_driller = true;
					break;
				}
				m.mapa[(*n).second][(*n).first - 1] = 1;
				break;
			}
			if (remove_driller) {
				n = drillers.erase(n);
			} else {
				drillers.push_back(make_pair((*n).first, (*n).second));
				if (rand() % 2)
					drillers.push_back(make_pair((*n).first, (*n).second));
				m.mapa[(*n).second][(*n).first] = 1;
				++n;
			}
		}
	}
}

// Nessa fun��o verifica-se se vai retirar ou colocar a comida no armaz�m
void verificarArmazem(Formiga &f, Mapa &m, int a) {
	int i;
	bool s = false;

	if (f.comidaAtual == 0) { // se a formiga n�o tiver comida, significa que ela vai pegar do armaz�m
		for (i = 3; i >= 0; i--) {
			if (m.armazem[a][i] != SEM_COMIDA) {
				f.comidaAtual = m.armazem[a][i];
				m.armazem[a][i] = SEM_COMIDA;
				m.mapa[f.x][f.y] = PERSONAGEM_CHEIO;
				f.vazio = false;
				i = -1;
			}
		}
	}else { // se j� tiver ela vai colocar no armaz�m
		for (i = 0; i <= 3; i++) {
			if (m.armazem[a][i] == SEM_COMIDA) {
				if (i == 0)
					s = true;
				else if (f.comidaAtual < m.armazem[a][i - 1])
					s = true;

				if (s) {
					m.armazem[a][i] = f.comidaAtual;
					f.comidaAtual = SEM_COMIDA;
					m.mapa[f.x][f.y] = PERSONAGEM_VAZIO;
					f.vazio = true;
				}
				i = 4;
			}
		}
	}
}

// Nessa fun��o s�o executados os comandos do jogo
void lerComandos(Mapa &m, Controle &c, Formiga &f) {
	char tecla = _getch();
	switch (tecla)
	{
	case TECLA_ACIMA:
		if (m.mapa[f.x - 1][f.y] == CAMINHO) {
			m.mapa[f.x][f.y] = CAMINHO;
			f.x--;
			formigaAtual(m, f);
		}
		break;
	case TECLA_ABAIXO:
		if (m.mapa[f.x + 1][f.y] == CAMINHO) {
			m.mapa[f.x][f.y] = CAMINHO;
			f.x++;
			formigaAtual(m, f);
		}
		break;
	case TECLA_ESQUERDA:
		if (m.mapa[f.x][f.y - 1] == CAMINHO) {
			m.mapa[f.x][f.y] = CAMINHO;
			f.y--;
			formigaAtual(m, f);
		}
		break;
	case TECLA_DIREITA:
		if (m.mapa[f.x][f.y + 1] == CAMINHO) {
			m.mapa[f.x][f.y] = CAMINHO;
			f.y++;
			formigaAtual(m, f);
		}
		break;
	case TECLA_PAUSE:
		c.pausa = true;
		c.jogar = false;
		break;
	case TECLA_SELECIONA:  // pega ou deposita comida
	// se alguma posi��o ao redor da formiga for comida ela pega
		if (m.mapa[f.x + 1][f.y] == ARMAZEM_1 ||
			m.mapa[f.x - 1][f.y] == ARMAZEM_1 ||
			m.mapa[f.x][f.y + 1] == ARMAZEM_1 ||
			m.mapa[f.x][f.y - 1] == ARMAZEM_1) // armazem 1
			verificarArmazem(f, m, ARMAZEM_LOCAL_1);
		if (m.mapa[f.x + 1][f.y] == ARMAZEM_2 ||
			m.mapa[f.x - 1][f.y] == ARMAZEM_2 ||
			m.mapa[f.x][f.y + 1] == ARMAZEM_2 ||
			m.mapa[f.x][f.y - 1] == ARMAZEM_2) // armazem 2 (meio)
			verificarArmazem(f, m, ARMAZEM_LOCAL_2);
		if (m.mapa[f.x + 1][f.y] == ARMAZEM_3 ||
			m.mapa[f.x - 1][f.y] == ARMAZEM_3 ||
			m.mapa[f.x][f.y + 1] == ARMAZEM_3 ||
			m.mapa[f.x][f.y - 1] == ARMAZEM_3) // armazem 3 (cima final)
			verificarArmazem(f, m, ARMAZEM_LOCAL_3);
		break;
	}
	Sleep(f.velocidade);
}

// Nessa fun��o a matriz � percorrida e os n�meros s�o substituidos
void imprimir(Mapa m, Controle c, Formiga f){
	int l = 0, t = 20;
	int x = 0, y = 100;
	/*---------------------------- HUD -------------------------------*/
	//cout << "Tempo ate o terremoto: " << (int)c.tempoTotal << "   " << endl;
	setfillstyle(SOLID_FILL, RED);
	bar(10, 10, 990, 90);
	
	for (int i = 0; i < m.y; i++) {
		for (int j = 0; j < m.x; j++) {
			if (m.mapa[i][j] == PAREDE) {
				setfillstyle(SOLID_FILL, GREEN);
				bar(l + x, l + y, t + x, t + y);
			}else if (m.mapa[i][j] == CAMINHO) {
				setfillstyle(SOLID_FILL, BROWN);
				bar(l + x, l + y, t + x, t + y);
			}else if (m.mapa[i][j] == PERSONAGEM_VAZIO) {
				setfillstyle(SOLID_FILL, BLUE);
				bar(l + x, l + y, t + x, t + y);
			}else if (m.mapa[i][j] == PERSONAGEM_CHEIO) {
				setfillstyle(SOLID_FILL, RED);
				bar(l + x, l + y, t + x, t + y);
			}else if (m.mapa[i][j] == ARMAZEM_1) {
				setfillstyle(SOLID_FILL, WHITE);
				bar(l + x, l + y, t + x, t + y);
			}else if (m.mapa[i][j] == ARMAZEM_2) {
				setfillstyle(SOLID_FILL, WHITE);
				bar(l + x, l + y, t + x, t + y);
			}else if (m.mapa[i][j] == ARMAZEM_3) {
				setfillstyle(SOLID_FILL, WHITE);
				bar(l + x, l + y, t + x, t + y);
			}
			x += t;
		}
		y += t;
		x = l;
	}
}

// Verificam se o jogador venceu
bool venceuDificil(int a[3][4]) {
	int i;

	for (i = 0; i < 4; i++)
		if (a[2][i] == 0)
			return false;
	return true;
}

bool venceuFacil(int a[3][4]) {
	if (a[2][0] == 4)
		return true;
	return false;
}
//-------------------------------
// Tela de fim de jogo
bool venceuJogo(double tempo) {
	/*
	system("cls");
	cout << "VOCE VENCEU O JOGO, PARABENS!!!\n\n";
	cout << "O tempo total foi: " << tempo << endl << endl;
	system("pause");
	*/
	return true;
}
//-------------------------------
//
// FIM DA PARTE DE C�DIGO ESCRITA POR CARLOS



/*---------------------------------------------------------------------------------------------------*/



// PARTE DO C�DIGO ESCRITA POR MATEUS
//
// Muda a posi��o da formiga para n�o ser soterrada
void mudarPosicao(Formiga &f, Mapa &m, Controle c, int a) {
	if (m.mapa[f.x][f.y] == PAREDE) {
		m.mapa[f.x][f.y] = a;
	}
	for (int i = 1; i < 50; i++) {
		if (m.mapa[f.x + i][f.y] == PAREDE) {
			m.mapa[f.x + i][f.y] = a;
			f.x++;
		}
		else if (m.mapa[f.x - i][f.y] == PAREDE) {
			m.mapa[f.x - i][f.y] = a;
			f.x--;
		}
		else if (m.mapa[f.x][f.y + i] == PAREDE) {
			m.mapa[f.x][f.y + i] = a;
			f.y++;
		}
		else if (m.mapa[f.x][f.y - i] == PAREDE) {
			m.mapa[f.x][f.y - i] = a;
			f.y--;
		}
	}
}
// fun��o para medir tempo e sortear novo mapa 
void medirTempo(bool inicio, Mapa &m, Controle &c, Formiga &f) {
	if (inicio) {
		c.tempoInicial = clock();
	}
	else {
		int aux = c.mapaAtual;

		c.tempoFinal = clock();
		c.tempoTotal -= (c.tempoFinal - c.tempoInicial) / (double)CLOCKS_PER_SEC;
		c.tempoExecucao -= (c.tempoFinal - c.tempoInicial) / (double)CLOCKS_PER_SEC;

		if (c.tempoTotal < 0) {
			for (int i = 0; i < m.x; i++) {
				for (int j = 0; j < m.y; j++) {
					if (m.mapa[i][j] == PERSONAGEM_VAZIO)
						m.mapa[i][j] = CAMINHO;
					if (m.mapa[i][j] == PERSONAGEM_CHEIO)
						m.mapa[i][j] = CAMINHO;
				}
			}

			srand(time(NULL));

			while (c.mapaAtual == aux)
				c.mapaAtual = rand() % 3;

			c.tempoTotal = TEMPO_MAXIMO;

			if (f.vazio)
				mudarPosicao(f, m, c, PERSONAGEM_VAZIO);
			else
				mudarPosicao(f, m, c, PERSONAGEM_CHEIO);
		}
	}
}
//
// FIM DA PARTE DE C�DIGO ESCRITA POR MATEUS



/*---------------------------------------------------------------------------------------------------*/



// TANTO A FUN��O MAIN COMO SUAS VARI�VEIS FORAM MANIPULADAS POR TODO O GRUPO
//
int main(void) {
	/*-------------------------------- VARI�VEIS ------------------------------*/
	Mapa m;
	Formiga f;
	Controle c;
	/*-------------------------------------------------------------------------*/

	/*------------------------------ INICIALIZA��O ----------------------------*/
	initwindow(1005, 645, "The Ant Quest");
	setfillstyle(SOLID_FILL, GREEN);
	bar(0, 0, 1000, 640);
	novoMapa(m);
	iniciarArmazem(m.armazem);
	/*-------------------------------------------------------------------------*/

	/*------------------------------ LOOP PRINCIPAL ---------------------------*/
	while (!c.sair) {
		if (c.menu) {
			menu(c);
		}else if (c.jogar) {
			//medirTempo(true, m, c, f);
			imprimir(m, c, f);
			//lerComandos(m, c, f);
			//medirTempo(false, m, c, f);
		}else if (c.pausa) {

		}

		if (c.facil && venceuFacil(m.armazem)) {
			c.sair = venceuJogo(c.tempoExecucao);
		}else if (!c.facil && venceuDificil(m.armazem)) {
			c.sair = venceuJogo(c.tempoExecucao);
		}
	}
	/*-------------------------------------------------------------------------*/
	closegraph();
	return 0;
}
//