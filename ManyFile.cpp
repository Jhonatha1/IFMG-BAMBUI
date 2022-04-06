#include <iostream>
#include <list>
#define GREYz 1  //PRIMEIRO COMEÇA.
#define PINKz 2  //SEGUNDO EM ANDAMENTO.
#define BLUEz 3  //TERCEIRO TERMINOU.
using namespace std;

class Division {
private:
    int z;
    int color;
    int time;

public:
void setAuxZ(int p){
    z=p;
}
int getZ(){
    return z;
}
int getColor(){
    return color;
}
void setColor(int c){
    color=c;
}
void seTime(int t){
    time=t;
}
int geTime(){
    return time;
}

};
class Graph {
public:
Graph(){
this->numD = 0;
    }

Graph(int D){
    this->numD = D;
    prox = new list<Division*>[D];
    ridges = new Division[D];
}
void clear(){
    numD=0;
    prox=NULL;
}
void setE(int V){
    this->numD = V;
    prox = new list<Division*>[V];
    ridges = new Division[V];
}
    Division* getDivision(int i){
    Division *d=&ridges[i];
        return d;
    }
void addRidges(){
    Division d;
    d.setColor(GREYz);
        for (int x=0;x<numD;x++){
            ridges[x]=d;
            ridges[x].setAuxZ(x);
            ridges[x].seTime(1);
        }
}
void addEdge(int rdg1, Division *rdg2){
    prox[rdg1].push_back(rdg2);
}
bool DFS(Division &d){
    list<Division*>::iterator itr;
    d.setColor(PINKz);
        for(itr = prox[d.getZ()].begin(); itr != prox[d.getZ()].end(); itr++){
            if((*itr)->getColor()==GREYz){
                DFS(**itr);
            }
                if((*itr)->getColor()==PINKz){
                return true;
                }
                if (((*itr)->geTime()+1)>d.geTime()){
                d.seTime((*itr)->geTime()+1);
            }
        }
            d.setColor(BLUEz);
        return false;
    }
int resp(){
        int time=0;
        for (int x=0;x<numD;x++){
            if(ridges[x].getColor()==GREYz){
                if(!DFS(ridges[x])){
                    if(ridges[x].geTime()>time)
                        time=ridges[x].geTime();
                }else{
                    return -1;
                }
            }
        }
        return time;
    }
private:
int numD; //numD = NÚMERO DE DIVISÕES
Division *ridges;
list<Division*> *prox;
};

int main(int argd, char *argr[])
{
int numD=1, n,m;
Graph auxG;
while(cin>>numD){
    auxG.setE(numD);
    auxG.addRidges();
    for(int x=1;x<=numD;x++){
        cin>>n;
            for(int z=0;z<n;z++){
                cin>>m;
                auxG.addEdge(m-1,auxG.getDivision(x-1));
            }
        }
    cout<<auxG.resp()<<endl;
    auxG.clear();
    }
    return 0;
}
// se for copiar, muda estrutura e métodos para não tomar plágio.
