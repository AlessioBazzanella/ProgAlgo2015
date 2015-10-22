#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef vector< vector<int> > Grafo;

int main(int argc, char **argv) {
	// ====================== RIGA 1 ======================
	// Variabili riga 1
	int nodi, archi, entrate_n, poteri;
	
	// Lettura variabili riga 1
	ifstream in("input0.txt");
	in >> nodi >> archi >> entrate_n >> poteri;
	
	// ====================== RIGA 2 ======================
	// Variabili riga 2
	vector<int> entrate;
	vector<int> entrate_contatore;
	
	// Lettura variabili riga 2
	int temp;
	for (int i = 0; i < entrate_n; i++) {
		in >> temp;
		entrate.push_back(temp);
	}
	
	/* STAMPA VETTORE
	for (int i=0; i<entrate.size();i++){
		cout << entrate[i] << endl;
	}
	 */
	
	
	// ==================== RESTO RIGHE ===================
	// Creazione grafo
	Grafo graph;
	int inizio, arrivo, peso;
	for(int i = 0; i < archi; i++) {
		in >> inizio >> arrivo >> peso;
		graph.push_back(vector<int>());
		graph[i].push_back(inizio);
		graph[i].push_back(arrivo);
		graph[i].push_back(peso);
		
		// Controllo
		for (int j = 0; j < entrate.size(); j++) {
			if (graph[i][0] == entrate[j]) {
				
			}
		}
	}
	
	/* STAMPA GRAFO
	for (int i=0; i<graph.size();i++) {
		for (int j=0; j < graph[i].size(); j++) {
			cout << graph[i][j];
		}
		cout << endl;
	}
	 */
	
	
	// CASO BASE:
	// Verificare se arrivo == N-1 e non ci sono tranelli
	
	//ofstream out("output0.txt");
	//out << nodi << archi << entrate_n << poteri << endl;
	
	
	return 0;
}