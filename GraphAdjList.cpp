/*
Pembuat : Fellix Allenfant
NRP : C14220039
Membuat base untuk graph
*/

#include <iostream>
#include <vector>
#include<queue>
using namespace std;

// class edge
struct Edge
{
    int vertice;
    int weight;

    Edge(int vertice, int weight) : vertice(vertice), weight(weight) {}
};

// class graph
// memakai array list untuk menyimpan edge hahahaha
class GraphAdjList
{
public:
    int vertices;                 // jumlah verticle
    vector<vector<Edge> > adjList; // tempat menyimpan vertice
    bool isDirected;              // menandakan graph directed atau undirected
    bool isWeighted;              // menandakan graph weighted atau unweighted

    // defailt constructor
    GraphAdjList() : vertices(0), isDirected(false), isWeighted(false) {}

    // constructor dengan parameter
    GraphAdjList(int numVertices, bool isDirected = false, bool isWeighted = false)
    {
        this->vertices = numVertices;
        this->adjList.resize(numVertices);
        this->isDirected = isDirected;
        this->isWeighted = isWeighted;
    }

    // function menghubungkan vertice
    void addEdge(int from, int to, int weight = 1)
    {
        // cek out of bound atau tidak
        if (checkBound(from) || checkBound(to))
        {
            cout << "Vertices not exist" << endl;
            return;
        }
        
        // jika unweighted, maka otomatis bernilai 1
        if (!this->isWeighted)
        {
            weight = 1;
        }

        // tambahkan edge
        this->adjList[from].push_back(Edge(to, weight));

        // jika undirected, maka tambahkan edge sebaliknya
        if (!this->isDirected)
        {
            this->adjList[to].push_back(Edge(from, weight));
        }
    }

    // print isi graph (menampilkan semua vertice beserta edgenya)
    void printGraph()
    {
        cout << "Verticle - edges" << endl;
        for (int i = 0; i < this->vertices; i++)
        {
            cout << i << " - ";
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


    /* 
     * Fungsi find shortest path menggunakan djikstra
     * Pembuat : Girvan Witartha
     * NRP : C14220167
     * Mencari distance terpendek dari start sampai end 
     */

    // ini digunakan menyimpan path menggunakan findshortest path 
    vector<int> shortestPath;

    // mencari distance tershortest menggunakan djikstra 
    void findShortestPath(int startVertex, int endVertex)
    {
        if (startVertex < 0 || startVertex >= vertices)
        {
            cout << "Invalid start vertex\n";
            return;
        }

        vector<int> path(this->vertices, -1);
        vector<int> distance(vertices, INT_MAX);
        vector<bool> visited(vertices, false);


        distance[startVertex] = 0;

        for (int i = 0; i < vertices - 1; ++i)
        {
            int u = findMinDistanceVertex(distance, visited);

            visited[u] = true;

            for (const Edge &neighbor : adjList[u])
            {
                int v = neighbor.vertice;
                int weight = neighbor.weight;
                if (!visited[v] && distance[u] != INT_MAX && distance[u] + weight < distance[v])
                {
                    distance[v] = distance[u] + weight;
                    path[v] = u;
                }
            }
        }
        cout << "Shortest Path from vertex " << startVertex << ":\n";
        cout << "Vertex " << endVertex << ": Distance = " << distance[endVertex] << endl;
         int p = path[endVertex];
        while (p != -1)
        {
            shortestPath.push_back(p);
            p = path[p];
        }
    }
    


private:

    // function untuk cek boundaries
    bool checkBound(int vertice)
    {
        return vertice < 0 || vertice >= this->vertices;
    }
    int findMinDistanceVertex(const vector<int> &distance, const vector<bool> &visited)
    {
        int minDistance = INT_MAX;
        int minVertex = -1;

        for (int v = 0; v < vertices; ++v)
        {
            if (!visited[v] && distance[v] <= minDistance)
            {
                minDistance = distance[v];
                minVertex = v;
            }
        }

        return minVertex;
    }

    
};
