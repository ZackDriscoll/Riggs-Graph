//Riggs_Graph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Here you also create the nodes and edges that will make up the graph to navigate.
//This automatically includes the pch header in case you add anything extra to the solution/project.

#include "pch.h"
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

//This is the structure that will make up the edges used in the graph
struct Edge 
{
	int src, dest;
};

//Graph class
class Graph
{
public:
	//Construct a vector of vectors to represent an adjacency list
	vector<vector<int>> adjList;

	//Stores indegree of a vertex
	//Indegree acts similar to an index for this graph
	vector<int> indegree;

	//Graph Constructor
	Graph(vector<Edge> const &edges, int N)
	{
		//N is not initialized on start, so you create the size here.
		adjList.resize(N);

		//Initialize indegree
		vector<int> temp(N, 0);
		indegree = temp;

		//Add edges to the directed graph
		for (auto &edge : edges)
		{
			//Insert edge destination at the end
			adjList[edge.src].push_back(edge.dest);

			//Increment indegree of destination vertex by 1
			indegree[edge.dest]++;
		}
	}
};

//Print adjacency list representation of graph
void printGraph(Graph const& graph, int N)
{
	//Use a for loop to make sure you go through the whole graph
	for (int i = 0; i < N; i++)
	{
		//Print current vertex number with and arrow for pointing at the next destination
		cout << i << " --> ";

		//Print all neighboring vertices of vertex i with spacing
		for (int v : graph.adjList[i])
		{
			cout << v << " ";
		}
		cout << endl;
	}
}

//DFS stands for Depth First Search
void DFS(Graph const &graph, int v, vector<bool> &discovered) 
{
	
	//Mark the current node as discovered
	discovered[v] = true;

	//Print current node
	cout << v << " ";

	//Go through each edge and check if it is discovered
	//If it isn't, mark it as discovered
	for (int u : graph.adjList[v]) 
	{
		// If u is not discovered
		if (!discovered[u]) 
		{
			DFS(graph, u, discovered);
		}
	}
}

//BFS stands for Breadth First Search
void BFS(Graph const &graph, int v, vector<bool> &discovered) 
{

	//Create a queue used to do BFS
	queue<int> q;

	//Mark source vertex as discovered
	discovered[v] = true;

	//Push the source vertex into the queue
	q.push(v);

	//As long as the queue isn't empty do this
	while (!q.empty()) 
	{
		
		//Pop front node from queue and print it
		v = q.front();
		q.pop();
		cout << v << " ";

		//Go through each edge and check if it is discovered
		//If it isn't, mark it as discovered
		for (int u : graph.adjList[v]) 
		{
			if (!discovered[u]) 
			{

				//Mark it as discovered and push it into queue
				discovered[u] = true;
				q.push(u);
			}
		}

	}
}

//Performs Topological Sort on a given DAG
bool doTopologicalSort(Graph const &graph, vector<int> &L, int N)
{
	//Update the indegree
	vector<int> indegree = graph.indegree;

	//Set of all nodes with no incoming edges
	vector<int> S;
	for (int i = 0; i < N; i++) 
	{
		if (!indegree[i]) 
		{
			S.push_back(i);
		}
	}

	//As long as S has values in it do this
	while (!S.empty())
	{
		//Remove node n from S
		int n = S.back();
		S.pop_back();

		//Add n to tail of L
		L.push_back(n);

		for (int m : graph.adjList[n])
		{
			//Remove edge from n to m from the graph
			indegree[m] -= 1;

			//If m has no other incoming edges then insert m into S
			if (!indegree[m]) 
			{
				S.push_back(m);
			}
		}
	}

	//The graph will have at least one cycle as long as it has edges
	for (int i = 0; i < N; i++) 
	{
		if (indegree[i]) 
		{
			return false;
		}
	}

	return true;
}


//Graph Implementation using STL
int main()
{
	//Create a vector to store all of the edges that are defined here
	vector<Edge> edges =
	{
		{ 0, 1 }, { 18, 2 }, { 15, 0 }, { 1, 2 },
		{ 15, 2 }, { 4, 5 }, { 10, 4 }, { 19, 4 },
		{ 13, 14 }, { 7, 2 }, { 17, 7 }, { 5, 14 },
		{ 16, 13 }, { 11, 15 }, { 12, 16 }, { 15, 10 },
		{ 8, 10 }, { 6, 3 }, { 15, 19 }, { 2, 19 }
	};

	//Variable to determine the number of nodes in the graph
	int N = 20;

	//Construct the graph
	Graph graph(edges, N);

	//Print adjacency list representation of graph
	printGraph(graph, N);

	//Pause so the user can see the graph
	system("pause");

	//Option to utilize/call the DFS created above
	//Commented out for the time being to use the BFS instead
	/*
	// Stores whether or not a vertex is discovered
	vector<bool> discovered(N);

	// Do DFS traversal on all undiscovered components
	for (int i = 0; i < N; i++) 
	{
		if (discovered[i] == false) 
		{
			DFS(graph, i, discovered);
		}
	}
	cout << endl;
	system("pause"); // Pause to see the Depth First Search
	*/

	//Vertex to store whether they are discovered or not
	vector<bool> discovered(N, false);

	//Do BFS traversal on all undiscovered nodes and edges
	for (int i = 0; i < N; i++) 
	{
		if (discovered[i] == false) 
		{
			BFS(graph, i, discovered);
		}
	}
	cout << endl;
	system("pause");
	

	//Empty list that will contain the sorted elements
	vector<int> L;

	//Call the Topological Sort
	if (doTopologicalSort(graph, L, N))
	{
		//Print in topological order
		for (int i : L)
		{
			cout << i << " "; cout << i << " ";
		}
	}
	else 
	{
		cout << "Graph has at least one cycle. "
			"Topological sorting is not possible";
	}


	return 0;
}