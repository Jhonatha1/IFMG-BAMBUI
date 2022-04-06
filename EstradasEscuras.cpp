#include <iostream>
#include <list>

#define BRANCO 0  //estado inicial
#define CINZA 1   //em processamento
#define PRETO 2   //terminou

using namespace std;

class Vertice {
private:
    int i;
    int cor;
    int tempo;

public:

    int getI(){
        return i;
    }

    void setI(int n){
        i=n;
    }

    int getCor(){
        return cor;
    }

    void setCor(int n){
        cor=n;
    }

    int getTempo(){
        return tempo;
    }

    void setTempo(int n){
        tempo=n;
    }
};


class Grafo {
private:
	int numV; // n�mero de vertices
	Vertice *Vertices;
	list<Vertice*> *adj;

public:

    Grafo(){
	this->numV = 0;
    }

    Grafo(int V){
        this->numV = V;
        adj = new list<Vertice*>[V];
        Vertices = new Vertice[V];
    }

    void limpa(){
        numV=0;
        adj=NULL;
    }

    void setV(int V){
        this->numV = V;
        adj = new list<Vertice*>[V];
        Vertices = new Vertice[V];
    }

    Vertice* getVertice(int i){
        Vertice *v=&Vertices[i];
        return v;
    }

    void addVertices(){
        Vertice v;
        v.setCor(BRANCO);
        for (int i=0;i<numV;i++){
            Vertices[i]=v;
            Vertices[i].setI(i);
            Vertices[i].setTempo(1);
        }
    }

    void addAresta(int v1, Vertice *v2){
        adj[v1].push_back(v2);
    }


    bool dfs(Vertice &v){
        v.setCor(CINZA);
        list<Vertice*>::iterator it;
        for(it = adj[v.getI()].begin(); it != adj[v.getI()].end(); it++){
            if((*it)->getCor()==BRANCO){
                dfs(**it);
            }
            if((*it)->getCor()==CINZA){
                return true;

            }
            if (((*it)->getTempo()+1)>v.getTempo()){
                v.setTempo((*it)->getTempo()+1);
            }
        }
        v.setCor(PRETO);
        return false;
    }

    int respostaFinal(){
        int tempo=0;
        for (int i=0;i<numV;i++){
            if(Vertices[i].getCor()==BRANCO){
                if(!dfs(Vertices[i])){
                    if(Vertices[i].getTempo()>tempo)
                        tempo=Vertices[i].getTempo();
                }else{
                    return -1;
                }

            }
        }
        return tempo;
    }
};


int main(int argc, char *argv[])
{
    int numV=1, n,m;
    Grafo g;

    while(cin>>numV){
        g.setV(numV);
        g.addVertices();

        for(int i=1;i<=numV;i++){ //linha
            cin>>n;//quantos arquivos que i depende
            for(int j=0;j<n;j++){
                cin>>m;
                g.addAresta(m-1,g.getVertice(i-1));
            }
        }
    cout<<g.respostaFinal()<<endl;
    g.limpa();
    }
    return 0;
}
// se for copiar, muda estrutura e métodos para não tomar plágio.
