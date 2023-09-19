#include <iostream>
#include <string>
#include<Windows.h>
using namespace std;

const int NAME_LEN = 20;

int accoutID; // 임시로 전역함수

void SC_bankMenu() //메뉴 인터페이스 함수 
{
    cout << "-----Menu-----" << endl;
    cout << "1. 계좌개설" << endl;
    cout << "2. 입  금" << endl;
    cout << "3. 출  금" << endl;
    cout << "4. 계좌정보 출력" << endl;
    cout << "5. 프로그램 종료" << endl;
}



void SC_bank_make_account() //계좌 계설 함수
{
    int accoutID;
    string name;

    cout << "[계좌개설]" << endl;

    cout << "계좌ID: ";
    cin >> accoutID;

    cout << "이  름: ";
    cin >> name;
}
void DepositMoney(void) // 입금 함수
{
    int money;
    int accoutID;

    cout << "[입  금]" << endl;
    cout << "계좌ID: ";
    cin >> accoutID;

    cout << "입금액: ";
    cin >> money;
    for (int i = 0; i < accoutID; i++)
    {
        if (accoutID == accoutID)
        {
            cout << "입금완료 !!" << endl;
            return;
        }
    }
    cout << "존재하지 않은 ID 입니다" << endl;

}

void WithdrawMoney()
{
    int money;
    int accoutID;
    cout << "[출  금]" << endl;

    cout << "계좌ID: ";
    cin >> accoutID;

    cout << "출금액: ";
    cin >> money;
    for (int i = 0; i < accoutID; i++)
    {
        if (accoutID == accoutID)
        {
            if (money == 0)
            {
                cout << "잔액이 부족합니다" << endl;
                return;
            }
            cout << "출금완료 !!" << endl;
            return;
        }
    }
    cout << "존재하지 않은 ID 입니다" << endl;
}

int main() //main 함수 시작1
{

    cout << "\t\t\t\t !!!!!!SC 제일은행에 온걸 환영합니다 !!!!!!\t\t" << endl;


    SC_bankMenu();
    int menuNum;

    cout << "입력  >> ";
    cin >> menuNum;
    while (1)
    {
        switch (menuNum)
        {
        case 1: cout << "계좌를 개설합니다!" << endl;
            break;
        case 2: cout << "입금을 합니다!" << endl;
            break;
        case 3: cout << "출금을 합니다!" << endl;
            break;
        case 4: cout << "계좌정보를 출력합니다" << endl;
            break;
        case 5: cout << "프로그램을 종료합니다" << endl;
            break;
        }

        if (menuNum == 1) //계좌 개설
        {
            SC_bank_make_account();

            Sleep(1500); //이전 내역들을 깜끔하게 지워주는 함수 
            system("cls");


            SC_bankMenu();
            cout << "입력  >> ";
            cin >> menuNum;
            cout << "\n";
        }
        if (menuNum == 2) //입금
        {
            DepositMoney();
            //
            Sleep(1500); //이전 내역들을 깜끔하게 지워주는 함수 
            system("cls");

            SC_bankMenu();
            cout << "입력  >> ";
            cin >> menuNum;
            cout << "\n";
        }
        if (menuNum == 3) //출금
        {


            WithdrawMoney();
            //
            Sleep(1500); //이전 내역들을 깜끔하게 지워주는 함수 
            system("cls");

            SC_bankMenu();
            cout << "입력  >> ";
            cin >> menuNum;
            cout << "\n";
        }

        if (menuNum == 4) // 계좌정보출력
        {


            Sleep(1500); //이전 내역들을 깜끔하게 지워주는 함수 
            system("cls");

            SC_bankMenu();
            cout << "입력  >> ";
            cin >> menuNum;
            cout << "\n";
        }
        if (menuNum == 5)
            break; // 프로그램 종료
    }
}