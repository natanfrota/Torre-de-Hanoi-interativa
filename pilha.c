#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

void inicializarPilha(Pilha *p){
    p->topo = NULL;
    p->tam = 0;
}

int estaVazia(Pilha *p)
{
    return (p->topo == NULL);
}

void empilhar(Pilha *p, int dado)
{
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL)
    {
        printf("Erro na alocacao.\n");
    }
    else
    {
        novo->valor = dado;
        novo->proximo = p->topo;
        p->topo = novo;
        p->tam++;
    }
}

int desempilhar(Pilha *p)
{
    No *aux = p->topo;

    if (estaVazia(p)){
        return -1;
    }

    int temp = p->topo->valor;
    p->topo = p->topo->proximo;
    p->tam--;
    free(aux);
    return temp;
}

int mostrarTopo(Pilha *p)
{
    if (estaVazia(p))
    {
        return 0;
    }
    else
        return p->topo->valor;
}