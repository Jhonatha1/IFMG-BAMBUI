#include <iostream>
#include <list>
#include <queue>

#define BRANCO 0  //quarto n�o explorado
#define PRETO 1   //quarto explorado
#define VERMELHO 2//cheguei na porta, mas n�o tenho a chave
#define CINZA 3   //ainda explorarei este quarto

using namespace std;

class Quarto{
private:
    int id;
    int cor;
    list<int> chaves;
    bool open;
    int idQuartoAnterior; //ser� usada apenas em caso de encontrar quartos fechados

public:

    int getId(){return id;}

    void setId(int n){id=n;}

    int getCor(){return cor;}

    void setCor(int n){cor=n;}

    list<int> getChaves(){return chaves;}

    void addChave(int n){chaves.push_back(n);}

    bool getOpen(){return open;}

    void setOpen(bool n){open=n;}

    void setAnt(int v){idQuartoAnterior=v;}

    int getAnt(){return idQuartoAnterior;}

};

class Castelo{
private:
    int numQ; // n�mero de quartos
	Quarto *Quartos;
    list<Quarto*> *corredores;
    int numQuartosRestantes;

public:
    void limpa(){
        numQ=0;
        corredores=NULL;
    }

    void setNQ(int V){
        this->numQ = V;
        corredores = new list<Quarto*>[V];
        Quartos = new Quarto[V];
    }

    int getNQ(){return numQ;}

    Quarto* getQuarto(int i){
        Quarto *v=&Quartos[i];
        return v;
    }

    void addQuartos(){
        Quarto v;
        v.setCor(BRANCO);
        v.setAnt(-1);
        for (int i=0;i<numQ;i++){
            Quartos[i]=v;
            Quartos[i].setId(i);
            Quartos[i].setOpen(false);
        }
        numQuartosRestantes=numQ;
    }

    void addCorredor(int v1, Quarto *v2){
        corredores[v1].push_back(v2);
    }

    void abrePortas(queue<Quarto*> &Q, Quarto *q){ //abre as portas com as chaves encontradas no quarto e, caso o quarto j� foi encontrado, explora ele
        list<int> chaves=q->getChaves();
        for(list<int>::iterator it2=chaves.begin(); it2!=chaves.end();it2++){
            Quartos[*it2].setOpen(true);
            if(Quartos[*it2].getCor()==VERMELHO){
                Q.push((&Quartos[Quartos[*it2].getAnt()])); //coloca o quarto irmao do vermelho para ser reexplorado
                numQuartosRestantes++; //como o quarto ser� reexplorado, aumenta um nos quartos restantes
                Quartos[*it2].setCor(BRANCO); //quarto vermelho torna-se branco novamente
            }
        }
    }

    int percorreQuartos(Quarto &q){
        queue<Quarto*> f;

        f.push(&q);

        Quarto *x;

        while(!f.empty()){
            x=f.front();
            f.pop();
            abrePortas(f,x);

            for(list<Quarto*>::iterator it = corredores[x->getId()].begin(); it != corredores[x->getId()].end();it++){
                if ((*it)->getCor()==BRANCO && !(*it)->getOpen()){
                    (*it)->setCor(VERMELHO);
                    (*it)->setAnt(x->getId());
                }else if(((*it)->getCor()==BRANCO) && (*it)->getOpen()){
                    f.push(*it);
                    (*it)->setCor(CINZA);
                }
            }
            x->setCor(PRETO);
            numQuartosRestantes--;
        }
        return numQuartosRestantes;
    }
};

int main(int argc, char *argv[])
{
    int numV=1, n,m;
    string r="";
    Castelo g;
    while(cin>>numV){
        g.setNQ(numV);
        g.addQuartos();
        cin>>numV;
        for(int i=0;i<numV;i++){
            cin>>n>>m;//quantos arquivos que i depende
            g.addCorredor(n-1,g.getQuarto(m-1));
            g.addCorredor(m-1,g.getQuarto(n-1));
        }
        for(int i=1;i<g.getNQ();i++){
            cin>>n;
            g.getQuarto(n-1)->addChave(i);
        }
        if((g.percorreQuartos(*g.getQuarto(0)))==0)
            r+="sim\n";
        else
            r+="nao\n";
        g.limpa();
    }
    cout<<r;
    return 0;
}
// se for copiar, muda estrutura e métodos para não tomar plágio.
