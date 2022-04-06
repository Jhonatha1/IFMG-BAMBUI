/******************************************
 * TRABALHO ÁRVORE B                      *
 *   Filipe Lehmann Pereira, RA: 0034075  *
 *   Yanky Jhonatha, RA: 0060194          *
 *   Implementado em 03/2022              *
 ******************************************/


#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <iostream>

using namespace std;

template <class T, const unsigned int MIN_DEGREE>
class node : serializable
{
public:
    node();
    node(bool leaf);
    node(const node& other);
    virtual ~node();
///    INLINE
    void setLeaf(bool leaf){this->leaf = leaf;}
    bool isLeaf(){return this->leaf;}
    unsigned int getSize() const{return this->n;}
    void setSize(unsigned int n){this->n = n;}
    void setKey(T k, unsigned int i){this->keys[i] = k;}
    unsigned int getNodeSize(){return this->n;}
    T getKey(int i){return this->keys[i];}
    unsigned int getChild(unsigned int i){return this->children[i];}
    void setChild(unsigned int i, unsigned int fileIndex){this->children[i] = fileIndex;}
    T getKey(unsigned int i){return this->keys[i];}
    void setKey(unsigned int i, T key){this->keys[i] = key;}

    static const unsigned int MIN = MIN_DEGREE - 1;
    static const unsigned int MAX = 2 * MIN_DEGREE - 1;
    static const unsigned int NOT_FOUND = -1;
    virtual string toString();
    virtual void fromString(string repr);
    virtual unsigned long long int size() const;

protected:
    vector<T> keys;
    vector<unsigned int> children;
    bool leaf;
    unsigned int n;
};

//Construtores:
template <class T, const unsigned int MIN_DEGREE>
node<T, MIN_DEGREE>::node()
{
    unsigned int i;
    this->setSize(0);

    keys.resize(MAX);
    children.resize(MAX + 1);

    for (i = 0; i < children.size(); i++)
    {
        this->setChild(i,NOT_FOUND);
    }
    this->setLeaf(true);
}

template <class T, const unsigned int MIN_DEGREE>
node<T, MIN_DEGREE>::node(bool leaf)
{
    unsigned int i;
    this->setSize(0);

    keys.resize(MAX);
    children.resize(MAX + 1);

    for (i = 0; i < children.size(); i++)
    {
        this->setChild(i,NOT_FOUND);
    }
    this->setLeaf(leaf);
}

template <class T, const unsigned int MIN_DEGREE>
node<T, MIN_DEGREE>::node(const node<T, MIN_DEGREE>& other)
{

    this->setLeaf(other.leaf);
    this->setSize(other.getSize());

    keys.resize(MAX);
    children.resize(MAX + 1);

    this->children = other.children;
    this->keys = other.keys;
}

template <class T, const unsigned int MIN_DEGREE>
node<T, MIN_DEGREE>::~node()
{

}

// Métodos de Serialização:
template <class T, const unsigned int MIN_DEGREE>
string node<T, MIN_DEGREE>::toString()
{

    string aux = "";
    aux += string(reinterpret_cast<char*>(&this->leaf), sizeof(this->leaf));
    aux += string(reinterpret_cast<char*>(&this->n), sizeof(this->n));

    for(unsigned int i=0; i< keys.size(); i++)
    {
        aux += keys[i].toString();
    }

    for(unsigned int i=0; i< children.size(); i++)
    {
        aux += string(reinterpret_cast<char*>(&this->children[i]), sizeof(this->children[i]));
    }

    return aux;
}

template <class T, const unsigned int MIN_DEGREE>
void node<T, MIN_DEGREE>::fromString(string repr)
{
    int pos = 0;

    repr.copy(reinterpret_cast<char*>(&this->leaf), sizeof(this->leaf), pos);
    pos += sizeof(this->leaf);

    repr.copy(reinterpret_cast<char*>(&this->n), sizeof(this->n), pos);
    pos += sizeof(this->n);

    string datastring = "";
    for(unsigned int i=0; i< keys.size(); i++)
    {
        datastring = repr.substr(pos,keys[i].size());
        keys[i].fromString(datastring);
        pos += keys[i].size();
        datastring = "";
    }

    for(unsigned int i=0; i< children.size(); i++)
    {
        repr.copy(reinterpret_cast<char*>(&this->children[i]), sizeof(this->children[i]), pos);
        pos += sizeof(this->children[i]);
    }
}

template <class T, const unsigned int MIN_DEGREE>
unsigned long long int node<T, MIN_DEGREE>::size() const
{
//    Retorna o tamanho de toda a página.
    return sizeof(n) + sizeof(leaf) + sizeof(children[0])*children.size() + keys[0].size()*keys.size();
}

#endif // NODE_H_INCLUDED
