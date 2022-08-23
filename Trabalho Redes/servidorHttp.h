/*                ________________________________________
                 | Trabalho de Redes de Computadores      |
                 | IFMG - BAMBUÍ 08/2022                  |
                 | Alunos:                                |
                 | Higor Pereira,   RA:0059791            |
                 | Yanky Jhonatha,  RA:0060194            |
                 | Gabriela Dâmaso. RA:0059796            |
                 |________________________________________|          */






#ifndef SERVIDORHTTP_H_INCLUDED
#define SERVIDORHTTP_H_INCLUDED

#include<thread>

#include "socketClass.h"
#include "respostaServidor.h"

class ServidorHttp{
    public:


        void iniciarServidor();     //inicializador do servidor

        virtual ~ServidorHttp();  //destrutor

        ServidorHttp(int porta , string host, string caminho); //criando socket de conexão


    private:


        string caminho;  //o diretorio que o servidor sera criado

        SocketClass *servidorSocket;     //ponteiro p referenciar o socket do servidor

};

#endif
