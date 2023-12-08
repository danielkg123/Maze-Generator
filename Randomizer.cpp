#include <iostream>
using namespace std;
class Randomizer
{
private:
public:
Randomizer(){
  srand(time(0));
}
int genStartX(int row, int col) {
    int simpanx = rand() % row;
    cout<<simpanx<<endl;
    return simpanx;
};
int genStartY(int row, int col) {
 int simpany = rand() % col;
    cout<<simpany<<endl;
    return simpany;
};
int genEndX(int row, int col) {
 int endx = rand() % row;
    cout<<endx<<endl;
    return endx;
};
int genEndY(int row, int col) {
 int endy = rand() % col;
    cout<<endy<<endl;
    return endy;
};

};
// int main () {
//     srand(time(0));
//     int cobaStartX = genStartX(10, 10);
//     int cobaStartY = genStartY(10, 10);
//     int cobaEndX = genEndX(10, 10);
//     int cobaEndY = genEndY(10, 10);
//     cout << cobaStartX << " " << cobaStartY << endl;
//     cout << cobaEndX << " " << cobaEndY << endl;
//     return 0;
// }