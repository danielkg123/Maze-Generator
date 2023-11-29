/*
Pembuat : Fellix Allenfant
NRP : C14220039
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "GraphAdjList.cpp"
#include "MazeDisplay.cpp"
using namespace std;

class MazeGenerator
{
public:
    GraphAdjList maze;
    int x;
    int y;
    int spawnX;
    int spawnY;
    MazeGenerator(int x = 0, int y = 0) : x(x), y(y), spawnX(0), spawnY(0), maze(x * y, false, false) {}


    void generateMaze()
    {
        cout << x << y << endl;
        // create 2D vector x * y of 0s
        vector<vector<int> > map(x, vector<int>(y, 0));

        // select random starting position
        srand(static_cast<unsigned int>(time(0)));
        spawnX = rand() % x;
        spawnY = rand() % y;

        // TODO: hapus kalau sudah selesai
        cout << "Spawn: " << spawnX << ", " << spawnY << endl;

        // save the current position
        int currentX = spawnX;
        int currentY = spawnY;

        // call recursive to create map
        recursiveMap(map, currentX, currentY);

        // TODO: hapus kalau sudah selesai
        // display map berdasarkan vertice
        cout << "Penamaan vertice dalam map" << endl;
        for (int i = 0; i < x; i++)
        {
            for (int j = 0; j < y; j++)
            {
                cout << convertVertice(i, j) << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    // Display Maze 
    // Pembuat : Daniel Kristianto Goenadi Go
    // NRP : C14220329
    // display menggunakan array2d untuk mudah di edit
    string** getDisplayMaze(){

        // Pembuatan Array setiap Node 3x3 jadi untuk display dikali 3

        string** display;
        display = new string*[x*3 +1];
        // [x*3 +1][y*3+1];

        // untuk display menggunakan array base 1 bukan dari 0 jadi mudah untuk menggunakan rumus
        for (int i = 1 ; i<= (x*3); i++){
            display[i] = new string[y*3+1];
            for(int j = 1 ; j<= (x*3); j++){
                display[i][j] = "#";
            }
        }

        for (int i = 1 ; i<= x; i++){
            for(int j = 1 ; j<= y; j++){
                display[i*3-1][j*3-1] = '.'; // rumus mengambil tengah i * 3 - 1 berlaku untuk panjang dan lebar
            }
        }

        // Penamaan vertice dalam map yang dibuat (ada di fungsi generateMaze)
        // 0 1 2 3
        // 4 5 6 7
        // 8 9 10 11
        // 12 13 14 15
        // contoh : vertice 2 ada di x = 3, y = 1



        int mazeY = 2; // 2 adalah vertice 0
        int mazeX = 2; // 2 adalah vertice 0
        int counter = 0;
        // cout << maze.vertices;
        for (int i = 0; i < maze.vertices; i++){      
            counter++;
            
            // cout << mazeY << " and " << mazeX <<  endl;
            for (const Edge neighbour : maze.adjList[i]){
                // CHECK LEFT SIDE OF NODE
                if (i-1 == neighbour.vertice){
                    display[mazeY][mazeX-1] = ' ';        
                }
                // CHECK RIGHT SIDE OF NODE
                if(i+1 == neighbour.vertice){ 
                    display[mazeY][mazeX+1] = ' ';  
                }
                // CHECK TOP SIDE OF NODE
                if(i-x == neighbour.vertice){
                    display[mazeY-1][mazeX] = ' ';  
                }
                // CHECK BOTTOM SIDE OF NODE
                if(i+x == neighbour.vertice){
                    display[mazeY+1][mazeX] = ' ';  
                }
            }


            // tambah koordinat untuk menyesuaikan
            mazeX +=3;
            if(counter%x == 0){
                mazeY+=3;
                mazeX = 2;
            }
        }
        return display;
    }

    void displayMaze(string** arr){
        for (int i = 1 ; i<= (x*3); i++){
            for(int j = 1 ; j<= (x*3); j++){
                cout<< arr[i][j];
            }
            cout << endl;
        }
    }

private:
    void recursiveMap(vector<vector<int> > &map, int currentX, int currentY)
    {
        // mark current position as visited
        map[currentX][currentY] = 1;

        // TODO: hapus kalau sudah selesai
        // display map
        for (int i = 0; i < map.size(); i++)
        {
            for (int j = 0; j < map[i].size(); j++)
            {
                if (i == currentX && j == currentY)
                    cout << "X ";
                else
                    cout << map[i][j] << " ";
            }
            cout << endl;
        }

        cout << endl;

        // loop until no neighbour left
        while (true)
        {
            // choose random neighbour
            int neighbour = chooseNeighbour(map, currentX, currentY);

            // if no neighbour left, return
            if (neighbour == 0)
                break;

            cout << "Neighbour: " << neighbour << endl;

            // if neighbour is available, create edge and call recursive
            int vertice = 0;
            if (neighbour == 1)
            {
                vertice = convertVertice(currentX - 1, currentY);
                // TODO: hapus kalau sudah selesai
                cout << "vertice : " << vertice << endl;
                maze.addEdge(convertVertice(currentX, currentY), vertice);
                recursiveMap(map, currentX - 1, currentY);
            }
            else if (neighbour == 2)
            {
                vertice = convertVertice(currentX + 1, currentY);
                // TODO: hapus kalau sudah selesai
                cout << "vertice : " << vertice << endl;
                maze.addEdge(convertVertice(currentX, currentY), vertice);
                recursiveMap(map, currentX + 1, currentY);
            }
            else if (neighbour == 3)
            {
                vertice = convertVertice(currentX, currentY - 1);
                // TODO: hapus kalau sudah selesai
                cout << "vertice : " << vertice << endl;
                maze.addEdge(convertVertice(currentX, currentY), vertice);
                recursiveMap(map, currentX, currentY - 1);
            }
            else if (neighbour == 4)
            {
                vertice = convertVertice(currentX, currentY + 1);
                // TODO: hapus kalau sudah selesai
                cout << "vertice : " << vertice << endl;
                maze.addEdge(convertVertice(currentX, currentY), vertice);
                recursiveMap(map, currentX, currentY + 1);
            }
        }
    }

    int chooseNeighbour(vector<vector<int> > &map, int currentX, int currentY)
    {
        // create vector to pick all available neighbours
        vector<int> array;
        if (!outOfBounds(map, currentX - 1, currentY) && map[currentX - 1][currentY] == 0)
            array.push_back(1);
        if (!outOfBounds(map, currentX + 1, currentY) && map[currentX + 1][currentY] == 0)
            array.push_back(2);
        if (!outOfBounds(map, currentX, currentY - 1) && map[currentX][currentY - 1] == 0)
            array.push_back(3);
        if (!outOfBounds(map, currentX, currentY + 1) && map[currentX][currentY + 1] == 0)
            array.push_back(4);

        // if no neighbour available, return 0
        if (array.size() == 0)
        {
            return 0;
        }
        else
        {
            // pick random number based on vector size
            srand(static_cast<unsigned int>(time(0)));
            int random = rand() % array.size();

            // return true if neighbour is available
            return array[random];
        }
    }

    bool outOfBounds(vector<vector<int> > &map, int currentX, int currentY)
    {
        return currentX < 0 || currentX >= x || currentY < 0 || currentY >= y;
    }

    int convertVertice(int x, int y)
    {
        return x * this->y + y;
    }
};
