#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::string filePath;

    std::cout << "새로운 파일 경로와 이름을 입력하세요: ";
    std::getline(std::cin >> std::ws, filePath);

    std::ofstream file(filePath); // 새로운 파일 생성

    if (file.is_open()) { // 파일이 성공적으로 열렸는지 확인
        std::string content;
        std::cout << "파일에 저장할 내용을 입력하세요. (종료하려면 'q'를 입력하세요)" << std::endl;

        while (true) {
            std::getline(std::cin >> std::ws, content); // 한 줄씩 읽어오기

            if (content == "q") { // 'q'가 입력되면 종료
                break;
            }

            file << content << "\n"; // 읽어온 내용을 파일에 저장
        }

        file.close(); // 파일 닫기
        std::cout << "파일이 성공적으로 저장되었습니다." << std::endl;
    }
    else {
        std::cout << "파일을 열 수 없습니다." << std::endl;
    }

    return 0;
}