/******************************************
 * TRABALHO ÁRVORE B                      *
 *   Filipe Lehmann Pereira, RA: 0034075  *
 *   Yanky Jhonatha, RA: 0060194          *
 *   Implementado em 03/2022              *
 ******************************************/


#include <iostream>
#include <algorithm>
#include "serialfrac.h"

using namespace std;

serialfrac::serialfrac()
{
    this->num = 0;
    this->den = 1;
}

serialfrac::serialfrac(int n, int d)
{
    this->num = n;
    this->den = d;
}

serialfrac::serialfrac(const serialfrac& other)
{
    this->num = other.num;
    this->den = other.den;
}

serialfrac::~serialfrac()
{

}

serialfrac serialfrac::operator=(const serialfrac& other)
{
    if(this != &other)
    {
        this->num=other.num;
        this->den=other.den;
        return *this;
    }
    return *this;
}

void serialfrac::input_processing(string aux, serialfrac& frac)
{
    string mul;
    int num,den,factor;
    if(aux.find('.') != aux.npos)
    {
        mul = aux.substr(0, aux.find('.'));
        num = stoi(aux.substr(aux.find('.')+1,(aux.find('/')-mul.size()-1)));
    }
    else
    {
        num = stoi(aux.substr(0,aux.find('/')));
    }
    den = stoi(aux.substr(aux.find('/')+1));

    if(!mul.empty())
    {
        num += stoi(mul)*den;
    }
    factor = __gcd(num,den);
    if(num/factor<0)
    {
        frac.num = -num/factor;
        frac.den = den/factor;
    }
    else
    {
        frac.num = num/factor;
        frac.den = den/factor;
    }
}

istream& operator>>(istream &in, serialfrac &frac)
{
    string aux;
    cout << "Insira a fração no formato 1/2 ou 1.2/3: " << endl;
    in >> aux;
    frac.input_processing(aux, frac);

    return in;
}

void serialfrac::setFrac(string s)
{
    serialfrac frac;
    frac.input_processing(s, frac);
    this->den = frac.den;
    this->num = frac.num;
}

string serialfrac::getFrac() const
{
    string aux1(to_string(this->num)), aux2(to_string(this->den));
    return aux1+"/"+aux2;
}

string serialfrac::toString()
{
    string repr = "";
    repr += string(reinterpret_cast<char*>(&this->num), sizeof(this->num));
    repr += string(reinterpret_cast<char*>(&this->den), sizeof(this->den));
    return repr;
}

void serialfrac::fromString(string repr)
{
    // fstream::seekg move a cabeça de leitura para o byte designado.
    // fstream::read lê o número especificado de bytes (char) do arquivo.
    int pos = 0;
    int value = 0;
    repr.copy(reinterpret_cast<char*>(&value), sizeof(this->num), pos);
    this->num = value;
    pos += sizeof(this->num);
    repr.copy(reinterpret_cast<char*>(&value), sizeof(this->den), pos);
    this->den = value;
}


bool serialfrac::operator==(const serialfrac &other)const
{
    return ((float)this->num/this->den) == ((float)other.num/other.den);
}

bool serialfrac::operator<(const serialfrac &other)const
{
    return ((float)this->num/this->den) < ((float)other.num/other.den);
}
bool serialfrac::operator<=(const serialfrac &other)const
{
    return ((float)this->num/this->den) <= ((float)other.num/other.den);
}
bool serialfrac::operator>(const serialfrac &other)const
{
    return ((float)this->num/this->den) > ((float)other.num/other.den);
}
bool serialfrac::operator>=(const serialfrac &other)const
{
    return ((float)this->num/this->den) >= ((float)other.num/other.den);
}
bool serialfrac::operator!=(const serialfrac &other)const
{
    return ((float)this->num/this->den) != ((float)other.num/other.den);
}
unsigned long long int serialfrac::size() const
{
    return sizeof(this->num)+sizeof(this->den);
}

