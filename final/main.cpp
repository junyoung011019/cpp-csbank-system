#include <iostream> //�Է� �� ��� �۾��� �ٷ�� ����� ��Ʈ�� ���
#include <mysql.h>  //MySQL �����ͺ��̽� ������ ���� ��� ����
#include <string>   //C++���� ���ڿ� ������ ���� ��� ����
#include <windows.h> // Windows API �Լ��� ���� ��� ����
#include <cstdlib>  // exit �Լ��� ����ϱ� ���� ���
#include <iomanip>  //������ ���� ���
#include <iomanip>  // setw ��� �߰�

using namespace std;

MYSQL Conn;                              // MySQL ���� ���� ����ü
MYSQL* ConnPtr = NULL;                  // MySQL �ڵ�
MYSQL_RES* Result;                      // ���� ������ ����� ��� ����ü ������
MYSQL_ROW Row;                  // ���� ������ ����� ���� ���� ������ ��� ����ü



int Stat;              // ���� ��û �� ��� (����, ����)
string MemberNo = "NULL"; // ȸ�� ��ȣ�� ��Ÿ���� Member No ����

void end() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // �ϴ� ���� ���
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
    // ������� �����Ͽ� ���� ����� ������� ��Ÿ������ ��
    SetConsoleTextAttribute(hConsole, 15);
}

/////////////////////////////////////////////////�α��� Ŭ����//////////////////////////////////////////
class Login {
public:
    string Input_ID, Input_PW;
    int missing = 0;
protected:
    void login();
};

void Login::login()
{
    mysql_init(&Conn); // MySQL ���� �ʱ�ȭ

    // �����ͺ��̽��� ����
    ConnPtr = mysql_real_connect(&Conn, "localhost", "root", "1q2w3e4r!", "cs_bank", 3306, (char*)NULL, 0);
    // MySql DB�� �����ϱ� ���� ��
    //  MYSQL ����ü�� ���� �����ͷ� ��, ���� ���� �� ����ü�� �ʱ�ȭ ȣ��Ʈ�� / ����� �̸� / ��й�ȣ / ��Ű�� / ��Ʈ��ȣ / �����Ϳ� ���� 0 ��� C++���� NULL�� �ؼ�

    // ���� ��� Ȯ��. null�� ��� ����
    if (ConnPtr == NULL) {
        fprintf(stderr, "Mysql query error:%s", mysql_error(&Conn));
        return;
    }

    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //�ϴ� ���� ���
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
        cout << "���̵� �Է��ϼ���. >";
        cin >> Input_ID;
        cout << "��й�ȣ�� �Է��ϼ���. >";
        cin >> Input_PW;

        // SQL ���� - customer_table���� ID�� �ִ� ��� Į���� �����ּ���
        string query = "SELECT * FROM customer_table WHERE ID = '" + Input_ID + "' AND password = '" + Input_PW + "'";
        // SQL ������ �����ϰ� ���� ���� Ȯ��
        if (mysql_query(&Conn, query.c_str()) == 0) {
            // ����� ����
            MYSQL_RES* result = mysql_store_result(&Conn);

            // ����� ���� ���
            if (result) {
                // ù ��° ���� ������
                MYSQL_ROW row = mysql_fetch_row(result);

                // ���� �����ϸ� �α��� ����
                if (row) {
                    // ��� ��Ʈ ����
                    mysql_free_result(result);

                    // �α����� ������� ������ �ٽ� �������� SQL ���� ����
                    string whoLoginquery = "SELECT Name, NO FROM cs_bank.customer_table WHERE ID = '" + Input_ID + "'";

                    // SQL ������ �����ϰ� ���� ���� Ȯ��
                    if (mysql_query(&Conn, whoLoginquery.c_str()) == 0) {
                        // ����� ����
                        MYSQL_RES* result = mysql_store_result(&Conn);

                        // ����� ���� ���
                        if (result != NULL) {
                            // ù ��° ���� ������
                            MYSQL_ROW row = mysql_fetch_row(result);

                            // ���� �����ϸ� ȯ�� �޽��� ���
                            if (row != NULL) {
                                cout << "ȯ���մϴ�! " << row[0] << "��!"; //row[0]���� name�� ����Ǿ� ����
                                MemberNo = row[1]; //row[1]���� No�� ����Ǿ� ����
                            }
                        }

                        // ��� ��Ʈ ����
                        mysql_free_result(result);
                    }

                    // 1�� ���
                    Sleep(1000);

                    // �Լ� ���� (�α��� ���� ��)
                    return;
                }
                else {
                    // ��й�ȣ ���� �ִ� 5�� ����
                    missing += 1;
                    cout << "��й�ȣ�� �����ʽ��ϴ�." << endl;
                    cout << "���� ��й�ȣ" << missing << "ȸ �����Դϴ�." << endl;
                    if (missing < 5) {
                        continue;
                    }
                    cout << "�α��� 5ȸ ���н� �α����� ���ѵ˴ϴ�." << endl;

                    //��� ��Ʈ ��ü
                    mysql_free_result(result);

                    //���α׷� ����
                    cout << "\n";
                    cout << "���� : �α��� 5ȸ ����" << endl;
                    cout << "\n\n\n\n";
                    end();
                    exit(0);

                }

            }
        }
        else {
            // ���� ������ ���� �߻�
            cout << "SQL query error: " << mysql_error(&Conn);
        }
    }
    mysql_close(&Conn); // �޸� ������ �����ϰ� ���ҽ��� ��ȯ
}

////////////////////////////////////////////////ȸ������ Ŭ����//////////////////////////////////////////
class SignUp {
public:
    string ID, PW, NAME, confirmPW; //confirmPW : ��й�ȣ�� �ѹ��� ġ�� �ϱ����� ����
    string PhoneNumber;
    string AcccountNumber;
protected:
    void signup();
};

void SignUp::signup() {


    mysql_init(&Conn); // MySQL ���� �ʱ�ȭ

    // �����ͺ��̽��� ����
    MYSQL* ConnPtr = mysql_real_connect(&Conn, "localhost", "root", "1q2w3e4r!", "cs_bank", 3306, (char*)NULL, 0);
    // MySql DB�� �����ϱ� ���� ��
    //  MYSQL ����ü�� ���� �����ͷ� ��, ���� ���� �� ����ü�� �ʱ�ȭ ȣ��Ʈ�� / ����� �̸� / ��й�ȣ / ��Ű�� / ��Ʈ��ȣ / �����Ϳ� ���� 0 ��� C++���� NULL�� �ؼ�

    // ���� ��� Ȯ��. null�� ��� ����
    if (ConnPtr == NULL) {
        fprintf(stderr, "Mysql query error:%s", mysql_error(&Conn));
        return;
    }

    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // �ϴ� ���� ���
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
    // ������� �����Ͽ� ���� ����� ������� ��Ÿ������ ��
    SetConsoleTextAttribute(hConsole, 15);
    cout << "           ================================ȸ������================================                  \n\n\n\n";

    while (1) {
        cout << "\n";
        cout << "����Ͻ� ���̵� �Է��ϼ���. (���� ���� �ִ� 50��) >> ";
        cin >> ID;

        // ID �ߺ� üũ�� ���� SQL ���� ����
        string idCheckQuery = "SELECT ID FROM customer_table WHERE ID = '" + ID + "'";

        // SQL ���� ����
        mysql_query(&Conn, idCheckQuery.c_str());

        // ����� ����
        MYSQL_RES* idCheckResult = mysql_store_result(&Conn);

        // ��� ���� ������ Ȯ���Ͽ� �ߺ� ���θ� �Ǵ�
        if (mysql_num_rows(idCheckResult) == 0) {
            // ��� ��Ʈ ����
            mysql_free_result(idCheckResult);

            // �ߺ��� ������ �ݺ��� ����
            break;
        }

        cout << "�̹� �����ϴ� ���̵� �Դϴ�!\n";
        mysql_free_result(idCheckResult);
    }

    cout << "\n";
    cout << "�̸��� �Է��ϼ���. (����� �Է����ּ���) >> ";
    cin >> NAME;


    // ��ȭ��ȣ �Է�
    cout << "\n";
    cout << "��ȭ��ȣ�� �Է��ϼ���. >> ";
    cin >> PhoneNumber;


    // ��й�ȣ �Է�
    while (1) {
        cout << "\n";
        cout << "����Ͻ� ��й�ȣ�� �Է��ϼ���. (���� 4�ڸ�) >> ";
        cin >> PW;

        // ��й�ȣ Ȯ��
        cout << "��й�ȣ�� �ٽ� �Է��ϼ���. >> ";
        cin >> confirmPW;

        while (PW != confirmPW) {
            cout << "��й�ȣ�� ��ġ���� �ʽ��ϴ�. �ٽ� �Է����ּ���.\n";

            // �ٽ� �Է� �ޱ�
            cout << "\n";
            cout << "����Ͻ� ��й�ȣ�� �Է��ϼ���. (���� 4�ڸ�) >> ";
            cin >> PW;

            cout << "��й�ȣ�� �ٽ� �Է��ϼ���. >> ";
            cin >> confirmPW;
        }

        cout << "��й�ȣ�� �����Ǿ����ϴ�!.\n";

        break;
    }

    cout << "������ �������� ȯ���մϴ�!!!\n";
    Sleep(3000);
    //���� �ο� �Ǻ� �� No�� ����
    int No = 0; // ������ ȸ���� ��ϵǸ� NO(ȸ����ȣ)�� ȸ���� �ľ�


    // �� ���̺��� ���ڵ� ������ �������� ���� SQL ���� ����
    string AccountCountQuery = "SELECT COUNT(*) FROM customer_table";
    //�� ���̺� �ִ� ��� Į���� �˻����ּ���

    // SQL ���� ����
    if (mysql_query(&Conn, AccountCountQuery.c_str()) != 0) {
        // SQL ���� ���� �� ���� �߻� �� ���� �޽��� ���
        fprintf(stderr, "SQL �� ���� ����: %s\n", mysql_error(&Conn));
    }
    else {
        // SQL ���� ������ ������ ��� ����� ��������
        MYSQL_RES* result = mysql_use_result(&Conn);

        // ��� �� ��������
        MYSQL_ROW row = mysql_fetch_row(result);

        // ��� ���� �����ϴ� ���
        if (row != NULL) {
            // ���ڵ� ������ ������ ��ȯ�Ͽ� No ������ ����
            No = atoi(row[0]); //atoi()���� ������ ��ȯ

            // ��� ��Ʈ ����
            mysql_free_result(result);
        }
    }
    //���� �ο� +1 =No   ex) �����̺� 5���� ���� �����ϸ� ���� ȸ�����ʹ� NO.6 ����
    No += 1;

    // ȸ�� ������ �����ͺ��̽��� �����ϱ� ���� SQL ���� ���� �� ����
    string insertQuery = "INSERT INTO `cs_bank`.`customer_table` (`No`, `ID`, `Name`, `Phone`, `Password`) VALUES ('" + to_string(No) + "','" + ID + "', '" + NAME + "',  '" + PhoneNumber + "'  , '" + PW + "')";
    //DBd�� cs_bank �� �ִ� �� ���̺��� `No`, `ID`, `Name`, `Phone`, `Password` Į���� ������� �������ּ���

    if (mysql_query(&Conn, insertQuery.c_str()) != 0) {
        fprintf(stderr, "Mysql query error:%s", mysql_error(&Conn));
    }
    Sleep(5000);
    mysql_close(&Conn); // �޸� ������ �����ϰ� ���ҽ��� ��ȯ
}



////////////////////////////////��ŸƮ Ŭ����/////////////////////
class Start : public Login, public SignUp  // ������ ����ߴ� �α��� ȸ������ Ŭ������ ���� ���
{
public:
    int StartMenuNum = 0; // 1.�α��� 2.ȸ������ 3.���� �� �ޱ����� ���� ����
    void start();
};


class User : public Start // ��� �α���, ȸ������ Ŭ������ ��� �޾Ҵ� StartŬ������ User�� �θ�Ŭ������ ��
{
private:
    string ID, Name, Phone, Password; //�� ��� �������� Ŭ���� ���ο����� ������ �����ϸ�, private�� ���� ȸ�� ������ �ܺο��� ���� ������ �� ����  
public:
    int UserMenuNum = 0; // 6���� ����� �̿��ϱ� ���� ���� ����(1. ���°輳, 2. �Ա�, 3. ���, 4. ������ü, 5. �����ڸ��, 6. ���� ���� Ȯ��

    void UserFunction(); //8������ �޴��� �ִ� �Լ�

    //������ ������ �޾ƿ��� ����
    void GetUserInfo();
    //���� ����
    void OpenAccount();
    //���� ���� Ȯ��
    void IsHaveAccount();
    //�Ա�
    void deposit();
    //���
    void withdraw();
    //������ü
    void transfer();
    //������ - ��� ���̺� Ȯ��
    void displayCustomerTable();
    //����� - ���� ���� Ȯ��
    void checkmyInfo();

};
void User::GetUserInfo()
{
    // �α����� ȸ���� ������ �������� ���� SQL ���� ����
    string whoLoginquery = "SELECT ID, Name, Phone, Password FROM cs_bank.customer_table WHERE No = '" + MemberNo + "'";
    //�ؼ� = cs_bankDB�ӿ� customer_table���� No�� ������ �ִ� ID, Name, Phone, Password�� ��ȸ�� �ּ���

    // SQL ���� ����
    if (mysql_query(&Conn, whoLoginquery.c_str()) == 0) {
        // ����� ����
        MYSQL_RES* result = mysql_store_result(&Conn);

        // ����� �����ϴ� ���
        if (result != NULL) {
            // ù ��° ���� ������
            MYSQL_ROW row = mysql_fetch_row(result);

            // ���� �����ϴ� ��� ȸ�� ������ �����ͼ� �ش� Ŭ������ ��� ������ �Ҵ�
            if (row != NULL) {
                ID = row[0];
                Name = row[1];
                Phone = row[2];
                Password = row[3];
            }

            // ��� ��Ʈ ����
            mysql_free_result(result);
        }
    }
}

void User::OpenAccount() //���� ����
{
    string CheckPhone; //��ȭ��ȣ�� �Է� �޴� ����
    string agree; // �����Ұ����� ���� �Է� ����
    cout << "���� ���� �������Դϴ�.\n";
    cout << "���� Ȯ���� ���� ��ȭ��ȣ�� �Է��ϼ���. >> ";
    cin >> CheckPhone;

    if (Phone != CheckPhone) {
        cout << "���� Ȯ�ο� �����߽��ϴ�.\n";
        cout << "�����ڿ��� ���ǹٶ��ϴ�. \n";
        Sleep(2000); //2�ʵ�
        UserFunction(); //8������ �޴��� �ִ� �Լ�
    }
    cout << "���� Ȯ���� �Ǿ����ϴ�.\n";
    cout << "\n";
    cout << "���̽��ǽ� �� ���� ��� ������Ⱑ �����Կ� ����, ������ ������� ���ظ� ������ �����ϰ� ������ �ڻ��� ��ȣ�ϰ��� �մϴ�.";
    cout << "\n";
    cout << "���� ���� ������ ���� ����� �����Ű���? < Yes / NO > >> ";
    cin >> agree;
    if (agree == "No" || agree == "NO") {
        cout << "�����ڿ��� ���ǹٶ��ϴ�. \n";
        Sleep(2000); //2�ʵ�
        UserFunction(); //8������ �޴��� �ִ� �Լ�
    }

    int randomNumber = 0;
    // ���� ������ ���鼭 �ߺ����� ���� ���¹�ȣ ����
    while (1) {
        //���¹�ȣ ���� ����
        srand(time(NULL));
        randomNumber = 10000000 + rand() % (99999999 - 10000000 + 1);

        // ������ ���¹�ȣ �ߺ� Ȯ���� ���� SQL ���� ����      
        string AccountCheckQuery = "SELECT ID FROM account_table WHERE ID = '" + to_string(randomNumber) + "'";
        // SQL ���� ����
        mysql_query(&Conn, AccountCheckQuery.c_str());
        // ����� ����
        MYSQL_RES* idCheckResult = mysql_store_result(&Conn);

        //���࿡ �ߺ��� ���� �ʴ´ٸ� �ű� ���¹�ȣ�� ���
        if (mysql_num_rows(idCheckResult) == 0) {
            mysql_free_result(idCheckResult);
            cout << "������ ���¹�ȣ��" << randomNumber << "�Դϴ�.\n";
            break;
        }
    }
    Sleep(3000);

    // ���� ���̺��� ���ڵ� ������ �������� ���� SQL ���� ����
    string AccountCountQuery = "SELECT COUNT(*) FROM account_table";

    int accountCount = 0;
    if (mysql_query(&Conn, AccountCountQuery.c_str()) != 0) {
        fprintf(stderr, "SQL �� ���� ����: %s\n", mysql_error(&Conn));
    }
    else {
        // SQL ���� ������ ������ ��� ����� ��������
        MYSQL_RES* result = mysql_use_result(&Conn);
        // ��� �� ��������
        MYSQL_ROW row = mysql_fetch_row(result);

        // ��� ���� �����ϴ� ��� ���ڵ� ������ ������ ��ȯ�Ͽ� accountCount ������ ����
        if (row != NULL) {
            if (row != NULL) {
                accountCount = atoi(row[0]);
            }
            mysql_free_result(result);
        }
    }

    //���� ���� +1
    accountCount += 1;

    //���� �̸� ����
    string accountName = "cs_account";
    accountName += to_string(accountCount);

    // ȸ�� ������ �����ͺ��̽��� �����ϱ� ���� SQL ���� ���� �� ����
    string insertQuery = "INSERT INTO `cs_bank`.`account_table` (`ID`, `AccountName`, `AccountNumber`, `Balance`) VALUES ('" + ID + "', '" + accountName + "',   '" + to_string(randomNumber) + "'  , '" + to_string(0) + "')";
    // SQL ���� ����
    if (mysql_query(&Conn, insertQuery.c_str()) != 0) {
        fprintf(stderr, "Mysql query error:%s", mysql_error(&Conn));
    }

    cout << "���� ������ �����մϴ�";
    Sleep(2000);
}

void User::IsHaveAccount() //���� ����
{
    // ���� ������ ������ ����
    string CountAccount = "";

    // ���°� �ִ��� Ȯ���ϴ� SQL ���� ����
    string IsHaveAccount = "SELECT COUNT(*) FROM account_table WHERE ID = '" + ID + "'";

    // SQL ���� ����
    if (mysql_query(&Conn, IsHaveAccount.c_str()) == 0) {
        // ����� ����
        MYSQL_RES* result = mysql_store_result(&Conn);

        // ����� �����ϴ� ���
        if (result != NULL) {
            // ù ��° ���� ������
            MYSQL_ROW row = mysql_fetch_row(result);

            // ���� �����ϴ� ��� ���� ������ ������ CountAccount�� ����
            if (row != NULL) {
                CountAccount = row[0];
            }

            // ��� ��Ʈ ����
            mysql_free_result(result);
        }
    }
    //���࿡ ���°� ���� ���� ���� ���
    if (CountAccount == "0") {
        cout << "���°� �����ϴ�!\n���� ���� ���� ���ּ���.";
        Sleep(3000);
        UserFunction(); //8������ �޴��� �ִ� �Լ�
    }
}

void User::deposit() //�Ա�
{

    // ȸ���� ������ �ִ� ��� ���� ��� 
    string AllAccount = "SELECT AccountName, AccountNumber, Balance FROM account_table WHERE ID = '" + ID + "'";
    // ���� ����
    mysql_query(&Conn, AllAccount.c_str());
    // ��� ����
    MYSQL_RES* result = mysql_store_result(&Conn);

    // ���࿡ ����� ���ٸ� �Լ� ����
    if (result == NULL) {
        fprintf(stderr, "Mysql query error:%s\n", mysql_error(ConnPtr));
        return;
    }
    // ��� ���
    int i = 1;
    cout << Name << "���� ���� ���\n\n";
    cout << "No       ���� �̸�           ���¹�ȣ            �ܾ�\n";
    while ((Row = mysql_fetch_row(result)) != NULL)
    {
        cout << i << "        " << Row[0] << "         " << Row[1] << "            " << Row[2] << endl;
        i++;
    }

    cout << "\n";

    int DepositAccount;
    cout << "�Ա� �Ͻ� ���¸� �Է��ϼ���. >> ";
    cin >> DepositAccount;

    string AccountName;
    string DepositQuery = "SELECT AccountName FROM account_table WHERE AccountNumber = '" + to_string(DepositAccount) + "'";
    //���� ���̺��� �Է¹��� DepositAccount�� AccountName�� ��ȸ���ּ���

    //���� ���� �� ��� ����
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
        cout << "���°� �������� �ʽ��ϴ�.\n ���� ��ȣ ��Ȯ�� �ٶ��ϴ�!";
        Sleep(3000);
        UserFunction();
    }
    cout << "�Ա��Ͻô� ���¸��� " << AccountName << "�� �����Ű���? <Yes/No> >> ";

    string AccountNameCheck;
    cin >> AccountNameCheck;

    if (AccountNameCheck == "No" || AccountNameCheck == "NO" || AccountNameCheck == "N" || AccountNameCheck == "n") {
        cout << "���� ��ȣ ��Ȯ�� �ٶ��ϴ�!";
        Sleep(3000);
        UserFunction();
    }

    int InputDeposit;
    cout << "�Ա� �Ͻ� �ݾ��� �Է��ϼ���. >> ";
    cin >> InputDeposit;

    string updateQuery = "UPDATE account_table SET Balance = Balance+'" + to_string(InputDeposit) + "' WHERE AccountNumber = '" + to_string(DepositAccount) + "'";
    //AccountNumber�� �Է� ����DepositAccount�� �������̺��� �Է� ���� �ݾ��� ������Ʈ ���ּ��� 
    if (mysql_query(&Conn, updateQuery.c_str()) == 0) {
        cout << "���������� �Ա��� �Ϸ�Ǿ����ϴ�.";

        Sleep(3000);
    }
    else
    {
        cout << "������Ʈ�� �����ϴ� ���� ������ �߻��߽��ϴ�.";
        Sleep(3000);
    }

}

void User::withdraw() //��� 
{

    // ��� ���� ��� 
    string AllAccount = "SELECT AccountName, AccountNumber, Balance FROM account_table WHERE ID = '" + ID + "'";
    //���� ���̺��� �Է� ���� ID�� AccountName, AccountNumber, Balance  ������� ��ȸ ���ּ���

    mysql_query(&Conn, AllAccount.c_str());
    //���� ����
    MYSQL_RES* result = mysql_store_result(&Conn);
    //��� ����

    if (result == NULL) {
        fprintf(stderr, "Mysql query error:%s\n", mysql_error(ConnPtr));
        return;
    }


    // ��� ���
    int i = 1;
    cout << Name << "���� ���� ���\n\n";
    cout << "No       ���� �̸�           ���¹�ȣ            �ܾ�\n";
    while ((Row = mysql_fetch_row(result)) != NULL)
    {
        cout << i << "        " << Row[0] << "         " << Row[1] << "            " << Row[2] << endl;
        i++;
    }

    cout << "\n";

    int WithdrawAccount;
    cout << "��� �Ͻ� ���� ��ȣ�� �Է��ϼ���. >> ";
    cin >> WithdrawAccount;

    //����ϴ� ���¸� �ҷ����� ����
    string AccountName;
    string AccountNameQuery = "SELECT AccountName FROM account_table WHERE AccountNumber = '" + to_string(WithdrawAccount) + "'";
    //�Է� ���� WithdrawAccount���� AccountName�� ��ȸ���ּ��� ���� ���̺���

    // ���� ���� �� ��� ����
    if (mysql_query(&Conn, AccountNameQuery.c_str()) == 0) {
        MYSQL_RES* result = mysql_store_result(&Conn);
        if (result != NULL) {
            MYSQL_ROW row = mysql_fetch_row(result);
            if (row != NULL) {
                AccountName = row[0];
            }
        }
    }

    //����ϴ� ���°� ���� �������� Ȯ���ϴ� ����
    string AccountID;
    string AccountIDQuery = "SELECT ID FROM account_table WHERE AccountNumber = '" + to_string(WithdrawAccount) + "'";
    //AccountNumber�� WithdrawAccount�� �������̺��� ID�� ��ȸ ���ּ���

    //���� ���� �� ��� ����
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
        cout << "���°� �������� �ʽ��ϴ�.\n ���� ��ȣ ��Ȯ�� �ٶ��ϴ�!";
        Sleep(3000);
        UserFunction();
    }

    //���� �α��ε� ���̵�� �Է¹��� ���¹�ȣ�� ���̵� �ٸ� ���
    if (AccountID != ID) {
        cout << "����Ϸ��� ���°� ���� ���ǰ� �ƴմϴ�.\n ���� Ȯ���� �ٽ� ���ּ���.";
        Sleep(3000);
        UserFunction();
    }

    cout << "����Ͻô� ���¸��� " << AccountName << "�� �����Ű���? <Yes/No> >> ";
    string AccountNameCheck;
    cin >> AccountNameCheck;
    if (AccountNameCheck == "No" || AccountNameCheck == "NO") {
        cout << "���� ��ȣ ��Ȯ�� �ٶ��ϴ�!";
        Sleep(3000);
        UserFunction();
    }

    string checkPW;
    cout << "����� ��й�ȣ�� �Է��ϼ���. >>";
    cin >> checkPW;
    //����� ��й�ȣ�� �Է� ��й�ȣ�� �ٸ� ���
    if (checkPW != Password) {
        cout << "��й�ȣ ��Ȯ�� �ٶ��ϴ�!";
        Sleep(3000);
        UserFunction();
    }

    int InputWithdraw;
    cout << "��� �Ͻ� �ݾ��� �Է��ϼ���. >> ";
    cin >> InputWithdraw;

    //�ܾ��� �������� Ȯ���ϴ� ����
    string NowAccountBalnce;
    string IsBalanceQuery = "SELECT Balance FROM account_table WHERE AccountNumber = '" + to_string(WithdrawAccount) + "'";
    //AccountNumber�� WithdrawAccount�� ���� ���̺��� �ܾ��� ��ȸ���ּ���

    //���� ���� �� ��� ����
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

    //���� ����Ϸ��� �ݾ��� �ܾ׺��� Ŭ ���
    if (stoi(NowAccountBalnce) < InputWithdraw)
    {
        cout << "�ܾ��� �����մϴ�!";
        Sleep(3000);
        UserFunction();
    }

    //��� ����
    string updateQuery = "UPDATE account_table SET Balance = Balance-'" + to_string(InputWithdraw) + "' WHERE AccountNumber = '" + to_string(WithdrawAccount) + "'";
    //AccountNumber�� WithdrawAccount�� ���� ���̺��� �ܾ��� InputWithdraw�� ������Ʈ ���ּ���

    if (mysql_query(&Conn, updateQuery.c_str()) == 0) {
        cout << "���������� ����� �Ϸ�Ǿ����ϴ�.\n";
    }
    else {
        cout << "������Ʈ�� �����ϴ� ���� ������ �߻��߽��ϴ�.";
        Sleep(3000);
    }

    //��� �� �ܾ� Ȯ�� ����
    string BalanceQuery = "SELECT Balance FROM account_table WHERE AccountNumber = '" + to_string(WithdrawAccount) + "'";
    //AccountNumber�� WithdrawAccount�� ���� ���̺��� �ܾ��� ��ȸ���ּ���

    string AccountBalnce;

    //���� ���� �� ��� ����
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
    cout << "�ܾ��� " << AccountBalnce << "�Դϴ�.";
    Sleep(3000);
}



void User::transfer() //������ü 
{

    string YourAccountName;
    int YourAccount;
    cout << "��ü ������ ���� ��ȣ�� �Է��ϼ���. >> ";
    cin >> YourAccount;

    //��ü(�Ա�) ���¸� �ҷ����� ����
    string SendAccountName;
    string YourAccountNameQuery = "SELECT AccountName FROM account_table WHERE AccountNumber = '" + to_string(YourAccount) + "'";
    //AccountNumber�� YourAccount�� ���� ���̺��� AccountName�� ��ȸ���ּ���

    //���� ���� �� ��� ����
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
        cout << "���°� �������� �ʽ��ϴ�.\n ���� ��ȣ ��Ȯ�� �ٶ��ϴ�!";
        Sleep(3000);
        UserFunction();
    }

    cout << "��ü ������ ���¸��� ���¸��� " << YourAccountName << "�� �����Ű���? <Yes/No> >> ";
    string YourAccountNameCheck;
    cin >> YourAccountNameCheck;
    if (YourAccountNameCheck == "No" || YourAccountNameCheck == "NO" || YourAccountNameCheck == "N" || YourAccountNameCheck == "n") {
        cout << "���� ��ȣ ��Ȯ�� �ٶ��ϴ�!";
        Sleep(3000);
        UserFunction();
    }

    //��ü(���) - ���� ��� ���� ���
    string MyAllAccount = "SELECT AccountName, AccountNumber, Balance FROM account_table WHERE ID = '" + ID + "'";
    //account_table�� ID�� �������̺��� AccountName, AccountNumber, Balance�� ��ȸ���ּ���

    //���� ���� �� ��� ����
    mysql_query(&Conn, MyAllAccount.c_str());
    MYSQL_RES* result = mysql_store_result(&Conn);

    if (result == NULL) {
        fprintf(stderr, "Mysql query error:%s\n", mysql_error(ConnPtr));
        return;
    }

    int i = 1;
    cout << "\nNo       ���� �̸�           ���¹�ȣ            �ܾ�\n";
    while ((Row = mysql_fetch_row(result)) != NULL)
    {
        cout << i << "        " << Row[0] << "         " << Row[1] << "            " << Row[2] << endl;
        i++;
    }
    cout << "\n";

    //��ü(���) - ���� ����

    int MyAccountNumber;
    cout << "��ü �Ͻ� ���� ��ȣ�� �Է��ϼ���. >> ";
    cin >> MyAccountNumber;

    //��ü(���) ���¸� �ҷ����� ����
    string MyAccountName;
    string AccountNameQuery = "SELECT AccountName FROM account_table WHERE AccountNumber = '" + to_string(MyAccountNumber) + "'";
    //AccountNumber�� MyAccountNumber�� ���� ���̺��� AccountName ��ȸ���ּ���

    //���� ���� �� ��� ����
    if (mysql_query(&Conn, AccountNameQuery.c_str()) == 0) {
        MYSQL_RES* result = mysql_store_result(&Conn);
        if (result != NULL) {
            MYSQL_ROW row = mysql_fetch_row(result);
            if (row != NULL) {
                MyAccountName = row[0];
            }
        }
    }

    //���°� ���� �������� Ȯ���ϴ� ����
    string AccountID;
    string AccountIDQuery = "SELECT ID FROM account_table WHERE AccountNumber = '" + to_string(MyAccountNumber) + "'";
    //AccountNumber�� MyAccountNumber�� �������̺��� ID�� ��ȸ���ּ���

    //���� ���� �� ��� ����
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
        cout << "���°� �������� �ʽ��ϴ�.\n ���� ��ȣ ��Ȯ�� �ٶ��ϴ�!";
        Sleep(3000);
        UserFunction();
    }

    //���� �α��ε� ���̵�� �Է¹��� ���¹�ȣ�� ���̵� �ٸ� ���
    if (AccountID != ID) {
        cout << "��ü�Ͻ� ���°� ���� ���ǰ� �ƴմϴ�.\n ���� Ȯ���� �ٽ� ���ּ���.";
        Sleep(3000);
        UserFunction();
    }

    cout << "��ü�Ͻô� ���¸��� " << MyAccountName << "�� �����Ű���? <Yes/No> >> ";
    string AccountNameCheck;
    cin >> AccountNameCheck;
    if (AccountNameCheck == "No" || AccountNameCheck == "NO") {
        cout << "���� ��ȣ ��Ȯ�� �ٶ��ϴ�!";
        Sleep(3000);
        UserFunction();
    }


    string checkPW;
    cout << "����� ��й�ȣ�� �Է��ϼ���. >>";
    cin >> checkPW;
    //����� ��й�ȣ�� �Է� ��й�ȣ�� �ٸ� ���
    if (checkPW != Password) {
        cout << "��й�ȣ ��Ȯ�� �ٶ��ϴ�!";
        Sleep(3000);
        UserFunction();
    }

    int InputTransfer;
    cout << "��ü �Ͻ� �ݾ��� �Է��ϼ���. >> ";
    cin >> InputTransfer;

    //�ܾ��� �������� Ȯ���ϴ� ����
    string MyAccountBalnce;
    string MyBalanceQuery = "SELECT Balance FROM account_table WHERE AccountNumber = '" + to_string(MyAccountNumber) + "'";
    //AccountNumber�� MyAccountNumber ���� ���̺��� Balance(�ܾ�)�� ��ȸ���ּ���

    //���� ���� �� ��� ����
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

    //���� ����Ϸ��� �ݾ��� �ܾ׺��� Ŭ ���
    if (stoi(MyAccountBalnce) < InputTransfer) {
        cout << "�ܾ��� �����մϴ�!";
        Sleep(3000);
        UserFunction();
    }

    //��� ����
    string WithdrawAccountQuery = "UPDATE account_table SET Balance = Balance-'" + to_string(InputTransfer) + "' WHERE AccountNumber = '" + to_string(MyAccountNumber) + "'";
    //AccountNumber�� MyAccountNumber�� �������̺��� �ܾ��� ������Ʈ ���ּ���

    //���� ����
    if (mysql_query(&Conn, WithdrawAccountQuery.c_str()) == 0) {
        cout << "���� ���� �Ϸ�...\n";
    }
    else {
        cout << "������Ʈ�� �����ϴ� ���� ������ �߻��߽��ϴ�.";
        Sleep(3000);
    }

    //��ü �Ϸ�
    string updateQuery = "UPDATE account_table SET Balance = Balance+'" + to_string(InputTransfer) + "' WHERE AccountNumber = '" + to_string(YourAccount) + "'";
    //AccountNumber�� YourAccount �������̺��� �ܾ��� ������Ʈ ���ּ���

     //��������
    if (mysql_query(&Conn, updateQuery.c_str()) == 0) {
        cout << "���������� ��ü�� �Ϸ�Ǿ����ϴ�.";
        Sleep(3000);
    }
    else {
        cout << "������Ʈ�� �����ϴ� ���� ������ �߻��߽��ϴ�.";
        Sleep(3000);
    }
}

void User::checkmyInfo() // �� ���� Ȯ��
{

    cout << "ID :" << ID << endl;
    cout << "�̸� :" << Name << endl;
    cout << "��ȭ��ȣ :" << Phone << endl;

    // ��� ���� ��� 
    string AllAccount = "SELECT AccountName, AccountNumber, Balance FROM account_table WHERE ID = '" + ID + "'";
    //ID�� �Է¹��� ID�� ���� ���̺��� AccountName, AccountNumber, Balance ��ȸ���ּ���

    //���� ���� �� ��� ����
    mysql_query(&Conn, AllAccount.c_str());
    MYSQL_RES* result = mysql_store_result(&Conn);

    if (result == NULL) {
        fprintf(stderr, "Mysql query error:%s\n", mysql_error(ConnPtr));
        return;
    }


    // ��� ���
    int i = 1;
    cout << Name << "���� ���� ���\n\n";
    cout << "No       ���� �̸�           ���¹�ȣ            �ܾ�\n";
    while ((Row = mysql_fetch_row(result)) != NULL)
    {
        cout << i << "        " << Row[0] << "         " << Row[1] << "            " << Row[2] << endl;
        i++;
    }
    Sleep(3000);
}


void User::displayCustomerTable() //������ ���
{
    // �� ���̺� ��� ���� ��û
    const char* customerquery = "SELECT * FROM customer_table";
    //�� ���̺��� ��� Į���� ��ȸ���ּ���

    Stat = mysql_query(&Conn, customerquery);

    if (Stat != 0) {
        fprintf(stderr, "Mysql query error:%s\n", mysql_error(ConnPtr));
        return;
    }

    Result = mysql_store_result(&Conn); //MySQL���� ������ ������ ��� ������ Result�� ����

    cout << "Customer Table:\n";
    cout << setw(4) << left << "No";
    cout << setw(8) << left << "ID";
    cout << setw(16) << left << "�̸�";
    cout << setw(20) << left << "��ȭ��ȣ";
    cout << setw(16) << left << "��й�ȣ\n";

    // �ݺ��� ������ Row ������ ����Ͽ� ��� ���տ��� �� �྿ �����͸� ó���̶�, NULL�� ���� ������ ��� �ݺ�
    while ((Row = mysql_fetch_row(Result)) != NULL)
    {
        cout << setw(4) << left << Row[0];
        cout << setw(8) << left << Row[1];
        cout << setw(16) << left << Row[2];
        cout << setw(20) << left << Row[3];
        cout << setw(16) << left << Row[4] << "\n";
    }

    cout << "\n";

    // ���� ���̺� ��� ���� ��û
    const char* accountquery = "SELECT * FROM account_table";
    //���� ���̺��� ��� Į���� ��ȸ���ּ���

    Stat = mysql_query(&Conn, accountquery);

    if (Stat != 0) {
        fprintf(stderr, "Mysql query error:%s\n", mysql_error(&Conn));
        return;
    }

    Result = mysql_store_result(&Conn); //MySQL���� ������ ������ ��� ������ Result�� ����

    // ��� ���
    cout << "Account Table:\n";
    cout << setw(8) << left << "ID";
    cout << setw(16) << left << "���¸�";
    cout << setw(16) << left << "���¹�ȣ";
    cout << setw(8) << left << "�ܾ�\n";

    // �ݺ��� ������ Row ������ ����Ͽ� ��� ���տ��� �� �྿ �����͸� ó���̶�, NULL�� ���� ������ ��� �ݺ�
    while ((Row = mysql_fetch_row(Result)) != NULL)
    {
        cout << setw(8) << left << Row[0];
        cout << setw(16) << left << Row[1];
        cout << setw(16) << left << Row[2];
        cout << setw(8) << left << Row[3] << "\n";
    }

    Sleep(6000); //6�� ����
}

void User::UserFunction() {
    GetUserInfo();
    system("cls");

    cout << "---------------ȯ���մϴ�!" << Name << "��!---------------" << "\n";
    cout << "0. ���� ����" << endl;
    cout << "1. ���� �Ա�" << endl;
    cout << "2. ���� ���" << endl;
    cout << "3. ���� ��ü" << endl;
    cout << "4. �� ���� ���� " << endl;
    cout << "5. �α׾ƿ�" << endl;
    cout << "6. ������ ���" << endl;
    cout << "7. ���α׷� ����" << endl;
    cout << "\n";
    cout << "���Ͻô� �޴��� �Է��� �ּ���. >> ";
    cin >> UserMenuNum;

    switch (UserMenuNum) {
    case 0:
        OpenAccount(); break;//���� ����
    case 1:
        IsHaveAccount();
        deposit();  break; //���� �Ա�
    case 2:
        IsHaveAccount();
        withdraw();  break;//���� ���
    case 3:
        IsHaveAccount();
        transfer(); break;//���� ��ü
    case 4:
        checkmyInfo(); break;//�� ���� ����
    case 5:
        login(); break; // �α׾ƿ�
    case 6: //������ ���
    {
        string adminPassword;
        cout << "������ ��й�ȣ�� �Է��ϼ���: ";
        cin >> adminPassword;

        // �Էµ� ��й�ȣ�� ����ϴ� ������ ��й�ȣ�� ��
        if (adminPassword == "1q2w3e4r!") {
            displayCustomerTable();  // ������ ��� �Լ� ȣ��
        }
        else {
            cout << "�߸��� ��й�ȣ�Դϴ�. ������ ������ �����ϴ�.\n";
            Sleep(1000);
        }
        break;
    }
    case 7:
        cout << "���α׷��� �����մϴ�" << endl; // ���α׷� ����
        cout << "\n";
        cout << "�̿��� �ּż� �����մϴ�" << endl;
        cout << "\n";
        end();
        exit(0);

    default:
        system("cls");
        cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n";
        UserFunction();
    }
}

void Start::start() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    cout << "\n";
    cout << "                                 �����������������������������������\n";
    cout << "                                 ��                                ��\n";
    cout << "                                 ��                                ��\n";
    cout << "                                 ��        ";
    SetConsoleTextAttribute(hConsole, 12);
    cout << "����� �Է��ϼ���";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "       ��\n";
    cout << "                                 ��                                ��\n";
    cout << "                                 ��                                ��\n";
    cout << "                                 ��           1. �α���            ��\n";
    cout << "                                 ��                                ��\n";
    cout << "                                 ��          2. ȸ������           ��\n";
    cout << "                                 ��                                ��\n";
    cout << "                                 ��            3. ����             ��\n";
    cout << "                                 ��                                ��\n";
    cout << "                                 ��                                ��\n";
    cout << "                                 �����������������������������������\n";
    cout << "\n";
    cout << "�̿��Ͻ� ����� ������ �ּ��� >> ";
    cin >> StartMenuNum;
    switch (StartMenuNum) {
    case 1:
        login();  break;
    case 2:
        signup();  break;
    case 3:
        cout << "���α׷��� �����մϴ�" << endl;
        cout << "\n";
        cout << "�̿��� �ּż� �����մϴ�" << endl;
        cout << "\n";
        end();
        exit(0);
    default:
        system("cls");
        cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n";
        start();
    }

    if (MemberNo != "NULL") {
        //�α��� �Ϸ�
    }
}


//////////////////////////////////////MYSQL ���� + MAIN ����//////////////////////////////////////

int main()
{
    //system("chcp 65001");
    system("CS BANK");
    User user; //User Ŭ������ ��ü ����
    Start customer; //Start Ŭ������ ��ü ����

    mysql_init(&Conn); // MySQL ���� �ʱ�ȭ  

    // �����ͺ��̽��� ����
    ConnPtr = mysql_real_connect(&Conn, "localhost", "root", "1q2w3e4r!", "cs_bank", 3306, (char*)NULL, 0);

    // ���� ��� Ȯ��. null�� ��� ����
    if (ConnPtr == NULL) {
        fprintf(stderr, "Mysql query error:%s", mysql_error(&Conn));
        return 1;
    }

    //�ܼ�â ����
    SetConsoleTitle("CS_Bank");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("mode con: cols=100 lines=40");

    //////////////////////////////////////���� ���� ����//////////////////////////////////////
    while (1)
    {
        system("cls");
        //�ϴ� ���� ���
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
        cout << "\n\n\n";
        cout << "                 ######   ######     ########     ###    ##    ## ##    ##                 \n";
        cout << "                ##    ## ##    ##    ##     ##   ## ##   ###   ## ##   ##                  \n";
        cout << "                ##       ##          ##     ##  ##   ##  ####  ## ##  ##                   \n";
        cout << "                ##        ######     ########  ##     ## ## ## ## #####                    \n";
        cout << "                ##             ##    ##     ## ######### ##  #### ##  ##                   \n";
        //�ʷ� ���� ���
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        cout << "                ##    ## ##    ##    ##     ## ##     ## ##   ### ##   ##                  \n";
        cout << "                 ######   ######     ########  ##     ## ##    ## ##    ##                 \n";
        cout << "\n\n\n\n";
        //���� ���� ���
        SetConsoleTextAttribute(hConsole, 15);
        cout << "                                  CS�������࿡ ���Ű��� ȯ���մϴ�!                                 \n\n\n\n";

        customer.start();
        while (1)
        {
            //ȸ���� No�� ������ ������ 8���� �޴��� �̿��� �� ���� ��, CS��ũ�� ȸ���� �ƴ϶�� �޴��� �̿��� �� ����
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
    mysql_free_result(Result);// MySQL C API���� ����� �޸𸮸� �����ϴ� �Լ�
    mysql_close(ConnPtr); // MySQL �����ͺ��̽� ������ �ݴ� �Լ�
    end();
    return 0;
}
