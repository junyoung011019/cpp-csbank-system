#include <iostream>
#include <fstream>
using namespace std;
int main() {
	char x;
	cout << "파일명을 입력하세요";
	cin >> x;
	string line;
	ofstream file(x);
	if(!file){
		cout << "파일 열 수 없음";
		return 1;
	}
	file << "whangmin\n";
	file.close();
	return 0;
}