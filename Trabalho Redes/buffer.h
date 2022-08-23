/*                ________________________________________
                 | Trabalho de Redes de Computadores      |
                 | IFMG - BAMBUÍ 08/2022                  |
                 | Alunos:                                |
                 | Higor Pereira,   RA:0059791            |
                 | Yanky Jhonatha,  RA:0060194            |
                 | Gabriela Dâmaso. RA:0059796            |
                 |________________________________________|          */


#ifndef BUFFER_H_INCLUDED
#define BUFFER_H_INCLUDED

#include <string.h>
#define tamMaxRecv 5000

class Buffer{
    public:
        virtual ~Buffer();
        Buffer();
        int getTamMaxRecv();
        void setTamBuffer(int tamBuffer);
        int getTamBuffer();
        char* getDados();
    private:
        char dadosC[tamMaxRecv];
        int tamBuffer;

};

#endif
