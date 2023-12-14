/*
Pembuat : Alexander Yofilio Setiawan
NRP : C14220071
Membuat base untuk spawn generator
*/

#include <iostream>
using namespace std;
class Randomizer {
    public:
    Randomizer(){
        srand(time(0)); // random seed di-reset setiap kali objek Randomizer diinstansiasi
    }

    // Fungsi untuk menghasilkan titik mulai X
    int genStartX(int row, int col) {
        int simpanx = rand() % row;
        return simpanx;
    };
    
    // Fungsi untuk menghasilkan titik mulai Y
    int genStartY(int row, int col) {
        int simpany = rand() % col;
        return simpany;
    };

    // Fungsi untuk menghasilkan titik akhir X
    int genEndX(int row, int col) {
        int endx = rand() % row;
        return endx;
    };

    // Fungsi untuk menghasilkan titik akhir Y
    int genEndY(int row, int col) {
        int endy = rand() % col;
        return endy;
    };
};