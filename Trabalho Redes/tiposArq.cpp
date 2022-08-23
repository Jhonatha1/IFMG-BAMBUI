/*                ________________________________________
                 | Trabalho de Redes de Computadores      |
                 | IFMG - BAMBUÍ 08/2022                  |
                 | Alunos:                                |
                 | Higor Pereira,   RA:0059791            |
                 | Yanky Jhonatha,  RA:0060194            |
                 | Gabriela Dâmaso. RA:0059796            |
                 |________________________________________|          */




#include "tiposArq.h"

Tipos::Tipos() {}  //Construtor padrão

string Tipos::getTipo(string tipo){

    for (int i=0; i<13;i++) { //Laço utilizado para retornar o tipo de arquivo
        if(tipo == tipos[i][0]){
            return tipos[i][1]; //Retorno a tipo correspondente à solicitação
                                // viabilizando o corregamento pelo servidor
    }
    }

    return "aplication/"+tipo; //Caso o tipo de arquivo não esteja presente esse return permite baixar
                            //o arquivo solictado
}
