#include "Framework.h"


MYSQL Conn;                //mysql 정보 담을 구조체
MYSQL* ConnPtr = NULL;    //mysql 핸들
MYSQL_RES* Result;        //쿼리 성공시 결과를 담는 구조체 포인터
MYSQL_ROW Row;            //쿼리 성공시 결과로 나온 행의 정보를 담는 구조체
int Stat;                 //쿼리 요청 후 결과 (성공, 실패)

int g_end = 0;

class Login {
protected:
    void login() {}
};

class SignUp {
public:
    string ID, PW, NAME;
    int PhoneNumber = 0;
    string AcccountNumber;
protected:
    void signup();
};

void SignUp::signup(){
    system("cls");
    cout << "---------------회원가입---------------" << "\n";
    cout << "이름을 입력하세요. (현재는 영문만 가능) >";
    cin >> NAME;
    while (1) {
        cout << "사용하실 아이디를 입력하세요. (영문 2자)";
        cin >> ID;
        char idcheck[] = "SELECT ID FROM customer_table";
        cout << idcheck<<endl;
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
    AcccountNumber= PhoneNumber;
    stringstream AcccountNumber;
    cout << "가입을 진심으로 환영합니다!!!\n";
    "INSERT INTO `cs_bank`.`customer_table` (`ID`, `Name`, `Phone`, `Password`, `ACCOUNTNUMBER`) VALUES(ID, NAME, PhoneNumber, PW, AcccountNumber)";
    int a;
    cin >> a;

    
}

class Start: public Login, public SignUp{
public:
    void start();
    int StartMenuNum = 0;
};

void Start::start(){
    
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
        g_end = 1; break;
    default:
        system("cls");
        cout << "잘못된 입력입니다. 다시 입력해주세요.\n";
        start();
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
        customer.start();
        if (g_end == 1) {
            return 0;
        }
    }
}
