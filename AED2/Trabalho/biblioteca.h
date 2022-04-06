/******************************************************************************
 * ESTE TRABALHO TEM MINHA AUTORIA, PODERÁ SER USADO APENAS PARA APRENDIZADO. *
 * NÃO IREI ACEITAR CÓPIAS.                                                   *
 * IFMG-CAMPUS BAMBUÍ - AULAS DE ENGENHARIA DE COMPUTAÇÃO.                    *
 * TRABALHO FINAL DE AED 2                                                    *
 * ALUNO YANKY JHONATHA MONTEIRO FONTE BOA                                    *
 * CRIAÇÃO DE UM SUPERMERCADO E TODOS SEUS PROCEDIMENTOS EM C++.              *
 ******************************************************************************/

#ifndef BIBLIOTECA_H_INCLUDED
#define BIBLIOTECA_H_INCLUDED
//declarações e implementações, chamadas das bibliotecas.
// AQUI SOMENTE É ONDE TUDO FOI CRIADO, AS ESTRUTURAS E AS CHAMADAS À BIBLIOTECA....

using namespace std;
struct TProdutos{
string nome;
int quantidade;
int valor;
int codigo;
int x;
};
struct TCelula{
TCelula *proximo;
TProdutos produto;

};
//LISTA
struct TListaP{
TCelula *primeiro;
TCelula *ultimo;
};
//*****
//PILHA
struct TPilhaP{
    TCelula *fundo;
    TCelula *topo;
};
//*****

//ÁRVORE BINÁRIA
struct TItem{
    int codigo;
    string nome;
    int quantidade;
    int valor;
    int x;


};

struct TNo{
    TItem produto;
    TNo *esquerda;
    TNo *direita;
    TItem iAux;

};

struct TArvoreBin{
    string nomeArvore;
    int contItens;
    TNo *raiz;
};
//******
//OPERAÇÕES E CHAMADAS
void criarArvoreBinVazia(TArvoreBin &a, string n);

void inserir(TArvoreBin &a, TNo *&no, TItem i);

void percorrerINOrdem(TNo *&no);

void pesquisar(TArvoreBin a, int c, TNo *&n);

void criarLista(TListaP &l);

void inserirL(TListaP &l, TProdutos x);

bool estaVazia(TListaP l);

void mostrar(TListaP l);

void criarPilhaP(TPilhaP &p);

bool estaVaziaP(TPilhaP p);

void empilhar(TPilhaP &p, TProdutos x);

void mostrarP(TPilhaP p);

void atualizarEstoque(TArvoreBin a, TProdutos &produto , TNo *&n);

void passarPilha(TListaP &l,TPilhaP &pilhaP);
// AQUI É O FIM DE TUDO ISSO.

#endif // BIBLIOTECA_H_INCLUDED
