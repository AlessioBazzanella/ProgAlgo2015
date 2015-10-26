// A C++ program to find single source shortest paths for Directed Acyclic Graphs
#include <iostream>
#include <fstream>
#include <list>
#include <stack>
#include <vector>

#define INF INT_MAX
#define NINF INT_MIN
using namespace std;

// Graph is represented using adjacency list. Every node of adjacency list
// contains vertex number of the vertex to which edge connects. It also
// contains weight of the edge
class AdjListNode
{
	int v;
	int weight;
public:
	AdjListNode(int _v, int _w)  { v = _v;  weight = _w;}
	int getV()       {  return v;  }
	int getWeight()  {  return weight; }
};

// Class to represent a graph using adjacency list representation
class Graph
{
	int V;    // No. of vertices'
	
	// Pointer to an array containing adjacency lists
	list<AdjListNode> *adj;
	
	// A function used by shortestPath
	void topologicalSortUtil(int v, bool visited[], stack<int> &Stack);
public:
	Graph(int V);   // Constructor
	
	// function to add an edge to graph
	void addEdge(int u, int v, int weight);
	
	// Finds shortest paths from given source vertex
	void shortestPath(int s, int d, int p);
	
	// Finds longest paths from given source vertex
	void longestPath(int s, int d, int p);
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<AdjListNode>[V];
}

void Graph::addEdge(int u, int v, int weight)
{
	AdjListNode node(v, weight);
	adj[u].push_back(node); // Add v to u's list
}

// A recursive function used by shortestPath. See below link for details
// http://www.geeksforgeeks.org/topological-sorting/
void Graph::topologicalSortUtil(int v, bool visited[], stack<int> &Stack)
{
	// Mark the current node as visited
	visited[v] = true;
	
	// Recur for all the vertices adjacent to this vertex
	list<AdjListNode>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
	{
		AdjListNode node = *i;
		if (!visited[node.getV()])
			topologicalSortUtil(node.getV(), visited, Stack);
	}
	
	// Push current vertex to stack which stores topological sort
	Stack.push(v);
}

// The function to find shortest paths from given vertex. It uses recursive
// topologicalSortUtil() to get topological sorting of given graph.
void Graph::shortestPath(int s, int d, int p)
{
	stack<int> Stack;
	int dist[V];
	
	// Mark all the vertices as not visited
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;
	
	// Call the recursive helper function to store Topological Sort
	// starting from all vertices one by one
	for (int i = 0; i < V; i++)
		if (visited[i] == false)
			topologicalSortUtil(i, visited, Stack);
	
	// Initialize distances to all vertices as infinite and distance
	// to source as 0
	for (int i = 0; i < V; i++)
		dist[i] = INF;
	dist[s] = 0;
	
	// Process vertices in topological order
	while (Stack.empty() == false)
	{
		// Get the next vertex from topological order
		int u = Stack.top();
		Stack.pop();
		
		// Update distances of all adjacent vertices
		list<AdjListNode>::iterator i;
		if (dist[u] != INF)
		{
			for (i = adj[u].begin(); i != adj[u].end(); ++i) {
				if (s == i->getV()) {
					cout << " (CICLO) ";
				}
				if (dist[i->getV()] > dist[u] + i->getWeight()) {
					dist[i->getV()] = dist[u] + i->getWeight();
				}
			}
		}
	}
	
	// Print the calculated shortest distances
	(dist[d] == INF)? cout << "INF ": cout << dist[d] << " ";
}

// The function to find longest distances from a given vertex. It uses
// recursive topologicalSortUtil() to get topological sorting.
void Graph::longestPath(int s, int d, int p)
{
	stack<int> Stack;
	int dist[V];
	
	// Mark all the vertices as not visited
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;
	
	// Call the recursive helper function to store Topological Sort
	// starting from all vertices one by one
	for (int i = 0; i < V; i++)
		if (visited[i] == false)
			topologicalSortUtil(i, visited, Stack);
	
	// Initialize distances to all vertices as infinite and distance
	// to source as 0
	for (int i = 0; i < V; i++)
		dist[i] = NINF;
	dist[s] = 0;
	
	// Process vertices in topological order
	while (Stack.empty() == false)
	{
		// Get the next vertex from topological order
		int u = Stack.top();
		Stack.pop();
		
		// Update distances of all adjacent vertices
		list<AdjListNode>::iterator i;
		if (dist[u] != NINF)
		{
			for (i = adj[u].begin(); i != adj[u].end(); ++i) {
				if (s == i->getV()) {
					cout << " (CICLO) ";
				}
				if (dist[i->getV()] < dist[u] + i->getWeight()) {
					dist[i->getV()] = dist[u] + i->getWeight();
				}
			}
		}
	}
	
	// Print the calculated longest distances
	(dist[d] == NINF)? cout << "INF ": cout << dist[d] << " ";
}

// Driver program to test above functions
int main()
{
	
	ifstream in("input0.txt");
	// Variabili riga 1
	int nodi, archi, entrate_n, poteri;
	in >> nodi >> archi >> entrate_n >> poteri;
	
	// Variabili riga 2
	vector<int> entrate;
	// Lettura variabili riga 2
	int temp;
	for (int i = 0; i < entrate_n; i++) {
		in >> temp;
		entrate.push_back(temp);
	}
	
	Graph g(nodi);
	
	int partenza, arrivo, peso;
	for (int i = 0; i < archi; i++) {
		in >> partenza >> arrivo >> peso;
		g.addEdge(partenza, arrivo, peso);
	}
	
	for (int i = 0; i < entrate.size(); i++) {
		cout << "Following are shortest distances from source " << entrate[i] << ": ";
		g.shortestPath(entrate[i], nodi-1, poteri);
		cout << endl;
		
		cout << "Following are longest distances from source " << entrate[i] << ": ";
		g.longestPath(entrate[i], nodi-1, poteri);
		cout << endl << endl;
	}
	
	return 0;
}
