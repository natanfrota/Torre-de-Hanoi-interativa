#include "pilha.h"
#include <stdio.h>
#include <stdlib.h> // system()

#ifdef _WIN32
#include <windows.h> //Beep()
#endif

void limparTela();
void jogar(int discos);
void emitirSom();
int estaCheia(Pilha *p, int discos);
void moverDisco(Pilha *pOrigem, Pilha *pDestino);
void imprimirTitulo(int discos);
void imprimirDisco(int i, int discos);
void imprimirHaste(int discos);
void imprimirTorres(Pilha t[], int discos);
void liberarMemoria(Pilha t[]);

int main()
{
    int i, opcao, qntDiscos = 3, dificuldade;

    do
    {
        limparTela();
        for (i = 0; i < 56; i++)
            printf("_");
        printf("\n|\t\t\t\t\t\t\t|\n");
        printf("|\t\t\tTORRE DE HANOI\t\t\t|\n");
        printf("|\t\t\t\t\t\t\t|\n");
        printf("|\t\t1 - JOGAR\t\t\t\t|\n");
        printf("|\t\t2 - NIVEL DE DIFICULDADE\t\t|\n");
        printf("|\t\t3 - INSTRUCOES\t\t\t\t|\n");
        printf("|\t\t4 - SAIR\t\t\t\t|\n");
        printf("|\t\t\t\t\t\t\t|\n|");
        for (i = 0; i < 55; i++)
            printf("_");
        printf("|\n");
        
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            jogar(qntDiscos);
            getchar();
            getchar();
            break;
        case 2:
            limparTela();
            for (i = 0; i < 56; i++)
                printf("_");
            printf("\n|\t\t\t\t\t\t\t|\n");
            printf("|\t\tNIVEL DE DIFICULDADE\t\t\t|\n");
            printf("|\t\t\t\t\t\t\t|\n");
            printf("|\t\t1 - FACIL (3 DISCOS)\t\t\t|\n");
            printf("|\t\t2 - MEDIO (5 DISCOS)\t\t\t|\n");
            printf("|\t\t3 - DIFICIL (7 DISCOS)\t\t\t|\n");
            printf("|\t\t4 - PERSONALIZADO\t\t\t|\n");
            printf("|\t\t\t\t\t\t\t|\n|");
            for (i = 0; i < 55; i++)
                printf("_");
            printf("|\n");
            
            scanf("%d", &dificuldade);

            switch (dificuldade)
            {
            case 1:
                qntDiscos = 3;
                break;
            case 2:
                qntDiscos = 5;
                break;
            case 3:
                qntDiscos = 7;
                break;
            case 4:
                limparTela();
                printf("\n\nDigita a quantidade de discos desejada: ");
                scanf("%d", &qntDiscos);
                while (qntDiscos < 1 || qntDiscos > 20)
                {
                    printf("\nQuantidade invalida. Tenta novamente.\n");
                    scanf("%d", &qntDiscos);
                }
                break;
            default:
                printf("\nEntrada invalida.\n");
                getchar();
                getchar();
            }
            break;
        case 3:
            limparTela();
            for (i = 0; i < 56; i++)
                printf("_");
            
            printf("\n|\t\t\t\t\t\t\t|");
            printf("\n|\t\t\tINSTRUCOES\t\t\t|\n");
            printf("|\t\t\t\t\t\t\t|\n");
            printf("| O objetivo deste jogo e mover todos os discos de uma  |\n| haste para outra, respeitando as seguintes regras:\t|\n| Mover apenas um disco de cada vez.\t\t\t|\n| Nao colocar um disco maior sobre um menor.\t\t|\n| Nao mover um disco que esteja abaixo de outro.\t|\n|");
            
            for (i = 0; i < 55; i++)
                printf("_");
            printf("|\n");
            getchar();
            getchar();
            break;
        case 4:
            break;
        default:
            printf("\nOpcao invalida.\n");
            getchar();
            getchar();
        }
    } while (opcao != 4);

    return 0;
}

void jogar(int discos)
{
    Pilha torres[3];
    int i;

    for (i = 0; i < 3; i++)
        inicializarPilha(&torres[i]);

    for (i = discos; i > 0; i--)
        empilhar(&torres[0], i);

    int tOrigem, tDestino, topoD, topoO;

    do
    {
        limparTela();

        imprimirTorres(torres, discos);

        printf("\nEscolhe a torre de origem do disco: ");
        scanf("%d", &tOrigem);
        printf("\nEscolhe a torre de destino do disco: ");
        scanf("%d", &tDestino);

        tOrigem--;
        tDestino--;

        if ((tOrigem < 0 || tOrigem > 2) || (tDestino < 0 || tDestino > 2))
        {
            printf("\nJogada invalida: torre de origem ou destino incorreta.\n");
            getchar();
            getchar();
            continue;
        }
        if (estaVazia(&torres[tOrigem]) || (tOrigem == tDestino))
        {
            printf("\nJogada invalida: torre de origem vazia ou igual a torre de destino.\n");
            getchar();
            getchar();
            continue;
        }
        if (estaVazia(&torres[tDestino]) == 0)
        {
            topoD = mostrarTopo(&torres[tDestino]);
            topoO = mostrarTopo(&torres[tOrigem]);

            if (topoO > topoD)
            {
                printf("\nJogada invalida: disco maior nao pode ser movido sobre disco menor.\n");
                getchar();
                getchar();
                continue;
            }
        }

        moverDisco(&torres[tOrigem], &torres[tDestino]);
        emitirSom();

        /* A repetição continua enquanto todos os discos não tiverem sido passados para a torre 2 ou 3*/
    } while (estaCheia(&torres[1], discos) == 0 && estaCheia(&torres[2], discos) == 0);

    limparTela();
    imprimirTorres(torres, discos);
    printf("\n\tGanhaste!\n\n");
    liberarMemoria(torres);
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
    /*Imprime espaços em branco antes do disco. (2 * discos) representa o tamanho da base da torre + 1 para simetria + 3 quadrados de cada lado (6) - os quadrados de cada lado do quadrado do meio na quantidade que o número representa (2 * i) = quantidade de espaços*/
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

void liberarMemoria(Pilha t[]){
    int i, tam;

    for (i = 0; i < 3; i++){
        if(estaVazia(&t[i]) == 0){
            tam = t[i].tam;
            for (; tam > 0; tam--)
                desempilhar(&t[i]);
        }
    }
}