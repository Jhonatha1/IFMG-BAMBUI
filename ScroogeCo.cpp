#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

class Grafo {
public:

	int V;
	vector<vector<pair<int, int>>> adjcent;
	Grafo(int V) {
		this->V = V;
		adjcent = vector<vector<pair<int, int>>>(V);
	}
	void Aresta(int U, int W, int K) {
		adjcent[U].push_back({W, K});
	}
	int Dijkstra(int root, int fim) {
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> aux;
		vector<int> distancia(V, 100000);
		vector<bool> ver(V, 0);
		aux.push({0, root});
		distancia[root] = 0;
		while (!aux.empty()) {
			int U = aux.top().second;
			aux.pop();
			ver[U] = 1;
			if (ver[fim]) break;
			for (const auto& W : adjcent[U]) {
				if (!ver[W.first] && distancia[U] + W.second < distancia[W.first]) {
					distancia[W.first] = distancia[U] + W.second;
					aux.push({distancia[W.first], W.first});
				}
			}
		}
		return distancia[fim];
	}

};

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	string O, D;
	int X, N, V, T, Tempo, Chave;
	while (cin >> X >> N >> V && (X || N || V)) {
		Tempo = (X<=30?17*60+30:17*60+50);
		Chave = 0;
		Grafo g(V);
		map<string, int> m;

		while (N--) {
			cin >> O >> D >> T;
			if (!m.count(O)) m[O] = Chave++;
			if (!m.count(D)) m[D] = Chave++;
			g.Aresta(m[O], m[D], T);
		}
		Tempo += g.Dijkstra(m["varzea"], m["alto"]);
		cout << Tempo/60 << ":" << setfill('0') << setw(2) << Tempo%60 << endl;
		if (Tempo <= 18*60) cout << "Nao ira se atrasar\n";
		else cout << "Ira se atrasar\n";
	}
	return 0;
}
// se for copiar muda a estrutura e os métodos, se não toma plágio.
