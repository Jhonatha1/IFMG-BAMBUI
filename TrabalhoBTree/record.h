/******************************************
 * TRABALHO ÁRVORE B                      *
 *   Filipe Lehmann Pereira, RA: 0034075  *
 *   Yanky Jhonatha, RA: 0060194          *
 *   Implementado em 03/2022              *
 ******************************************/


#ifndef RECORD_H
#define RECORD_H

#include <string>
#include "serializable.h"

using namespace std;

template <class T,const unsigned int MIN_DEGREE>
class record : public serializable {
   static_assert(is_base_of<serializable, T>::value, "T must be serializable");
   public:
      record();
      record(node<T, MIN_DEGREE> d);
      record(const record<T, MIN_DEGREE> &other);
      virtual ~record();
      record<T, MIN_DEGREE> operator=(const record<T, MIN_DEGREE> &other);
      node<T, MIN_DEGREE> getData() const;
      unsigned long long int getSuccessor() const;
      void setData(node<T, MIN_DEGREE> d);
      bool operator==(const record<T, MIN_DEGREE> &other);
      void setSuccessor(unsigned long long int n);
      bool isDel() const;
      void del();
      void undel();
      virtual void fromString(string repr);
      virtual string toString();
      virtual unsigned long long int size() const;
   protected:
      unsigned long long int prox;
      bool deleted;
      node<T, MIN_DEGREE> data;
};


template <class T,const unsigned int MIN_DEGREE>
record<T, MIN_DEGREE>::record(node<T, MIN_DEGREE> d) : serializable() {
    this->data = d;
    this->prox = 0;
    this->deleted = false;
}

template <class T,const unsigned int MIN_DEGREE>
record<T, MIN_DEGREE>::~record() {

}

template <class T,const unsigned int MIN_DEGREE>
record<T, MIN_DEGREE>::record() : serializable() {
    node<T, MIN_DEGREE> data;
    this->data = data;
    this->prox = 0;
    this->deleted = true;
}

template <class T,const unsigned int MIN_DEGREE>
record<T, MIN_DEGREE>::record(const record<T, MIN_DEGREE> &other) {
    this->data = other.data;
    this->prox = other.prox;
    this->deleted = other.deleted;
}

template <class T,const unsigned int MIN_DEGREE>
record<T, MIN_DEGREE> record<T, MIN_DEGREE>::operator=(const record<T, MIN_DEGREE> &other) {
    if(this != &other){
        record<T, MIN_DEGREE> n(other);
        this->data = other.data;
        this->prox = other.prox;
        this->deleted = other.deleted;
        return *this;
    }
    return *this;
}

template <class T,const unsigned int MIN_DEGREE>
bool record<T, MIN_DEGREE>::operator==(const record<T, MIN_DEGREE> &other) {
    return (this->data == other.data) && (this->deleted == other.deleted) && (this->prox == other.prox);
}

template <class T,const unsigned int MIN_DEGREE>
node<T,MIN_DEGREE> record<T, MIN_DEGREE>::getData() const {
    return this->data;
}

template <class T,const unsigned int MIN_DEGREE>
void record<T, MIN_DEGREE>::setData(node<T, MIN_DEGREE> d) {
    this->data = d;
}

template <class T,const unsigned int MIN_DEGREE>
unsigned long long int record<T, MIN_DEGREE>::getSuccessor() const {
    return this->prox;
}

template <class T,const unsigned int MIN_DEGREE>
void record<T, MIN_DEGREE>::setSuccessor(unsigned long long int n) {
    this->prox = n;
}

template <class T,const unsigned int MIN_DEGREE>
bool record<T, MIN_DEGREE>::isDel() const {
    return this->deleted;
}


template <class T,const unsigned int MIN_DEGREE>
void record<T, MIN_DEGREE>::undel() {
    this->deleted = false;
}
template <class T,const unsigned int MIN_DEGREE>
void record<T, MIN_DEGREE>::del() {
    this->deleted = true;
}

template <class T,const unsigned int MIN_DEGREE>
void record<T, MIN_DEGREE>::fromString(string repr) {
    int plc = 0;
    string datastring = repr.substr(plc,data.size());
    this->data.fromString(datastring);
    plc += this->data.size();
    repr.copy(reinterpret_cast<char*>(&this->deleted), sizeof(this->deleted), plc);
    plc += sizeof(this->deleted);
    repr.copy(reinterpret_cast<char*>(&this->prox), sizeof(this->prox), plc);
    plc += sizeof(this->prox);
}

template <class T,const unsigned int MIN_DEGREE>
unsigned long long int record<T, MIN_DEGREE>::size() const {
    return data.size() + sizeof(deleted) + sizeof(prox);
}

template <class T,const unsigned int MIN_DEGREE>
string record<T, MIN_DEGREE>::toString() {
    string repr = "";
    repr += data.toString();
    repr += string(reinterpret_cast<char*>(&this->deleted), sizeof(this->deleted));
    repr += string(reinterpret_cast<char*>(&this->prox), sizeof(this->prox));
    return repr;
}


#endif // RECORD_H
