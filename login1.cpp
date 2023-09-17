#include <iostream>
#include <string>
#include <map>

using namespace std;

struct User {
	string name;
	string phoneNumber;
	string Security;
	string id;
	string password;
};

map<string, User> users; // 회원 정보를 저장할 맵

void Register() {
	string name, phoneNumber, Security, id, password;

	cout << "이름: ";
	getline(cin >> ws, name);

	cout << "전화번호: ";
	getline(cin >> ws, phoneNumber);

	cout << "주민번호 뒷자리 7자리: ";
	cin >> Security;

	cout << "새로운 아이디: ";
	cin >> id;

	cout << "새로운 비밀번호: ";
	cin >> password;

	User newUser = { name, phoneNumber,Security, id, password };
	// 주민번호를 키로 하여 회원 정보 저장
	users[id] = newUser;

	cout << "회원가입이 완료되었습니다." << endl;
}

void Login() {
	string idInput, passwordInput;

	cout << "아이디:";
	cin >> idInput;

	cout << "비밀번호:";
	cin >> passwordInput;


	for (auto& user : users) {
		if (user.second.id == idInput && user.second.password == passwordInput) {
			cout << user.second.name << "님으로 로그인되었습니다." << endl;
			return;
		}
	}

	cout << "일치하는 회원 정보가 없습니다." << endl;
}

void FindID() {
	string nameInp, numberInp, SecurityInp;

	cout << "이름:";
	getline(cin >> ws, nameInp);

	cout << "전화번호:";
	getline(cin >> ws, numberInp);

	cout << "주민등록 번호 뒷자리 7자리:";
	getline(cin >> ws, SecurityInp);


	for (auto& user : users) {
		if (user.second.Security == SecurityInp && user.second.phoneNumber == numberInp && user.second.name == nameInp) {
			cout << "당신의 아이디는 " << user.second.id << endl;
			return;
		}
	}

	cout << "일치하는 사용자를 찾지 못했습니다." << endl;


}


void FindPassword() {
	string namefn, numberfn, Securityfn;

	cout << "이름:";
	getline(cin >> ws, namefn);

	cout << "전화번호:";
	getline(cin >> ws, numberfn);

	cout << "주민등록 번호 뒷자리 7자리:";
	getline(cin >> ws, Securityfn);


	for (auto& user : users) {
		if (user.second.Security == Securityfn && user.second.phoneNumber == numberfn && user.second.name == namefn) {
			cout << "당신의 패스워드는 " << user.second.password << endl;
			return;
		}
	}

	cout << "일치하는 사용자를 찾지 못했습니다." << endl;

	}

int main() {
	int choice;

	while (true) {
		cout << "\n[1] 회원 가입 [2] 로그인 [3] 아이디 찾기 [4] 비밀번호 찾기 [5] 종료" << endl;
		cin >> choice;

		switch (choice) {
		case 1:
			cin.ignore();
			Register();
			break;

		case 2:
			Login();
			break;

		case 3:
			cin.ignore();
			FindID();
			break;

		case 4:
			cin.ignore();
			FindPassword();
			break;

		case 5:
			cout << "프로그램을 종료합니다." << endl;
			return 0;

		default:
			cout << "잘못된 선택입니다. 다시 선택해주세요." << endl;
			break;
		}

		// 버퍼 비우기
		cin.clear();

	}

	return 0;
}