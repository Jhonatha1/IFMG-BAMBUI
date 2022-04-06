/******************************************
 * TRABALHO ÁRVORE B                      *
 *   Filipe Lehmann Pereira, RA: 0034075  *
 *   Yanky Jhonatha, RA: 0060194          *
 *   Implementado em 03/2022              *
 ******************************************/


#ifndef TYPEDFILE_H
#define TYPEDFILE_H

#include <fstream>
#include <type_traits>
#include "node.h"
#include "header.h"
#include "record.h"

using namespace std;

const ios::openmode mod = ios::in | ios::out | ios::binary;

template <class T, const unsigned int MIN_DEGREE>
class typedFile : private fstream
{
    static_assert(is_base_of<serializable, T>::value, "T precisa ser serializado.\n");
public:
    header head;
    typedFile();
    typedFile(const string name, const string type, const unsigned int version, ios::openmode openmode=mod);
    virtual ~typedFile();
    bool open();
    bool close();
    bool open(const string name, const string type, const unsigned int version, ios::openmode openmode);
    bool isOpen();
    bool examineRecord(record<T, MIN_DEGREE> &rec, unsigned long long int i);
    void clear();
    bool fixNode(record<T, MIN_DEGREE> &rec, unsigned long long int i, bool isnew);
    bool fixRecord(record<T, MIN_DEGREE> &rec, unsigned long long int i);
    bool insertRoot(record<T, MIN_DEGREE> &rec);
    bool delNode(record<T, MIN_DEGREE> &rec, unsigned long long int i);
    bool delRecord(unsigned long long int i);
    void setFirstValid(unsigned long long int idx);
    unsigned long long int search(T data);
    unsigned long long int holdFirstDel();
    unsigned long long int getFirstValid();
    unsigned long long int lastPlace();
    unsigned long long int calcIdx();
private:
    bool fixHeader(header &h);
    unsigned long long int plc2idx(unsigned long long int p);
    unsigned long long int index2pos(unsigned long long int i);
    bool examineHeader(header &h);
    bool delRR(unsigned long long int idxRRecord);
    bool delAsk(unsigned long long int idxRecord);
};

template <class T, const unsigned int MIN_DEGREE>
typedFile<T, MIN_DEGREE>::typedFile() : fstream()
{
    //Se foi possível abrir o arquivo, com nenhum erro, é informado ao usuário.
    if(this->open("default.dat","ArvoreB",MIN_DEGREE,mod))
    {
        cout<<"O arquivo default.dat está aberto!"<<endl;
    }
    else
    {
    //O arquivo é fechado caso ele tenha sido aberto de forma errada.
        cout<<"Erro ao abrir o arquivo."<<endl;
        close();
    }
}

template <class T, const unsigned int MIN_DEGREE>
typedFile<T, MIN_DEGREE>::typedFile(const string name, const string type, const unsigned int ver, ios::openmode openmode) : fstream(name.c_str(), mod)
{
    if(this->open(name,type,ver,mod))
    {
        cout<<"Arquivo " << name << " aberto."<<endl;
    }
    else
    {
        cout<<"Erro ao abrir esse arquivo, as versões ou os tipos são diferentes."<<endl;
        close();
    }
}

template <class T, const unsigned int MIN_DEGREE>
typedFile<T, MIN_DEGREE>::~typedFile()
{
    this->close();
}

template <class T, const unsigned int MIN_DEGREE>
bool typedFile<T, MIN_DEGREE>::open(const string name, const string type, const unsigned int ver, ios::openmode openmode)
{
    fstream::open(name.c_str(), openmode);
    //Abertura do arquivo com ios:out , nos valores default.
    if (!this->isOpen() && ver == MIN_DEGREE)
    {
        fstream::open(name.c_str(), ios::out);
        fstream::close();
        fstream::open(name.c_str(), openmode);
        this->head.setType(type);
        this->head.setFirstDeleted(0);
        this->head.setFirstValid(0);
        this->head.setVersion(ver);
        this->fixHeader(this->head);
        // Insere nova raiz vazia.

        record<T, MIN_DEGREE> recentRoot;
        insertRoot(recentRoot);
        return true;
    }
    else
    {
        // Se o header já existir, ele é carregado na memória.
        this->examineHeader(this->head);
        // É verificado se o grau da Árvore B, os tipos e as versões são idênticas às informadas.
        if(type == this->head.getType() && ver == this->head.getVersion() && MIN_DEGREE == ver)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}



template <class T, const unsigned int MIN_DEGREE>
bool typedFile<T, MIN_DEGREE>::close()
{
    fstream::close();
    return true;
}

template <class T, const unsigned int MIN_DEGREE>
bool typedFile<T, MIN_DEGREE>::isOpen()
{
    return fstream::is_open();
}

template <class T, const unsigned int MIN_DEGREE>
void typedFile<T, MIN_DEGREE>::clear()
{
    fstream::clear();
}

template <class T, const unsigned int MIN_DEGREE>
bool typedFile<T, MIN_DEGREE>::examineRecord(record<T, MIN_DEGREE> &rec, unsigned long long int i)
{
    char *aux = new char[rec.size()];
    this->clear();
    //A cabeça da leitura é posicionada referente ao i a partir do começo, e é lido até os bytes.
    fstream::seekg(this->index2pos(i), ios::beg);
    fstream::read(aux, rec.size());

    //É efetuado o cast nessa implementação.
    string serializedRecord = string(aux,rec.size());
    //As informações são inseridas no record rec.
    rec.fromString(serializedRecord);
    //O ponteiro aux é deletado e logo depois apontado para null.
    delete[] aux;
    aux = nullptr;
    return true;
}

template <class T, const unsigned int MIN_DEGREE>
bool typedFile<T, MIN_DEGREE>::fixRecord(record<T, MIN_DEGREE> &rec, unsigned long long int i)
{
    this->clear();
    //A cabeça da escrita é inserida na posição i desde o início.
    fstream::seekp(this->index2pos(i), ios::beg);
    //O record rec rec.size() bytes é escrito no arquivo.
    fstream::write(rec.toString().c_str(), rec.size());
    return true;
}

template <class T, const unsigned int MIN_DEGREE>
bool typedFile<T, MIN_DEGREE>::insertRoot(record<T, MIN_DEGREE> &rec)
{
    //Verifica se tem algum record deletado.
    if(this->head.getFirstDeleted() != 0)
    {
        //O idx do record é encadeado.
        unsigned long long int idx = this->head.getFirstDeleted();
        record<T, MIN_DEGREE> recentRoot;
        //Verifica se foi possível ler o record.
        if(this->examineRecord(recentRoot,idx))
        {
            /* O header é inserido no próximo record deletado, e o próximo válido na
               Árvore B, e assim, o próximo válido sempre será a raiz.
            */
            this->head.setFirstDeleted(recentRoot.getSuccessor());
            //O record aqui é inserido.
            recentRoot = rec;
            recentRoot.setSuccessor(this->head.getFirstValid());
            //O novo primeiro válido é salvo e também é salvo no head e record.
            this->head.setFirstValid(idx);
            this->fixRecord(recentRoot,idx);
            this->fixHeader(this->head);
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        //Verifica caso não há arquivos deletados.
        unsigned long long int pos;
        //A cabeça da gravação é posicionada na última posição do arquivo.
        seekp(0,ios::end);
        pos = fstream::tellp();
        //O próximo do record é inserido. --árvore b.
        rec.setSuccessor(this->head.getFirstValid());
        //O próximo é inserido no head.
        this->head.setFirstValid(this->plc2idx(pos));
        //O head e o record são salvos.
        this->fixHeader(this->head);
        this->fixRecord(rec,this->plc2idx(pos));
        return true;
    }
}

template <class T, const unsigned int MIN_DEGREE>
unsigned long long int typedFile<T, MIN_DEGREE>::holdFirstDel()
{
    return this->head.getFirstDeleted();
}

template <class T, const unsigned int MIN_DEGREE>
unsigned long long int typedFile<T, MIN_DEGREE>::getFirstValid()
{
    return this->head.getFirstValid();
}
template <class T, const unsigned int MIN_DEGREE>
unsigned long long int typedFile<T, MIN_DEGREE>::search(T data)
{
    unsigned long long int idx = this->getFirstValid();
    //Essa implementação também é apenas para o arquivo typedfile.
    while(fstream::good() && idx != 0)
    {
        record<T, MIN_DEGREE> aux;
        this->examineRecord(aux,idx);
        if(data == aux.getData())
        {
            return idx;
        }
        idx = aux.getSuccessor();
    }
    return 0;
}

template <class T, const unsigned int MIN_DEGREE>
bool typedFile<T, MIN_DEGREE>::delRecord(unsigned long long int i)
{
    //Essa implementação é apenas para o arquivo typedfile.
    unsigned long long int idx = this->getFirstValid();
    unsigned long long int leftResident = 0;
    record<T, MIN_DEGREE> aux;

    if(i != idx)
    {
        while(fstream::good() && idx != 0)
        {
            this->examineRecord(aux,idx);
            if(i == aux.getSuccessor())
            {
                leftResident = idx;
                return delRR(leftResident);
            }
            leftResident = idx;
            idx = aux.getSuccessor();
        }
        return false;
    }
    else
    {
        this->examineRecord(aux,idx);
        return delAsk(idx);;
    }
}

template <class T, const unsigned int MIN_DEGREE>
bool typedFile<T, MIN_DEGREE>::examineHeader(header &h)
{

    char *aux = new char[this->head.size()];
    this->clear();
    //O header é carregado para a memória na posição 0.
    fstream::seekg(0, ios::beg);
    fstream::read(aux, this->head.size());
    string serializedHeader = string(aux, this->head.size());
    //O fromString do head é convocado para execução.
    this->head.fromString(serializedHeader);
    //O ponteiro aux é deletado.
    delete[] aux;
    aux = nullptr;
    return true;
}

template <class T, const unsigned int MIN_DEGREE>
bool typedFile<T, MIN_DEGREE>::fixHeader(header &h)
{
    //O header é escrito da posição 0 até h.size() na memória.
    this->clear();
    fstream::seekp(0, ios::beg);
    fstream::write(h.toString().c_str(), h.size());
    return true;
}

template <class T, const unsigned int MIN_DEGREE>
unsigned long long int typedFile<T, MIN_DEGREE>::index2pos(unsigned long long int i)
{
    record<T, MIN_DEGREE> aux;
    //O index é modificado na posição estendida pelo fstream.
    unsigned long long int place = this->head.size() + ((i - 1) * aux.size());
    return place;
}

template <class T, const unsigned int MIN_DEGREE>
unsigned long long int typedFile<T, MIN_DEGREE>::plc2idx(unsigned long long int p)
{
    record<T, MIN_DEGREE> aux;
    //A posição é modificada em index absorvido pelo typedfile.
    unsigned long long int idx = ((p - this->head.size()) / aux.size()) + 1;
    return idx;
}

template <class T, const unsigned int MIN_DEGREE>
bool typedFile<T, MIN_DEGREE>::delRR(unsigned long long int idxRRecord)
{
    record<T, MIN_DEGREE> delRecord, residentRecord;
    unsigned long long int idxRecord;
    unsigned long long int idx1Del = this->holdFirstDel();
    //Essa implementação também é apenas para o arquivo typedfile.
    this->examineRecord(residentRecord,idxRRecord);
    idxRecord = residentRecord.getSuccessor();
    this->examineRecord(delRecord,idxRecord);

    residentRecord.setSuccessor(delRecord.getSuccessor());
    delRecord.setSuccessor(idx1Del);
    delRecord.del();
    this->head.setFirstDeleted(idxRecord);

    this->fixRecord(residentRecord,idxRRecord);
    this->fixRecord(delRecord,idxRecord);
    this->fixHeader(this->head);
    return true;

}

template <class T, const unsigned int MIN_DEGREE>
bool typedFile<T, MIN_DEGREE>::delAsk(unsigned long long int idxRecord)
{
    record<T, MIN_DEGREE> delRecord;
    unsigned long long int idx1Del = this->holdFirstDel();
    //utilizado apenas no typedfile
    this->examineRecord(delRecord,idxRecord);
    this->head.setFirstValid(delRecord.getSuccessor());
    delRecord.setSuccessor(idx1Del);
    delRecord.del();

    this->head.setFirstDeleted(idxRecord);
    this->fixRecord(delRecord,idxRecord);
    this->fixHeader(this->head);
    return true;
}

template <class T, const unsigned int MIN_DEGREE>
unsigned long long int typedFile<T, MIN_DEGREE>::lastPlace()
{
    unsigned long long int pos;

    //O index da última posição é retornado como forma de bytes do arquivo.
    seekp(0,ios::end);
    pos = fstream::tellp();
    return plc2idx(pos);
}

template <class T, const unsigned int MIN_DEGREE>
bool typedFile<T, MIN_DEGREE>::fixNode(record<T, MIN_DEGREE> &rec,unsigned long long int idx, bool isnew)
{
    if(!isnew)
    {
        //se não é um novo node, eu apenas salvo
        return this->fixRecord(rec, idx);
    }
    else
    {
        //se é um node novo, utilizo lógica do insertRoot porém, sem atualizar o firstValid
        if(this->head.getFirstDeleted() != 0)
        {
            idx = this->head.getFirstDeleted();
            record<T, MIN_DEGREE> recentRoot;
            if(this->examineRecord(recentRoot,idx))
            {
                this->head.setFirstDeleted(recentRoot.getSuccessor());
                recentRoot = rec;
                this->fixRecord(recentRoot,idx);
                this->fixHeader(this->head);
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            idx = lastPlace();
            this->fixRecord(rec,idx);
            return true;
        }
    }

}

template <class T, const unsigned int MIN_DEGREE>
void typedFile<T, MIN_DEGREE>::setFirstValid(unsigned long long int idx)
{
    head.setFirstValid(idx);
    fixHeader(this->head);
}

template <class T, const unsigned int MIN_DEGREE>
unsigned long long int typedFile<T, MIN_DEGREE>::calcIdx()
{
    //O index é calculado para o próximo record que vai ser inserido.
    if(this->head.getFirstDeleted() != 0)
    {
        //Se possuir um record apagado, retorna o index dele.
        return this->head.getFirstDeleted();
    }
    else
    {
        //Se não tiver um record apagado, retorna a posição em relação ao fim do arquivo.
        unsigned long long int pos;
        seekp(0,ios::end);
        pos = fstream::tellp();
        return plc2idx(pos);
    }

}

template <class T, const unsigned int MIN_DEGREE>
bool typedFile<T, MIN_DEGREE>::delNode(record<T, MIN_DEGREE> &rec, unsigned long long int i)
{
    //O primeiro apagado é atualizado.
    rec.setSuccessor(this->holdFirstDel());
    head.setFirstDeleted(i);
    //O header e o record são salvos.
    this->fixHeader(this->head);
    return this->fixRecord(rec,i);
}

#endif // TYPEDFILE_H
