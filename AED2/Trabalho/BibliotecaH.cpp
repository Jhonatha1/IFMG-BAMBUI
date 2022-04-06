/*****************************************************************************
 * ESTE TRABALHO TEM MINHA AUTORIA, PODERÁ SER USADO APENAS PARA APRENDIZADO *
 * NÃO IREI ACEITAR CÓPIAS.                                                  *
 * IFMG-CAMPUS BAMBUÍ - AULAS DE ENGENHARIA DE COMPUTAÇÃO.                   *
 * TRABALHO FINAL DE AED 2                                                   *
 * ALUNO YANKY JHONATHA MONTEIRO FONTE BOA                                   *
 * CRIAÇÃO DE UM SUPERMERCADO E TODOS SEUS PROCEDIMENTOS EM C++.             *
******************************************************************************/

#include <iostream>
#include "biblioteca.h"

using namespace std;

// AQUI É A CRIAÇÃO DE TODO O ALGORITMO QUE FAZ FUNCIONAR O PROGRAMA, QUE TEM A IMPLEMENTAÇÃO DA ÁRVORE E AS LIGAÇÕES ENTRE
// ÁRVORE, LISTA E PILHA, UTILIZEI ESSES TADS E CONSEGUI MONTAR ALGO BACANA ENTRE ELES...


//CRIAÇÃO DA ÁRVORE BINÁRIA


void criarArvoreBinVazia(TArvoreBin &a, string n){ // cria a árvore binária
    a.nomeArvore = n;
    a.contItens = 10;
    a.raiz = NULL;
}

void inserir(TArvoreBin &a, TNo *&no, TItem i){ // insere os produtos na árvore binária
    if (no == NULL){
        no = new TNo;
        no->produto = i;
        no->esquerda = NULL;
        no->direita = NULL;
        a.contItens++;
        if (a.raiz == NULL){
            a.raiz = no;
        }
    }
    else{
        if (i.codigo < no->produto.codigo){ // chamada recursiva ESQ
            inserir(a,no->esquerda,i);
        }
        else{
            if (i.codigo > no->produto.codigo){ // chamada recursiva DIR
                inserir(a,no->direita,i);
            }
            else{
                if (i.codigo == no->produto.codigo){
                    cout << "Não posso inserir. Item já existe!" << endl;
                 }
            }
        }

    }
}
void percorrerINOrdem(TNo *&no){    // AQUI É ONDE MOSTRA O ESTOQUE DO SUPERMERCADO, NO CASO ELE VAI LA NA ÁRVORE E PERCORRE E DEPOIS MOSTRA EM ORDEM.
    TProdutos produtosF;
    if(no!=NULL){
        percorrerINOrdem(no->esquerda);
        cout << "\nNome: " << no->produto.nome;
        cout << "\nCódigo do produto: " << no->produto.codigo;
        cout << "\nValor: " << no->produto.valor;
        cout << "\nQuantidade em estoque: " << no->produto.quantidade;

cout << "\n______________________________________________________________";
        percorrerINOrdem(no->direita);

    }
}
void atualizarEstoque(TArvoreBin a, TProdutos &produto , TNo *&n){ //AQUI É UM PROCEDIMENTO QUE REMOVE
                                            // A QUANTIDADE DO PRODUTO DA ÁRVORE QUANDO A PESSOA DIGITA QUANTO ELA QUER COMPRAR.
    int g;
    if (n == NULL){
        cout << "Não há esse código de produto." << endl;
    }
    else {
        if (produto.codigo < n->produto.codigo){
            atualizarEstoque(a, produto, n->esquerda);
        }
        else {
            if (produto.codigo > n->produto.codigo){
                atualizarEstoque(a, produto, n->direita);
            }
            else{
            produto.nome = n->produto.nome;
            produto.valor = n->produto.valor;
            n->produto.quantidade = n->produto.quantidade - produto.quantidade;

                }

            }
        }
    }


void pesquisar(TArvoreBin a, int c, TNo *&n){ //PESQUISAR NA ÁRVORE ALGUM PRODUTO.
    if (n == NULL){
        cout << "Não há esse código de produto." << endl;
    }
    else {
        if (c < n->produto.codigo){
            pesquisar(a, c, n->esquerda);
        }
        else {
            if (c > n->produto.codigo){
                pesquisar(a, c, n->direita);
            }
            else{

                }

            }
        }
    }


void pegarAnterior(TNo *q, TNo *&r){ // AQUI É CASO EU PRECISE RETIRAR UM ITEM DA ÁRVORE, É APENAS UM AUXILIAR.

    if (r->direita != NULL){
        pegarAnterior(q, r->direita);
    }
    else{
        q->produto = r->produto;
        q = r;
        r = r->esquerda;
        delete q;
    }
}
void retirar(int c, TNo *&p){ // PROCEDIMENTO PARA RETIRAR UM ITEM DA ÁRVORE.
TNo *aux;

    if (p == NULL){
        cout << "Código não encontrado." << endl;
    }
    else{
        if (c < p->produto.codigo){
            retirar(c, p->esquerda);
        }
        else{
            if (c > p->produto.codigo){
                retirar(c, p->direita);
            }
            else{
                if (p->direita == NULL){
                    aux = p;
                    p = p->esquerda;
                    delete aux;
                }
                else{
                    if (p->esquerda != NULL){
                        pegarAnterior(p, p->esquerda);
                    }
                    else{
                        aux = p;
                        p = p->direita;
                        delete aux;

                    }
                }
            }
        }
    }
}

//******
//AQUI É A CRIAÇÃO DA LISTA



void criarLista(TListaP &l){ //criei uma nova célula e assim chamei de primeiro e depois atribui colocando o primeiro sendo último
l.primeiro = new TCelula;
l.ultimo =l.primeiro;
l.primeiro -> proximo = NULL;
}
void inserirL(TListaP &l, TProdutos x){ // aqui criei um procedimento que insere os itens na lista.
l.ultimo->proximo= new TCelula;
l.ultimo= l.ultimo->proximo;
l.ultimo ->produto = x;
l.ultimo ->proximo = NULL;
}
bool estaVazia(TListaP l){         //aqui é um procedimento para verificar se a lista está vazia.
    return l.primeiro == l.ultimo;
}
void mostrar(TListaP l){ // criei um procedimento que mostra a lista de produtos.
    TCelula *celAux;
    celAux = l.primeiro->proximo;

cout << "--------------------MOSTRANDO O SEU CARRINHO--------------------"<< endl;

    if (estaVazia(l)){
        cout << "Nenhum item a ser mostrado, carrinho vazio." << endl;


    }
    while (celAux != NULL){
        cout << "Nome: " << celAux->produto.nome << endl;
        cout << "Quantidade: " << celAux->produto.quantidade << endl;
        cout << "Código: " << celAux->produto.codigo << endl;
        cout << "Valor: " << celAux->produto.valor << endl;
        celAux = celAux->proximo;
    }
}

//TÉRMINO DA CRIAÇÃO DA LISTA.

//INÍCIO DA CRIAÇÃO DA PILHA
void criarPilhaP(TPilhaP &p){ // procedimento que cria a pilha
   p.topo = new TCelula;
   p.fundo = p.topo;
   p.fundo->proximo = NULL;
}
bool estaVaziaP(TPilhaP p){ //verifica se está vazia
    return p.topo->proximo == NULL;
}
void empilhar(TPilhaP &p, TProdutos x){ // procedimento que empilha a pilha
    TCelula *aux = new TCelula;
    p.topo->produto = x;
    aux->proximo = p.topo;
    p.topo = aux;

}
void mostrarP(TPilhaP p){ // AQUI MOSTRA AS COMPRAS QUE A PESSOA FEZ, NO CASO DENTRO DA PILHA JÁ.
    TCelula *celAux;
    celAux = p.topo->proximo;

cout << "----------------------MOSTRANDO AS COMPRAS----------------------" << endl;
    if (estaVaziaP(p)){
        cout << "Você não comprou nada! Nenhum elemento para mostrar!" << endl;
    }
    else{
        while (celAux != NULL){
            cout << "\nNome do produto: " << celAux->produto.nome << endl;
            cout << "\nCódigo do produto: " << celAux->produto.codigo << endl;
            cout << "\nValor do produto: " << celAux->produto.valor << endl;
            cout << "\nQuantidade comprada: " << celAux->produto.quantidade << endl;
cout << "\n______________________________________________________________";
            celAux = celAux->proximo;
        }
    }
}
void passarPilha(TListaP &l,TPilhaP &pilhaP){ // AQUI A LISTA É PASSADA PARA A PILHA, NO CASO AS COMPRAS DO CARRINHO PARA O PROCESSO FINAL.
    while (!estaVazia(l)){
        TCelula *aux = l.primeiro;
        l.primeiro = l.primeiro ->proximo;
        delete(aux);
        empilhar(pilhaP,l.primeiro->produto);
    }
}
// AQUI É O FIM DE TUDO ISSO. OBRIGADO GABRIEL.
//FIM DA CRIAÇÃO DA PILHA



