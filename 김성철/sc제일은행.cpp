// CS 제일은행


#include <iostream>
#include <string>

using namespace std;

// 입출금을 처리하는 기본 클래스
class Transaction
{
protected:
    double balance;  // 잔액 추가

public:
    Transaction() : balance(0.0) {}

    // 입금 함수
    void deposit(double amount)
    {
        balance += amount;
        cout << amount << "원 입금 완료. 현재 잔액: " << balance << endl;
    }

    // 출금 함수
    void withdraw(double amount)
    {
        if (amount > balance)
        {
            cout << "잔액이 부족합니다." << endl;
        }
        else
        {
            balance -= amount;
            cout << amount << "원 출금 완료. 현재 잔액: " << balance << endl;
        }
    }

    // 잔액 조회 함수
    double getBalance() const
    {
        return balance;
    }
};

// 고객 정보 클래스, 입출금 클래스를 상속받음
class CustomerInfo : public Transaction
{
private:
    string name;
    string address;
    string phone_number;
    string PW;
    bool Islogin;  // 회원가입 여부를 나타내는 플래그

public:
    // 생성자
    CustomerInfo(double EarlyBalance = 0.0) : Transaction(), Islogin(false)
    {
        balance = EarlyBalance;
    }

    // 사용자로부터 정보 입력
    void inputInfo()
    {
        cout << "이름을 입력하세요: ";
        cin >> name;

        cout << "주소를 입력하세요: ";
        cin >> address;

        cout << "전화번호를 입력하세요: ";
        cin >> phone_number;

        cout << "비밀번호를 입력하세요: ";
        cin >> PW;

        Islogin = true;  // 회원가입 완료 시 플래그를 true로 설정
    }

    // 이체 대상을 입력받는 함수
    void inputTransferInfo()
    {
        cout << "이체할 대상의 이름을 입력하세요: ";
        cin >> name;

        cout << "이체할 대상의 전화번호를 입력하세요: ";
        cin >> phone_number;
    }

    // 정보 출력 함수
    void displayInfo() const
    {
        cout << "고객 정보:" << endl;
        cout << "이름: " << name << endl;
        cout << "주소: " << address << endl;
        cout << "전화번호: " << phone_number << endl;
        cout << "잔액: " << balance << endl;
    }

    // 이체 수행 함수
    void transfer(CustomerInfo recipient, double amount) //recipient 변수 : 받는 사람
    {
        if (amount > balance)
        {
            cout << "이체 실패: 잔액이 부족합니다." << endl;
        }
        else {
            // 이체 대상에게 입금
            recipient.deposit(amount);

            // 이체하는 고객에서 출금
            withdraw(amount);

            cout << "이체 완료: " << amount << "원 이체됨." << endl;
        }
    }

    // 회원가입 여부 확인 함수
    bool isRegisteredUser()
    {
        return Islogin;
    }
};

//////////////////////////////////////////메인함수 시작//////////////////////////////////////////////////////////////////////

int main()
{
    cout << " =========================**cs 제일은행에 오신 걸 환영합니다**=============================\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";

    int MenuChoice;

    CustomerInfo customer;  // 고객 객체 생성

    while (1)
    {
        cout << "------------------------------------" << "\n";
        cout << "1. 회원가입" << endl;
        cout << "2. 예금 입금" << endl;
        cout << "3. 예금 출금" << endl;
        cout << "4. 계좌 이체" << endl;
        cout << "5. 계좌 조회" << endl;
        cout << "6. 종료" << endl;
        cout << "------------------------------------" << "\n";

        cout << "원하시는 메뉴를 입력해 주세요 >> ";
        cin >> MenuChoice;

        switch (MenuChoice)
        {
        case 1:
        {
            double EarlyBalance;
            cout << "초기 잔액을 입력하세요: ";
            cin >> EarlyBalance;
            customer = CustomerInfo(EarlyBalance);  // 회원가입 시 초기 잔액 설정
            customer.inputInfo();
        }
        break;
        case 2:
            if (!customer.isRegisteredUser())
            {
                cout << "회원가입이 필요합니다." << endl;
                break;
            }

            double depositAmount;
            cout << "입금할 금액을 입력하세요: ";
            cin >> depositAmount;
            customer.deposit(depositAmount);
            break;
        case 3:
            if (!customer.isRegisteredUser())
            {
                cout << "회원가입이 필요합니다." << endl;
                break;
            }

            double withdrawAmount;
            cout << "출금할 금액을 입력하세요: ";
            cin >> withdrawAmount;
            customer.withdraw(withdrawAmount);
            break;
        case 4:
            if (!customer.isRegisteredUser())
            {
                cout << "회원가입이 필요합니다." << endl;
                break;
            }

            {
                CustomerInfo recipient;  // 이체 대상 고객 객체 생성
                customer.inputTransferInfo();  // 이체 대상 입력 받기
                double transferAmount;

                cout << "이체할 금액을 입력하세요: ";
                cin >> transferAmount;

                // 이체 수행
                customer.transfer(recipient, transferAmount);
            }
            break;
        case 5:
            if (!customer.isRegisteredUser())
            {
                cout << "회원가입이 필요합니다." << endl;
                break;
            }

            customer.displayInfo();
            break;
        case 6:
            cout << "프로그램을 종료합니다." << endl;
            return 0;
        default:
            cout << "올바른 메뉴를 선택하세요." << endl;
        }
    }

    return 0;
}
