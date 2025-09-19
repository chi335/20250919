#include <stdio.h>
#include <windows.h>  // Beep 함수 사용

// 음계별 주파수 정의
#define NOTE_C  261
#define NOTE_D  294
#define NOTE_E  329
#define NOTE_F  349
#define NOTE_G  392
#define NOTE_A  440
#define NOTE_B  494

// 학교종이 땡땡땡 멜로디 주파수 배열
int melody[] = {
    NOTE_G, NOTE_G, NOTE_A, NOTE_G, NOTE_F, NOTE_E,
    NOTE_G, NOTE_G, NOTE_A, NOTE_G, NOTE_F, NOTE_E,
    NOTE_E, NOTE_E, NOTE_F, NOTE_G, NOTE_G, NOTE_A, NOTE_G, NOTE_F, NOTE_E
};

int duration = 400;  // 음 길이 (ms)

int main() {
    printf("학교종이 땡땡땡 멜로디 연주 시작\n");

    for (int i = 0; i < sizeof(melody)/sizeof(melody[0]); i++) {
        Beep(melody[i], duration);
        Sleep(50); // 음 사이 쉬는 시간
    }

    printf("연주 종료\n");
    return 0;
}
