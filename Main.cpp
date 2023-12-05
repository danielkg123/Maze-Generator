#include <iostream>
#include <cstdlib>
#include <ctime>
#include "MazeGenerator.cpp"
using namespace std;

int main() {
    // // membuat maze, input ukuran maze
    // MazeGenerator generator(10, 10);
    // // memberitau "aku ingin menjadi admin, aku ingin lihat proses generate maze"
    // // jika ingin generate maze besar, disarankan jangan menggunakan mode admin
    // generator.setAdmin(false);
    // // generate maze
    // generator.generateMaze();
    // // menampilkan maze dalam bentuk graph
    // cout << "Isi Graph : " << endl;
    // generator.maze.printGraph();
    // // menampilkan tampilan maze
    // cout << endl << "Display Maze : " << endl;
    // string** arrDisplay = generator.getDisplayMaze();
    // generator.displayMaze(arrDisplay);

    // generator.shortest();
    // return 0;

    // diatas default tanpa choices kalau mau coba coba


    // Menu : c14220329 Daniel

    int width,length;
    cout << "Input length: ";
    cin >> length;
    cout << "Input Width: ";
    cin >> width;

    MazeGenerator generator(width    , length);
    generator.generateMaze();
    
    cout << "Maze Generated!" << endl;


    int choice;

    do
    {
    cout << endl;
    cout << "Welcome to the Maze Game";
    cout << endl
    << " 1 - Display Maze.\n"
    << " 2 - Start Game.\n"
    << " 3 - Show Shortest Path. \n"
    << " 4 - Print Graph.\n"
    << " 5 - About.\n"
    << " 6 - Exit.\n"
    << " Enter your choice : ";
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        cout << "Display Maze : " << endl;
        string** arrDisplay = generator.getDisplayMaze();
        generator.displayMaze(arrDisplay);
        break;
    }
    case 2:
    {
        // program start game
        break;
    }
    case 3:
    {
        generator.shortest();
        break;
    }

    case 4:
    {
        cout << "Vertice dan edge map : " << endl;
        generator.maze.printGraph();
        break;

    }

    case 5:
    {
        cout << "About a Maze game that is created by us";
        break;
    }

    case 6:
    {
    cout << "End of Program.\n";
    break;
    }

    default:
    cout << "Not a Valid Choice. \n"
    << "Choose again.\n";
    break;
    }
    } while (choice !=6);

    return 0;
}