/*                ________________________________________
                 | Trabalho de Redes de Computadores      |
                 | IFMG - BAMBUÍ 08/2022                  |
                 | Alunos:                                |
                 | Higor Pereira,   RA:0059791            |
                 | Yanky Jhonatha,  RA:0060194            |
                 | Gabriela Dâmaso. RA:0059796            |
                 |________________________________________|          */


#include "socketClass.h"

SocketClass::SocketClass(int porta, string source) {
//ESSE É O CONSTRUTOR DO SOCKET, TUDO DEPENDE DELE.

    socketAux = socket(AF_INET, SOCK_STREAM, 0);
//INSTANCIAÇÃO DO SOCKET COM AUXILIAR DO SOCKET


    configuracaoSocket(enderecoServidor, porta, source);
//CRIA A CONFIGURAÇÃO DO SOCKET

    int confirmado = 1;
    if (setsockopt(socketAux, SOL_SOCKET, SO_REUSEADDR, &confirmado, sizeof(int)) == -1) {
        cout << "ERRO DE  SETSOCKOPT" << endl;
        //SE O SOCKET FOR CRIADO ERRADO, É RETORNADO AO CLIENTE.
    }

    if (bind(socketAux, (struct sockaddr*)&enderecoServidor, sizeof(enderecoServidor)) == -1) {
        cout << "ERRO DE BIND, VEJA SE A PORTA NÃO ESTÁ OCUPADA" << endl;
        close(socketAux);
    }
    cout << "OUVINDO A PORTA: " << porta << endl;
    //SE DER ERRO DE CONEXÃO, É INFORMADO AO CLIENTE, SE NÃO, ELE OUVE A PORTA NORMALMENTE.
}


// PRINCIPAIS CONFIGS DO SOCKET ABAIXO \/\/\/\/





int SocketClass::conexaoSocket(int& socketAux, struct sockaddr_in& servidor) {

    return bind(socketAux, (struct sockaddr*)&servidor, sizeof(servidor));
    //PREENCHE A CONEXÃO
}



int SocketClass::confirmaRequisicao() {

    return accept(socketAux, (struct sockaddr*)&clienteEndereco, &tamanhoEnderecoCliente);
    //CONFIRMA A REQUISIÇÃO
}


void SocketClass::tempoAberto(int &socketAux, int tempo) {

    timeval tt;
    tt.tv_sec = tempo;
    tt.tv_usec = 0;
    setsockopt(socketAux, SOL_SOCKET, SO_RCVTIMEO,(char *)&tt,sizeof(struct timeval));
    //FORNECE O TEMPO DE ESPERA DA CONEXÃO
}

int SocketClass::esperandoSocket(int req ) {
        return listen(socketAux, req );
    //ESCUTA A QUANTIDADE DE REQUISIÇÃO DO SOCKET
}


void SocketClass::configuracaoSocket(struct sockaddr_in& servidor,int porta, string source) {

    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(porta);
    inet_aton(source.c_str(), &servidor.sin_addr);
    memset(servidor.sin_zero, '\0', sizeof(servidor.sin_zero));
    //CONFIGURA O SOCKET
}



int SocketClass::asksendSocket(int &socketAux, string x) {

    return send(socketAux, x.c_str(), x.size(), 0);
    //RETORNA UMA RESPOSTA PARA O CLIENTE
}



sockaddr_in SocketClass::getClienteEndereco() {

    return clienteEndereco;
    //FORNECE O ENDEREÇO DO CLIENTE
}



BufferAux SocketClass::bufferReceptor(int &socketAux){

    BufferAux datarec;
    datarec.tamanhoBuffer = recv(socketAux, datarec.dadosC, tamanhoMaximoRecive, 0);
    return datarec;
    //INTERPETA AO BUFFER A REQUISIÇÃO NECESSÁRIA
}



SocketClass::~SocketClass(){
    xSocket();
    //FECHA A CONEXÃO DO SOCKET
}



void SocketClass::xSocket(int &socketAux) {

    close(socketAux);
    //DA CLOSE NA CONEXÃO
}



void SocketClass::xSocket() {

    close(this->socketAux);
    //FECHA A CONEXÃO DO SOCKET
}
