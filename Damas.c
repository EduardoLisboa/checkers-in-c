#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char tabuleiro[12][12]= //Variável global do tabuleiro, pré-definido com os '.' como espacos vazios, 'P' como pecas pretas e 'B' como pecas brancas
{
	{' ', ' ', '1', '2', '3', '4', '5', '6', '7', '8', ' ', ' '}, //0
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //1
    {'1', ' ', 'B', '.', 'B', '.', 'B', '.', 'B', '.', ' ', '1'}, //2
    {'2', ' ', '.', 'B', '.', 'B', '.', 'B', '.', 'B', ' ', '2'}, //3
    {'3', ' ', 'B', '.', 'B', '.', 'B', '.', 'B', '.', ' ', '3'}, //4
    {'4', ' ', '.', '.', '.', '.', '.', '.', '.', '.', ' ', '4'}, //5
    {'5', ' ', '.', '.', '.', '.', '.', '.', '.', '.', ' ', '5'}, //6
    {'6', ' ', '.', 'P', '.', 'P', '.', 'P', '.', 'P', ' ', '6'}, //7
    {'7', ' ', 'P', '.', 'P', '.', 'P', '.', 'P', '.', ' ', '7'}, //8
    {'8', ' ', '.', 'P', '.', 'P', '.', 'P', '.', 'P', ' ', '8'}, //9
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //10
    {' ', ' ', '1', '2', '3', '4', '5', '6', '7', '8', ' ', ' '}  //11
}; // 0    1    2    3    4    5    6    7    8    9   10   11

char tabuleiroreset[12][12]= //Para reiniciar o jogo
{
	{' ', ' ', '1', '2', '3', '4', '5', '6', '7', '8', ' ', ' '}, //0
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //1
    {'1', ' ', 'B', '.', 'B', '.', 'B', '.', 'B', '.', ' ', '1'}, //2
    {'2', ' ', '.', 'B', '.', 'B', '.', 'B', '.', 'B', ' ', '2'}, //3
    {'3', ' ', 'B', '.', 'B', '.', 'B', '.', 'B', '.', ' ', '3'}, //4
    {'4', ' ', '.', '.', '.', '.', '.', '.', '.', '.', ' ', '4'}, //5
    {'5', ' ', '.', '.', '.', '.', '.', '.', '.', '.', ' ', '5'}, //6
    {'6', ' ', '.', 'P', '.', 'P', '.', 'P', '.', 'P', ' ', '6'}, //7
    {'7', ' ', 'P', '.', 'P', '.', 'P', '.', 'P', '.', ' ', '7'}, //8
    {'8', ' ', '.', 'P', '.', 'P', '.', 'P', '.', 'P', ' ', '8'}, //9
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //10
    {' ', ' ', '1', '2', '3', '4', '5', '6', '7', '8', ' ', ' '}  //11
}; // 0    1    2    3    4    5    6    7    8    9   10   11

int sair = 0; //Variável global para sair do programa
char anterior; //Variável global que armazena a peça que foi jogada anteriormente, impedindo que o mesmo tipo seja jogado duas vezes

int pontospretas = 0, pontosbrancas = 0;
int contpretas, contbrancas;

typedef struct posicao_tabuleiro //Struct global para as posicoes no tabuleiro
{
	int xi;
	int yi;
	int xf;
	int yf;
} posicao_tabuleiro;

posicao_tabuleiro posicao; //Definicao global de um variavel "posicao" do tipo "posicao_tabuleiro"

/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
//----------------------------------- PONTUAÇÃO -----------------------------------\\
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/

void pontuacao()
{
	pontosbrancas = 25 * (12 - contpretas);
	pontospretas = 25 * (12 - contbrancas);
	printf("\n\t     PRETAS: %d       BRANCAS: %d\n\n", pontospretas, pontosbrancas);
}

void exibirMatriz() //Função que exibe a matriz Tabuleiro atualizada
{
	int i, j;
	for(i = 0; i < 12; i++)
	{
		printf("\t");
		for(j = 0; j < 12; j++)
		{
			printf(" %c ", tabuleiro[i][j]);
		}
		printf("\n");
	}
}

/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
//------------------------------------- DAMAS -------------------------------------\\
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/

int damabranca = 0, damapreta = 0;
void checaDama(int xf, int yf) //Checa se ha alguma peça que possa se tornar dama
{
	int j;
	for(j = 0; j < 12; j++)
	{
		if(tabuleiro[2][j]=='P')
		{
			damapreta = 1;
		}
		if(tabuleiro[9][j]=='B')
		{
			damabranca = 1;
		}
	}

	if(damapreta == 1 && tabuleiro[xf][yf] == 'P' && xf == 2)
	{
		tabuleiro[xf][yf] = 'K';
		return;
	}
	if(damabranca == 1 && tabuleiro[xf][yf] == 'B' && xf == 9)
	{
		tabuleiro[xf][yf] = 'W';
		return;
	}
}

void moveDama(int xi, int yi, int xf, int yf) //Faz a movimentacao das damas
{
	int i, j;

	if(xf > xi && yf > yi) //Andar de cima para baixo, da esquerda para a direita
	{
		if(xf == xi + 1 && yf == yi + 1) //Andar uma casa
		{
			if(tabuleiro[xi + 1][yi + 1] == '.')
			{
				anterior = tabuleiro[xi][yi];
				tabuleiro[xi + 1][yi + 1] = tabuleiro[xi][yi];
				tabuleiro[xi][yi] = '.';
				return;
			}
			else
			{
				printf("\nJogada invalida\n");
				getchar();
				getchar();
				return;
			}
		}
		else if(xf == xi + 2 && yf == yi + 2) //Andar duas casas e comer
		{
			if(tabuleiro[xi + 2][yi + 2] == '.') //Checa se há alguma peça no destino e substitui a peça que estiver no espaço no meio em um '.'
			{
				anterior = tabuleiro[xi][yi];
				tabuleiro[xf][yf] = tabuleiro[xi][yi];
				tabuleiro[xi + 1][yi + 1] = '.';
				tabuleiro[xi][yi] = '.';
				return;
			}
			else
			{
				printf("\nJogada invalida\n");
				getchar();
				getchar();
				return;
			}
		}
		else //Andar mais de duas casas
		{
			j = yi + 1;
			for(i = xi + 1; i <= xf; i++)
			{
				if(tabuleiro[i][j] != '.')
				{
					anterior = tabuleiro[xi][yi];
					tabuleiro[i - 1][j - 1] = tabuleiro[xi][yi];
					tabuleiro[xi][yi] = '.';
					return;
				}
				j++;
			}
			anterior = tabuleiro[xi][yi];
			tabuleiro[xf][yf] = tabuleiro[xi][yi];
			tabuleiro[xi][yi] = '.';
			return;
		}
	} //Fecha movimentos de cima para baixo, da esquerda para a direita

	if(xf > xi && yf < yi) //Andar de cima para baixo, da direita para a esquerda
	{
		if(xf == xi + 1 && yf == yi - 1) //Andar uma casa
		{
			if(tabuleiro[xi + 1][yi - 1] == '.')
			{
				anterior = tabuleiro[xi][yi];
				tabuleiro[xi + 1][yi - 1] = tabuleiro[xi][yi];
				tabuleiro[xi][yi] = '.';
				return;
			}
			else
			{
				printf("\nJogada invalida\n");
				getchar();
				getchar();
				return;
			}
		}
		else if(xf == xi + 2 && yf == yi - 2) //Andar duas casa e comer peca
		{
			if(tabuleiro[xi + 2][yi - 2] == '.') //Checa se há alguma peça no destino e substitui a peça que estiver no espaço no meio em um '.'
			{
				anterior = tabuleiro[xi][yi];
				tabuleiro[xf][yf] = tabuleiro[xi][yi];
				tabuleiro[xi + 1][yi - 1] = '.';
				tabuleiro[xi][yi] = '.';
				return;
			}
			else
			{
				printf("\nJogada invalida\n");
				getchar();
				getchar();
				return;
			}
		}
		else //Andar mais de duas casas
		{
			j = yi - 1;
			for(i = xi + 1; i <= xf; i++)
			{
				if(tabuleiro[i][j] != '.')
				{
					anterior = tabuleiro[xi][yi];
					tabuleiro[i - 1][j + 1] = tabuleiro[xi][yi];
					tabuleiro[xi][yi] = '.';
					return;
				}
				j--;
			}
			anterior = tabuleiro[xi][yi];
			tabuleiro[xf][yf] = tabuleiro[xi][yi];
			tabuleiro[xi][yi] = '.';
			return;
		}
	} //Fecha movimentos de cima para baixo, da direita para a esquerda

	if(xf < xi && yf > yi) //De baixo para cima, da esquerda para a direita
	{
		if(xf == xi - 1 && yf == yi + 1) //Andar uma casa
		{
			if(tabuleiro[xi - 1][yi + 1] == '.')
			{
				anterior = tabuleiro[xi][yi];
				tabuleiro[xi - 1][yi + 1] = tabuleiro[xi][yi];
				tabuleiro[xi][yi] = '.';
				return;
			}
			else
			{
				printf("\nJogada invalida\n");
				getchar();
				getchar();
				return;
			}
		}
		else if(xf == xi - 2 && yf == yi + 2) //Andar duas casa e comer peca
		{
			if(tabuleiro[xi - 2][yi + 2] == '.') //Checa se há alguma peça no destino e substitui a peça que estiver no espaço no meio em um '.'
			{
				anterior = tabuleiro[xi][yi];
				tabuleiro[xf][yf] = tabuleiro[xi][yi];
				tabuleiro[xi - 1][yi + 1] = '.';
				tabuleiro[xi][yi] = '.';
				return;
			}
			else
			{
				printf("\nJogada invalida\n");
				getchar();
				getchar();
				return;
			}
		}
		else //Andar mais de duas casas
		{
			j = yi + 1;
			for(i = xi - 1; i >= xf; i--)
			{
				if(tabuleiro[i][j] != '.')
				{
					anterior = tabuleiro[xi][yi];
					tabuleiro[i + 1][j - 1] = tabuleiro[xi][yi];
					tabuleiro[xi][yi] = '.';
					return;
				}
				j++;
			}
			anterior = tabuleiro[xi][yi];
			tabuleiro[xf][yf] = tabuleiro[xi][yi];
			tabuleiro[xi][yi] = '.';
			return;
		}
	} //Fecha movimentos de baixo para cima, da esquerda para a direita

	if(xf < xi && yf < yi) //De baixo para cima, da direita para a esquerda
	{
		if(xf == xi - 1 && yf == yi - 1) //Andar uma casa
		{
			if(tabuleiro[xi - 1][yi - 1] == '.')
			{
				anterior = tabuleiro[xi][yi];
				tabuleiro[xi - 1][yi - 1] = tabuleiro[xi][yi];
				tabuleiro[xi][yi] = '.';
				return;
			}
			else
			{
				printf("\nJogada invalida\n");
				getchar();
				getchar();
				return;
			}
		}
		else if(xf == xi - 2 && yf == yi - 2) //Andar duas casa e comer peca
		{
			if(tabuleiro[xi - 2][yi - 2] == '.') //Checa se há alguma peça no destino e substitui a peça que estiver no espaço no meio em um '.'
			{
				anterior = tabuleiro[xi][yi];
				tabuleiro[xf][yf] = tabuleiro[xi][yi];
				tabuleiro[xi - 1][yi - 1] = '.';
				tabuleiro[xi][yi] = '.';
				return;
			}
			else
			{
				printf("\nJogada invalida\n");
				getchar();
				getchar();
				return;
			}
		}
		else //Andar mais de duas casas
		{
			j = yi - 1;
			for(i = xi - 1; i >= xf; i--)
			{
				if(tabuleiro[i][j] != '.')
				{
					anterior = tabuleiro[xi][yi];
					tabuleiro[i + 1][j + 1] = tabuleiro[xi][yi];
					tabuleiro[xi][yi] = '.';
					return;
				}
				j--;
			}
			anterior = tabuleiro[xi][yi];
			tabuleiro[xf][yf] = tabuleiro[xi][yi];
			tabuleiro[xi][yi] = '.';
			return;
		}
	}
	
}

/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
//------------------------------------ JOGADAS ------------------------------------\\
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/

int pecaanterior=0;
void Anterior(int xi, int yi) //Checa se a peca jogada na rodada anterior e a mesma dessa rodada
{
	if((anterior=='B' || anterior=='W') && (tabuleiro[xi][yi]=='B' || tabuleiro[xi][yi]=='W'))
	{
		printf("\nVez do outro jogador\n");
		pecaanterior=1;
		getchar();
		getchar();
		return;
	}
	else if((anterior=='P' || anterior=='K') && (tabuleiro[xi][yi]=='P' || tabuleiro[xi][yi]=='K'))
	{
		printf("\nVez do outro jogador\n");
		pecaanterior=1;
		getchar();
		getchar();
		return;
	}
	anterior='.';
}

void jogadaValida(int xi, int yi, int xf, int yf) //Funcao para validar as jogadas
{

	Anterior(xi,yi);
	if(pecaanterior)
	{
		pecaanterior=0;
		return;
	}

	if(xi==xf || yi==yf) //Andou na vertical ou horizontal
	{
		printf("\nJogada invalida\n");
		getchar();
		getchar();
		return;
	}

	if(tabuleiro[xi][yi]=='W' || tabuleiro[xi][yi]=='K')
	{
		moveDama(xi,yi,xf,yf);
		return;
	}
	else
	{
		if((xf>xi && yf>yi) && tabuleiro[xi][yi]=='B') //Andar de cima para baixo, da esquerda para a direita
		{
			if(xf>xi+2 || yf>yi+2) //Se andar mais de duas casas
			{
				printf("\nJogada invalida\n");
				getchar();
				getchar();
				return;
			}
			else if((tabuleiro[xi+1][yi+1]!='.') && (xf==xi+1 && yf==yi+1)) //Checa se há alguma peça no destino
			{
				printf("\nJogada invalida\n");
				getchar();
				getchar();
				return;
			}
			else if((tabuleiro[xi+2][yi+2]=='.') && (xf==xi+2 && yf==yi+2)) //Checa se há alguma peça no destino e substitui a peça que estiver no espaço no meio em um '.'
			{
				anterior=tabuleiro[xi][yi];
				tabuleiro[xf][yf]=tabuleiro[xi][yi];
				tabuleiro[xi+1][yi+1]='.';
				tabuleiro[xi][yi]='.';

				checaDama(xf,yf);
				
				return;
			}
			else //Qualquer outro caso andará apenas uma peça e substituirá o espaço onde ela estava por um '.'
			{
				anterior=tabuleiro[xi][yi];
				tabuleiro[xi+1][yi+1]=tabuleiro[xi][yi];
				tabuleiro[xi][yi]='.';

				checaDama(xi+1,yi+1);
				
				return;
			}
		}
		else if((xf>xi && yf>yi) && tabuleiro[xi][yi]!='B')
		{
			printf("\nJogada invalida\n");
			getchar();
			getchar();
			return;
		}
		
		if((xf>xi && yf<yi) && tabuleiro[xi][yi]=='B') //Andar de cima para baixo, da direita para a esquerda
		{
			if(xf>xi+2 && yf<yi-2) //Mesma coisa da anterior, apenas alterando o lado do movimento
			{
				printf("\nJogada invalida\n"); 
				getchar();
				getchar();
				return;
			}
			else if((tabuleiro[xi+1][yi-1]=='P' || tabuleiro[xi+1][yi-1]=='B') && (xf==xi+1 && yf==yi-1)) //Checa se há alguma peça no destino
			{
				printf("\nJogada invalida\n");
				getchar();
				getchar();
				return;
			}
			else if((tabuleiro[xi+2][yi-2]=='.') && (xf==xi+2 && yf==yi-2))
			{
				anterior=tabuleiro[xi][yi];
				tabuleiro[xf][yf]=tabuleiro[xi][yi];
				tabuleiro[xi+1][yi-1]='.';
				tabuleiro[xi][yi]='.';
			
				checaDama(xf,yf);
				
				return;
			}
			else
			{
				anterior=tabuleiro[xi][yi];
				tabuleiro[xi+1][yi-1]=tabuleiro[xi][yi];
				tabuleiro[xi][yi]='.';
			
				checaDama(xi+1,yi-1);
				
				return;
			}
		}
		else if((xf>xi && yf<yi) && tabuleiro[xi][yi]!='B')
		{
			printf("\nJogada invalida\n");
			getchar();
			getchar();
			return;
		}
		
		if((xf<xi && yf>yi) && tabuleiro[xi][yi]=='P') //De baixo para cima, da esquerda para a direita
		{
			if(xf<xi-2 && yf>yi+2)
			{
				printf("\nJogada invalida\n");
				getchar();
				getchar();
				return;
			}
			else if((tabuleiro[xi-1][yi+1]=='P' || tabuleiro[xi-1][yi+1]=='B') && (xf==xi-1 && yf==yi+1)) //Checa se há alguma peça no destino
			{
				printf("\nJogada invalida\n");
				getchar();
				getchar();
				return;
			}
			else if((tabuleiro[xi-2][yi+2]=='.') && (xf==xi-2 && yf==yi+2))
			{
				anterior=tabuleiro[xi][yi];
				tabuleiro[xf][yf]=tabuleiro[xi][yi];
				tabuleiro[xi-1][yi+1]='.';
				tabuleiro[xi][yi]='.';
			
				checaDama(xf,yf);
				
				return;
			}
			else
			{
				anterior=tabuleiro[xi][yi];
				tabuleiro[xi-1][yi+1]=tabuleiro[xi][yi];
				tabuleiro[xi][yi]='.';
			
				checaDama(xi-1,yi+1);
				
				return;
			}
		}
		else if((xf<xi && yf>yi) && tabuleiro[xi][yi]!='P')
		{
			printf("\nJogada invalida\n");
			getchar();
			getchar();
			return;
		}

		if((xf<xi && yf<yi) && tabuleiro[xi][yi]=='P') //De baixo para cima, da direita para a esquerda
		{
			if(xf<xi-2 && yf<yi-2)
			{
				printf("\nJogada invalida\n");
				getchar();
				getchar();
				return;
			}
			else if((tabuleiro[xi-1][yi-1]=='P' || tabuleiro[xi-1][yi-1]=='B') && (xf==xi-1 && yf==yi-1)) //Checa se há alguma peça no destino
			{
				printf("\nJogada invalida\n");
				getchar();
				getchar();
				return;
			}
			else if((tabuleiro[xi-2][yi-2]=='.') && (xf==xi-2 && yf==yi-2))
			{
				anterior=tabuleiro[xi][yi];
				tabuleiro[xf][yf]=tabuleiro[xi][yi];
				tabuleiro[xi-1][yi-1]='.';
				tabuleiro[xi][yi]='.';
			
				checaDama(xf,yf);
				
				return;
			}
			else
			{
				anterior=tabuleiro[xi][yi];
				tabuleiro[xi-1][yi-1]=tabuleiro[xi][yi];
				tabuleiro[xi][yi]='.';
			
				checaDama(xi-1,yi-1);
				
				return;
			}
		}
		else if((xf<xi && yf<yi) && tabuleiro[xi][yi]!='P')
		{
			printf("\nJogada invalida\n");
			getchar();
			getchar();
			return;
		}
	}
}

/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
//------------------------------ RECEBER COORDENADAS ------------------------------\\
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/

void jogada() //Funcao que escaneia as pecas e, caso estejam fora dos parametros básicos, exibe erro e repete a solicitacao
{
    int i, j;
    char xini[10000], yini[10000], xfin[10000], yfin[10000];

    fflush(stdin);
	printf("\nCoordenadas da peca a ser movida: ");
	scanf("%s %s", xini, yini);

	if(strlen(xini)>1 || strlen(yini)>1)
	{
		printf("\nEntrada invalida\n");
		getchar();
		getchar();
		return;
	}
	if(xini[0]<48 || xini[0]>57 || yini[0]<48 || yini[0]>57)
	{
		printf("\nEntrada invalida\n");
		getchar();
		getchar();
		return;
	}

	posicao.xi=xini[0]-'0';
	posicao.yi=yini[0]-'0';
	if(posicao.xi==0 && posicao.yi==0)
	{
		sair=1;
		return;
	}
	if(posicao.xi>8 || posicao.xi<1)
	{
		printf("\nPeca invalida\n");
		getchar();
		getchar();
		return;
	}
	if(posicao.yi>8 || posicao.yi<1)
	{
		printf("\nPeca invalida\n");
		getchar();
		getchar();
		return;
	}

	printf("Coordenadas do destino:           ");
	scanf("%s %s", xfin, yfin);

	if(strlen(xfin)>1 || strlen(yfin)>1)
	{
		printf("\nEntrada invalida\n");
		getchar();
		getchar();
		return;
	}
	if(xfin[0]<48 || xfin[0]>57 || yfin[0]<48 || yfin[0]>57)
	{
		printf("\nEntrada invalida\n");
		getchar();
		getchar();
		return;
	}

	posicao.xf=xfin[0]-'0';
	posicao.yf=yfin[0]-'0';
	if(posicao.xf==0 && posicao.yf==0)
	{
		sair=1;
		return;
	}
	if(posicao.xf>8 || posicao.xf<1)
	{
		printf("\nDestino invalido\n");
		getchar();
		getchar();
		return;
	}
	if(posicao.yf>8 || posicao.yf<1)
	{
		printf("\nDestino invalido\n");
		getchar();
		getchar();
		return;
	}
	
	int *pontxi, *pontyi, *pontxf, *pontyf;
	int auxxi, auxyi, auxxf, auxyf;

	pontxi=&posicao.xi;
	auxxi=*pontxi;

	pontyi=&posicao.yi;
	auxyi=*pontyi;

	pontxf=&posicao.xf;
	auxxf=*pontxf;

	pontyf=&posicao.yf;
	auxyf=*pontyf;

	auxxi+=1; //Adição de 1 para facilitar trabalhar com os valores na matriz Tabuleiro
	auxyi+=1;
	auxxf+=1;
	auxyf+=1;

	jogadaValida(auxxi,auxyi,auxxf,auxyf); //Passa como parametros as coordenadas iniciais e finais da peca a ser movida

}

/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
//---------------------------------- CONTAR PEÇAS ---------------------------------\\
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/

void pecasBrancas(char matriz[12][12]) //Funcao para contar as pecas brancas
{
	int i, j;
	contbrancas=0;

	for(i=0; i<12; i++)
	{
		for(j=0; j<12; j++)
		{
			if(matriz[i][j]=='B' || matriz[i][j]=='W')
			{
				contbrancas++;
			}
		}
	}
}

void pecasPretas(char matriz[12][12]) //Funcao para contar as pecas pretas
{
	int i, j;
	contpretas=0;

	for(i=0; i<12; i++)
	{
		for(j=0; j<12; j++)
		{
			if(matriz[i][j]=='P' || matriz[i][j]=='K')
			{
				contpretas++;
			}
		}
	}
}

/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
//------------------------------- RESETAR TABULEIRO -------------------------------\\
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/

void resetarTabuleiro()
{
	int i, j;
	for(i=0; i<12; i++)
	{
		for(j=0; j<12; j++)
		{
			tabuleiro[i][j]=tabuleiroreset[i][j];
		}
	}
}

/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
//-------------------------------------- MAIN -------------------------------------\\
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/

int main()
{
	int brancas, pretas;
	char continuar;
	system("cls");
	printf("\n\n\tPara sair, digite '0 0'\n\n\n\t   ENTER PARA JOGAR\n\n\n");
	getchar();
	for(;;) //Loop infinito para manter o jogo rodando
	{
	    system("cls"); //Windows = CLS, Ubuntu = CLEAR  | Limpa o terminal a cada jogada
	    pecasBrancas(tabuleiro); //Conta a quantidade de pecas brancas
		pecasPretas(tabuleiro); //Conta a quantidade de pecas pretas
		if(contbrancas==0 && contpretas!=0) //Checa a vitoria das pretas baseado na quantidade de pecas
		{
			pontuacao();
			exibirMatriz();
			printf("\n\t        VITORIA DAS PRETAS\n");
			getchar();
			getchar();
			
			system("cls");
			printf("\n\n\n\n   Deseja reiniciar o jogo? (s/n) ");
			scanf("%c", &continuar);
			if(continuar=='s' || continuar=='S') //Caso o jogo deseje ser reiniciado
			{
				sair=0; //Retorna o valor original da condição de saída
				anterior='.';
				resetarTabuleiro(); //Reinicia o tabuleiro para a posicao inicial
				main(); //Chama a função main recursivamente
				return 0;
			}
			else //Caso contrário, sai do jogo
			{
				system("cls");
				printf("\n\n\n\n\n\t\tAte logo!\n\n\n\n\n");
				getchar();
				getchar();
				break;
			}
		}
		else if(contbrancas!=0 && contpretas==0) //Checa a vitoria das brancas baseado na quantidade de pecas
		{
			pontuacao();
			exibirMatriz();
			printf("\n\t        VITORIA DAS BRANCAS\n");
			getchar();
			getchar();
			
			system("cls");
			printf("\n\n\n\n   Deseja reiniciar o jogo? (s/n) ");
			scanf("%c", &continuar);
			if(continuar=='s' || continuar=='S') //Caso o jogo deseje ser reiniciado
			{
				sair=0; //Retorna o valor original da condição de saída
				anterior='.';
				resetarTabuleiro(); //Reinicia o tabuleiro para a posicao inicial
				main(); //Chama a função main recursivamente
				return 0;
			}
			else //Caso contrário, sai do jogo
			{
				system("cls");
				printf("\n\n\n\n\n\t\tAte logo!\n\n\n\n\n");
				getchar();
				getchar();
				break;
			}
		}
		pontuacao(); //Exibe a pontuacao
		exibirMatriz(); //Exibe a matriz atualizada
		jogada(); //Realiza a jogada
		if(sair==1) //Valor recebido na área de RECEBER COORDENADAS
		{
			system("cls");
			fflush(stdin);

			printf("\n\n\n\n   Deseja reiniciar o jogo? (s/n) ");
			scanf("%c", &continuar);
			if(continuar=='s' || continuar=='S') //Caso o jogo deseje ser reiniciado
			{
				sair=0; //Retorna o valor original da condição de saída
				anterior='.';
				resetarTabuleiro(); //Reinicia o tabuleiro para a posicao inicial
				main(); //Chama a função main recursivamente
				return 0;
			}
			else //Caso contrário, sai do jogo
			{
				system("cls");
				printf("\n\n\n\n\n\t\tAte logo!\n\n\n\n\n");
				getchar();
				getchar();
				break;
			}
		}
	}

return 0;
}