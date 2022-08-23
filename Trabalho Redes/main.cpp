/*                ________________________________________
                 | Trabalho de Redes de Computadores      |
                 | IFMG - BAMBUÍ 08/2022                  |
                 | Alunos:                                |
                 | Higor Pereira,   RA:0059791            |
                 | Yanky Jhonatha,  RA:0060194            |
                 | Gabriela Dâmaso. RA:0059796            |
                 |________________________________________|          */




#include "socketClass.h"
#include "servidorHttp.h"
#include <iostream>

using namespace std;

int main(){
    std::string caminho;
    std::cout<<"Informe o caminho do diretório: ";
    std::cin>> caminho;

    ServidorHttp*http = new ServidorHttp(8889, "0.0.0.0", caminho);

    http->iniciarServidor();
    delete http;
    http = nullptr;

    return 0;
}
