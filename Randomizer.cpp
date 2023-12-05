#include <iostream>
using namespace std;

int genStartX(int row, int col) {
    return rand() % row;
};
int genStartY(int row, int col) {
    return rand() % col;
};
int genEndX(int row, int col) {
    return rand() % row;
};
int genEndY(int row, int col) {
    return rand() % col;
};


int main () {
    srand(time(0));
    int cobaStartX = genStartX(10, 10);
    int cobaStartY = genStartY(10, 10);
    int cobaEndX = genEndX(10, 10);
    int cobaEndY = genEndY(10, 10);

    cout << cobaStartX << " " << cobaStartY << endl;
    cout << cobaEndX << " " << cobaEndY << endl;
    return 0;
}