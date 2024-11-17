#include <iostream>
#include <fstream>
using namespace std;

int main(){
    fstream file("outpu1t.txt", ios::in);
    int n;
    int size = 0;
    while (!file.eof()){
        file >> n;
        size++;
    }
    cout << size << endl;
    return 0;
}