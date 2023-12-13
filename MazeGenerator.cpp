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
#include "Randomizer.cpp"
using namespace std;

// class maze generator
class MazeGenerator
{
public:
    GraphAdjList maze; // graph untuk menyimpan maze
    Randomizer rd;
    int x;             // panjang maze
    int y;             // lebar maze
    int spawnX;        // posisi spawn x
    int spawnY;        // posisi spawn y
    int startX;        // posisi start X (utk player dan shortest player)
    int startY;        // posisi start Y (utk player dan shortest player)
    int endX;          // posisi end X (utk player dan shortest player)
    int endY;          // posisi start Y (utk player dan shortest player)
    bool isAdmin;      // penanda apakah ingin menampilkan proses generate maze atau tidak

    // constructor
    MazeGenerator(int x = 0, int y = 0, bool isAdmin = false) : x(x), y(y), spawnX(0), spawnY(0), startX(rd.genStartX(x, y)), startY(rd.genStartY(x, y)), endX(rd.genEndX(x, y)), endY(rd.genEndY(x, y)), isAdmin(isAdmin), maze(x * y, false, false) {}

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
    string** getDisplayMaze(){

        // Pembuatan Array setiap Node 3x3 jadi untuk display dikali 3

        string** display;
        display = new string*[x*3 +1];
        // [x*3 +1][y*3+1];

        // untuk display menggunakan array base 1 bukan dari 0 jadi mudah untuk menggunakan rumus
        for (int i = 1 ; i<= (x*3); i++){
            display[i] = new string[y*5+1];
            for(int j = 1 ; j<= (y*5); j++){
                display[i][j] = "#";
            } 
        }

        for (int i = 1 ; i<= x; i++){
            for(int j = 1 ; j<= y; j++){
                display[i*3-1][j*5 - 2] = '.'; // rumus mengambil tengah i * 3 - 1 berlaku untuk panjang dan lebar
                display[i*3-1][j*5 - 3] = ' ';
                display[i*3-1][j*5 - 1] = ' ';
            }
        }

        // Penamaan vertice dalam map yang dibuat (ada di fungsi generateMaze)
        // 0 1 2 3
        // 4 5 6 7
        // 8 9 10 11
        // 12 13 14 15
        // contoh : vertice 2 ada di x = 3, y = 1



        int mazeY = 3; // 2 adalah vertice 0
        int mazeX = 2; // 2 adalah vertice 0
        int counter = 0;
        // cout << maze.vertices;
        for (int i = 0; i < maze.vertices; i++){      
            counter++;
            
            // cout << mazeY << " and " << mazeX <<  endl;
            for (const Edge neighbour : maze.adjList[i]){
                // CHECK LEFT SIDE OF NODE
                if (i-1 == neighbour.vertice){
                    display[mazeX][mazeY-2] = ' ';        
                }
                // CHECK RIGHT SIDE OF NODE
                if(i+1 == neighbour.vertice){ 
                    display[mazeX][mazeY+2] = ' ';  
                }
                // CHECK TOP SIDE OF NODE
                if(i-y == neighbour.vertice){
                    display[mazeX-1][mazeY] = ' ';  
                    display[mazeX-1][mazeY-1] = ' ';  
                    display[mazeX-1][mazeY+1] = ' ';  
                }
                // CHECK BOTTOM SIDE OF NODE
                if(i+y == neighbour.vertice){
                    display[mazeX+1][mazeY] = ' ';  
                    display[mazeX+1][mazeY-1] = ' ';  
                    display[mazeX+1][mazeY+1] = ' ';  
                }
            }

            // tambah koordinat untuk menyesuaikan
            mazeY +=5;
            if(counter%y == 0){
                mazeX+=3;
                mazeY = 3;
            }
        }
        return display;
    }

    void displayMaze(string** arr){
        for (int i = 1 ; i<= (x*3); i++){
            for(int j = 1 ; j<= (y*5); j++){
                cout<< arr[i][j];
            }
            cout << endl;
        }
    }


    /* 
     * Shortest path
     * Pembuat : Girvan Witartha
     * NRP : C14220167
     * menampilkan path terpendek yang didapatkan dari distance terpendek (findshortestpath)
     */
    //mencari titik awal yang di random
    // untuk mendapatkan vertice mulai 
    int titikAwal(){
        return y * startX + startY;
    };

    int titikAkhir(){
        return y * endX + endY;
    };


    //fungsi menampilkan display dari path yang sudah disimpan di vector 
    void shortest() {
        int titik_awal = titikAwal();
        int titik_akhir = titikAkhir();

        maze.findShortestPath(titik_awal, titik_akhir);
        vector<int> shortestPath = maze.shortestPath;
        shortestPath.insert(shortestPath.begin(), titik_akhir);

        // vector yang berisi jalan terpendek 
        cout << "Shortest Path: ";
        for (int vertex : shortestPath) {
            cout << vertex << " ";
        }
        cout << endl;

        // menampilkan display 
        string** displayWithShortestPath = getDisplayMazeWithShortestPath(shortestPath);

        for (int i = 1; i <= (x * 3); i++) {
            for (int j = 1; j <= (y * 5); j++) {
                cout << displayWithShortestPath[i][j];
            }
            cout << endl;
        }
    }

    /**
     * Function untuk Start Game
     * Pembuat : Alexander Yofilio Setiawan
     * NRP : C14220071
    */
    void playGame() {
        bool isSolved = false;
        bool isInvalid = false;
        int pStartX = startX;
        int pStartY = startY;
        string** displayPath = getDisplayMaze();

        // vector<int> pathTaken;
        // pathTaken.push_back(start);

        if (maze.isPlayed){
            cout << "You have played the game before. Type 3 to reveal the shortest path! \n";
            return;
        } else {
            while (!isSolved) {
                system("clear");

                if (isInvalid) {
                    cout << "Invalid move" << endl;
                    isInvalid = false;
                }

                // maze.printPlayedMaze(start, end);
                cout << "Input your next step (w,a,s,d): \n";
                cout << "Type 'r' to reveal the answer! \n";
                cout << "Your next move: ";

                system("stty raw");
                char move = getchar();
                system("stty cooked");
                cout << endl;

                switch (move) {
                case 'w':
                case 'W':
                case '8':
                    if (pStartX - 1 >= 0){
                        pStartX--;
                    }
                    else{
                        isInvalid = true;
                    }

                    if (isReached(pStartX, pStartY)){
                        cout << "You Win!" << endl;
                        isSolved = true;
                        maze.isPlayed = true;
                    }
                    break;
            
                case 'a':
                case 'A':
                case '4':
                    if (pStartY - 1 >= 0){
                        pStartY--;
                    }
                    else{
                        isInvalid = true;
                    }

                    if (isReached(pStartX, pStartY)){
                        cout << "You Win!" << endl;
                        isSolved = true;
                        maze.isPlayed = true;
                    }
                    break;
            
                case 's':
                case 'S':
                case '2':
                    if (pStartX + 1 <= x){
                        pStartX++;
                    }
                    else{
                        isInvalid = true;
                    }

                    if (isReached(pStartX, pStartY)){
                        cout << "You Win!" << endl;
                        isSolved = true;
                        maze.isPlayed = true;
                    }
                    break;

                case 'd':
                case 'D':
                case '6':
                    if (pStartY + 1 <= y){
                        pStartY++;
                    }
                    else{
                        isInvalid = true;
                    }

                    if (isReached(pStartX, pStartY)){
                        cout << "You Win!" << endl;
                        isSolved = true;
                        maze.isPlayed = true;
                    }
                    break;

                case 'r':
                case 'R':
                    cout << "Revealing the answer... \n";
                    this->shortest();
                    isSolved = true;
                    maze.isPlayed = true;
                    break;

                default:
                    cout << "Invalid move" << endl;
                    break;
                }
            }
        }
    }


private:
    string** getDisplayMazeWithShortestPath(vector<int> shortestPath) {
        string** display = getDisplayMaze(); 

        for (int vertex : shortestPath) {
            int mazeY = 2 + (vertex % y) * 5;
            int mazeX = 2 + (vertex / y) * 3;
            display[mazeX][mazeY+1] = '*';
        }

        int startVertex = shortestPath.front();
        int endVertex = shortestPath.back();
        display[2 + (startVertex / y) * 3][2 + (startVertex % y) * 5 + 1 ] = 'E';
        display[2 + (endVertex / y) * 3][2 + (endVertex % y) * 5 + 1] = 'S';

        for (int i = 1; i < shortestPath.size(); i++) {
            int prevVertex = shortestPath[i - 1];
            int currVertex = shortestPath[i];
            int prevY = 2 + (prevVertex % y) * 5;
            int prevX = 2 + (prevVertex / y) * 3;

            int currY = 2 + (currVertex % y) * 5;
            int currX = 2 + (currVertex / y) * 3;

            if (prevY == currY) {
                int minY = min(prevX, currX);
                int maxY = max(prevX, currX);
                for (int x = minY + 1; x < maxY; x++) {
                    if(prevVertex-currVertex < 0){
                    display[x][prevY+1] = '^';                
                    };
                    if(prevVertex-currVertex > 0){
                    display[x][prevY+1] = 'v';               
                    }
                }
            } else if (prevX == currX) {
                int minX = min(prevY, currY);
                int maxX = max(prevY, currY);
                for (int y = minX + 1; y < maxX; y++) {
                    if(prevVertex-currVertex < 0){
                        display[prevX][y+1] = '<';                
                    };
                    if(prevVertex-currVertex > 0){
                        display[prevX][y+1] = '>';              
                    }
                }
            }
        }
        return display;
    }
    // fungsi utama random map
    void recursiveMap(vector<vector<int> > &map, int currentX, int currentY)
    {
        // ingat posisi sekarang sudah dikunjungi
        map[currentX][currentY] = 1;

        // menampilkan proses generate map (jika admin)
        if (isAdmin)
        {
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
            
            // menambahkan edge ke dalam graph
            int vertice = convertVertice(targetX, targetY);
            maze.addEdge(convertVertice(currentX, currentY), vertice);

            // menampilkan posisi tetangga yang dipilih (jika admin)
            if (isAdmin)
                cout << "Neighbour's Vertice : " << vertice << endl;

            // lanjutkan rekursif ke tetangga yang dipilih
            recursiveMap(map, targetX, targetY);
        }
    }

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

    // cek apakah posisi sekarang sudah mencapai end atau belum
    bool isReached (int x, int y){
        return x == endX && y == endY;
    }
};