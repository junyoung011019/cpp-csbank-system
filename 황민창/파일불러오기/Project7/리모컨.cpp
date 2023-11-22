// 김성철 컴퓨터 - 소프트웨어 학과 - 20102049 

#include <iostream>
#include <windows.h>
using namespace std;



class TV
{
    bool on;
    int channel;
    int volume;

public:
    void powerOn()
    {
        on = true;
        cout << "TV를 켰습니다" << endl;
    }
    void powerOFF()
    {
        on = false;
        cout << "TV를 껐습니다" << endl;
    }
    void menu() // 메뉴 선택
    {
        cout << "==================" << endl;
        cout << "1. 채널 선택" << endl;
        cout << "2. 볼륨 선택" << endl;
        cout << "3. 채널 재 선택" << endl;
        cout << "4. TV 종료" << endl;
        cout << "==================" << endl;
    }
    void pyeonseongpyo() // 채널 편성표
    {
        cout << "==================" << endl;
        cout << "1번 SBS" << endl;
        cout << "2번 KBS" << endl;
        cout << "3번 MBC" << endl;
        cout << "4번 EBS" << endl;
        cout << "5번 SPORT TV" << endl;
        cout << "==================" << endl;


    }
    void setChannel(int choiceChl)
    {
      

            while (1)
            {
                if (choiceChl == 1)
                {
                    cout << "SBS 채널을 시청 중입니다 !!";
                    break;
                }
                if (choiceChl == 2)
                {
                    cout << "KBS 채널을 시청 중입니다 !!";
                    break;
                }
                if (choiceChl == 3)
                {
                    cout << "MBC 채널을 시청 중입니다 !!";
                    break;
                }
                if (choiceChl == 4)
                {
                    cout << "EBS 채널을 시청 중입니다 !!";
                    break;
                }
                if (choiceChl == 5)
                {
                    cout << "SPORT TV 채널을 시청 중입니다 !!";
                    break;
                }
               

            }
        
    }

    void incVol();

    void decVol();

    void setVol(int vol);

};


int main()
{
    TV tv; // 클래스 객체 선언
    int menuCho; // 메뉴 선택
    int choiceChl = 0; // 채널 선택


    tv.powerOn(); // TV 전원 ON

    tv.menu();
    cout << "메뉴를 선택 해주세요 >> ";
    cin >> menuCho;

    if (menuCho == 1)
    {
        tv.pyeonseongpyo();
        cout << "보고싶은 채널을 입력하세요 >> ";
        tv.setChannel(choiceChl);
        cin >> choiceChl;

        Sleep(800);
        system("cls");
    }

    tv.menu();
    cout << "메뉴를 선택 해주세요 >> ";
    cin >> menuCho;


   







    if (menuCho == 4)
    {
        tv.powerOFF();
    }
}