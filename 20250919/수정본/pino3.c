#include <stdio.h>
#include <windows.h>  // Beep 함수 사용

// 음계별 주파수 정의 (4옥타브 기준)
#define NOTE_C  261
#define NOTE_D  294
#define NOTE_E  329
#define NOTE_F  349
#define NOTE_G  392
#define NOTE_A  440
#define NOTE_B  494

// 음계 이름과 주파수를 쌍으로 저장하는 구조체
typedef struct {
    int frequency;
    const char* name;
} NoteInfo;

// 음계 정보 배열
NoteInfo notes[] = {
    {NOTE_C, "도"},
    {NOTE_D, "레"},
    {NOTE_E, "미"},
    {NOTE_F, "파"},
    {NOTE_G, "솔"},
    {NOTE_A, "라"},
    {NOTE_B, "시"}
};

// 학교종이 땡땡땡 멜로디 (주파수 배열)
int melody[] = {
    NOTE_G, NOTE_G, NOTE_A, NOTE_G, NOTE_F, NOTE_E,
    NOTE_G, NOTE_G, NOTE_A, NOTE_G, NOTE_F, NOTE_E,
    NOTE_E, NOTE_E, NOTE_F, NOTE_G, NOTE_G, NOTE_A, NOTE_G, NOTE_F, NOTE_E
};

int duration = 400;  // 각 음의 지속 시간 (ms)

// 주어진 주파수에 해당하는 음계 이름 반환 함수
const char* getNoteName(int freq) {
    for (int i = 0; i < sizeof(notes)/sizeof(notes[0]); i++) {
        if (notes[i].frequency == freq)
            return notes[i].name;
    }
    return "Unknown";
}

int main() {
    system("chcp 65001");  // 한글 출력이 깨질 경우 UTF-8 모드 설정
    printf("🎵 학교종이 땡땡땡 멜로디 연주 시작\n\n");

    for (int i = 0; i < sizeof(melody)/sizeof(melody[0]); i++) {
        const char* noteName = getNoteName(melody[i]);
        printf("%s ", noteName);
        fflush(stdout);  // 즉시 출력
        Beep(melody[i], duration);
        Sleep(50); // 음 사이 잠깐 휴식
    }

    printf("\n\n🎵 연주 종료\n");
    return 0;
}
