#include <iostream>
#include <cstdlib>
#include <ctime>
#include "MazeGenerator.cpp"
using namespace std;

int main() {
    // membuat maze, input ukuran maze
    MazeGenerator* generator = new MazeGenerator();

    // memberitau "aku ingin menjadi admin, aku ingin lihat proses generate maze"
    // jika ingin generate maze besar, disarankan jangan menggunakan mode admin
    generator->setAdmin(false);

    // generate maze
    generator->generateMaze(3, 3);

    // menampilkan maze dalam bentuk graph
    cout << "Isi Graph : " << endl;
    generator->maze->printGraph();

    // menampilkan tampilan maze
    cout << endl << "Display Maze : " << endl;
    string** arrDisplay = generator->getDisplayMaze();
    generator->displayMaze(arrDisplay);

    // menampilkan shortest path
    generator->shortest();

    // mencoba retry maze dengan ukuran sama
    generator->retryMaze();
    cout << endl << "Display Maze Retry : " << endl;
    arrDisplay = generator->getDisplayMaze();
    generator->displayMaze(arrDisplay);

    // mencoba resize
    generator->generateMaze(5, 5);
    cout << endl << "Display Maze Retry : " << endl;
    arrDisplay = generator->getDisplayMaze();
    generator->displayMaze(arrDisplay);
    return 0;

    // diatas default tanpa choices kalau mau coba coba


    // Menu : c14220329 Daniel

    // int width, length;
    // cout << "Input length: ";
    // cin >> length;
    // cout << "Input Width: ";
    // cin >> width;

    // MazeGenerator* generator = new MazeGenerator();
    // generator->generateMaze(length, width);
    
    // cout << "Maze Generated!" << endl;


    // int choice;

    // do {
    // cout << endl;
    // cout << "Welcome to the Maze Game";
    // cout << endl
    // // << " 0 - Generate New Maze. \n"
    // << " 1 - Display Maze. \n"
    // << " 2 - Start Game. \n"
    // << " 3 - Show Shortest Path. \n"
    // << " 4 - Print Graph. \n"
    // << " 5 - About. \n"
    // << " 6 - Exit. \n"
    // << " Enter your choice : ";
    // cin >> choice;

    // switch (choice)
    // {
    // // case 0: {
    // //     cout << "Input length: ";
    // //     cin >> length;
    // //     cout << "Input Width: ";
    // //     cin >> width;
    // //     generator->generateMaze();
    // //     cout << "Maze Generated!" << endl;
    // //     break;
    // // }
    // case 1: {
    //     cout << "Display Maze : " << endl;
    //     string** arrDisplay = generator->getDisplayMaze();
    //     generator->displayMaze(arrDisplay);
    //     break;
    // }
    // case 2: {
    //     generator->playGame();
    //     break;
    // }
    // case 3: {
    //     generator->shortest();
    //     break;
    // }

    // case 4: {
    //     cout << "Vertice dan edge map : " << endl;
    //     generator->maze->printGraph();
    //     break;
    // }

    // case 5: {
    //     cout << "About a Maze game that is created by us";
    //     break;
    // }

    // case 6: {
    //     cout << "End of Program.\n";
    //     break;
    // }

    // default:
    // cout << "Not a Valid Choice. \n"
    // << "Choose again.\n";
    // break;
    // }

    // } while (choice !=6);

    // return 0;
}