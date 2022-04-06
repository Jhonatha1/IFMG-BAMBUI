/******************************************
 * TRABALHO ÁRVORE B                      *
 *   Filipe Lehmann Pereira, RA: 0034075  *
 *   Yanky Jhonatha, RA: 0060194          *
 *   Implementado em 03/2022              *
 ******************************************/


#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include<iostream>
#include <string>
#include <vector>
#include "typedfile.h"
#include "node.h"
#include "record.h"

using namespace std;

template <class T,const unsigned int MIN_DEGREE>
class btree: private typedFile<T, MIN_DEGREE>
{
public:
    ~btree();
    btree();
    btree(const string name, const string type, const unsigned int version);
    bool insertKey(T key);
    void print();
    bool search(T key);
    bool remove(T key);
    void close();
    bool isOpen();

private:
    //Suporte print
    void printAux(node<T, MIN_DEGREE> x, vector<string> &v, unsigned int nivel);

    //Suporte search
    bool searchAux(node<T,MIN_DEGREE> x, T key);
    node<T,MIN_DEGREE> root;

    //Get e set
    node<T,MIN_DEGREE> getRoot() const
    {
        return this->root;
    }
    void setRoot(node<T,MIN_DEGREE> root )
    {
        this->root = root;
    }

    //Suporte remove
    bool removeAux(node<T,MIN_DEGREE> x, T key, unsigned int idfX);
    bool removeFromNonLeaf(node<T, MIN_DEGREE> x, unsigned int idx, unsigned int idfX);
    bool removeFromLeaf(node<T, MIN_DEGREE> x, unsigned int idx, unsigned int idfX);
    T findSuc(node<T, MIN_DEGREE> x, unsigned int idx, unsigned int idfX);
    T findPred(node<T, MIN_DEGREE> x, unsigned int idx, unsigned int idfX);
    void bottom(node<T, MIN_DEGREE> x, unsigned int idx, unsigned int idfX);
    bool downnOrganize(node<T, MIN_DEGREE> x,unsigned int idx, unsigned int idfX);
    void twirlKeys(node<T, MIN_DEGREE> x,unsigned int idx, unsigned int idfX,bool direction);

    //Suporte insertKey
    unsigned int hasKey(node<T, MIN_DEGREE> x, T key);
    bool insertNonFull( node<T,MIN_DEGREE>& x, T key, unsigned int idx);
    void splitChild(node<T,MIN_DEGREE>& x, unsigned int idx, unsigned int idfX);

    //Suporte typedFile
    node<T,MIN_DEGREE> examineNode(unsigned int idfXNode);
    bool fixNode(node<T,MIN_DEGREE> x, unsigned int idfXNode,bool isnew);
    unsigned int getlastPlace();
    unsigned int getrootIdx();
    void setrootidfX(unsigned int idx);
    bool insertRoot(node<T, MIN_DEGREE> n);
    bool delNode(node<T, MIN_DEGREE> n, unsigned int i);
};

template <class T, const unsigned int MIN_DEGREE>
btree<T, MIN_DEGREE>::~btree()
{
    close();
}

///Caregamento da raiz
template <class T, const unsigned int MIN_DEGREE>
btree<T, MIN_DEGREE>::btree():typedFile<T, MIN_DEGREE>::typedFile()
{
    this->setRoot(this->examineNode(this->getrootIdx()));
}

template <class T, const unsigned int MIN_DEGREE>
btree<T, MIN_DEGREE>::btree(const string name, const string type, const unsigned int version):typedFile<T, MIN_DEGREE>::typedFile(name, type, version)
{
    this->setRoot(this->examineNode(this->getrootIdx()));
}

template <class T, const unsigned int MIN_DEGREE>
bool btree<T, MIN_DEGREE>::insertKey(T key)
{
    bool result = false;
    node<T, MIN_DEGREE> r = this->getRoot();
    //Verificação de raiz cheia.
    if(r.getSize() == r.MAX)
    {
        //Criação de nova raiz.
        node<T, MIN_DEGREE> s(false),aux;
        unsigned int i = 0;

        s.setChild(0, this->getrootIdx());

        this->insertRoot(s);
        /*O filho mais a esquerda, no caso a raiz anterior é dividida, e a chave
          do meio é transferida para a raiz.
        */
        splitChild(s,0, this->getrootIdx());

        //Após a divisão, é verificado o local por onde se deve descer( 0 ou 1 )
        if (s.getKey(0) < key)
        {
            i++;
        }
        //O filho 0 ou o filho 1 da raiz é recarregado.
        aux = this->examineNode(s.getChild(i));

        //A chave é inserida passando o filho chave e o indexNo do arquivo para aux.
        result = insertNonFull(aux,key,s.getChild(i));

        this->setRoot(s);
        //A raiz é carregada para a memória.
        return result;
    }
    else
    {
        /*Verifica se não está cheia, caso estiver, é mandado inserir em algum node não cheio
        e a raiz é carregada para a memória.
        */
        result = insertNonFull(r,key,this->getrootIdx());
        this->setRoot(r);
        return result;
    }
}

template <class T, const unsigned int MIN_DEGREE>
bool btree<T, MIN_DEGREE>::insertNonFull(node<T,MIN_DEGREE>& x,T key,unsigned int idx)
{
    //O tamanho do node analisado é carregado.
    int i = x.getSize() - 1;
    //Caso for uma folha, é inserido.
    if(x.isLeaf())
    {
        while(i >= 0 && key < x.getKey(i))
        {
            x.setKey(i + 1, x.getKey(i));
            --i;
        }
        ++i;
        x.setKey(i, key);
        x.setSize(x.getSize()+1);
        return this->fixNode(x,idx, false);
    }
    else
    {
        //Se não for uma folha;
        node<T, MIN_DEGREE> aux;
        //É verificado por onde se deve descer.
        int n = 0;
        while(n <= i && x.getKey(n) < key)
        {
            n++;
        }

        aux = this->examineNode(x.getChild(n));
        //É verificado se pode descer.
        if (aux.getSize() == aux.MAX)
        {
            //Se por acaso não for possível descer para inserir, o filho de x é dividido em i.
            splitChild(x,n,idx);
            //Verificação novamente por onde se pode descer.
            if (x.getKey(n) < key)
                n++;
        }
        //O filho é carregado e desce para a remoção.
        aux = this->examineNode(x.getChild(n));
        return insertNonFull(aux,key,x.getChild(n));
    }
}

template <class T, const unsigned int MIN_DEGREE>
void btree<T, MIN_DEGREE>::splitChild(node<T,MIN_DEGREE>& x, unsigned int idx, unsigned int idfX)
{

    node <T, MIN_DEGREE> y,z;
    //O filho da esquerda de x é carregado.
    y = this->examineNode(x.getChild(idx));
    /*Se y e z estão no mesmo nível, então, se y é folha, z é folha,
    e se y não é folha, z também não vai ser.
    */
    z.setLeaf(y.isLeaf());
    z.setSize(z.MIN);
    //O splitChild é chamado se caso y contém MAX, e ao final do split y e z terá MIN.

    //O MIN chaves é copiado para z.
    for (unsigned int j = 0; j < z.getSize(); j++)
    {
        z.setKey(j, y.getKey(j + MIN_DEGREE));
    }
    //O MIN + 1 filhos de y são copiados para z, e é começado se MIN_DEGREE for.
    if(!y.isLeaf())
    {
        for (unsigned int j = 0; j < MIN_DEGREE; j++)
        {
            z.setChild(j, y.getChild(j + MIN_DEGREE));
        }
    }
    //O tamanho de y é colocado como MIN.
    y.setSize(y.MIN);
    //Os filhos de x são realocados em uma posição à frente, até ser index + 1.
    for (unsigned int j = x.getSize(); j >= idx + 1; j--)
    {
        x.setChild(j+1, x.getChild(j));
        if(j == 0)
        {
            break;
        }
    }
    //A posição que z terá que salvar é calculada no arquivo e salva no filho de x.
    x.setChild(idx + 1, this->getlastPlace());

    //As chaves de x são colocadas uma posição à frente.
    if(x.getSize() > 0)
    {
        for (unsigned int j = x.getSize() - 1; j >= idx; j--)
        {
            x.setKey(j + 1, x.getKey(j));
            if(j == 0)
            {
                break;
            }
        }
    }
    //A chave de x é colocado como sendo a anterior do meio de y.
    x.setKey(idx, y.getKey(y.MIN));
    x.setSize(x.getSize() + 1);
    //X, Y e Z são salvos.
    this->fixNode(x, idfX, false);
    this->fixNode(y, x.getChild(idx),false);
    this->fixNode(z,0, true);
}

template <class T, const unsigned int MIN_DEGREE>
bool btree<T, MIN_DEGREE>::search(T key)
{
    //A raiz é carregada e se ela for diferente de 0, é retornado o searchAux, e se não for, é retornado false.
    node<T, MIN_DEGREE> r = this->getRoot();
    if (r.getSize() != 0)
    {
        return searchAux(r, key);
    }
    return false;
}

template <class T, const unsigned int MIN_DEGREE>
bool btree<T, MIN_DEGREE>::searchAux(node<T, MIN_DEGREE> x,T key)
{
    node <T, MIN_DEGREE> aux;
    unsigned int i = 0;
    //Aqui olha por onde deve descer.
    while (i < x.getSize() && key > x.getKey(i))
    {
        i++;
    }
    //É verificado se a chave está alocada no node.
    if (x.getKey(i) == key)
    {
        return true;
    }
    //Se não estiver e for uma folha, é retornado false.
    if (x.isLeaf())
    {
        return false;
    }
    //Se não estiver e for uma página interna, é carregado o filho de x em i.
    aux = this->examineNode(x.getChild(i));
    //É retornado recursivamente o searchAux que passa o filho de x em i e a chave.
    return searchAux(aux, key);

}

template <class T, const unsigned int MIN_DEGREE>
bool btree<T, MIN_DEGREE>::remove(T key)
{

    bool removido = false;

    node<T, MIN_DEGREE> root = this->getRoot();
    //Se o tamanho da raiz é 0, vai retornar false.
    if (root.getSize() == 0)
    {
        return removido;
    }

    //O removeAux é convocado, que passa pela raiz, pela chave e pelo index da raiz.
    removido = removeAux(root,key, this->getrootIdx());

    //É carregada a raiz da memória.
    this->setRoot(this->examineNode(this->getrootIdx()));

    root = this->getRoot();
    //Se a raiz estiver ficado com tamanho = 0;
    if (root.getSize() == 0 && !root.isLeaf())
    {
        //O filho da direito é carregado como sendo a nova raiz, e a raiz anterior é deletada.
        node<T, MIN_DEGREE> previousRoot = root;
        unsigned int previousrootIdx = getrootIdx();

        this->setrootidfX(root.getChild(0));

        this->setRoot(this->examineNode(root.getChild(0)));

        return delNode(previousRoot, previousrootIdx);
    }
    return removido;
}

template <class T, const unsigned int MIN_DEGREE>
bool btree<T, MIN_DEGREE>::removeAux(node<T, MIN_DEGREE> x, T key, unsigned int idfX)
{

    unsigned int idx = hasKey(x, key);
    //O index é carregado do lugar onde se deve descer, ou da chave no node.

    //É verificado se a chave se encontra no node atual e se ela é uma chave válida.
    if(idx < x.getSize() && x.getKey(idx) == key)
    {
        if(x.isLeaf())
        {
            //Caso estiver em um node e o node for uma folha, o caso 1 é chamado.
            return removeFromLeaf(x, idx, idfX);
        }
        else
        {
            //Caso estiver em um node e o node for uma página interna, o caso 2 é chamado.
            return removeFromNonLeaf(x, idx, idfX);
        }
    }
    else if (!x.isLeaf())
    {
        //Se não estiver no node e ele não for uma folha, o caso 3 é chamado.
        node<T, MIN_DEGREE> child;

        /*Para saber se aconteceu uma junção no último filho,
          é verificado o size do node, e se ele é o mesmo valor que o index.  */

        bool lastgroupChild = ((idx == x.getSize())? true : false );
        //O filho é carregado.
        child = this->examineNode(x.getChild(idx));

        //O filho é verificado se possui o MIN_DEGREE.
        if(child.getSize() < MIN_DEGREE)
        {
            //Se caso não possuir, desce para organizar e o x é recarregado.
            downnOrganize(x, idx, idfX);
            x = this->examineNode(idfX);
        }

        //Se por acaso descer pelo filho mais a direita de x, e o x diminuiu o tamanho;
        if(lastgroupChild && idx > x.getSize())
        {
            //O child a esquerda é carregado.
            child = this->examineNode(x.getChild(idx - 1));
            return removeAux(child,key,x.getChild(idx - 1));

        }
        else
        {
            //O child é carregado.
            child = this->examineNode(x.getChild(idx));
            return removeAux(child,key,x.getChild(idx));
        }

    }
    else
    {
        return false;
    }
}

template <class T, const unsigned int MIN_DEGREE>
unsigned int btree<T, MIN_DEGREE>::hasKey(node<T, MIN_DEGREE> x, T key)
{
    unsigned int idx = 0;
    //O index é carregado por onde se deve descer ou o da chave do node.
    while(idx < x.getSize() && key > x.getKey(idx))
    {
        idx++;
    }
    return idx;
}

template <class T, const unsigned int MIN_DEGREE>
bool btree<T, MIN_DEGREE>::removeFromLeaf(node<T, MIN_DEGREE> x, unsigned int idx, unsigned int idfX)
{
    //A chave no index de x é removida e salvo em x.
    for (unsigned int i = idx; i < x.getSize() - 1; i++)
    {
        x.setKey(i, x.getKey(i + 1));
    }
    x.setSize(x.getSize() - 1);

    return this->fixNode(x, idfX, false);
}

template <class T, const unsigned int MIN_DEGREE>
bool btree<T, MIN_DEGREE>::removeFromNonLeaf(node<T, MIN_DEGREE> x, unsigned int idx, unsigned int idfX)
{
    T key = x.getKey(idx);
    node<T, MIN_DEGREE> childrenL,childrenR;

    //Os filhos são carregados.
    childrenL = this->examineNode(x.getChild(idx));
    childrenR = this->examineNode(x.getChild(idx+1));

    //Caso o vizinho da esquerda tenha MIN_DEGREE ou mais chaves;
    if(childrenL.getSize() >= MIN_DEGREE)
    {
        //O predecessor é encontrado
        T pred = findPred(x, idx, idfX);
        //E salvo em x no index da chave que ia ser removida.
        x.setKey(idx, pred);
        //O x é salvo.
        return this->fixNode(x, idfX, false);

    }
    else if(childrenR.getSize() >= MIN_DEGREE)
    {
        //O sucessor é encontrado.
        T suc = findSuc(x, idx, idfX);
        //O sucessor é salvo em x no index da chave que ia ser removida.
        x.setKey(idx, suc);
        //O x é salvo.
        return this->fixNode(x, idfX, false);

    }
    else
    {
        /*Caso os filhos da esquerda e da direita estejam
          com o MIN de chaves, é efetuado a união pelo bottom entre eles.  */
        bottom(x,idx,idfX);
        //O children da esquerda é carregado.
        childrenL = this->examineNode(x.getChild(idx));
        //O removeAux é convocado.
        return removeAux(childrenL, key, x.getChild(idx));

    }

}

template <class T, const unsigned int MIN_DEGREE>
T btree<T, MIN_DEGREE>::findPred(node<T, MIN_DEGREE> x, unsigned int idx, unsigned int idfX)
{
    node<T, MIN_DEGREE> child;
    child = this->examineNode(x.getChild(idx));
    T key;
    //É uma flag para verificar se vai descer pelo filho mais a direita.

    bool lastgroupChild = ((idx == x.getSize())? true : false );
    //É verificado se é preciso organizar antes de descer.
    if(child.getSize() < MIN_DEGREE)
    {
        //Organiza e carrega o filho.
        this->downnOrganize(x, idx, idfX);
        child = this->examineNode(x.getChild(idx));
    }

    //Verificação de quem contém o index de child.
    if(lastgroupChild && idx > x.getSize())
    {
        idfX = x.getChild(idx - 1);

    }
    else
    {
        idfX = x.getChild(idx);
    }


    while(!child.isLeaf())
    {
        //Os mesmos passos são executados novamente, porém, sempre entra no filho mais a direita.
        node<T, MIN_DEGREE> aux = this->examineNode(child.getChild(child.getSize()));
        unsigned int idfX = child.getSize();

        if(aux.getSize() < MIN_DEGREE)
        {
            this->downnOrganize(child, child.getSize(), idfX);
            child = this->examineNode(idfX);
            aux = this->examineNode(child.getChild(child.getSize()));
        }

        if(idfX > child.getSize())
        {
            idfX = child.getChild(idfX - 1);
        }
        else
        {
            idfX = child.getChild(idfX);
        }
        child = aux;
    }
    //O filho é carregado.
    child = this->examineNode(idfX);
    //A chave é salva em aux.
    key = child.getKey(child.getSize() - 1);
    //A chave k é removida em child.
    this->removeFromLeaf(child, child.getSize() - 1, idfX);
    return key;
}

template <class T, const unsigned int MIN_DEGREE>
T btree<T, MIN_DEGREE>::findSuc(node<T, MIN_DEGREE> x, unsigned int idx, unsigned int idfX)
{
    /*Acontece a mesma coisa com o findPred, mas agora a primeira parte do código
    entra no filho mais a direita, e depois sempre no filho mais a direita. */
    node<T, MIN_DEGREE> child;
    child = this->examineNode(x.getChild(idx + 1));

    bool lastgroupChild = (((idx + 1) == x.getSize())? true : false );

    if(child.getSize() < MIN_DEGREE)
    {
        this->downnOrganize(x, idx + 1, idfX);
        child = this->examineNode(x.getChild(idx + 1));
    }


    if(lastgroupChild && idx > x.getSize())
    {
        idfX = x.getChild(idx);

    }
    else
    {
        idfX = x.getChild(idx + 1);
    }


    while(!child.isLeaf())
    {

        node<T, MIN_DEGREE> aux = this->examineNode(child.getChild(0));
        unsigned int idfX = 0;

        if(aux.getSize() < MIN_DEGREE)
        {
            this->downnOrganize(child, 0, idfX);
            child = this->examineNode(idfX);
            aux = this->examineNode(child.getChild(0));
        }


        idfX = child.getChild(idfX);
        child = aux;
    }

    T key;
    child = this->examineNode(idfX);
    key = child.getKey(0);
    this->removeFromLeaf(child, 0, idfX);
    return key;


}

template <class T, const unsigned int MIN_DEGREE>
void btree<T, MIN_DEGREE>::bottom(node<T, MIN_DEGREE> x, unsigned int idx,unsigned int idfX )
{
    node<T, MIN_DEGREE> childrenL,childrenR;
    int idxchildrenR = x.getChild(idx + 1);

    //Carrega filhos
    childrenL = this->examineNode(x.getChild(idx));
    childrenR = this->examineNode(x.getChild(idx + 1));
    //A chave de x é transferida para o filho da direita.
    childrenL.setKey(childrenL.MIN, x.getKey(idx));

    //As chaves são copiadas do filho da direita para os filhos da esquerda.
    for (unsigned int i = 0; i < childrenR.getSize(); i++)
    {
        childrenL.setKey(i + MIN_DEGREE, childrenR.getKey(i));
    }
    //Se o filho for folha, os filhos são copiados do filho da direita para os da esquerda.
    if (!childrenL.isLeaf())
    {
        for(unsigned int i = 0; i <= childrenR.getSize(); i++)
        {
            childrenL.setChild(i + MIN_DEGREE, childrenR.getChild(i));
        }
    }
    //As chaves de x são realocadas para uma posição atrás.
    for (unsigned int i = idx + 1; i < x.getSize(); i++)
    {
        x.setKey(i - 1, x.getKey(i));
    }

    //Os filhos de x são realocados para uma posição atrás.
    for (unsigned int i = idx + 2; i <= x.getSize(); i++)
    {
        x.setChild(i - 1, x.getChild(i));
    }
    //Os novos tamanhos dos filhos são reajustados à esquerda e também o de seu pai x.
    childrenL.setSize(childrenL.getSize() + 1 + childrenR.getSize());
    x.setSize(x.getSize() - 1);

    //O x é salvo em childrenL e em childrenR é deletado.
    this->fixNode(childrenL, x.getChild(idx), false);
    this->fixNode(x, idfX, false);
    this->delNode(childrenR, idxchildrenR);
    return;
}

template <class T, const unsigned int MIN_DEGREE>
bool btree<T, MIN_DEGREE>::downnOrganize(node<T, MIN_DEGREE> x, unsigned int idx,unsigned int idfX )
{

    node<T, MIN_DEGREE> auxChild;
    //Se o index não for 0, é pedido para rotacionar da esquerda para direita.
    if ( idx != 0 )
    {

        auxChild = this->examineNode(x.getChild(idx - 1));


        if(auxChild.getSize() >= MIN_DEGREE)
        {
            twirlKeys(x, idx, idfX, false);
            return true;
        }

    }
    //Se o index não for do tamanho máximo e nem for 0, é possível pedir para rotacionar da direita para esquerda.
    if( idx != x.getSize() )
    {

        auxChild = this->examineNode(x.getChild(idx + 1));

        if(auxChild.getSize() >= MIN_DEGREE)
        {
            twirlKeys(x, idx, idfX, true);
            return true;
        }

    }
    //Se não for, é verificado se o filho que é necessário fundir tem irmão a direita.
    if(idx != x.getSize())
    {
        //Caso ele tiver, é efetuado o bottom com o filho a direita.
        bottom( x, idx, idfX );
        return true;
    }
    else
    {
        //Se não, é efetuado o bottom com o filho a esquerda.
        bottom( x, idx - 1, idfX );
        return true;
    }
}

template <class T, const unsigned int MIN_DEGREE>
void btree<T, MIN_DEGREE>::twirlKeys(node<T, MIN_DEGREE> x, unsigned int idx,unsigned int idfX, bool direction)
{
    //Se caso a rotação for da direita para a esquerda;
    if(direction)
    {

        node<T, MIN_DEGREE> child,right;

        //Carrega os filhos
        child = this->examineNode(x.getChild(idx));
        right = this->examineNode(x.getChild(idx + 1));

        //A chave de x desce para o child
        child.setKey(child.getSize(), x.getKey(idx));

        //Caso o child for uma página interna, o primeiro filho do irmão da esquerda vai para child.
        if(!child.isLeaf())
        {
            child.setChild(child.getSize() + 1, right.getChild(0));
        }
        //A primeira chave do irmão da direita sobe para o pai.
        x.setKey(idx, right.getKey(0));

        //Realocação das chaves do irmão à esquerda.
        for (unsigned int i = 1; i < right.getSize(); i++)
        {
            right.setKey(i - 1, right.getKey(i));
        }
        //Irmão à esquerda como página interna;
        if (!right.isLeaf())
        {
            //Realocação de seus filhos.
            for(unsigned int i = 1; i <= right.getSize(); i++)
            {
                right.setChild(i - 1, right.getChild(i));
            }
        }
        //Incremento de child e decremento de size.
        child.setSize(child.getSize() + 1);
        right.setSize( right.getSize() - 1);

        //O x, right e child são salvos.
        this->fixNode(x, idfX, false);
        this->fixNode(right, x.getChild(idx + 1), false);
        this->fixNode(child, x.getChild(idx), false);


        return;

    }
    else
    {
        //A diferença do caso acima é que agora a rotação é com o filho da esquerda, então é feita da esquerda para direita.
        node<T, MIN_DEGREE> child,left;

        //Carrega os filhos.
        child = this->examineNode(x.getChild(idx));
        left = this->examineNode(x.getChild(idx - 1));


        for (unsigned int i = child.getSize() - 1 ; i >= 0; i--)
        {
            child.setKey(i + 1, child.getKey(i));
            if(i == 0)
            {
                break;
            }
        }

        if (!child.isLeaf())
        {

            for(unsigned int i = child.getSize(); i >= 0; i--)
            {
                child.setChild( i + 1, child.getChild(i));
                if(i == 0)
                {
                    break;
                }
            }
        }

        child.setKey(0, x.getKey(idx - 1));

        if(!child.isLeaf())
        {
            child.setChild(0, left.getChild(left.getSize()));
        }

        x.setKey(idx - 1, left.getKey(left.getSize() - 1));

        child.setSize(child.getSize() + 1);
        left.setSize( left.getSize() - 1);

        this->fixNode(x, idfX, false);
        this->fixNode(left, x.getChild(idx - 1),false);
        this->fixNode(child, x.getChild(idx), false);

    }
}
template <class T, const unsigned int MIN_DEGREE>
node<T, MIN_DEGREE> btree<T, MIN_DEGREE>::examineNode(unsigned int idfXNode)
{
    //O record é carregado para a memória e é retornado o node.
    record<T, MIN_DEGREE> recentRoot;
    typedFile<T, MIN_DEGREE>::examineRecord(recentRoot, idfXNode);
    return recentRoot.getData();
}

template <class T, const unsigned int MIN_DEGREE>
unsigned int btree<T, MIN_DEGREE>::getrootIdx()
{
    //O index da raiz é retornado.
    return typedFile<T, MIN_DEGREE>::getFirstValid();
}

template <class T, const unsigned int MIN_DEGREE>
void btree<T, MIN_DEGREE>::setrootidfX(unsigned int idx)
{
    //O index da raiz é alocado.
    typedFile<T, MIN_DEGREE>::setFirstValid(idx);
}

template <class T, const unsigned int MIN_DEGREE>
unsigned int btree<T, MIN_DEGREE>::getlastPlace()
{
    //Index é calculado para um novo nó.
    return typedFile<T, MIN_DEGREE>::calcIdx();
}

template <class T, const unsigned int MIN_DEGREE>
bool btree<T, MIN_DEGREE>::insertRoot(node<T, MIN_DEGREE> n)
{
    //Uma nova raiz é inserida.
    record<T, MIN_DEGREE> recentRoot1;
    recentRoot1.setData(n);
    return typedFile<T, MIN_DEGREE>::insertRoot(recentRoot1);
}

template <class T, const unsigned int MIN_DEGREE>
bool btree<T, MIN_DEGREE>::fixNode(node<T,MIN_DEGREE> x, unsigned int idfXNode, bool isnew)
{
    //O node é salvo.
    record<T, MIN_DEGREE> recentRoot;
    recentRoot.setData(x);
    return typedFile<T, MIN_DEGREE>::fixNode(recentRoot,idfXNode, isnew);
}

template <class T, const unsigned int MIN_DEGREE>
bool btree<T, MIN_DEGREE>::delNode(node<T, MIN_DEGREE> x, unsigned int i)
{
    //O node é deletado e colocado na lista de deletados.
    record<T, MIN_DEGREE> recentRoot;
    recentRoot.setData(x);
    return typedFile<T, MIN_DEGREE>::delNode(recentRoot, i);
}

template <class T, const unsigned int MIN_DEGREE>
void btree<T, MIN_DEGREE>::close()
{
    typedFile<T, MIN_DEGREE>::close();
}

template <class T, const unsigned int MIN_DEGREE>
bool btree<T, MIN_DEGREE>::isOpen()
{
    return typedFile<T, MIN_DEGREE>::isOpen();
}
/*A árvore é percorrida e sendo salva as chaves dos nodes em um vetor,
  assim que percorrer, o vetor de string é mostrado. */
template <class T, const unsigned int MIN_DEGREE>
void btree<T, MIN_DEGREE>::print()
{
    int nivel = 0;
    vector<string> niveis(1);
    printAux(root, niveis, nivel);

    for (string s : niveis)
    {
        cout << s << endl;
    }
}

template <class T, const unsigned int MIN_DEGREE>
void btree<T, MIN_DEGREE>::printAux(node<T, MIN_DEGREE> x, vector<string> &v, unsigned int nivel)
{
    string str = "[";
    unsigned int i = 0;
    //Se caso mudou o nível, o resize em v é feito.
    if (v.size() < nivel + 1)
    {
        v.resize(nivel + 1);
    }
    //Se caso x não for folha;
    if (!x.isLeaf())
    {
        //É verificado os filhos, e chamado o printAux recursivamente e aumenta-se o nível.
        for (i = 0; i <= x.getSize(); i++)
        {
            if (x.getChild(i) != x.NOT_FOUND)
            {
                node<T, MIN_DEGREE> aux = this->examineNode(x.getChild(i));
                printAux(aux, v, nivel + 1);
            }
        }
    }
    //As chaves são salvas todas em uma string.
    for (i = 0; i < x.getSize(); i++)
    {
        str += (x.getKey(i).getFrac()) + ", ";
    }
    //A string é organizada.
    if (str.length() > 1)
    {
        str += "\b\b] ";
    }
    else
    {
        str += "] ";
    }
    //E por fim, é somado no vetor com o seu nível indicado.
    v[nivel] += str;
}
//obs: fim graças à deus ;)
#endif // TREE_H_INCLUDED
