#include <iostream>
#include <fstream>
using namespace std;

void print_file() {
    ifstream fin;
    fin.open("file.txt");
    int number[4];
    fin >> number[0]
        >> number[1]
        >> number[2]
        >> number[3];
    for (int i = 0; i < 4; i++) {
        cout << number[i] << endl;
    }
}

int main()
{
    ofstream fout;
    fout.open("file.txt");
    fout << 1 << "\n"
        << 2 << "\n"
        << 3 << "\n"
        << 4;
    fout.close();

    print_file();
}