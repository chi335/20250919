#include <stdio.h>
#include <windows.h>

#define BASE_OCTAVE 4

// 음계 인덱스 (도=0, 레=1, 미=2, 파=3, 솔=4, 라=5, 시=6)
enum Notes { DO=0, RE, MI, FA, SOL, LA, SI };

// 4옥타브 기준 도~시 주파수
int baseFrequencies[7] = {262, 294, 330, 349, 392, 440, 494};

// 음계 이름 문자열 배열
const char* noteNames[7] = {"도", "레", "미", "파", "솔", "라", "시"};

// 옥타브에 따른 주파수 반환 함수
int getFrequency(int noteIndex, int octave) {
    int baseFreq = baseFrequencies[noteIndex];
    int octaveDiff = octave - BASE_OCTAVE;
    if (octaveDiff > 0)
        return baseFreq << octaveDiff;
    else if (octaveDiff < 0)
        return baseFreq >> (-octaveDiff);
    else
        return baseFreq;
}

// 반짝반짝 작은별 멜로디 (음계 인덱스)
int melody[] = {
    DO, DO, SOL, SOL, LA, LA, SOL,
    FA, FA, MI, MI, RE, RE, DO
};

// 각 음 길이(ms)
int durations[] = {
    400, 400, 400, 400, 400, 400, 800,
    400, 400, 400, 400, 400, 400, 800
};

int main() {
    int length = sizeof(melody)/sizeof(melody[0]);
    int octave = 5;       // 5옥타브로 재생

    system("chcp 65001");  // 한글 깨짐 방지 (필요시)

    // 음 출력과 음계 이름 출력
    for (int i = 0; i < length; i++) {
        printf("%s ", noteNames[melody[i]]);
        fflush(stdout);  // 출력 버퍼 바로 비우기
        int freq = getFrequency(melody[i], octave);
        Beep(freq, durations[i]);
        Sleep(50);  // 음 사이 짧은 쉬는 시간
    }

    printf("\n멜로디 연주 종료\n");

    return 0;
}
