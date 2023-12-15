#include <iostream>
#include <cstdlib>
#include <ctime>
#include "MazeGenerator.cpp"
using namespace std;

int main() {
    // Menu : C14220329 Daniel & C14220071 Yofilio
    char outerChoice;
    bool isExit = false;

    do {
        // Menu luar untuk memilih mau main atau exit
        cout << "\033[1;34m Welcome to the Maze Game \033[0m" << endl;
        cout << " Y - Start. \n";
        cout << " N - Exit. \n";
        cout << " Enter your choice : ";
        cin >> outerChoice;

        switch (outerChoice) {
            case 'y':
            case 'Y': {
                // Kalau Yes, baru dibuatkan maze generator nya
                MazeGenerator* generator = new MazeGenerator();
                int choice;
                bool isGenerated = false;
                int length, width;

                do {
                    // Menu dalam untuk user, memilih buat maze baru, resize, dll
                    cout << endl << endl;
                    cout << "\033[1;34mMenu: \n \033[0m";
                    cout << endl
                    << " 0 - Generate New Maze. \n"
                    << " 1 - Regenerate Maze (Same dimension). \n"
                    << " 2 - Resize Maze. \n"
                    << " 3 - Display Maze. \n"
                    << " 4 - Start Game. \n"
                    << " 5 - Show Shortest Path. \n"
                    << " 6 - Print Graph. \n"
                    << " 7 - About. \n"
                    << " 8 - Exit. \n"
                    << " Enter your choice : ";
                    cin >> choice;

                    switch (choice) {
                        // Untuk buat Maze baru
                        case 0: {
                            if (isGenerated){
                                cout << "\033[1;31mMaze already generated! \033[0m" << endl;
                                break;
                            }
                            system("clear");
                            cout << "\033[1;34mGenerate New Maze: \n \033[0m" << endl;
                            cout << "Input the dimension of the maze. \n";
                            cout << "Input length: ";
                            cin >> length;
                            cout << "Input Width: ";
                            cin >> width;
                            generator->generateMaze(length, width);
                            cout << "\033[1;32mMaze Generated! \033[0m" << endl;
                            isGenerated = true;
                            break;
                        }

                        // Untuk regenerate maze dengan ukuran yang sama (pola maze berubah)
                        case 1: {
                            if (isGenerated){
                                system("clear");
                                cout << "\033[1;34mRegenerate Maze : \n \033[0m" << endl;
                                generator->retryMaze();
                                cout << "\033[1;32mMaze Regenerated! \033[0m" << endl;
                                isGenerated = true;
                                break;
                            } else {
                                cout << "\033[1;31mThere is no maze to regenerate. \033[0m" << endl;
                                cout << "\033[1;31mPlease generate maze first! \033[0m" << endl;
                            }
                            break;
                        }

                        // Untuk mengubah ukuran maze (resize) sekaligus generate maze baru
                        case 2: {
                            if (isGenerated){
                                system("clear");
                                cout << "\033[1;34mResize Maze : \n \033[0m" << endl;
                                cout << "Input the dimension of the new maze. \n";
                                cout << "Input length: ";
                                cin >> length;
                                cout << "Input Width: ";
                                cin >> width;
                                generator->generateMaze(length, width);
                                cout << "\033[1;32mMaze Resized! \033[0m" << endl;
                                isGenerated = true;
                                break;
                            } else {
                                cout << "\033[1;31mThere is no maze to resize. \033[0m" << endl;
                                cout << "\033[1;31mPlease generate maze first! \033[0m" << endl;
                            }
                            break;
                        }

                        // Untuk menampilkan maze hasil generate
                        case 3: {
                            if (isGenerated){
                                system("clear");
                                cout << "\033[1;34mDisplay Maze : \033[0m" << endl;
                                string** arrDisplay = generator->getDisplayMaze();
                                generator->displayMaze(arrDisplay);
                            } else {
                                cout << "\033[1;31mPlease generate maze first! \033[0m" << endl;
                            }
                            break;
                        }

                        // Untuk memulai game
                        case 4: {
                            if (isGenerated){
                                generator->playGame();
                            } else {
                                cout << "\033[1;31mPlease generate maze first! \033[0m" << endl;
                            }
                            break;
                        }

                        // Untuk menampilkan shortest path (Dijkstra)
                        case 5: {
                            if (isGenerated){
                                system("clear");
                                generator->shortest();
                            } else {
                                cout << "\033[1;31mPlease generate maze first! \033[0m" << endl;
                            }
                            break;
                        }

                        // Untuk menampilkan graph dalam bentuk adjacency list
                        case 6: {
                            if(isGenerated){
                                system("clear");
                                cout << "\033[1;34mVertice and edge map : \033[0m" << endl;
                                generator->maze->printGraph();
                            } else {
                                cout << "\033[1;31mPlease generate maze first! \033[0m" << endl;
                            }
                            break;
                        }

                        //Deskripsi Game
                        case 7: {
                            cout << "\033[1;34m About a Maze Game that is created collaboratively by Fellix, Lio, Girvan, and Daniel. \n \033[0m" << endl;
                            break;
                        }

                        // Pilihan exit
                        case 8: {
                            cout << "\033[1;31m End of Program.\n \033[0m" << endl;
                            cout << endl;
                            break;
                        }

                        // Error handling (pilihan tidak valid)
                        default:{
                            cout << endl;
                            cout << "\033[1;31mNot a valid Choice. \n \033[0m" << endl;
                            cout << "\033[1;33mChoose again.\n \033[0m" << endl;
                            break;
                        }
                    }
                } while (choice != 8);
                break;
            }

            case 'n':
            case 'N': {
                // Kalau No, keluar dari program
                cout << "\033[1;32mThank you! \033[0m" << endl;
                isExit = true;
                break;
            }
            default: {
                // Error handling (pilihan tidak valid)
                cout << "Choose either Y or N." << endl;
                break;
            }
        }
    } while (!isExit);
    return 0;
}