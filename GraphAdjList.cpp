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
// memakai array list untuk menyimpan edge jok guyon
class GraphAdjList
{
public:
    int vertices;                 // jumlah verticle
    vector<vector<Edge> > adjList; // tempat menyimpan vertice
    bool isDirected;              // menandakan graph directed atau undirected
    bool isWeighted;              // menandakan graph weighted atau unweighted
    bool isFound = false;
    bool isPlayed = false;

    // default constructor
    GraphAdjList() : vertices(0), isDirected(false), isWeighted(false) {}

    // destructor
    ~GraphAdjList()
    {
        for (int i = 0; i < this->vertices; i++)
        {
            this->adjList[i].clear();
        }
        this->adjList.clear();
    }

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
    void findShortestPath(int startVertex, int endVertex) {
        if (isFound && isPlayed) {
            return;
        } else {
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
        isFound = true;
        isPlayed = true;
    }
    }

    /*
    * Fungsi untuk menampilkan path yang dipilih user
    * Pembuat : Alexander Yofilio Setiawan
    * NRP : C14220071
    * Mengisi path yang dipilih user dengan karakter yang sesuai dengan arahnya, dan diberi warna
    */
    string** fillPath (string** displayPath, int posX, int posY, char c, int reach = 0){
        int realX = (posX * 3) + 2;
        int realY = (posY * 5) + 3;

        switch (c) {
            case '^':
                if(displayPath[realX + 1][realY] == " "){
                    displayPath[realX + 1][realY] = "\033[1;32m^\033[0m";
                    displayPath[realX + 2][realY] = "\033[1;32m^\033[0m";
                    displayPath[realX + 3][realY] = "\033[1;32m*\033[0m";
                } else if (displayPath[realX + 1][realY] == "\033[1;32mv\033[0m") {
                    displayPath[realX + 1][realY] = ' ';
                    displayPath[realX + 2][realY] = ' ';
                    displayPath[realX + 3][realY] = '.';
                }

                if (reach == 0) {
                displayPath[realX][realY] = "\033[1;31mP\033[0m";
                } else {
                    displayPath[realX][realY] = "\033[1;31mE\033[0m";
                    displayPath[realX + 1][realY] = "\033[1;32m^\033[0m";
                    displayPath[realX + 2][realY] = "\033[1;32m^\033[0m";
                    displayPath[realX + 3][realY] = "\033[1;32m*\033[0m";
                }

            break;

            case 'v':
                if(displayPath[realX - 1][realY] == " "){
                    displayPath[realX - 1][realY] = "\033[1;32mv\033[0m";
                    displayPath[realX - 2][realY] = "\033[1;32mv\033[0m";
                    displayPath[realX - 3][realY] = "\033[1;32m*\033[0m";
                } else if (displayPath[realX - 1][realY] == "\033[1;32m^\033[0m") {
                    displayPath[realX - 1][realY] = ' ';
                    displayPath[realX - 2][realY] = ' ';
                    displayPath[realX - 3][realY] = '.';
                }

                if (reach == 0) {
                displayPath[realX][realY] = "\033[1;31mP\033[0m";
                } else {
                    displayPath[realX][realY] = "\033[1;31mE\033[0m";
                    displayPath[realX - 1][realY] = "\033[1;32mv\033[0m";
                    displayPath[realX - 2][realY] = "\033[1;32mv\033[0m";
                    displayPath[realX - 3][realY] = "\033[1;32mv\033[0m";
                }
            break;

            case '<':
                if(displayPath[realX][realY + 1] == " "){
                    displayPath[realX][realY + 1] = "\033[1;32m<\033[0m";
                    displayPath[realX][realY + 2] = "\033[1;32m<\033[0m";
                    displayPath[realX][realY + 3] = "\033[1;32m<\033[0m";
                    displayPath[realX][realY + 4] = "\033[1;32m<\033[0m";
                    displayPath[realX][realY + 5] = "\033[1;32m*\033[0m";
                } else if (displayPath[realX][realY + 1] == "\033[1;32m>\033[0m") {
                    displayPath[realX][realY + 1] = ' ';
                    displayPath[realX][realY + 2] = ' ';
                    displayPath[realX][realY + 3] = ' ';
                    displayPath[realX][realY + 4] = ' ';
                    displayPath[realX][realY + 5] = '.';
                }

                if (reach == 0) {
                displayPath[realX][realY] = "\033[1;31mP\033[0m";
                } else {
                    displayPath[realX][realY] = "\033[1;31mE\033[0m";
                    displayPath[realX][realY + 1] = "\033[1;32m<\033[0m";
                    displayPath[realX][realY + 2] = "\033[1;32m<\033[0m";
                    displayPath[realX][realY + 3] = "\033[1;32m<\033[0m";
                    displayPath[realX][realY + 4] = "\033[1;32m<\033[0m";
                    displayPath[realX][realY + 5] = "\033[1;32m*\033[0m";
                }
            break;

            case '>':
                if(displayPath[realX][realY - 1] == " "){
                    displayPath[realX][realY - 1] = "\033[1;32m>\033[0m";
                    displayPath[realX][realY - 2] = "\033[1;32m>\033[0m";
                    displayPath[realX][realY - 3] = "\033[1;32m>\033[0m";
                    displayPath[realX][realY - 4] = "\033[1;32m>\033[0m";
                    displayPath[realX][realY - 5] = "\033[1;32m*\033[0m";
                } else if (displayPath[realX][realY - 1] == "\033[1;32m<\033[0m") {
                    displayPath[realX][realY - 1] = ' ';
                    displayPath[realX][realY - 2] = ' ';
                    displayPath[realX][realY - 3] = ' ';
                    displayPath[realX][realY - 4] = ' ';
                    displayPath[realX][realY - 5] = '.';
                }

                if (reach == 0) {
                displayPath[realX][realY] = "\033[1;31mP\033[0m";
                } else {
                    displayPath[realX][realY] = "\033[1;31m>E033[0m";
                    displayPath[realX][realY - 1] = "\033[1;32m>\033[0m";
                    displayPath[realX][realY - 2] = "\033[1;32m>\033[0m";
                    displayPath[realX][realY - 3] = "\033[1;32m>\033[0m";
                    displayPath[realX][realY - 4] = "\033[1;32m>\033[0m";
                    displayPath[realX][realY - 5] = "\033[1;32m*\033[0m";
                }
            break;

            case 'P':
                displayPath[realX][realY] = "\033[1;31mP\033[0m";
            break;

            case 'E':
                displayPath[realX][realY] = "\033[1;31mE\033[0m";
            break;
        }
        return displayPath;
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
