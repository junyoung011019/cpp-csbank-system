#include<iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
	string line;
	ifstream file("example. txt");
	if (file.is_open()) {
		while (getline(file, line)) {
			cout << line << endl;
		}
		file.close();
	}
	else {
		cout << "unable to open file";
		return 1;
	}
	return 0;
}