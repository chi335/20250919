# 🃏 트럼프 카드 구조체 및 셔플 프로그램

---

## 📌 개요

이 프로그램은 C 언어로 작성된 트럼프 카드 시뮬레이션 프로그램입니다.  
총 52장의 카드를 구조체로 정의하고, 초기화, 출력, 셔플 기능을 포함합니다.  
카드의 모양과 숫자를 바탕으로 정렬 또는 출력이 가능하며, 셔플 알고리즘도 두 가지 방식으로 구현 가능합니다.

---

## 🧱 구조체 정의

```
typedef struct {
    int order;         // 카드의 우선순위 (♠: 0, ◆: 1, ♥: 2, ♣: 3)
    char shape[4];     // 카드의 모양 (완성형 문자, 예: "♠")
    char number[3];    // 카드 숫자 또는 문자 (예: "1", "K")
} Card;
```

---
order: 카드의 우선순위를 나타내는 정수

shape: 카드의 모양을 저장하는 문자열

number: 카드의 숫자(1~13) 또는 문자(J, Q, K)


```
const char *shapes[4] = { "♠", "◆", "♥", "♣" };
```

---
## 🔢 카드 숫자 처리 방식

각 모양별로 13장의 카드가 있으며, 숫자는 1부터 13까지입니다.
하지만 11, 12, 13은 각각 J, Q, K로 표시합니다.

```
switch (i + 1) {
    case 11: strcpy(card.number, "J"); break;
    case 12: strcpy(card.number, "Q"); break;
    case 13: strcpy(card.number, "K"); break;
    default: sprintf(card.number, "%d", i + 1); break;
}
```

## 🖨 출력 형식 지정자

숫자일 경우: %-2d → 2자리 왼쪽 정렬

문자일 경우: %-2c → 2자리 공간 확보


```
if (숫자일 경우)
    printf("%-2d ", number);
else
    printf("%-2c ", character);
```

---
🔁 카드 셔플 방법
방법 1: 단순 교환 방식

rand()로 난수 생성: rnd = rand() % 52

card[i]와 card[rnd]를 교환

반복문을 통해 0~51까지 수행

---

```
for (int i = 0; i < 52; i++) {
    int rnd = rand() % 52;
    Card temp = deck[i];
    deck[i] = deck[rnd];
    deck[rnd] = temp;
}
```


---

⚠️ 문제점:

i == rnd일 경우 자기 자신과 교환 → 실질적 변화 없음

---
방법 2: 중복 방지 교환 방식

rnd == i일 경우 다시 난수 생성

중복 없이 확실히 섞을 수 있음


```
for (int i = 0; i < 52; i++) {
    int rnd;
    do {
        rnd = rand() % 52;
    } while (rnd == i);

    Card temp = deck[i];
    deck[i] = deck[rnd];
    deck[rnd] = temp;
}
```

---
💡 주요 구현 포인트

완성형 문자(♠◆♥♣) 출력 → system("chcp 65001") 필요 (Windows용)

랜덤 값 생성을 위한 srand(time(NULL)) 사용

출력 지연 방지를 위한 fflush(stdout) 사용

Beep(frequency, duration)을 활용한 주파수 기반 음 출력도 연계 가능
---
