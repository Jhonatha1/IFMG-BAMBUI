/*                ________________________________________
                 | Trabalho de Redes de Computadores      |
                 | IFMG - BAMBUÍ 08/2022                  |
                 | Alunos:                                |
                 | Higor Pereira,   RA:0059791            |
                 | Yanky Jhonatha,  RA:0060194            |
                 | Gabriela Dâmaso. RA:0059796            |
                 |________________________________________|          */







#ifndef RESPOSTASERVIDOR_H_INCLUDED
#define RESPOSTASERVIDOR_H_INCLUDED

#include <vector>
#include <string>
#include "socketClass.h"
#include "tiposArq.h"
#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;

class respostaServidor
{
    public:
        virtual ~respostaServidor() {};         //estabelece conexão
        respostaServidor() {};


        int getdds(int thread_id, int clientSockfd, sockaddr_in clienteEndereco, string root, string extension, string caminho);


        void pegArq(int thread_id, int clientSockfd, sockaddr_in clienteEndereco, string caminho);   //pegar arquivos

        //Abre o arquivo
        bool abriArq(string root, int &len, string &n);

        //pegar dados do arquivo:
        vector<string> split(string x, char del);

       //define o status:
        string pegStatus(int resp, int len, string extension);

        int	operator()(int thread_id, int clientSockfd, sockaddr_in clienteEndereco, string caminho)
        {
            pegArq(thread_id, clientSockfd, clienteEndereco, caminho);
            return (0);
        }
        //lê os dados:
        void lerArquivo(fstream &file, string &n, int len);

    private:
        SocketClass socli;
};

#endif
