#include <iostream>
#include <conio.h>
#include<windows.h>
using namespace std;

string now_channel(int num);

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13


class TV {
private:
	bool on;
	int channel;
	int volume;
public:
	TV() : on(false), channel(0), volume(15) {

	}

	void powerOn() {
		on = true;
		cout << "TV가 켜졌습니다.\n";
	}
	void powerOff() {
		on = false;
		cout << "TV가 꺼졌습니다.\n";
	}
	void increaseChannel() {
		channel += 1;
		if (channel == 10) {
			channel = 0;
		}
		cout << "TV 채널이 1 증가했습니다.\n" << now_channel(channel) << "\n";
	}
	void decreaseChannel() {
		channel -= 1;
		if (channel == -1) {
			channel = 9;
		}
		cout << "TV 채널이 1 감소했습니다.\n" << now_channel(channel) << "\n";
	}
	void increaseVolume() {
		if (volume == 30) {
			cout << "더 이상 볼륨을 올릴 수 없습니다.\n" << volume << "\n";
		}
		else {
			volume += 1;
			cout << "TV 볼륨이 1 증가했습니다.\n" << volume << "\n";
		}

	}
	void decreaseVolume() {
		if (volume == 0) {
			cout << "더 이상 볼륨을 내릴 수 없습니다.\n" << volume << "\n";
		}
		else {
			volume -= 1;
			cout << "TV 볼륨이 1 감소했습니다.\n" << volume << "\n";
		}
	}
	bool isOn() {
		return on;
	}

	int channel_num() {
		return channel;
	}


};

string now_channel(int num) {
	switch (num) {
	case 0:
		return "채널 0 : 기본 채널";
		break;
	case 1:
		return "채널 1 : tvN";
		break;
	case 2:
		return "채널 2 : 롯데 홈쇼핑";
		break;
	case 3:
		return "채널 3 : SBS";
		break;
	case 4:
		return "채널 4 : KBS2";
		break;
	case 5:
		return "채널 5 : KBS1";
		break;
	case 6:
		return "채널 6 : MBC";
		break;
	case 7:
		return "채널 7 : EBS";
		break;
	case 8:
		return "채널 8 : JTBC";
		break;
	case 9:
		return "채널 9 : MBN";
		break;
	default:
		return "알 수 없는 채널";


	}
}

void function(TV& tv, char answer) {
	switch (answer) {
	case UP:
		tv.increaseChannel();
		break;
	case DOWN:
		tv.decreaseChannel();
		break;
	case RIGHT:
		tv.increaseVolume();
		break;
	case LEFT:
		tv.decreaseVolume();
		break;
	case ENTER:
		tv.powerOff();
		break;
	default:
		cout << "잘못된 값입니다.\n";

	}
}

int main() {
	TV tv;
	while (1) {
		if (tv.isOn()) {
			cout << "현재 TV 상태 : ON\n";
			cout << now_channel(tv.channel_num()) << "\n";
			cout << "기능을 입력해주세요.\n";

			char function_answer;
			function_answer = _getch();
			function(tv, function_answer);
			if (tv.isOn() == false) {
				Sleep(1000);
				system("cls");
			}

		}
		else {
			cout << "현재 TV 상태 : OFF\n";
			cout << "TV를 켜시겠습니까 ? (예 : Y / 아니오 : N / 프로그램 종료 : E) > ";
			char power_answer;
			cin >> power_answer;
			if (power_answer == 'Y') {
				system("cls");
				tv.powerOn();
			}
			else if (power_answer != 'Y' && power_answer != 'N' && power_answer != 'E') {
				system("cls");
				cout << "잘못된 값이 입력 되었습니다. 재입력 해주세요.\n";
			}
			else if (power_answer == 'E') {
				cout << "프로그램을 종료합니다.";
				return 0;
			}
			//티비를 켜지않으면(power_answer가 N이면) 반복
		}

	}

}