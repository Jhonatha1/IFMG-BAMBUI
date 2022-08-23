/*                ________________________________________
                 | Trabalho de Redes de Computadores      |
                 | IFMG - BAMBUÍ 08/2022                  |
                 | Alunos:                                |
                 | Higor Pereira,   RA:0059791            |
                 | Yanky Jhonatha,  RA:0060194            |
                 | Gabriela Dâmaso. RA:0059796            |
                 |________________________________________|          */




#include "buffer.h"

Buffer::~Buffer(){}

Buffer::Buffer(){
    memset(dadosC, '\0', tamMaxRecv);  //reserva um espaço na memoria
    tamBuffer = 0;   //zera o
}


int Buffer::getTamMaxRecv(){return tamMaxRecv;  }


char* Buffer::getDados() {return dadosC;  }


void Buffer::setTamBuffer(int tamBuffer){ this->tamBuffer = tamBuffer; }


int Buffer::getTamBuffer(){return tamBuffer;  }
