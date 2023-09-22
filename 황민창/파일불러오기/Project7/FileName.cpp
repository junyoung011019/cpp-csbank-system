#include <iostream>
#include <fstream>
using namespace std;

int main() {
    string filepath;
   ifstream file("C:\\Users\\hwmic\\source\\repos\\Project8\\Project8\\hwmich030520"); // 텍스트 파일 열기

    if (!file) { // 파일이 성공적으로 열렸는지 확인
        cout << "파일 열 수 없음";
        return 1;
    }
    char str[50];
    char i ;

    file >> str >> i;
    cout << str << i << endl;
    file.close();
    return 0;
}