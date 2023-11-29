#include <iostream>
#include <cstdlib>
#include <ctime>
#include "MazeGenerator.cpp"
using namespace std;

int main() {
    MazeGenerator generator(4, 4);
    generator.generateMaze();
    
    cout << "Vertice dan edge map : " << endl;
    generator.maze.printGraph();

    cout << "Display Maze : " << endl;
    string** arrDisplay = generator.getDisplayMaze();
    generator.displayMaze(arrDisplay);

    return 0;
}