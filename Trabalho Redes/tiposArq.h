/*                ________________________________________
                 | Trabalho de Redes de Computadores      |
                 | IFMG - BAMBUÍ 08/2022                  |
                 | Alunos:                                |
                 | Higor Pereira,   RA:0059791            |
                 | Yanky Jhonatha,  RA:0060194            |
                 | Gabriela Dâmaso. RA:0059796            |
                 |________________________________________|          */





#ifndef TIPOSARQ_H_INCLUDED
#define TIPOSARQ_H_INCLUDED

using namespace std;
#include<string>

class Tipos //Classe criada para auxiliar no fornecimento de arquivos de determinados tipos a partir da requisição
{
 public:
    Tipos();
    string getTipo(string tipo); //Método para retorno do tipo de arquivo da requisição
    // Matriz de tipos de arquivos
    string tipos[14][2]={{"jpeg","image/jpeg"},{"png","image/png"},{"html","text/html"},{"jpg","image/jpg"},
    {"gif","image/gif"}, {"css","text/css"}, {"au","audio/basic"}, {"wav","audio/wav"}, {"avi","video/x-msvideo"},
    {"mp3","audio/mpeg"}, {"txt","text/txt"}, {"js","text/js"}, {".ico", "image/x-icon"}, {"pdf", "application/pdf"}};
};

#endif
