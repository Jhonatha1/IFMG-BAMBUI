/*                ________________________________________
                 | Trabalho de Redes de Computadores      |
                 | IFMG - BAMBUÍ 08/2022                  |
                 | Alunos:                                |
                 | Higor Pereira,   RA:0059791            |
                 | Yanky Jhonatha,  RA:0060194            |
                 | Gabriela Dâmaso. RA:0059796            |
                 |________________________________________|          */




#ifndef SOCKETCLASS_H
#define SOCKETCLASS_H
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
//BIBLIOTECAS E CONFIGURAÇÕES DO SOCKET
#include <iostream>
#include <string.h>
//BIBLIOTECAS DE DECLARAÇÃO/OUTPUT/INPUT DE TODAS CONFIG DO SOCKET

using namespace std;

#define tamanhoMaximoRecive 5000
struct BufferAux {
    int tamanhoBuffer;
    char dadosC[tamanhoMaximoRecive];
//CRIAÇÃO DE UM BUFFER QUE RECEBE TODAS REQUISIÇÕES
};

class SocketClass
{
    public:


        SocketClass(int porta, string source);

        virtual ~SocketClass();

        SocketClass() {};
//AQUI COMEÇA A MANIPULAÇÃO DO SOCKET E SUAS CONEXÕES

        void configuracaoSocket(struct sockaddr_in &servidor,int porta, string source);
 //CONFIG DO SOCKET


        int esperandoSocket(int req);
//OUVE REQUISIÇÕES DO SOCKET

        int conexaoSocket(int &socketAux,struct sockaddr_in &clienteEndereco);
 //ESTABELECIMENTO DE CONEXÃO DO SOCKET

        int confirmaRequisicao();
//CONFIRMA AS REQUISIÇÕES DO SOCKET

        BufferAux bufferReceptor(int &socketAux);
//BUFFER RECEPTOR QUE SERVE COMO AUXILIAR

        void tempoAberto(int &socketAux, int tempo);
 //TEMPO DE CONEXÃO DO SOCKET

        int asksendSocket(int &socketAux, string x);
//FORNECE A RESPOSTA DAS REQUISIÇÕES DO SOCKET

        sockaddr_in getClienteEndereco();
 //FORNECE O ENDEREÇO DO CLIENTE

        void xSocket();
//FECHA O SOCKET

        void xSocket(int &socketAux);
//DA CLOSE NO SOCKET


    private:

        socklen_t tamanhoEnderecoCliente;
//ESTABELECE O TAMANHO DO ENDEREÇO DO CLIENTE


        struct sockaddr_in enderecoServidor;
//ESTABELECE ENDEREÇO DO SERVIDOR

        struct sockaddr_in clienteEndereco;
//ESTABELECE ENDEREÇO DO CLIENTE

        int socketAux;
        //AUXILIAR SOCKET


};

#endif
