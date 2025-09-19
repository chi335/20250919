// deck_shuffle.c
// 조커 2장 제외한 52장 트럼프 카드 생성 -> 섞기 -> 출력
// 컴파일: gcc deck_shuffle.c -o deck_shuffle
// 실행: ./deck_shuffle

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    char suit[4];   // 모양(문자열로 저장, UTF-8 심볼 사용 가능)
    char rank[3];   // 숫자 또는 문자 ('A','2'...'10','J','Q','K')
} Card;

#define DECK_SIZE 52

// 모양과 랭크 문자열 (원하면 ASCII 대체도 아래 주석 참고)
const char *suits_utf8[4] = {"\u2660", "\u2666", "\u2665", "\u2663"}; // ♠ ◆ ♥ ♣
const char *suits_ascii[4] = {"S", "D", "H", "C"}; // 콘솔에서 심볼 문제 시 사용
const char *ranks[13] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};

// 덱 초기화 (스페이드, 다이아몬드, 하트, 클로버 순서)
void init_deck(Card deck[]) {
    int idx = 0;
    for (int s = 0; s < 4; s++) {
        for (int r = 0; r < 13; r++) {
            // 모양(UTF-8) 복사
            strncpy(deck[idx].suit, suits_utf8[s], sizeof(deck[idx].suit)-1);
            deck[idx].suit[sizeof(deck[idx].suit)-1] = '\0';
            // 랭크 복사
            strncpy(deck[idx].rank, ranks[r], sizeof(deck[idx].rank)-1);
            deck[idx].rank[sizeof(deck[idx].rank)-1] = '\0';
            idx++;
        }
    }
}

// Fisher–Yates 섞기
void shuffle_deck(Card deck[]) {
    for (int i = DECK_SIZE - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        // swap deck[i] and deck[j]
        Card tmp = deck[i];
        deck[i] = deck[j];
        deck[j] = tmp;
    }
}

// 덱 출력
void print_deck(const Card deck[]) {
    for (int i = 0; i < DECK_SIZE; i++) {
        // 출력 형식: [모양 랭크] (예: ♠ A 또는 S A)
        printf("[%s %2s] ", deck[i].suit, deck[i].rank);
        if ((i+1) % 8 == 0) printf("\n"); // 보기 좋게 8장씩 줄바꿈
    }
    if (DECK_SIZE % 8 != 0) printf("\n");
}

int main(void) {
    Card deck[DECK_SIZE];

    // srand 초기화 (현재 시간 사용)
    srand((unsigned)time(NULL));

    // 덱 생성, 섞기, 출력
    init_deck(deck);
    shuffle_deck(deck);

    printf("Shuffled 52-card deck (no jokers):\n\n");
    print_deck(deck);

    return 0;
}
