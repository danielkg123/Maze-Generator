#include <iostream>
#include <cstdlib>
#include <ctime>
#include "MazeGenerator.cpp"
using namespace std;

int main() {
    MazeGenerator generator(3, 3);
    generator.generateMaze();
    
    cout << "Vertice dan edge map : " << endl;
    generator.maze.printGraph();

    return 0;
}