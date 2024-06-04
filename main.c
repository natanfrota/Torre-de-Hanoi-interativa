#include "pilha.h"
#include <stdio.h>
#include <stdlib.h> // system()

#ifdef _WIN32
#include <windows.h> //Beep()
#endif

/*
          |                   |                   |
         -1-                  |                   |
        --2--                 |                   |
       ---3---                |                   |
    -------------       -------------       -------------
       Torre 1            Torre 2              Torre 3
*/

void limparTela();
void emitirSom();
int estaCheia(Pilha *p, int discos);
void moverDisco(Pilha *pOrigem, Pilha *pDestino);
void imprimirTitulo(int discos);
void imprimirDisco(int i, int discos);
void imprimirHaste(int discos);
void imprimirTorres(Pilha t[], int discos);

int main()
{
    Pilha torres[3];

    int i, qntDiscos;
    printf("\nEscolhe a quantidade de discos com que desejas jogar: ");
    scanf("%d", &qntDiscos);

    for (i = 0; i < 3; i++)
        inicializarPilha(&torres[i]);

    for (i = qntDiscos; i > 0; i--)
        empilhar(&torres[0], i);

    int tOrigem, tDestino, topoD, topoO;
    
    do
    {
        limparTela();

        imprimirTorres(torres, qntDiscos);

        printf("\nEscolhe a torre de origem do disco: ");
        scanf("%d", &tOrigem);
        printf("\nEscolhe a torre de destino do disco: ");
        scanf("%d", &tDestino);

        tOrigem--;
        tDestino--;

        if ((tOrigem < 0 || tOrigem > 2) || (tDestino < 0 || tDestino > 2) ||
            (tOrigem == tDestino) || estaVazia(&torres[tOrigem]))
        {
            printf("\nJogada invalida.\n");
            getchar();
            getchar();
            continue;
        }
        if ((tOrigem >= 0 && tOrigem <= 2) && (tDestino >= 0 && tDestino <= 2))
            if (estaVazia(&torres[tDestino]) == 0)
            {
                topoD = mostrarTopo(&torres[tDestino]);
                topoO = mostrarTopo(&torres[tOrigem]);

                if (topoO > topoD)
                {
                    printf("\nJogada invalida.\n");
                    getchar();
                    getchar();
                    continue;
                }
            }

        moverDisco(&torres[tOrigem], &torres[tDestino]);
        emitirSom();

        /* A repetição continua enquanto todos os discos não tiverem sido passados para as
        torres 2 ou 3*/
    } while (estaCheia(&torres[1], qntDiscos) == 0 && estaCheia(&torres[2], qntDiscos) == 0);
    // 0 == 0 && 0 == 0 v
    // 0 == 0 && 1 == 0 f

    limparTela();
    imprimirTorres(torres, qntDiscos);

    return 0;
}

void limparTela()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void emitirSom()
{
#ifdef _WIN32
    Beep(400, 200);
#endif
}

int estaCheia(Pilha *p, int discos)
{
    return (p->tam == discos);
}

void moverDisco(Pilha *pOrigem, Pilha *pDestino)
{
    int disco = desempilhar(pOrigem);
    empilhar(pDestino, disco);
}

void imprimirTitulo(int discos){
    printf("\n\t\t\t\t");
    int i; 
    for (i = 0; i < discos * 2; i++)
        printf(" ");
    printf("TORRE DE HANOI\n\n");
}

void imprimirDisco(int i, int discos)
{
    int j;
    printf("\t\t");
    /*Imprime espaços em branco antes do disco. (2 * discos) representa o tamanho da base da torre 
    + 1 para simetria + 3 quadrados de cada lado (6) - os quadrados de cada lado do número na quantidade que ele representa (2 * i) = quantidade de espaços*/
    for (j = 0; j < (discos * 2 + 1 + 6 - 2 * i) / 2; j++)
    {
        printf(" ");
    }
    // Imprime o disco formado por vários quadrados (i quadrados à direita, 1 no meio e i quadrados à esquerda)
    for (j = 0; j < 2 * i + 1; j++)
    {
        printf("%c", 254);
    }
    
    // Imprime espaços em branco depois do disco
    for (j = 0; j < (discos * 2 + 1 + 6 - 2 * i) / 2; j++)
    {
        printf(" ");
    }
}

void imprimirHaste(int discos)
{
    printf("\t\t");
    int i;
    for (i = 0; i < (discos * 2 + 1 + 6) / 2; i++)
        printf(" ");
    printf("|");
    for (i = 0; i < (discos * 2 + 1 + 6) / 2; i++)
        printf(" ");
}

void imprimirTorres(Pilha t[], int discos)
{
    int i, j;
    No *aux[3];
    int tam[3];

    for (i = 0; i < 3; i++)
    {
        aux[i] = t[i].topo;
        tam[i] = t[i].tam;
    }
    
    imprimirTitulo(discos);
    printf("\n\n");

    for (i = 0; i < 3; i++)
        imprimirHaste(discos);
    printf("\n");
    // Imprime os discos de cada torre ou a haste dela
    for (i = discos; i > 0; i--)
    {
        // Para cada disco, imprime uma linha de cada torre
        for (j = 0; j < 3; j++)
        {
            if (tam[j] == i && aux[j])
            {
                imprimirDisco(aux[j]->valor, discos);
                tam[j]--;
                aux[j] = aux[j]->proximo;
            }
            else
            {
                imprimirHaste(discos);
            }
        }
        printf("\n");
    }

    for (i = 0; i < 3; i++)
    {
        printf("\t\t");
        // Imprime a base da torre
        for (j = 0; j < discos * 2 + 1 + 6; j++)
            printf("%c", 254);
    }

    printf("\n");

    for (i = 0; i < 3; i++)
    {
        // Imprime o nome da torre
        printf("\t\t");
        // A mesma expressão menos a quantidade de letras correpondente ao nome da torre
        for (j = 0; j < (discos * 2 + 1 + 6 - 7) / 2; j++)
            printf(" ");
        printf("Torre %d", i + 1);
        for (j = 0; j < (discos * 2 + 1 + 6 - 7) / 2; j++)
            printf(" ");
    }

    printf("\n\n");
}
