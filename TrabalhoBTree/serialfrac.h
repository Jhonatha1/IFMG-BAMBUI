/******************************************
 * TRABALHO ÁRVORE B                      *
 *   Filipe Lehmann Pereira, RA: 0034075  *
 *   Yanky Jhonatha, RA: 0060194          *
 *   Implementado em 03/2022              *
 ******************************************/


#ifndef SERIALFRAC_H_INCLUDED
#define SERIALFRAC_H_INCLUDED

#include "serializable.h"

class serialfrac : serializable
{
private:
//    Numerador, denominador.
    int num,den;
public:
    serialfrac();
    serialfrac(int n, int d);
    serialfrac(const serialfrac& other);
    virtual ~serialfrac();
    serialfrac operator=(const serialfrac& other);
    bool operator==(const serialfrac &other)const;
    bool operator<(const serialfrac &other)const;
    bool operator<=(const serialfrac &other)const;
    bool operator>(const serialfrac &other)const;
    bool operator>=(const serialfrac &other)const;
    bool operator!=(const serialfrac &other)const;
    friend istream& operator >> (istream &in, serialfrac& frac);
    friend ostream& operator << (ostream &out, const serialfrac& frac){ return out << frac.num << "/" << frac.den;}
    //    Métodos auxiliares:
    void input_processing(string aux, serialfrac& frac);
    void setFrac(string s);
    string getFrac() const;
    virtual string toString();
    virtual void fromString(string repr);
    virtual unsigned long long int size() const;

};

#endif // SERIALFRAC_H_INCLUDED
