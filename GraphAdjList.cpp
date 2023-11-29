/*
Pembuat : Fellix Allenfant
NRP : C14220039
*/

#include <iostream>
#include <vector>
using namespace std;

struct Edge
{
    int vertice;
    int weight;

    Edge(int vertice, int weight) : vertice(vertice), weight(weight) {}
};

class GraphAdjList
{
public:
    int vertices;
    vector<vector<Edge> > adjList;
    bool isDirected;
    bool isWeighted;

    GraphAdjList() : vertices(0), isDirected(false), isWeighted(false) {}

    GraphAdjList (int numVertices, bool isDirected = false, bool isWeighted = false)
    {
        this->vertices = numVertices;
        this->adjList.resize(numVertices);
        this->isDirected = isDirected;
        this->isWeighted = isWeighted;
    }

    void addEdge(int from, int to, int weight = 1)
    {
        if (checkBound(from) || checkBound(to))
        {
            cout << "Vertices not exist" << endl;
            return;
        }

        if (!this->isWeighted)
        {
            weight = 1;
        }

        this->adjList[from].push_back(Edge(to, weight));

        if (!this->isDirected)
        {
            this->adjList[to].push_back(Edge(from, weight));
        }
    }

    void printGraph()
    {
        for (int i = 0; i < this->vertices; i++)
        {
            cout << i << ": ";
            for (const Edge neighbour : this->adjList[i])
            {
                if (this->isWeighted)
                {
                    cout << "(" << neighbour.vertice << ", " << neighbour.weight << ") ";
                }
                else
                {
                    cout << neighbour.vertice << " ";
                }
            }
            cout << endl;
        }
    }

private:
    bool checkBound(int vertice)
    {
        return vertice < 0 || vertice >= this->vertices;
    }
};
