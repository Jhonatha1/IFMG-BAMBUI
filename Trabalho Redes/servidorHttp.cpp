/*                ________________________________________
                 | Trabalho de Redes de Computadores      |
                 | IFMG - BAMBUÍ 08/2022                  |
                 | Alunos:                                |
                 | Higor Pereira,   RA:0059791            |
                 | Yanky Jhonatha,  RA:0060194            |
                 | Gabriela Dâmaso. RA:0059796            |
                 |________________________________________|          */





#include "servidorHttp.h"

ServidorHttp::ServidorHttp(int porta, string host, string caminho){
    //this.caminho = caminho;   // definindo caminho desejado p criar o servidor
    //servidorSocket SocketClass(porta, host);   //instanciando objeto socket

    servidorSocket = new SocketClass(porta, host);
    this->caminho=caminho;
}

ServidorHttp::~ServidorHttp(){
    delete servidorSocket;
    servidorSocket = nullptr;
}

void ServidorHttp::iniciarServidor(){
    int i=0;
    respostaServidor resposta;

    servidorSocket->esperandoSocket(10);  //permite 10 conexões ao mesmo tempo

    while(true){
        int socketAux = servidorSocket->confirmaRequisicao();     //conexão aceita
        servidorSocket->tempoAberto(socketAux, 60);    //limte de 60 segundos p a conexão mandar requisições

        thread(resposta, i++, socketAux, servidorSocket->getClienteEndereco(), caminho).detach();
        //cria uma thread, passa o socket do servidor ligado ao endereço do cliente e o caminho
        //alem disso trata a resposta do servidor, adiciona 1 ao limite de conexões e "detach" separa essa thread da principal

    }
}
