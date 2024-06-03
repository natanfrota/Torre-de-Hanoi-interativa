#ifndef PILHA_H
#define PILHA_H

typedef struct no{
    int valor;
    struct no *proximo;
} No;

typedef struct{
    No *topo;
    int tam;
} Pilha;

void inicializarPilha(Pilha *p);
int estaVazia(Pilha *p);
void empilhar(Pilha *p, int dado);
int desempilhar(Pilha *p);
int mostrarTopo(Pilha *p);

#endif