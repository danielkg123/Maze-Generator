#include <iostream>
#include <cstdlib>
#include <ctime>
#include "MazeGenerator.cpp"
using namespace std;

int main() {
    // membuat maze, input ukuran maze
    MazeGenerator generator(10, 10);
    // memberitau "aku ingin menjadi admin, aku ingin lihat proses generate maze"
    // jika ingin generate maze besar, disarankan jangan menggunakan mode admin
    generator.setAdmin(false);
    // generate maze
    generator.generateMaze();
    // menampilkan maze dalam bentuk graph
    cout << "Isi Graph : " << endl;
    generator.maze.printGraph();
    // menampilkan tampilan maze
    cout << endl << "Display Maze : " << endl;
    string** arrDisplay = generator.getDisplayMaze();
    generator.displayMaze(arrDisplay);

    generator.shortest();
    return 0;
}