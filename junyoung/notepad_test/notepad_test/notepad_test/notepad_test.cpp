#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;


struct UserInfo {
    string name;
    string id;
    string pw;
};

UserInfo signup_function() {
    UserInfo user;
    cout << "이름 입력>>";
    cin >> user.name;
    cout << "id 입력>>";
    cin >> user.id;
    cout << "pw 입력>>";
    cin >> user.pw;

    return user;
}



void file_input() {
    ofstream fout;
    fout.open("file.txt", std::ios_base::app);
    UserInfo userInfo = signup_function();
    fout << userInfo.name << " "<< userInfo.id << " " << userInfo.pw << "\n";
    fout.close();
}

void file_output() {
    ifstream fin;
    fin.open("file.txt");
    string number[100];
    int time = 0;
    for (int a = 0; a < 100; a++) {
        fin >> number[a];
    }
   
    for (int i = 1; i < 100; i++) {
        cout << number[i-1] << number[i]<< number[i +1]<<"\n";
    }

    cout << "\n";
}



int main()
{
    while (1) {
        int num;
        cout << "실행할 번호 입력 1.입력 2.출력 3.초기화>>";
        cin >> num;
        if (num == 1) {
            file_input();
        }else if(num == 2) {
            file_output();
        }
        else if (num == 3) {
            cout << "내용을 정말 초기화 하시겠습니까? 확인 1, 취소 2>>";
            int check;
            cin >> check;
            if (check == 1) {
                std::remove("file.txt");
            }
        }
        
    }

}