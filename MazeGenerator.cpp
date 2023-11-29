/*
Pembuat : Fellix Allenfant
NRP : C14220039
Membuat base untuk maze generator
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <random>
#include "GraphAdjList.cpp"

using namespace std;

// class maze generator
class MazeGenerator
{
public:
    GraphAdjList maze; // graph untuk menyimpan maze
    int x;             // panjang maze
    int y;             // lebar maze
    int spawnX;        // posisi spawn x
    int spawnY;        // posisi spawn y
    bool isAdmin;      // penanda apakah ingin menampilkan proses generate maze atau tidak

    // constructor
    MazeGenerator(int x = 0, int y = 0, bool isAdmin = false) : x(x), y(y), spawnX(0), spawnY(0), isAdmin(isAdmin), maze(x * y, false, false) {}

    /*
     * set admin, apakah ingin melihat proses generate atau tidak
     * default valuenya adalah false
     */
    void setAdmin(bool isAdmin)
    {
        this->isAdmin = isAdmin;
    }

    void setSize(int x, int y)
    {
        this->x = x;
        this->y = y;
        this->maze = GraphAdjList(x * y, false, false);
    }

    // generate maze
    void generateMaze()
    {
        // membuat array 2d untuk menandakan apakah koordinat sudah dikunjungi atau tidak
        vector<vector<int> > map(x, vector<int>(y, 0));

        // menampilkan posisi vertice dalam map (jika admin)
        if (isAdmin)
        {
            // display map berdasarkan vertice
            cout << "Vertice's Position :" << endl;
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

        // ambil starting position secara random
        random_device rd;
        uniform_int_distribution<int> dist(0, x - 1);
        spawnX = dist(rd);
        dist.param(uniform_int_distribution<int>::param_type(0, y - 1));
        spawnY = dist(rd);

        // menampilkan posisi spawn rate (jika admin)
        if (isAdmin)
            cout << "Spawn: " << spawnX << ", " << spawnY << endl;

        // simpan posisi sekarang dengan posisi spawn
        int currentX = spawnX;
        int currentY = spawnY;

        // membuat map (menggunakan rekursif)
        recursiveMap(map, currentX, currentY);
    }

    /* 
     * Display Maze
     * Pembuat : Daniel Kristianto Goenadi Go
     * NRP : C14220329
     * display menggunakan array2d untuk mudah di edit
     */
    string **getDisplayMaze()
    {
        // Pembuatan Array setiap Node 3x3 jadi untuk display dikali 3
        string **display;
        display = new string *[x * 3 + 1];
        // [x*3 +1][y*3+1];

        // untuk display menggunakan array base 1 bukan dari 0 jadi mudah untuk menggunakan rumus
        for (int i = 1; i <= (x * 3); i++)
        {
            display[i] = new string[y * 3 + 1];
            for (int j = 1; j <= (x * 3); j++)
            {
                display[i][j] = "#";
            }
        }

        for (int i = 1; i <= x; i++)
        {
            for (int j = 1; j <= y; j++)
            {
                display[i * 3 - 1][j * 3 - 1] = '.'; // rumus mengambil tengah i * 3 - 1 berlaku untuk panjang dan lebar
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
        for (int i = 0; i < maze.vertices; i++)
        {
            counter++;

            // cout << mazeY << " and " << mazeX <<  endl;
            for (const Edge neighbour : maze.adjList[i])
            {
                // CHECK LEFT SIDE OF NODE
                if (i - 1 == neighbour.vertice)
                {
                    display[mazeY][mazeX - 1] = ' ';
                }
                // CHECK RIGHT SIDE OF NODE
                if (i + 1 == neighbour.vertice)
                {
                    display[mazeY][mazeX + 1] = ' ';
                }
                // CHECK TOP SIDE OF NODE
                if (i - x == neighbour.vertice)
                {
                    display[mazeY - 1][mazeX] = ' ';
                }
                // CHECK BOTTOM SIDE OF NODE
                if (i + x == neighbour.vertice)
                {
                    display[mazeY + 1][mazeX] = ' ';
                }
            }

            // tambah koordinat untuk menyesuaikan
            mazeX += 3;
            if (counter % x == 0)
            {
                mazeY += 3;
                mazeX = 2;
            }
        }
        return display;
    }

    void displayMaze(string **arr)
    {
        for (int i = 1; i <= (x * 3); i++)
        {
            for (int j = 1; j <= (x * 3); j++)
            {
                cout << arr[i][j];
            }
            cout << endl;
        }
    }

private:
    // fungsi utama random map
    void recursiveMap(vector<vector<int> > &map, int currentX, int currentY)
    {
        // ingat posisi sekarang sudah dikunjungi
        map[currentX][currentY] = 1;

        // tampilkan map (jika admin)
        if (isAdmin)
        {
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
        }

        // function berhenti ketika sudah tidak ada tetangga available
        while (true)
        {
            // ambil posisi sembarang tetangga
            int neighbour = chooseNeighbour(map, currentX, currentY);

            // jika tidak ada (bernilai 0), maka function berhenti
            if (neighbour == 0)
                break;

            // menampilkan tetangga yang dipilih (jika admin)
            if (isAdmin)
            {
                if (neighbour == 1)
                    cout << "Selected Neighbour: up" << endl;
                else if (neighbour == 2)
                    cout << "Selected Neighbour: down" << endl;
                else if (neighbour == 3)
                    cout << "Selected Neighbour: left" << endl;
                else if (neighbour == 4)
                    cout << "Selected Neighbour: right" << endl;
            }

            // jika lolos (tetangga ada), cari posisi tetangga
            int targetX = 0;
            int targetY = 0;
            if (neighbour == 1)
            {
                targetX = currentX - 1;
                targetY = currentY;
            }
            else if (neighbour == 2)
            {
                targetX = currentX + 1;
                targetY = currentY;
            }
            else if (neighbour == 3)
            {
                targetX = currentX;
                targetY = currentY - 1;
            }
            else if (neighbour == 4)
            {
                targetX = currentX;
                targetY = currentY + 1;
            }

            // mencari posisi tetangga dan disimpan dalam graph
            int vertice = convertVertice(targetX, targetY);
            maze.addEdge(convertVertice(currentX, currentY), vertice);

            // menampilkan posisi tetangga terpilih (jika admin)
            if (isAdmin)
                cout << "Neighbour's Vertice : " << vertice << endl;

            // rekursif untuk tetangga terpilih
            recursiveMap(map, targetX, targetY);
        }
    }

    /*
     * function untuk memilih tetangga yang available di posisi sekarang
     * jika tidak ada tetangga, return 0
     * jika ada tetangga, return code tetangga (1, 2, 3, 4)
     * 1 = atas
     * 2 = bawah
     * 3 = kiri
     * 4 = kanan
     */
    int chooseNeighbour(vector<vector<int> > &map, int currentX, int currentY)
    {
        // cek tetangga yang available, disimpan ke dalam array
        vector<int> array;
        if (!outOfBounds(map, currentX - 1, currentY) && map[currentX - 1][currentY] == 0)
            array.push_back(1);
        if (!outOfBounds(map, currentX + 1, currentY) && map[currentX + 1][currentY] == 0)
            array.push_back(2);
        if (!outOfBounds(map, currentX, currentY - 1) && map[currentX][currentY - 1] == 0)
            array.push_back(3);
        if (!outOfBounds(map, currentX, currentY + 1) && map[currentX][currentY + 1] == 0)
            array.push_back(4);

        // jika array kosong, maka tidak ada tetangga lagi available dan function berhenti
        if (array.size() == 0)
            return 0;
        else
        {
            // jika ada tetangga yang available, maka pilih tetangga yang available secara random
            random_device rd;
            uniform_int_distribution<int> dist(0, array.size() - 1);
            int random = dist(rd);

            // mengembalikan code tetangga yang dipilih
            return array[random];
        }
    }

    // cek apakah posisi sekarang out of bounds atau tidak
    bool outOfBounds(vector<vector<int> > &map, int currentX, int currentY)
    {
        return currentX < 0 || currentX >= x || currentY < 0 || currentY >= y;
    }

    // convert posisi x dan y ke kode vertice agar bisa disimpan dalam graph
    int convertVertice(int x, int y)
    {
        return x * this->y + y;
    }
};
