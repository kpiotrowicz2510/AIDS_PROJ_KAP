// A C / C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph

#include <stdio.h>
#include <limits.h>
#include <iostream>
#include <vector>

using namespace std;
// Number of vertices in the graph
#define V 4

class Node {
public:
	int value;
	int* connections;
	int id;
	bool connected;
	bool bridge;
	Node() {
		this->value = 0;
		this->connected = false;
		this->connections = new int[100];
		for (int i = 0; i < 10; i++) {
			this->connections[i] = 0;
		}
	}
	Node(int max) {
		this->value = 0;
		this->connections = new int[max];
		for (int i = 0; i < max; i++) {
			this->connections[i] = 0;
		}
	}
	void addConnection(int id, int value) {
		this->connected = true;
		this->connections[id] = value;
	}
};
vector<Node*> crossings;
// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[], int max)
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < max; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

// A utility function to print the constructed distance array
void printSolution(int dist[], int n, int max)
{
	printf("%i", dist[max - 1]);
}

// Funtion that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int** graph, int src, int max)
{
	int* dist = new int[max];     // The output array.  dist[i] will hold the shortest
								  // distance from src to i

	bool *sptSet = new bool[max]; // sptSet[i] will true if vertex i is included in shortest
								  // path tree or shortest distance from src to i is finalized

								  // Initialize all distances as INFINITE and stpSet[] as false
	for (int i = 0; i < max; i++)
		dist[i] = INT_MAX, sptSet[i] = false;

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < max - 1; count++)
	{
		// Pick the minimum distance vertex from the set of vertices not
		// yet processed. u is always equal to src in first iteration.
		int u = minDistance(dist, sptSet, max);

		// Mark the picked vertex as processed
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the picked vertex.
		for (int v = 0; v < max; v++)

			// Update dist[v] only if is not in sptSet, there is an edge from 
			// u to v, and total weight of path from src to  v through u is 
			// smaller than current value of dist[v]
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
				&& dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
	}

	// print the constructed distance array
	printSolution(dist, max, max);
}

// driver program to test above function
int main()
{
	int crossingNumber, wayNumber;
	cin >> crossingNumber >> wayNumber;
	if (crossingNumber > wayNumber) {
		cout << "#" << endl;
		return 0;
	}
	for (int i = 0; i < wayNumber; i++) {
		crossings.push_back(new Node());
	}
	for (int i = 0; i < wayNumber; i++) {
		int start, stop, num;
		cin >> start >> stop >> num;
		Node * a = new Node(crossingNumber);
		a->id = start;
		a->addConnection(stop, num);
		//crossings[a->id] = a;
		if (crossings[a->id]->connected == true) {
			crossings[a->id]->addConnection(stop, num);
		}
		else {
			crossings[a->id] = a;
		}
		a = new Node(crossingNumber);
		a->id = stop;
		a->addConnection(start, num);
		if (crossings[a->id]->connected == true) {
			crossings[a->id]->addConnection(start, num);
		}
		else {
			crossings[a->id] = a;
		}
	}
	int **graph = new int*[crossingNumber];
	for (int i = 0; i < crossingNumber; i++) {
		Node* a = crossings[i];
		graph[a->id] = new int[wayNumber];

		for (int j = 0; j < wayNumber; j++) {
			graph[a->id][j] = a->connections[j];
		}
	}
	/* Let us create the example graph discussed above */
	/*int graph[V][V] = {
	{ 0, 4, 0, 0, 0, 0, 0, 8, 0 },
	{ 4, 0, 8, 0, 0, 0, 0, 11, 0 },
	{ 0, 8, 0, 7, 0, 4, 0, 0, 2 },
	{ 0, 0, 7, 0, 9, 14, 0, 0, 0 },
	{ 0, 0, 0, 9, 0, 10, 0, 0, 0 },
	{ 0, 0, 4, 0, 10, 0, 2, 0, 0 },
	{ 0, 0, 0, 14, 0, 2, 0, 1, 6 },
	{ 8, 11, 0, 0, 0, 0, 1, 0, 7 },
	{ 0, 0, 2, 0, 0, 0, 6, 7, 0 }
	};*/
	/*for (int i = 0; i < crossingNumber; i++) {
	Node* a = crossings[i];
	for (int j = 0; j < wayNumber; j++) {
	cout << a->connections[j];
	}
	cout << endl;
	}*/


	dijkstra(graph, 0, crossingNumber);

	return 0;
}