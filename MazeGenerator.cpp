#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "GraphAdjList.cpp"
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