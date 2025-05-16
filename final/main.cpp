#include <iostream> //입력 및 출력 작업을 다루는 입출력 스트림 헤더
#include <mysql.h>  //MySQL 데이터베이스 연결을 위한 헤더 파일
#include <string>   //C++에서 문자열 조작을 위한 헤더 파일
#include <windows.h> // Windows API 함수를 위한 헤더 파일
#include <cstdlib>  // exit 함수를 사용하기 위한 헤더
#include <iomanip>  //랜덤을 위한 헤더
#include <iomanip>  // setw 헤더 추가

using namespace std;

MYSQL Conn;                              // MySQL 정보 담을 구조체
MYSQL* ConnPtr = NULL;                  // MySQL 핸들
MYSQL_RES* Result;                      // 쿼리 성공시 결과를 담는 구조체 포인터
MYSQL_ROW Row;                  // 쿼리 성공시 결과로 나온 행의 정보를 담는 구조체



int Stat;              // 쿼리 요청 후 결과 (성공, 실패)
string MemberNo = "NULL"; // 회원 번호를 나타내는 Member No 변수

void end() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // 하늘 색상 출력
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    cout << "           #### ##  ###  ##    ##     ###  ##  ##  ###           ##  ##    ## ##   ##  ###\n";
    cout << "           # ## ##   ##  ##     ##      ## ##  ##  ##            ##  ##   ##   ##  ##   ##\n";
    cout << "             ##      ##  ##   ## ##    # ## #  ## ##             ##  ##   ##   ##  ##   ##\n";
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    cout << "             ##      ## ###   ##  ##   ## ##   ## ##              ## ##   ##   ##  ##   ##\n";
    cout << "             ##      ##  ##   ## ###   ##  ##  ## ###              ##     ##   ##  ##   ##\n";
    cout << "             ##      ##  ##   ##  ##   ##  ##  ##  ##              ##     ##   ##  ##   ##\n";
    cout << "            ####    ###  ##  ###  ##  ###  ##  ##  ###             ##      ## ##    ## ##\n";
    cout << "\n\n\n\n";
    // 흰색으로 설정하여 다음 출력이 흰색으로 나타나도록 함
    SetConsoleTextAttribute(hConsole, 15);
}

/////////////////////////////////////////////////로그인 클래스//////////////////////////////////////////
class Login {
public:
    string Input_ID, Input_PW;
    int missing = 0;
protected:
    void login();
};

void Login::login()
{
    mysql_init(&Conn); // MySQL 정보 초기화

    // 데이터베이스와 연결
    ConnPtr = mysql_real_connect(&Conn, "localhost", "root", "1q2w3e4r!", "cs_bank", 3306, (char*)NULL, 0);
    // MySql DB와 연동하기 위한 문
    //  MYSQL 구조체에 대한 포인터로 즉, 연결 성공 시 구조체가 초기화 호스트명 / 사용자 이름 / 비밀번호 / 스키마 / 포트번호 / 포인터와 숫자 0 모두 C++에서 NULL로 해석

    // 연결 결과 확인. null일 경우 실패
    if (ConnPtr == NULL) {
        fprintf(stderr, "Mysql query error:%s", mysql_error(&Conn));
        return;
    }

    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //하늘 색상 출력
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    cout << "\n\n\n";
    cout << "                            ##        ##        ## ##    ####   ###   ##\n";
    cout << "                            ##      ##   ##   ##   ##     ##      ##  ##\n";
    cout << "                            ##      ##   ##   ##          ##     # ## ##\n";
    cout << "                            ##      ##   ##   ##  ###     ##     ## ##\n";
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    cout << "                            ##      ##   ##   ##   ##     ##     ##  ##\n";
    cout << "                            ##       ## ##     ##   ##    ##     ##  ##\n";
    cout << "                            ### ###   ##        ## ##    ####   ###  ##\n";

    SetConsoleTextAttribute(hConsole, 15);
    cout << "\n\n\n\n";

    while (1)
    {
        cout << "\n";
        cout << "아이디를 입력하세요. >";
        cin >> Input_ID;
        cout << "비밀번호를 입력하세요. >";
        cin >> Input_PW;

        // SQL 쿼리 - customer_table에서 ID에 있는 모든 칼럼을 보여주세요
        string query = "SELECT * FROM customer_table WHERE ID = '" + Input_ID + "' AND password = '" + Input_PW + "'";
        // SQL 쿼리를 실행하고 성공 여부 확인
        if (mysql_query(&Conn, query.c_str()) == 0) {
            // 결과를 저장
            MYSQL_RES* result = mysql_store_result(&Conn);

            // 결과가 있을 경우
            if (result) {
                // 첫 번째 행을 가져옴
                MYSQL_ROW row = mysql_fetch_row(result);

                // 행이 존재하면 로그인 성공
                if (row) {
                    // 결과 세트 해제
                    mysql_free_result(result);

                    // 로그인한 사용자의 정보를 다시 가져오는 SQL 쿼리 생성
                    string whoLoginquery = "SELECT Name, NO FROM cs_bank.customer_table WHERE ID = '" + Input_ID + "'";

                    // SQL 쿼리를 실행하고 성공 여부 확인
                    if (mysql_query(&Conn, whoLoginquery.c_str()) == 0) {
                        // 결과를 저장
                        MYSQL_RES* result = mysql_store_result(&Conn);

                        // 결과가 있을 경우
                        if (result != NULL) {
                            // 첫 번째 행을 가져옴
                            MYSQL_ROW row = mysql_fetch_row(result);

                            // 행이 존재하면 환영 메시지 출력
                            if (row != NULL) {
                                cout << "환영합니다! " << row[0] << "님!"; //row[0]에는 name이 저장되어 있음
                                MemberNo = row[1]; //row[1]에는 No가 저장되어 있음
                            }
                        }

                        // 결과 세트 해제
                        mysql_free_result(result);
                    }

                    // 1초 대기
                    Sleep(1000);

                    // 함수 종료 (로그인 성공 시)
                    return;
                }
                else {
                    // 비밀번호 실패 최대 5번 가능
                    missing += 1;
                    cout << "비밀번호가 옳지않습니다." << endl;
                    cout << "현재 비밀번호" << missing << "회 오류입니다." << endl;
                    if (missing < 5) {
                        continue;
                    }
                    cout << "로그인 5회 실패시 로그인이 제한됩니다." << endl;

                    //결과 세트 해체
                    mysql_free_result(result);

                    //프로그램 종료
                    cout << "\n";
                    cout << "사유 : 로그인 5회 실패" << endl;
                    cout << "\n\n\n\n";
                    end();
                    exit(0);

                }

            }
        }
        else {
            // 쿼리 실행중 오류 발생
            cout << "SQL query error: " << mysql_error(&Conn);
        }
    }
    mysql_close(&Conn); // 메모리 누수를 방지하고 리소스를 반환
}

////////////////////////////////////////////////회원가입 클래스//////////////////////////////////////////
class SignUp {
public:
    string ID, PW, NAME, confirmPW; //confirmPW : 비밀번호를 한번더 치게 하기위한 변수
    string PhoneNumber;
    string AcccountNumber;
protected:
    void signup();
};

void SignUp::signup() {


    mysql_init(&Conn); // MySQL 정보 초기화

    // 데이터베이스와 연결
    MYSQL* ConnPtr = mysql_real_connect(&Conn, "localhost", "root", "1q2w3e4r!", "cs_bank", 3306, (char*)NULL, 0);
    // MySql DB와 연동하기 위한 문
    //  MYSQL 구조체에 대한 포인터로 즉, 연결 성공 시 구조체가 초기화 호스트명 / 사용자 이름 / 비밀번호 / 스키마 / 포트번호 / 포인터와 숫자 0 모두 C++에서 NULL로 해석

    // 연결 결과 확인. null일 경우 실패
    if (ConnPtr == NULL) {
        fprintf(stderr, "Mysql query error:%s", mysql_error(&Conn));
        return;
    }

    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // 하늘 색상 출력
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    std::cout << "\n\n\n";
    cout << "                ## ##     ####    ## ##   ###  ##           ##  ###  ### ##   \n";
    cout << "               ##   ##     ##    ##   ##    ## ##           ##   ##   ##  ##  \n";
    cout << "               ####        ##    ##        # ## #           ##   ##   ##  ##  \n";
    cout << "                #####      ##    ##  ###   ## ##            ##   ##   ##  ##  \n";
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    cout << "                   ###     ##    ##   ##   ##  ##           ##   ##   ## ##   \n";
    cout << "               ##   ##     ##    ##   ##   ##  ##           ##   ##   ##      \n";
    cout << "                ## ##     ####    ## ##   ###  ##            ## ##   ####     \n";
    cout << "\n\n\n\n";
    // 흰색으로 설정하여 다음 출력이 흰색으로 나타나도록 함
    SetConsoleTextAttribute(hConsole, 15);
    cout << "           ================================회원가입================================                  \n\n\n\n";

    while (1) {
        cout << "\n";
        cout << "사용하실 아이디를 입력하세요. (공백 없이 최대 50자) >> ";
        cin >> ID;

        // ID 중복 체크를 위한 SQL 쿼리 생성
        string idCheckQuery = "SELECT ID FROM customer_table WHERE ID = '" + ID + "'";

        // SQL 쿼리 실행
        mysql_query(&Conn, idCheckQuery.c_str());

        // 결과를 저장
        MYSQL_RES* idCheckResult = mysql_store_result(&Conn);

        // 결과 행의 개수를 확인하여 중복 여부를 판단
        if (mysql_num_rows(idCheckResult) == 0) {
            // 결과 세트 해제
            mysql_free_result(idCheckResult);

            // 중복이 없으면 반복문 종료
            break;
        }

        cout << "이미 존재하는 아이디 입니다!\n";
        mysql_free_result(idCheckResult);
    }

    cout << "\n";
    cout << "이름을 입력하세요. (영어로 입력해주세요) >> ";
    cin >> NAME;


    // 전화번호 입력
    cout << "\n";
    cout << "전화번호를 입력하세요. >> ";
    cin >> PhoneNumber;


    // 비밀번호 입력
    while (1) {
        cout << "\n";
        cout << "사용하실 비밀번호를 입력하세요. (숫자 4자리) >> ";
        cin >> PW;

        // 비밀번호 확인
        cout << "비밀번호를 다시 입력하세요. >> ";
        cin >> confirmPW;

        while (PW != confirmPW) {
            cout << "비밀번호가 일치하지 않습니다. 다시 입력해주세요.\n";

            // 다시 입력 받기
            cout << "\n";
            cout << "사용하실 비밀번호를 입력하세요. (숫자 4자리) >> ";
            cin >> PW;

            cout << "비밀번호를 다시 입력하세요. >> ";
            cin >> confirmPW;
        }

        cout << "비밀번호가 설정되었습니다!.\n";

        break;
    }

    cout << "가입을 진심으로 환영합니다!!!\n";
    Sleep(3000);
    //가입 인원 판별 및 No값 삽입
    int No = 0; // 앞으로 회원이 등록되면 NO(회원번호)로 회원을 파악


    // 고객 테이블의 레코드 개수를 가져오기 위한 SQL 쿼리 생성
    string AccountCountQuery = "SELECT COUNT(*) FROM customer_table";
    //고객 테이블에 있는 모든 칼럼을 검색해주세요

    // SQL 쿼리 실행
    if (mysql_query(&Conn, AccountCountQuery.c_str()) != 0) {
        // SQL 쿼리 실행 중 오류 발생 시 오류 메시지 출력
        fprintf(stderr, "SQL 문 실행 오류: %s\n", mysql_error(&Conn));
    }
    else {
        // SQL 쿼리 실행이 성공한 경우 결과를 가져오기
        MYSQL_RES* result = mysql_use_result(&Conn);

        // 결과 행 가져오기
        MYSQL_ROW row = mysql_fetch_row(result);

        // 결과 행이 존재하는 경우
        if (row != NULL) {
            // 레코드 개수를 정수로 변환하여 No 변수에 저장
            No = atoi(row[0]); //atoi()통해 정수로 반환

            // 결과 세트 해제
            mysql_free_result(result);
        }
    }
    //가입 인원 +1 =No   ex) 고객테이블에 5명의 고객이 존재하면 다음 회원부터는 NO.6 지정
    No += 1;

    // 회원 정보를 데이터베이스에 삽입하기 위한 SQL 쿼리 생성 및 실행
    string insertQuery = "INSERT INTO `cs_bank`.`customer_table` (`No`, `ID`, `Name`, `Phone`, `Password`) VALUES ('" + to_string(No) + "','" + ID + "', '" + NAME + "',  '" + PhoneNumber + "'  , '" + PW + "')";
    //DBd인 cs_bank 에 있는 고객 테이블의 `No`, `ID`, `Name`, `Phone`, `Password` 칼럼에 순서대로 삽입해주세요

    if (mysql_query(&Conn, insertQuery.c_str()) != 0) {
        fprintf(stderr, "Mysql query error:%s", mysql_error(&Conn));
    }
    Sleep(5000);
    mysql_close(&Conn); // 메모리 누수를 방지하고 리소스를 반환
}



////////////////////////////////스타트 클래스/////////////////////
class Start : public Login, public SignUp  // 위에서 언급했던 로그인 회원가입 클래스를 다중 상속
{
public:
    int StartMenuNum = 0; // 1.로그인 2.회원가입 3.종료 를 받기위한 변수 선언
    void start();
};


class User : public Start // 방금 로그인, 회원가입 클래스를 상속 받았던 Start클래스가 User의 부모클래스가 됌
{
private:
    string ID, Name, Phone, Password; //당 멤버 변수들은 클래스 내부에서만 접근이 가능하며, private를 통해 회원 정보를 외부에서 직접 접근할 수 없음  
public:
    int UserMenuNum = 0; // 6가지 기능을 이용하기 위한 변수 선언(1. 계좌계설, 2. 입금, 3. 출금, 4. 계좌이체, 5. 관리자모드, 6. 본인 정보 확인

    void UserFunction(); //8가지의 메뉴가 있는 함수

    //유저의 정보를 받아오는 내용
    void GetUserInfo();
    //계좌 개설
    void OpenAccount();
    //계좌 여부 확인
    void IsHaveAccount();
    //입금
    void deposit();
    //출금
    void withdraw();
    //계좌이체
    void transfer();
    //관리자 - 모든 테이블 확인
    void displayCustomerTable();
    //사용자 - 본인 정보 확인
    void checkmyInfo();

};
void User::GetUserInfo()
{
    // 로그인한 회원의 정보를 가져오기 위한 SQL 쿼리 생성
    string whoLoginquery = "SELECT ID, Name, Phone, Password FROM cs_bank.customer_table WHERE No = '" + MemberNo + "'";
    //해석 = cs_bankDB속에 customer_table에서 No가 가지고 있는 ID, Name, Phone, Password를 조회해 주세요

    // SQL 쿼리 실행
    if (mysql_query(&Conn, whoLoginquery.c_str()) == 0) {
        // 결과를 저장
        MYSQL_RES* result = mysql_store_result(&Conn);

        // 결과가 존재하는 경우
        if (result != NULL) {
            // 첫 번째 행을 가져옴
            MYSQL_ROW row = mysql_fetch_row(result);

            // 행이 존재하는 경우 회원 정보를 가져와서 해당 클래스의 멤버 변수에 할당
            if (row != NULL) {
                ID = row[0];
                Name = row[1];
                Phone = row[2];
                Password = row[3];
            }

            // 결과 세트 해제
            mysql_free_result(result);
        }
    }
}

void User::OpenAccount() //계좌 개설
{
    string CheckPhone; //전화번호를 입력 받는 변수
    string agree; // 동의할건지에 대한 입력 변수
    cout << "계좌 개설 페이지입니다.\n";
    cout << "본인 확인을 위해 전화번호를 입력하세요. >> ";
    cin >> CheckPhone;

    if (Phone != CheckPhone) {
        cout << "본인 확인에 실패했습니다.\n";
        cout << "관리자에게 문의바랍니다. \n";
        Sleep(2000); //2초뒤
        UserFunction(); //8가지의 메뉴가 있는 함수
    }
    cout << "본인 확인이 되었습니다.\n";
    cout << "\n";
    cout << "보이스피싱 등 전기 통신 금융사기가 급증함에 따라, 고객님의 금융사기 피해를 사전에 예방하고 소중한 자산을 보호하고자 합니다.";
    cout << "\n";
    cout << "계좌 개설 목적이 본인 사용이 맞으신가요? < Yes / NO > >> ";
    cin >> agree;
    if (agree == "No" || agree == "NO") {
        cout << "관리자에게 문의바랍니다. \n";
        Sleep(2000); //2초뒤
        UserFunction(); //8가지의 메뉴가 있는 함수
    }

    int randomNumber = 0;
    // 무한 루프를 돌면서 중복되지 않은 계좌번호 생성
    while (1) {
        //계좌번호 랜덤 생성
        srand(time(NULL));
        randomNumber = 10000000 + rand() % (99999999 - 10000000 + 1);

        // 생성된 계좌번호 중복 확인을 위한 SQL 쿼리 생성      
        string AccountCheckQuery = "SELECT ID FROM account_table WHERE ID = '" + to_string(randomNumber) + "'";
        // SQL 쿼리 실행
        mysql_query(&Conn, AccountCheckQuery.c_str());
        // 결과를 저장
        MYSQL_RES* idCheckResult = mysql_store_result(&Conn);

        //만약에 중복이 있지 않는다면 신규 계좌번호를 출력
        if (mysql_num_rows(idCheckResult) == 0) {
            mysql_free_result(idCheckResult);
            cout << "고객님의 계좌번호는" << randomNumber << "입니다.\n";
            break;
        }
    }
    Sleep(3000);

    // 계좌 테이블의 레코드 개수를 가져오기 위한 SQL 쿼리 생성
    string AccountCountQuery = "SELECT COUNT(*) FROM account_table";

    int accountCount = 0;
    if (mysql_query(&Conn, AccountCountQuery.c_str()) != 0) {
        fprintf(stderr, "SQL 문 실행 오류: %s\n", mysql_error(&Conn));
    }
    else {
        // SQL 쿼리 실행이 성공한 경우 결과를 가져오기
        MYSQL_RES* result = mysql_use_result(&Conn);
        // 결과 행 가져오기
        MYSQL_ROW row = mysql_fetch_row(result);

        // 결과 행이 존재하는 경우 레코드 개수를 정수로 변환하여 accountCount 변수에 저장
        if (row != NULL) {
            if (row != NULL) {
                accountCount = atoi(row[0]);
            }
            mysql_free_result(result);
        }
    }

    //계좌 개수 +1
    accountCount += 1;

    //계좌 이름 생성
    string accountName = "cs_account";
    accountName += to_string(accountCount);

    // 회원 정보를 데이터베이스에 삽입하기 위한 SQL 쿼리 생성 및 실행
    string insertQuery = "INSERT INTO `cs_bank`.`account_table` (`ID`, `AccountName`, `AccountNumber`, `Balance`) VALUES ('" + ID + "', '" + accountName + "',   '" + to_string(randomNumber) + "'  , '" + to_string(0) + "')";
    // SQL 쿼리 실행
    if (mysql_query(&Conn, insertQuery.c_str()) != 0) {
        fprintf(stderr, "Mysql query error:%s", mysql_error(&Conn));
    }

    cout << "계좌 개설을 축하합니다";
    Sleep(2000);
}

void User::IsHaveAccount() //계좌 여부
{
    // 계좌 개수를 저장할 변수
    string CountAccount = "";

    // 계좌가 있는지 확인하는 SQL 쿼리 생성
    string IsHaveAccount = "SELECT COUNT(*) FROM account_table WHERE ID = '" + ID + "'";

    // SQL 쿼리 실행
    if (mysql_query(&Conn, IsHaveAccount.c_str()) == 0) {
        // 결과를 저장
        MYSQL_RES* result = mysql_store_result(&Conn);

        // 결과가 존재하는 경우
        if (result != NULL) {
            // 첫 번째 행을 가져옴
            MYSQL_ROW row = mysql_fetch_row(result);

            // 행이 존재하는 경우 계좌 개수를 가져와 CountAccount에 저장
            if (row != NULL) {
                CountAccount = row[0];
            }

            // 결과 세트 해제
            mysql_free_result(result);
        }
    }
    //만약에 계좌가 존재 하지 않을 경우
    if (CountAccount == "0") {
        cout << "계좌가 없습니다!\n계좌 생성 먼저 해주세요.";
        Sleep(3000);
        UserFunction(); //8가지의 메뉴가 있는 함수
    }
}

void User::deposit() //입금
{

    // 회원이 가지고 있는 모든 계좌 출력 
    string AllAccount = "SELECT AccountName, AccountNumber, Balance FROM account_table WHERE ID = '" + ID + "'";
    // 쿼리 실행
    mysql_query(&Conn, AllAccount.c_str());
    // 결과 저장
    MYSQL_RES* result = mysql_store_result(&Conn);

    // 만약에 결과가 없다면 함수 종료
    if (result == NULL) {
        fprintf(stderr, "Mysql query error:%s\n", mysql_error(ConnPtr));
        return;
    }
    // 결과 출력
    int i = 1;
    cout << Name << "님의 계좌 목록\n\n";
    cout << "No       계좌 이름           계좌번호            잔액\n";
    while ((Row = mysql_fetch_row(result)) != NULL)
    {
        cout << i << "        " << Row[0] << "         " << Row[1] << "            " << Row[2] << endl;
        i++;
    }

    cout << "\n";

    int DepositAccount;
    cout << "입금 하실 계좌를 입력하세요. >> ";
    cin >> DepositAccount;

    string AccountName;
    string DepositQuery = "SELECT AccountName FROM account_table WHERE AccountNumber = '" + to_string(DepositAccount) + "'";
    //계좌 테이블에서 입력받은 DepositAccount에 AccountName를 조회해주세요

    //쿼리 실행 및 결과 저장
    if (mysql_query(&Conn, DepositQuery.c_str()) == 0) {
        MYSQL_RES* result = mysql_store_result(&Conn);
        if (result != NULL) {
            MYSQL_ROW row = mysql_fetch_row(result);
            if (row != NULL) {
                AccountName = row[0];
            }
        }
        mysql_free_result(result);
    }
    else {
        cout << "계좌가 존재하지 않습니다.\n 계좌 번호 재확인 바랍니다!";
        Sleep(3000);
        UserFunction();
    }
    cout << "입금하시는 계좌명이 " << AccountName << "이 맞으신가요? <Yes/No> >> ";

    string AccountNameCheck;
    cin >> AccountNameCheck;

    if (AccountNameCheck == "No" || AccountNameCheck == "NO" || AccountNameCheck == "N" || AccountNameCheck == "n") {
        cout << "계좌 번호 재확인 바랍니다!";
        Sleep(3000);
        UserFunction();
    }

    int InputDeposit;
    cout << "입금 하실 금액을 입력하세요. >> ";
    cin >> InputDeposit;

    string updateQuery = "UPDATE account_table SET Balance = Balance+'" + to_string(InputDeposit) + "' WHERE AccountNumber = '" + to_string(DepositAccount) + "'";
    //AccountNumber가 입력 받은DepositAccount인 계좌테이블에서 입력 받은 금액을 업데이트 해주세요 
    if (mysql_query(&Conn, updateQuery.c_str()) == 0) {
        cout << "성공적으로 입금이 완료되었습니다.";

        Sleep(3000);
    }
    else
    {
        cout << "업데이트를 수행하는 동안 오류가 발생했습니다.";
        Sleep(3000);
    }

}

void User::withdraw() //출금 
{

    // 모든 계좌 출력 
    string AllAccount = "SELECT AccountName, AccountNumber, Balance FROM account_table WHERE ID = '" + ID + "'";
    //계좌 테이블에서 입력 받은 ID에 AccountName, AccountNumber, Balance  순서대로 조회 해주세요

    mysql_query(&Conn, AllAccount.c_str());
    //쿼리 실행
    MYSQL_RES* result = mysql_store_result(&Conn);
    //결과 저장

    if (result == NULL) {
        fprintf(stderr, "Mysql query error:%s\n", mysql_error(ConnPtr));
        return;
    }


    // 결과 출력
    int i = 1;
    cout << Name << "님의 계좌 목록\n\n";
    cout << "No       계좌 이름           계좌번호            잔액\n";
    while ((Row = mysql_fetch_row(result)) != NULL)
    {
        cout << i << "        " << Row[0] << "         " << Row[1] << "            " << Row[2] << endl;
        i++;
    }

    cout << "\n";

    int WithdrawAccount;
    cout << "출금 하실 계좌 번호를 입력하세요. >> ";
    cin >> WithdrawAccount;

    //출금하는 계좌명 불러오는 내용
    string AccountName;
    string AccountNameQuery = "SELECT AccountName FROM account_table WHERE AccountNumber = '" + to_string(WithdrawAccount) + "'";
    //입력 받은 WithdrawAccount에서 AccountName를 조회해주세요 계좌 테이블에서

    // 쿼리 실행 및 결과 저장
    if (mysql_query(&Conn, AccountNameQuery.c_str()) == 0) {
        MYSQL_RES* result = mysql_store_result(&Conn);
        if (result != NULL) {
            MYSQL_ROW row = mysql_fetch_row(result);
            if (row != NULL) {
                AccountName = row[0];
            }
        }
    }

    //출금하는 계좌가 본인 명의인지 확인하는 내용
    string AccountID;
    string AccountIDQuery = "SELECT ID FROM account_table WHERE AccountNumber = '" + to_string(WithdrawAccount) + "'";
    //AccountNumber가 WithdrawAccount인 계좌테이블에서 ID를 조회 해주세요

    //쿼리 실행 및 결과 저장
    if (mysql_query(&Conn, AccountIDQuery.c_str()) == 0) {
        MYSQL_RES* result = mysql_store_result(&Conn);
        if (result != NULL) {
            MYSQL_ROW row = mysql_fetch_row(result);
            if (row != NULL) {
                AccountID = row[0];
            }
        }
    }
    else {
        cout << "계좌가 존재하지 않습니다.\n 계좌 번호 재확인 바랍니다!";
        Sleep(3000);
        UserFunction();
    }

    //만약 로그인된 아이디와 입력받은 계좌번호의 아이디가 다를 경우
    if (AccountID != ID) {
        cout << "출금하려는 계좌가 본인 명의가 아닙니다.\n 계좌 확인을 다시 해주세요.";
        Sleep(3000);
        UserFunction();
    }

    cout << "출금하시는 계좌명이 " << AccountName << "이 맞으신가요? <Yes/No> >> ";
    string AccountNameCheck;
    cin >> AccountNameCheck;
    if (AccountNameCheck == "No" || AccountNameCheck == "NO") {
        cout << "계좌 번호 재확인 바랍니다!";
        Sleep(3000);
        UserFunction();
    }

    string checkPW;
    cout << "사용자 비밀번호를 입력하세요. >>";
    cin >> checkPW;
    //사용자 비밀번호와 입력 비밀번호가 다를 경우
    if (checkPW != Password) {
        cout << "비밀번호 재확인 바랍니다!";
        Sleep(3000);
        UserFunction();
    }

    int InputWithdraw;
    cout << "출금 하실 금액을 입력하세요. >> ";
    cin >> InputWithdraw;

    //잔액이 부족한지 확인하는 쿼리
    string NowAccountBalnce;
    string IsBalanceQuery = "SELECT Balance FROM account_table WHERE AccountNumber = '" + to_string(WithdrawAccount) + "'";
    //AccountNumber가 WithdrawAccount인 계좌 테이블에서 잔액을 조회해주세요

    //쿼리 실행 및 결과 저장
    if (mysql_query(&Conn, IsBalanceQuery.c_str()) == 0) {
        MYSQL_RES* result = mysql_store_result(&Conn);
        if (result != NULL) {
            MYSQL_ROW row = mysql_fetch_row(result);
            if (row != NULL) {
                NowAccountBalnce = row[0];
            }
        }
        mysql_free_result(result);
    }

    //만약 출금하려는 금액이 잔액보다 클 경우
    if (stoi(NowAccountBalnce) < InputWithdraw)
    {
        cout << "잔액이 부족합니다!";
        Sleep(3000);
        UserFunction();
    }

    //출금 쿼리
    string updateQuery = "UPDATE account_table SET Balance = Balance-'" + to_string(InputWithdraw) + "' WHERE AccountNumber = '" + to_string(WithdrawAccount) + "'";
    //AccountNumber가 WithdrawAccount인 계좌 테이블에서 잔액을 InputWithdraw로 업데이트 해주세요

    if (mysql_query(&Conn, updateQuery.c_str()) == 0) {
        cout << "성공적으로 출금이 완료되었습니다.\n";
    }
    else {
        cout << "업데이트를 수행하는 동안 오류가 발생했습니다.";
        Sleep(3000);
    }

    //출금 후 잔액 확인 쿼리
    string BalanceQuery = "SELECT Balance FROM account_table WHERE AccountNumber = '" + to_string(WithdrawAccount) + "'";
    //AccountNumber가 WithdrawAccount인 계좌 테이블에서 잔액을 조회해주세요

    string AccountBalnce;

    //쿼리 실행 및 결과 저장
    if (mysql_query(&Conn, BalanceQuery.c_str()) == 0) {
        MYSQL_RES* result = mysql_store_result(&Conn);
        if (result != NULL) {
            MYSQL_ROW row = mysql_fetch_row(result);
            if (row != NULL) {
                AccountBalnce = row[0];
            }
        }
        mysql_free_result(result);
    }
    cout << "잔액은 " << AccountBalnce << "입니다.";
    Sleep(3000);
}



void User::transfer() //계좌이체 
{

    string YourAccountName;
    int YourAccount;
    cout << "이체 받으실 계좌 번호를 입력하세요. >> ";
    cin >> YourAccount;

    //이체(입금) 계좌명 불러오는 쿼리
    string SendAccountName;
    string YourAccountNameQuery = "SELECT AccountName FROM account_table WHERE AccountNumber = '" + to_string(YourAccount) + "'";
    //AccountNumber가 YourAccount인 계좌 테이블에서 AccountName을 조회해주세요

    //쿼리 실행 및 결과 저장
    if (mysql_query(&Conn, YourAccountNameQuery.c_str()) == 0) {
        MYSQL_RES* result = mysql_store_result(&Conn);
        if (result != NULL) {
            MYSQL_ROW row = mysql_fetch_row(result);
            if (row != NULL) {
                YourAccountName = row[0];
            }
        }
    }
    else {
        cout << "계좌가 존재하지 않습니다.\n 계좌 번호 재확인 바랍니다!";
        Sleep(3000);
        UserFunction();
    }

    cout << "이체 받으실 계좌명의 계좌명이 " << YourAccountName << "이 맞으신가요? <Yes/No> >> ";
    string YourAccountNameCheck;
    cin >> YourAccountNameCheck;
    if (YourAccountNameCheck == "No" || YourAccountNameCheck == "NO" || YourAccountNameCheck == "N" || YourAccountNameCheck == "n") {
        cout << "계좌 번호 재확인 바랍니다!";
        Sleep(3000);
        UserFunction();
    }

    //이체(출금) - 본인 모든 계좌 출력
    string MyAllAccount = "SELECT AccountName, AccountNumber, Balance FROM account_table WHERE ID = '" + ID + "'";
    //account_table이 ID인 계좌테이블에서 AccountName, AccountNumber, Balance을 조회해주세요

    //쿼리 실행 및 결과 저장
    mysql_query(&Conn, MyAllAccount.c_str());
    MYSQL_RES* result = mysql_store_result(&Conn);

    if (result == NULL) {
        fprintf(stderr, "Mysql query error:%s\n", mysql_error(ConnPtr));
        return;
    }

    int i = 1;
    cout << "\nNo       계좌 이름           계좌번호            잔액\n";
    while ((Row = mysql_fetch_row(result)) != NULL)
    {
        cout << i << "        " << Row[0] << "         " << Row[1] << "            " << Row[2] << endl;
        i++;
    }
    cout << "\n";

    //이체(출금) - 계좌 선택

    int MyAccountNumber;
    cout << "이체 하실 계좌 번호를 입력하세요. >> ";
    cin >> MyAccountNumber;

    //이체(출금) 계좌명 불러오는 쿼리
    string MyAccountName;
    string AccountNameQuery = "SELECT AccountName FROM account_table WHERE AccountNumber = '" + to_string(MyAccountNumber) + "'";
    //AccountNumber가 MyAccountNumber인 계좌 테이블에서 AccountName 조회해주세요

    //쿼리 실행 및 결과 저장
    if (mysql_query(&Conn, AccountNameQuery.c_str()) == 0) {
        MYSQL_RES* result = mysql_store_result(&Conn);
        if (result != NULL) {
            MYSQL_ROW row = mysql_fetch_row(result);
            if (row != NULL) {
                MyAccountName = row[0];
            }
        }
    }

    //계좌가 본인 명의인지 확인하는 쿼리
    string AccountID;
    string AccountIDQuery = "SELECT ID FROM account_table WHERE AccountNumber = '" + to_string(MyAccountNumber) + "'";
    //AccountNumber가 MyAccountNumber인 계좌테이블에서 ID를 조회해주세요

    //쿼리 실행 및 결과 저장
    if (mysql_query(&Conn, AccountIDQuery.c_str()) == 0) {
        MYSQL_RES* result = mysql_store_result(&Conn);
        if (result != NULL) {
            MYSQL_ROW row = mysql_fetch_row(result);
            if (row != NULL) {
                AccountID = row[0];
            }
        }
    }
    else {
        cout << "계좌가 존재하지 않습니다.\n 계좌 번호 재확인 바랍니다!";
        Sleep(3000);
        UserFunction();
    }

    //만약 로그인된 아이디와 입력받은 계좌번호의 아이디가 다를 경우
    if (AccountID != ID) {
        cout << "이체하실 계좌가 본인 명의가 아닙니다.\n 계좌 확인을 다시 해주세요.";
        Sleep(3000);
        UserFunction();
    }

    cout << "이체하시는 계좌명이 " << MyAccountName << "이 맞으신가요? <Yes/No> >> ";
    string AccountNameCheck;
    cin >> AccountNameCheck;
    if (AccountNameCheck == "No" || AccountNameCheck == "NO") {
        cout << "계좌 번호 재확인 바랍니다!";
        Sleep(3000);
        UserFunction();
    }


    string checkPW;
    cout << "사용자 비밀번호를 입력하세요. >>";
    cin >> checkPW;
    //사용자 비밀번호와 입력 비밀번호가 다를 경우
    if (checkPW != Password) {
        cout << "비밀번호 재확인 바랍니다!";
        Sleep(3000);
        UserFunction();
    }

    int InputTransfer;
    cout << "이체 하실 금액을 입력하세요. >> ";
    cin >> InputTransfer;

    //잔액이 부족한지 확인하는 쿼리
    string MyAccountBalnce;
    string MyBalanceQuery = "SELECT Balance FROM account_table WHERE AccountNumber = '" + to_string(MyAccountNumber) + "'";
    //AccountNumber가 MyAccountNumber 계좌 테이블에서 Balance(잔액)을 조회해주세요

    //쿼리 실행 및 결과 저장
    if (mysql_query(&Conn, MyBalanceQuery.c_str()) == 0) {
        MYSQL_RES* result = mysql_store_result(&Conn);
        if (result != NULL) {
            MYSQL_ROW row = mysql_fetch_row(result);
            if (row != NULL) {
                MyAccountBalnce = row[0];
            }
        }
        mysql_free_result(result);
    }

    //만약 출금하려는 금액이 잔액보다 클 경우
    if (stoi(MyAccountBalnce) < InputTransfer) {
        cout << "잔액이 부족합니다!";
        Sleep(3000);
        UserFunction();
    }

    //출금 내용
    string WithdrawAccountQuery = "UPDATE account_table SET Balance = Balance-'" + to_string(InputTransfer) + "' WHERE AccountNumber = '" + to_string(MyAccountNumber) + "'";
    //AccountNumber가 MyAccountNumber인 계좌테이블에서 잔액을 업데이트 해주세요

    //쿼리 실행
    if (mysql_query(&Conn, WithdrawAccountQuery.c_str()) == 0) {
        cout << "정상 실행 완료...\n";
    }
    else {
        cout << "업데이트를 수행하는 동안 오류가 발생했습니다.";
        Sleep(3000);
    }

    //이체 완료
    string updateQuery = "UPDATE account_table SET Balance = Balance+'" + to_string(InputTransfer) + "' WHERE AccountNumber = '" + to_string(YourAccount) + "'";
    //AccountNumber가 YourAccount 게좌테이블에서 잔액을 업데이트 해주세요

     //쿼리실행
    if (mysql_query(&Conn, updateQuery.c_str()) == 0) {
        cout << "성공적으로 이체가 완료되었습니다.";
        Sleep(3000);
    }
    else {
        cout << "업데이트를 수행하는 동안 오류가 발생했습니다.";
        Sleep(3000);
    }
}

void User::checkmyInfo() // 내 정보 확인
{

    cout << "ID :" << ID << endl;
    cout << "이름 :" << Name << endl;
    cout << "전화번호 :" << Phone << endl;

    // 모든 계좌 출력 
    string AllAccount = "SELECT AccountName, AccountNumber, Balance FROM account_table WHERE ID = '" + ID + "'";
    //ID가 입력받은 ID인 계좌 테이블에서 AccountName, AccountNumber, Balance 조회해주세요

    //쿼리 실행 및 결과 저장
    mysql_query(&Conn, AllAccount.c_str());
    MYSQL_RES* result = mysql_store_result(&Conn);

    if (result == NULL) {
        fprintf(stderr, "Mysql query error:%s\n", mysql_error(ConnPtr));
        return;
    }


    // 결과 출력
    int i = 1;
    cout << Name << "님의 계좌 목록\n\n";
    cout << "No       계좌 이름           계좌번호            잔액\n";
    while ((Row = mysql_fetch_row(result)) != NULL)
    {
        cout << i << "        " << Row[0] << "         " << Row[1] << "            " << Row[2] << endl;
        i++;
    }
    Sleep(3000);
}


void User::displayCustomerTable() //관리자 기능
{
    // 고객 테이블 출력 쿼리 요청
    const char* customerquery = "SELECT * FROM customer_table";
    //고객 테이블에서 모든 칼럼을 조회해주세요

    Stat = mysql_query(&Conn, customerquery);

    if (Stat != 0) {
        fprintf(stderr, "Mysql query error:%s\n", mysql_error(ConnPtr));
        return;
    }

    Result = mysql_store_result(&Conn); //MySQL에서 실행한 쿼리의 결과 집합을 Result에 저장

    cout << "Customer Table:\n";
    cout << setw(4) << left << "No";
    cout << setw(8) << left << "ID";
    cout << setw(16) << left << "이름";
    cout << setw(20) << left << "전화번호";
    cout << setw(16) << left << "비밀번호\n";

    // 반복문 내에서 Row 변수를 사용하여 결과 집합에서 한 행씩 데이터를 처리이때, NULL을 만날 때까지 계속 반복
    while ((Row = mysql_fetch_row(Result)) != NULL)
    {
        cout << setw(4) << left << Row[0];
        cout << setw(8) << left << Row[1];
        cout << setw(16) << left << Row[2];
        cout << setw(20) << left << Row[3];
        cout << setw(16) << left << Row[4] << "\n";
    }

    cout << "\n";

    // 계좌 테이블 출력 쿼리 요청
    const char* accountquery = "SELECT * FROM account_table";
    //계좌 테이블에서 모든 칼럼을 조회해주세요

    Stat = mysql_query(&Conn, accountquery);

    if (Stat != 0) {
        fprintf(stderr, "Mysql query error:%s\n", mysql_error(&Conn));
        return;
    }

    Result = mysql_store_result(&Conn); //MySQL에서 실행한 쿼리의 결과 집합을 Result에 저장

    // 결과 출력
    cout << "Account Table:\n";
    cout << setw(8) << left << "ID";
    cout << setw(16) << left << "계좌명";
    cout << setw(16) << left << "계좌번호";
    cout << setw(8) << left << "잔액\n";

    // 반복문 내에서 Row 변수를 사용하여 결과 집합에서 한 행씩 데이터를 처리이때, NULL을 만날 때까지 계속 반복
    while ((Row = mysql_fetch_row(Result)) != NULL)
    {
        cout << setw(8) << left << Row[0];
        cout << setw(16) << left << Row[1];
        cout << setw(16) << left << Row[2];
        cout << setw(8) << left << Row[3] << "\n";
    }

    Sleep(6000); //6초 설정
}

void User::UserFunction() {
    GetUserInfo();
    system("cls");

    cout << "---------------환영합니다!" << Name << "님!---------------" << "\n";
    cout << "0. 계좌 생성" << endl;
    cout << "1. 예금 입금" << endl;
    cout << "2. 예금 출금" << endl;
    cout << "3. 계좌 이체" << endl;
    cout << "4. 내 정보 보기 " << endl;
    cout << "5. 로그아웃" << endl;
    cout << "6. 관리자 기능" << endl;
    cout << "7. 프로그램 종료" << endl;
    cout << "\n";
    cout << "원하시는 메뉴를 입력해 주세요. >> ";
    cin >> UserMenuNum;

    switch (UserMenuNum) {
    case 0:
        OpenAccount(); break;//계좌 개설
    case 1:
        IsHaveAccount();
        deposit();  break; //예금 입금
    case 2:
        IsHaveAccount();
        withdraw();  break;//예금 출금
    case 3:
        IsHaveAccount();
        transfer(); break;//계좌 이체
    case 4:
        checkmyInfo(); break;//내 정보 보기
    case 5:
        login(); break; // 로그아웃
    case 6: //관리자 기능
    {
        string adminPassword;
        cout << "관리자 비밀번호를 입력하세요: ";
        cin >> adminPassword;

        // 입력된 비밀번호를 기대하는 관리자 비밀번호와 비교
        if (adminPassword == "1q2w3e4r!") {
            displayCustomerTable();  // 관리자 기능 함수 호출
        }
        else {
            cout << "잘못된 비밀번호입니다. 관리자 권한이 없습니다.\n";
            Sleep(1000);
        }
        break;
    }
    case 7:
        cout << "프로그램을 종료합니다" << endl; // 프로그램 종료
        cout << "\n";
        cout << "이용해 주셔서 감사합니다" << endl;
        cout << "\n";
        end();
        exit(0);

    default:
        system("cls");
        cout << "잘못된 입력입니다. 다시 입력해주세요.\n";
        UserFunction();
    }
}

void Start::start() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    cout << "\n";
    cout << "                                 □□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
    cout << "                                 □                                □\n";
    cout << "                                 □                                □\n";
    cout << "                                 □        ";
    SetConsoleTextAttribute(hConsole, 12);
    cout << "기능을 입력하세요";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "       □\n";
    cout << "                                 □                                □\n";
    cout << "                                 □                                □\n";
    cout << "                                 □           1. 로그인            □\n";
    cout << "                                 □                                □\n";
    cout << "                                 □          2. 회원가입           □\n";
    cout << "                                 □                                □\n";
    cout << "                                 □            3. 종료             □\n";
    cout << "                                 □                                □\n";
    cout << "                                 □                                □\n";
    cout << "                                 □□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
    cout << "\n";
    cout << "이용하실 기능을 선택해 주세요 >> ";
    cin >> StartMenuNum;
    switch (StartMenuNum) {
    case 1:
        login();  break;
    case 2:
        signup();  break;
    case 3:
        cout << "프로그램을 종료합니다" << endl;
        cout << "\n";
        cout << "이용해 주셔서 감사합니다" << endl;
        cout << "\n";
        end();
        exit(0);
    default:
        system("cls");
        cout << "잘못된 입력입니다. 다시 입력해주세요.\n";
        start();
    }

    if (MemberNo != "NULL") {
        //로그인 완료
    }
}


//////////////////////////////////////MYSQL 연결 + MAIN 시작//////////////////////////////////////

int main()
{
    //system("chcp 65001");
    system("CS BANK");
    User user; //User 클래스의 객체 선언
    Start customer; //Start 클래스의 객체 선언

    mysql_init(&Conn); // MySQL 정보 초기화  

    // 데이터베이스와 연결
    ConnPtr = mysql_real_connect(&Conn, "localhost", "root", "1q2w3e4r!", "cs_bank", 3306, (char*)NULL, 0);

    // 연결 결과 확인. null일 경우 실패
    if (ConnPtr == NULL) {
        fprintf(stderr, "Mysql query error:%s", mysql_error(&Conn));
        return 1;
    }

    //콘솔창 설정
    SetConsoleTitle("CS_Bank");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("mode con: cols=100 lines=40");

    //////////////////////////////////////은행 구문 시작//////////////////////////////////////
    while (1)
    {
        system("cls");
        //하늘 색상 출력
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
        cout << "\n\n\n";
        cout << "                 ######   ######     ########     ###    ##    ## ##    ##                 \n";
        cout << "                ##    ## ##    ##    ##     ##   ## ##   ###   ## ##   ##                  \n";
        cout << "                ##       ##          ##     ##  ##   ##  ####  ## ##  ##                   \n";
        cout << "                ##        ######     ########  ##     ## ## ## ## #####                    \n";
        cout << "                ##             ##    ##     ## ######### ##  #### ##  ##                   \n";
        //초록 색상 출력
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        cout << "                ##    ## ##    ##    ##     ## ##     ## ##   ### ##   ##                  \n";
        cout << "                 ######   ######     ########  ##     ## ##    ## ##    ##                 \n";
        cout << "\n\n\n\n";
        //검정 색상 출력
        SetConsoleTextAttribute(hConsole, 15);
        cout << "                                  CS제일은행에 오신것을 환영합니다!                                 \n\n\n\n";

        customer.start();
        while (1)
        {
            //회원이 No를 가지고 있으면 8가지 메뉴를 이용할 수 있음 즉, CS뱅크의 회원이 아니라면 메뉴를 이용할 수 없음
            if (MemberNo != "NULL")
            {
                user.UserFunction();
            }
            else
            {
                break;
            }
        }
    }
    mysql_free_result(Result);// MySQL C API에서 사용한 메모리를 해제하는 함수
    mysql_close(ConnPtr); // MySQL 데이터베이스 연결을 닫는 함수
    end();
    return 0;
}
