#include <iostream>
#include <string>
#include <vector>

// 사용자 정보를 저장할 구조체
struct UserInfo {
    std::string juminNumber;
    std::string name;
    int age;
};

// 사용자 정보를 저장할 벡터
std::vector<UserInfo> userDatabase;

int main() {
    // 사용자 정보 입력
    UserInfo user;
    std::cout << "주민등록번호: ";
    std::cin >> user.juminNumber;
    std::cout << "이름: ";
    std::cin >> user.name;
    std::cout << "나이: ";
    std::cin >> user.age;

    // 사용자 정보를 데이터베이스에 추가
    userDatabase.push_back(user);

    // 사용자 정보 출력
    std::cout << "주민등록번호: " << userDatabase[0].juminNumber << std::endl;
    std::cout << "이름: " << userDatabase[0].name << std::endl;
    std::cout << "나이: " << userDatabase[0].age << std::endl;

    return 0;
}