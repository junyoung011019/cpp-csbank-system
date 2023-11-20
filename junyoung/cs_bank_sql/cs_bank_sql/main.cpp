#include "Framework.h"


MYSQL Conn;                //mysql 정보 담을 구조체
MYSQL* ConnPtr = NULL;    //mysql 핸들
MYSQL_RES* Result;        //쿼리 성공시 결과를 담는 구조체 포인터
MYSQL_ROW Row;            //쿼리 성공시 결과로 나온 행의 정보를 담는 구조체
int Stat;                 //쿼리 요청 후 결과 (성공, 실패)

int EndCode = 0;


class Login {
public:
    string Input_ID, Input_PW;
    int missing = 0, error = 0;
    int MemberNo = 0;
protected:
    void login() {}
};

void Login::login() {
    system("cls");
    cout << "---------------로그인---------------" << "\n";
    while (1) {
        cout << "아이디를 입력하세요. >";
        cin >> Input_ID;
        cout << "비밀번호를 입력하세요. >";
        cin >> Input_PW;
        //아이디 비밀번호를 sql에서 확인하는 구문
        if (1) {
            cout << "환영합니다!";
                //MemberNo 변수에 사용자의 키 값을 삽입
            break;
        }
        else {
            missing += 1;
            cout << "비밀번호가 옳지않습니다.";
            cout << "현재 비밀번호" << missing << "회 오류입니다.";
            if missing < 5{
                error = 1;
                break;
            }
            cout << "로그인 5회 실패시 로그인이 제한됩니다.";
        }
    }

}

class SignUp {
public:
    string ID, PW, NAME;
    int PhoneNumber = 0;
    string AcccountNumber;
protected:
    void signup();
};

void SignUp::signup() {
    system("cls");
    cout << "---------------회원가입---------------" << "\n";
    cout << "이름을 입력하세요. (현재는 영문만 가능) >";
    cin >> NAME;
    while (1) {
        cout << "사용하실 아이디를 입력하세요. (영문 2자)";
        cin >> ID;
        char idcheck[] = "SELECT ID FROM customer_table";
        cout << idcheck << endl;
        if (idcheck[0] == NULL) {
            break;
        }
        cout << "이미 존재하는 아이디입니다!\n";
        break;
    }
    cout << "사용하실 비밀번호를 입력하세요. (영문 2자)";
    cin >> PW;
    while (1) {
        cout << "전화번호를 입력하세요.";
        cin >> PhoneNumber;
        char phonenumcheck[] = "SELECT PhoneNumber FROM customer_table";
        if (phonenumcheck[0] == NULL) {
            break;
        }
        cout << "이미 가입된 회원입니다!\n";
        break;
    }
    cout << "고객님의 계좌 번호는" << PhoneNumber << "0 입니다!\n";
    AcccountNumber = PhoneNumber;
    stringstream AcccountNumber;
    cout << "가입을 진심으로 환영합니다!!!\n";
    "INSERT INTO `cs_bank`.`customer_table` (`ID`, `Name`, `Phone`, `Password`, `ACCOUNTNUMBER`) VALUES(ID, NAME, PhoneNumber, PW, AcccountNumber)";
    int a;
    cin >> a;
}

class Start : public Login, public SignUp {
public:
    int StartMenuNum = 0;
    void start();
};

class User : public Start {
public:
    int UserMenuNum = 0;
    void UserFunction();
    //유저의 정보를 받아오는 내용
    string UserName;


    deposit();
    withdraw();
    transfer();
    AccountCheck();
    TransferCheck(); break;
}

void User::deposit() {
    int InputDeposit;
    cout << "입금 하실 금액을 입력하세요.";
    cin >> InputDeposit;

}

void User::withdraw() {

}

void User::transfer() {

}

void User::AccountCheck() {

}

void User::TransferCheck() {

}

void User::UserFunction() {
    system("cls");
    cout << "---------------환영합니다!" << UserName << "님!---------------" << "\n";
    cout << "1. 예금 입금" << endl;
    cout << "2. 예금 출금" << endl;
    cout << "3. 계좌 이체" << endl;
    cout << "4. 계좌 정보 조회" << endl;
    cout << "5. 이체 내역 확인" << endl;
    cout << "6. 로그아웃" << endl;
    cout << "7. 프로그램 종료" << endl
        cin >> UserMenuNum;
    switch (UserMenuNum) {
    case 1:
        deposit();  break;
    case 2:
        withdraw();  break;
    case 3:
        transfer(); break;
    case 4:
        AccountCheck(); break;
    case 5:
        TransferCheck(); break;
    case 6:
        MemberNo = 0;
        break;
    case 7:
        EndCode = 1; break;
    default:
        system("cls");
        cout << "잘못된 입력입니다. 다시 입력해주세요.\n";
        UserFunction();
    }
}

void Start::start() {

    cout << "------------------------------------" << "\n";
    cout << "1. 회원가입" << endl;
    cout << "2. 로그인" << endl;
    cout << "3. 종료" << endl;
    cout << "------------------------------------" << "\n";
    cin >> StartMenuNum;
    switch (StartMenuNum) {
    case 1:
        signup();  break;
    case 2:
        login();  break;
    case 3:
        EndCode = 1; break;
    default:
        system("cls");
        cout << "잘못된 입력입니다. 다시 입력해주세요.\n";
        start();
    }
    if (error = 1) {
        cout << "에러 코드 1";
        cout << "로그인에 5회 실패했습니다.";
        cout << "프로그램이 종료됩니다";
        EndCode = 1; break;
    }
    if (MemberNo != 0) {
        //로그인 완료
        break;
    }
}

int main()
{
    //////////////////////////////////////MYSQL 연결//////////////////////////////////////



    mysql_init(&Conn);         //mysql 정보 초기화

    //데이터베이스와 연결
    ConnPtr = mysql_real_connect(&Conn, "localhost", "root", "1q2w3e4r!", "cs_bank", 3306, (char*)NULL, 0);

    //연결 결과 확인. null일경우 실패
    if (ConnPtr == NULL)
    {
        fprintf(stderr, "Mysql query error:%s", mysql_error(&Conn));
        return 1;
    }

    //데이터베이스와 연결해제
    char Query[] = "SELECT * FROM customer_table";    //세미콜론을 제외하고 쿼리문 작성
    Stat = mysql_query(ConnPtr, Query);           //쿼리 요청 및 성공여부 받아오기
    if (Stat != 0)                                //쿼리 요청 실패 시 에외 처리
    {
        fprintf(stderr, "Mysql query error:%s\n", mysql_error(&Conn));
        return 1;
    }
    Result = mysql_store_result(ConnPtr);          //결과확인
    while ((Row = mysql_fetch_row(Result)) != NULL) //결과 출력
    {
        printf("%s %s %s %s %s %s\n", Row[0], Row[1], Row[2], Row[3], Row[4], Row[5]);
    }
    mysql_free_result(Result);                         //결과 비우기

    mysql_close(ConnPtr);

    //////////////////////////////////////은행 구문 시작//////////////////////////////////////
    while (1) {
        system("cls");
        cout << " =========================**cs 제일은행에 오신 걸 환영합니다**=============================\n\n";
        Start customer;
        if (customer.MemberNo == 0) {
            customer.start();

        }
        else {
            User user;
            user.UserFunction();
        }
        if (EndCode == 1) {
            cout << "프로그램이 종료 됩니다!";
            return 0;
        }



    }
}