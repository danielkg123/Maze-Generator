/*
Pembuat : Fellix Allenfant
NRP : C14220039
Membuat base untuk graph
*/

#include <iostream>
#include <vector>
using namespace std;

// class edge
struct Edge
{
    int vertice;
    int weight;

    Edge(int vertice, int weight) : vertice(vertice), weight(weight) {}
};

// class graph
// memakai array list untuk menyimpan edge
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

private:
    // function untuk cek boundaries
    bool checkBound(int vertice)
    {
        return vertice < 0 || vertice >= this->vertices;
    }
};
