#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define L 16
#define C 32

using namespace std;

void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void mgotoxy(int x, int y)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ static_cast<short>(x), static_cast<short>(y) });
}

// PARTE DO C�DIGO ESCRITA POR CAIO
//
//Nessa fun��o a matriz � percorrida e os n�meros s�o substituidos
void imprime(int m[L][C], int comida, int a1[], int a2[], int a3[])
{
	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < C; j++)
		{
			if (m[i][j] == 1)
				cout << (char)178;
			else if (m[i][j] == 0)
				cout << " ";
			else if (m[i][j] == 9)
				cout << (char)667;
			else if (m[i][j] == 10)
				cout << "O";
			else if (m[i][j] == 6)
				cout << "1";
			else if (m[i][j] == 7)
				cout << "2";
			else if (m[i][j] == 8)
				cout << "3";
			else if (m[i][j] == 5)
				cout << (char)254;
		}
		cout << endl;
	}
	/*-------------- HUD -----------------*/
	cout << endl << endl;
	if (comida == 0)
		cout << "Comida atual: nenhum\n\n";
	else
		cout << "Comida atual: " << comida << "           \n\n"; 
	/*
	Neste simples caso eu coloquei espa�oes depois 
	da vari�vel pois o programa n�o limpa a tela, mas sim 
	sobrep�e os caracteres anteriores, ent�o quando o valor 
	da comida mudava, ficava sobrando uma parte do nenhum
	(CARLOS).
	*/
	cout << "Armazem 1 (BAIXO):\nP1: " << a1[0] << " | P2: " << a1[1] << " | P3: " << a1[2] << " | P4: " << a1[3] << endl << endl;
	cout << "Armazem 2  (MEIO):\nP1: " << a2[0] << " | P2: " << a2[1] << " | P3: " << a2[2] << " | P4: " << a2[3] << endl << endl;
	cout << "Armazem 3  (CIMA):\nP1: " << a3[0] << " | P2: " << a3[1] << " | P3: " << a3[2] << " | P4: " << a3[3] << endl << endl;
	/* 
	O armaz�m est� sem acento pois quando fui implementar
	o setlocale, bugou os caracteres respons�veis pelo mapa
	(CARLOS).
	*/
	/*------------------------------------*/
}

// DESCRI��O
void preencherMapas(int m1[L][C], int m2[L][C], int m3[L][C])
{
	int mapa1[L][C] =
	{
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,8,1 },
		{ 1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,5,1 },
		{ 1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,0,1 },
		{ 1,0,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1 },
		{ 1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,7,1,0,1,1,1,1,1,1,1,1,1,0,1 },
		{ 1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,0,0,5,1,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,1,0,0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,0,1,0,1,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,0,0,0,0,1,0,0,0,0,0,0,1 },
		{ 1,0,1,0,1,0,0,0,0,0,0,1,0,1,0,1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,0,1 },
		{ 1,0,1,0,1,0,1,1,1,1,1,1,0,1,0,1,0,1,1,0,0,0,0,0,1,0,1,0,1,1,0,1 },
		{ 1,0,1,0,1,1,1,1,1,1,1,0,0,1,0,1,0,0,1,1,1,0,1,0,1,0,1,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,1,0,0,0,1,0,0,0,1,0,1,1,1,1 },
		{ 1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1 },
		{ 1,6,5,0,1,0,0,0,0,0,0,0,1,1,1,0,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
	};
	int mapa2[L][C];
	int mapa3[L][C];

	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < C; j++)
		{
			m1[i][j] = mapa1[i][j];
		}

	}
}
//
// FIM DA PARTE DE C�DIGO ESCRITA POR CAIO





/*---------------------------------------------------------------------------------------------------*/





// PARTE DO C�DIGO ESCRITA POR CARLOS
//
// Verifica se a formiga est� ou n�o com comida
void formigaAtual(int m[L][C], int x, int y, bool vazio)
{
	if (vazio)
		m[x][y] = 9;
	else
		m[x][y] = 10;
}

// Inicializa o armaz�m inicial
void iniciarArmazem(int comida[])
{
	int i, j = 4;
	for (i = 0; i < 4; i++)
	{
		comida[i] = j;
		j--;
	}
}

// Nessa fun��o verifica-se se vai retirar ou colocar a comida no armaz�m
void verificarArmazem(int &comida, int local[], int m[L][C], int x, int y, bool &vazio)
{
	int i;
	bool s = false;
	if (comida == 0)
	{
		for (i = 3; i >= 0; i--)
		{
			if (local[i] != 0)
			{
				comida = local[i];
				local[i] = 0;
				m[x][y] = 10;
				vazio = false;
			}
		}
	}
	else
	{
		for (i = 0; i <= 3; i++)
		{
			if (local[i] == 0)
			{
				if (i == 0)
					s = true;
				else if (comida < local[i-1])
					s = true;

				if (s)
				{
					local[i] = comida;
					comida = 0;
					m[x][y] = 9;
					vazio = true;
				}
			}
		}
	}
}

// Nessa fun��o s�o executados os comandos do jogo
void comandos(int m[L][C], bool &sair, int local1[], int local2[], int local3[], bool &vazio, int &comidaAtualFormiga)
{
	static int x = 1, y = 1;
	char tecla;

	if (_kbhit())
	{
		tecla = _getch();

		switch (tecla)
		{
		case 'w': //cima
			if (m[x - 1][y] == 0)
			{
				m[x][y] = 0;
				x--;
				formigaAtual(m, x, y, vazio);
			}
			break;
		case 's': //baixo
			if (m[x + 1][y] == 0)
			{
				m[x][y] = 0;
				x++;
				formigaAtual(m, x, y, vazio);
			}
			break;
		case 'a': //esquerda
			if (m[x][y - 1] == 0)
			{
				m[x][y] = 0;
				y--;
				formigaAtual(m, x, y, vazio);
			}
			break;
		case 'd': //direita
			if (m[x][y + 1] == 0)
			{
				m[x][y] = 0;
				y++;
				formigaAtual(m, x, y, vazio);
			}
			break;
		case 27: // sair
			sair = true;
			break;
		case 32:  // pega ou deposita comida
			// se alguma posi��o ao redor da formiga for comida ela pega
			if (m[x + 1][y] == 5 || m[x - 1][y] == 5 || m[x][y + 1] == 5 || m[x][y - 1] == 5   )
			{
				if (x > 12 && y < 3) // armazem 1 (inicial baixo)
				{
					verificarArmazem(comidaAtualFormiga, local1, m, x, y, vazio);
				}
				if (x > 4 && x < 8 && y > 15 && y < 19) // armazem 2 (meio)
				{
					verificarArmazem(comidaAtualFormiga, local2, m, x, y, vazio);
				}
				if (x < 4 && y > 28) // armazem 3 (cima)
				{
					verificarArmazem(comidaAtualFormiga, local3, m, x, y, vazio);
				}
			}
			break;
		}
		Sleep(50);
	}
}
//
// FIM DA PARTE DE C�DIGO ESCRITA POR CARLOS





/*---------------------------------------------------------------------------------------------------*/





// PARTE DO C�DIGO ESCRITA POR MATEUS
//
// fun��o para medir tempo e sortear novo mapa 
void medirTempo(bool inicio, int &mapa)
{
	static clock_t tempo_inicial = 0, tempo_final = 0;
	static double tempo_total;
	const double TEMPO_MAXIMO = 120000.0;

	/*
	N�o cheguei nem a testar esse c�digo, n�o sei se a cada
	chamada do c�digo pode ter aquela inicializa��o em 0 das
	vari�veis (CARLOS).
	*/
	if (inicio)
	{
		tempo_inicial = clock();
	}
	else
	{
		tempo_final = clock();
		tempo_total += (tempo_final - tempo_inicial) / (double)CLOCKS_PER_SEC;
		if (tempo_total >= TEMPO_MAXIMO)
		{
			srand(time(NULL));
			mapa = rand() % 2;
			tempo_total = 0.0;
		}
	}
}
//
// FIM DA PARTE DE C�DIGO ESCRITA POR MATEUS





// TANTO A FUN��O MAIN COMO SUAS VARI�VEIS FORAM MANIPULADAS POR TODO O GRUPO
//

/*-------------------------------- STRUCTS ------------------------------------*/
struct Formiga
{
	int comidaAtual = 0;
	bool vazio = true;
};

struct Mapa
{
	int m[L][C];
};

struct Armazem
{
	int comida[4] = {0, 0, 0, 0};
};
/*-----------------------------------------------------------------------------*/

int main()
{
	/*-------------------------------- VARI�VEIS ------------------------------*/
	Formiga formiga;
	Mapa mapa[3];
	Armazem local[3]; // cada struct do vetor local representa um armazem no jogo
	int mapaAtual = 0;
	bool sair = false;
	/*-------------------------------------------------------------------------*/

	/*------------------------------ INICIALIZA��O ----------------------------*/
	hidecursor();
	preencherMapas(mapa[0].m, mapa[1].m, mapa[2].m);
	iniciarArmazem(local[0].comida);
	//setlocale(LC_ALL, "Portuguese"); AO TENTAR USAR O SETLOCALE BUGOU TODOS OS CARACTERES DO MAPA
	/*-------------------------------------------------------------------------*/

	while (!sair)
	{
		//medirTempo(true, mapaAtual);
		imprime(mapa[mapaAtual].m, formiga.comidaAtual, local[0].comida, local[1].comida, local[2].comida);
		comandos(mapa[mapaAtual].m, sair, local[0].comida, local[1].comida, local[2].comida, formiga.vazio, formiga.comidaAtual);
		mgotoxy(0, 0);
		//medirTempo(false, mapaAtual);
	}
	return 0;
}
//
//