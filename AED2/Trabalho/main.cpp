/*****************************************************************************
 * ESTE TRABALHO TEM MINHA AUTORIA, PODERÁ SER USADO APENAS PARA APRENDIZADO *
 * NÃO IREI ACEITAR CÓPIAS.                                                  *
 * IFMG-CAMPUS BAMBUÍ - AULAS DE ENGENHARIA DE COMPUTAÇÃO.                   *
 * TRABALHO FINAL DE AED 2                                                   *
 * ALUNO YANKY JHONATHA MONTEIRO FONTE BOA                                   *
 * CRIAÇÃO DE UM SUPERMERCADO E TODOS SEUS PROCEDIMENTOS EM C++.             *
 *****************************************************************************/

#include <iostream>
#include <clocale>
#include "biblioteca.h"

using namespace std;

int main(){
setlocale(LC_ALL,"Portuguese");
//árvore
TArvoreBin arvore1;

//******
//lista
TListaP listap;
TProdutos produtosF;
//******
//pilha
TPilhaP pilhaP; // instanciação
TProdutos produtosP;
//******
//árvore
TItem iAux;
criarArvoreBinVazia(arvore1,"Produtos");
iAux.codigo = 546;              // A PARTIR DAQUI É A IMPLEMENTAÇÃO DA ÁRVORE, NO CASO ONDE É INSERIDO TODA A CONFIGURAÇÃO DO SUPERMERCADO.
iAux.nome = "Óleo";
iAux.quantidade = 589;
iAux.valor = 11;
inserir(arvore1,arvore1.raiz,iAux);
iAux.codigo = 547;
iAux.nome = "Pó de Café";
iAux.quantidade = 101;
iAux.valor = 6;
inserir(arvore1,arvore1.raiz,iAux);
iAux.codigo = 548;
iAux.nome = "Açúcar";
iAux.quantidade = 203;
iAux.valor = 3;
inserir(arvore1,arvore1.raiz,iAux);
iAux.codigo = 549;
iAux.nome = "Sal";
iAux.quantidade = 441;
iAux.valor = 3;
inserir(arvore1,arvore1.raiz,iAux);
iAux.codigo = 550;
iAux.nome = "Abacaxi";
iAux.quantidade = 58;
iAux.valor = 2;
inserir(arvore1,arvore1.raiz,iAux);
iAux.codigo = 551;
iAux.nome = "Maçã";
iAux.quantidade = 600;
iAux.valor = 2;
inserir(arvore1,arvore1.raiz,iAux);
iAux.codigo = 552;
iAux.nome = "Macarrão";
iAux.quantidade = 78;
iAux.valor = 5;
inserir(arvore1,arvore1.raiz,iAux);
iAux.codigo = 553;
iAux.nome = "Farinha";
iAux.quantidade = 95;
iAux.valor = 3;
inserir(arvore1,arvore1.raiz,iAux);
iAux.codigo = 554;
iAux.nome = "Detergente";
iAux.quantidade = 42;
iAux.valor = 5;
inserir(arvore1,arvore1.raiz,iAux);
iAux.codigo = 555;
iAux.nome = "Refrigerante";
iAux.quantidade = 132;
iAux.valor = 6;
inserir(arvore1,arvore1.raiz,iAux);
cout << "-------------SUPERMERCADO IA - PRODUTOS DISPONÍVEIS-------------" << endl; // A PARTIR DAQUI COMEÇA OS PROCEDIMENTOS.
percorrerINOrdem(arvore1.raiz);

//******
//lista para pilha
criarLista(listap);
criarPilhaP(pilhaP);
char resp = 'S';
cout << "\n--------------ADICIONANDO PRODUTOS NO CARRINHO----------------";  // AQUI ADICIONA OS PRODUTOS NO CARRINHO, LENDO O QUE O USUÁRIO DIGITA.
while (resp != 'N'){
cout << "\nDIGITE O CÓDIGO DE BARRAS DO PRODUTO: ";
cin >> produtosF.codigo;
cout << "\nDIGITE A QUANTIDADE QUE DESEJA ADICIONAR: ";
cin >> produtosF.quantidade;
atualizarEstoque(arvore1,produtosF,arvore1.raiz);
inserirL(listap,produtosF);
cout << "\nDESEJA ADICIONAR OUTRO PRODUTO? S/N =  ";
cin >> resp;
cout << "\n______________________________________________________________";

}
char resp2= 'S';
char resp3 ='S';
cout << "\nDESEJA PASSAR O CARRINHO NO CAIXA? S/N = ";
cin >> resp2;
if (resp2 != 'S'){
cout << "\nENCERRANDO PROCESSO... NÃO FOI POSSÍVEL IR AO CAIXA.";
cout << "\n______________________________________________________________";
}
else{
cout << "\n---------------CAIXA - LENDO CÓDIGOS DE BARRAS----------------"; // AQUI É O PROCEDIMENTO QUE LÊ OS CÓDIGOS QUE O USUÁRIO INFORMA E NO CASO PASSA DA LISTA PARA A PILHA.
while (resp3 != 'N'){
    cout << "\nDIGITE O CÓDIGO DE BARRAS DO PRODUTO A SER PASSADO: ";
    cin >> produtosP.codigo;
    passarPilha(listap,pilhaP);
    cout << "\nDESEJA PASSAR O PRÓXIMO PRODUTO? S/N = ";
    cin >> resp3;
    if (resp3 != 'S'){
        cout << "\nPROCESSO ENCERRADO...";
    }

}
char resp5;
char resp4;
cout << "\n______________________________________________________________";
cout << "\nDESEJA VERIFICAR SE FICOU ALGO NO SEU CARRINHO? S/N = ";
cin >> resp4;
if(resp4 != 'S'){              // AQUI APENAS PERGUNTA AO USUÁRIO SE ELE QUER VER AS COMPRAS QUE FEZ.
    cout << "\nCOMPRAS FORAM PASSADAS NO CAIXA, JÁ PODE IR PARA CASA.";
    cout << "\nANTES DE IR PARA CASA, DESEJA VER SUAS COMPRAS? S/N = ";
cin >> resp5;
if (resp5 = 'S'){
    mostrarP(pilhaP);

}
}
 else{
        mostrar(listap);
 cout << "\nCOMPRAS FORAM PASSADAS NO CAIXA, JÁ PODE IR PARA CASA.";
    cout << "\nANTES DE IR PARA CASA, DESEJA VER SUAS COMPRAS? S/N = ";
cin >> resp5;
if (resp5 = 'S'){
    mostrarP(pilhaP);

}
 }
}
char x; // DAQUI PRA BAIXO É APENAS CASO ALGUÉM QUEIRA VER O ESTOQUE, COLOQUEI UMA SENHA, QUE SEPARA O OPERADOR DO USUÁRIO
char resp6; // SENHA É " STONKS ", APENAS UMA BRINCADEIRA...
cout << "\n-------------OPERAÇÃO FINAL, NO CASO DE OPERADOR--------------";
cout <<"\nDESEJA VER O ESTOQUE DO SUPERMERCADO? S/N = ";
cin >> resp6;
if (resp6 != 'S'){
    cout <<"\nPROCESSO ENCERRADO...";
}
else{
    cout <<"\nDIGITE A SENHA DO SISTEMA: ";
    cin >> x;
    if (x = 'STONKS'){
        cout << "\nENTRANDO NO SISTEMA.......";
        cout << "\nESTOQUE:";
        cout << "\n";
        percorrerINOrdem(arvore1.raiz);
    }
else {
    cout << "\nSENHA ERRADA, TENTE NOVAMENTE DEPOIS.";
    cout << "\nPROCESSO ENCERRADO...";
}
}


//******

// AQUI É O FIM DE TUDO ISSO.

    return 0;
}
