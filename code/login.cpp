#include <iostream>
#include <cstring>

using namespace std;

class user_info {
public:
    char user_name[10]; //이름
    string user_id; //아이디
    string user_pw;
};

class admin_info {
public:
    char admin_name[10]; //이름
    string admin_id; //아이디
    string admin_pw;
};



int main() {
    //임시 계정
    user_info test_user_1;
    strcpy(test_user_1.user_name, "테스트_정준영");
    test_user_1.user_id = "junyoung";
    test_user_1.user_pw = "1q2w3e4r!";

    admin_info test_admin1;
    strcpy(test_admin1.admin_name, "테스트_관리자1");
    test_admin1.admin_id = "admin";
    test_admin1.admin_pw = "1q2w3e4r!";

    //로그인 상태
    char login_state = '0';

    cout << "CS 제일 은행에 오신걸 환영합니다!\n로그인\n";
    //로그인시 입력 받는 id와 pw
    string input_id;
    string input_pw;
    //로그인 에러
    int login_error = 0;
    while (1) {
        //id 입력
        cout << "아이디를 입력해주세요.\n";
        cin >> input_id;
        //pw 입력
        cout << "비밀번호를 입력해주세요.\n";
        cin >> input_pw;
        //로그인 정보 확인
        if ((input_id == test_user_1.user_id) && (input_pw == test_user_1.user_pw)) {
            cout << "정준영님 환영합니다!\n";
            login_state = 'J';
            break;
        }
        else if ((input_id == test_admin1.admin_id) && (input_pw == test_admin1.admin_pw)) {
            cout << "관리자님 환영합니다.\n";
            login_state = 'A';
            break;
        }
        else {
            cout << "아이디 혹은 비밀번호가 일치하지 않습니다.\n";
            login_error += 1;
        }

        if (login_error == 5) {
            cout << "로그인 5회 실패로 인해 프로그램이 종료됩니다.";
            return 0;
        }
    }
    cout << "이 내용이 출력된다면, 정상 로그인 된것임. \n";
    if (login_state == 0) {
        cout << "로그인이 정상적으로 실행되지않고 넘어옴";
    }
    if (login_state == 'J') {
        cout << "정준영 계정으로 정상 로그인됨";
    }
    if (login_state == 'A') {
        cout << "테스트_관리자1 계정으로 정상 로그인됨";
    }


}

