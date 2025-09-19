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
📚 참고 사항

카드 모양 문자열은 UTF-8 완성형 문자이므로 출력 환경에 따라 깨질 수 있음

Git Bash 또는 Visual Studio 터미널에서 한글 및 특수문자 설정 확인 필요
---

# 🎵 음계와 피아노 건반 – 주파수 기반 음 생성 프로그램

---

## 📌 개요

이 문서는 저장된 MP3나 오디오 파일이 아닌, **컴퓨터 상에서 직접 주파수를 이용하여 음을 생성**하는 기계적인 방식의 음 표현 방법에 대해 설명합니다.

- 음의 표현은 주파수를 기반으로 하며, 주파수가 높을수록 고음, 낮을수록 저음을 생성합니다.
- 피아노 건반과 같은 **12평균율 기반의 음계 체계**를 사용하여 주파수를 계산하고 음을 출력합니다.
- `Beep()` 함수를 이용해 윈도우 스피커에서 음을 직접 생성합니다.

---

## 🎼 음계(Musical Scale)란?

- **음계**는 음을 높이순서로 나열한 것입니다.
- 음과 음 사이의 **음정(Tone)** 은 고정된 주파수 비율로 계산됩니다.
- 기준 음은 **'A' (라)** 로, 주파수는 **440Hz**로 고정되어 있습니다.
- 다른 음의 주파수는 이 기준에 따라 비례적으로 계산됩니다.

---

## 🎹 피아노 건반과 12평균율

- **12평균율**은 한 옥타브를 12개의 **반음정(semitone)** 으로 균등하게 나눈 음률 체계입니다.
- 옥타브 간의 음정 비율은 **1:2**입니다.
- 모든 반음은 일정한 주파수 비율로 증가하며, 약 **1.059463094** (12√2) 배씩 올라갑니다.

---

## 📊 주파수 계산 방법

- 기준음 `A4 = 440Hz`
- `n` 번째 반음의 주파수는 다음 공식으로 계산합니다:

```
f = 440 * pow(2, (n - 9) / 12.0);
```

---
| 음계     | 반음 번호(n) | 주파수(Hz) |
| ------ | -------- | ------- |
| C4 (도) | 0        | 261.63  |
| D4 (레) | 2        | 293.66  |
| E4 (미) | 4        | 329.63  |
| F4 (파) | 5        | 349.23  |
| G4 (솔) | 7        | 392.00  |
| A4 (라) | 9        | 440.00  |
| B4 (시) | 11       | 493.88  |
| C5 (도) | 12       | 523.25  |
---

📦 index 배열
```
int index[] = {0, 2, 4, 5, 7, 9, 11, 12};
//           =>  도, 레, 미, 파, 솔, 라, 시, 도(상행)
```

---

⚙️ 주파수 계산 함수 (정수형 반환)
'''
int calc_frequency(int octave, int semitoneIndex) {
    double baseFreq = 32.7032;  // 옥타브 1의 도(C) 주파수
    double freq = baseFreq * pow(2, octave - 1 + semitoneIndex / 12.0);
    return (int)(freq + 0.5);  // 소수점 첫째 자리 반올림
}
'''

---
🔉 주파수로 소리 출력 (Windows용)

Windows API의 Beep(frequency, duration) 함수 사용

헤더: <windows.h>
```
#include <windows.h>

Beep(440, 500);  // 라(A) 440Hz 음을 0.5초 동안 출력
```

---
⌨️ 키 입력 처리: getch() vs scanf()

scanf() 사용 시 Enter 키 입력 필요 → 음이 끊기고 어색함

getch()는 즉시 입력받을 수 있어 자연스러운 연주 가능

```
#include <conio.h>

char ch = getch();  // 사용자가 키를 누를 때까지 대기
```

---
🖥 실행 예시
```
도레미파솔라시도
도시라솔파미레도
```


스피커에서 각 음에 해당하는 소리가 연속적으로 출력됩니다.

각 음은 약 0.5초씩 유지됩니다

---
🧪 전체 연주 예시 코드


```
#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <conio.h>

int index[] = {0, 2, 4, 5, 7, 9, 11, 12};  // 도 ~ 도

int calc_frequency(int octave, int semitoneIndex) {
    double baseFreq = 32.7032;  // 1옥타브 도
    double freq = baseFreq * pow(2, octave - 1 + semitoneIndex / 12.0);
    return (int)(freq + 0.5);  // 반올림
}

int main() {
    int octave = 4;

    // 상행: 도레미파솔라시도
    for (int i = 0; i < 8; i++) {
        int freq = calc_frequency(octave, index[i]);
        Beep(freq, 500);
    }

    // 하행: 도시라솔파미레도
    for (int i = 7; i >= 0; i--) {
        int freq = calc_frequency(octave, index[i]);
        Beep(freq, 500);
    }

    return 0;
}

```

---

# 📚 자료구조(Data Structure)와 실생활 응용

---

## 📌 개요

**자료구조(data structure)**란 컴퓨터상에서 정보를 효율적으로 저장, 탐색, 추가, 삭제하기 위해 데이터를 구성하고 이들 간의 관계를 정의하는 방법입니다.

- **선형 구조**: 연결 리스트(Linked List), 스택(Stack), 큐(Queue), 데크(Deque) 등
- **비선형 구조**: 트리(Tree), 그래프(Graph) 등

이 문서에서는 **선형 구조**, 특히 **연결 리스트**와 **스택**이 **일상생활과 게임**에서 어떻게 활용되는지, 그리고 동적 메모리 관리 및 문자열 정렬 기법에 대해서 설명합니다.

---

## 🔗 연결 리스트 (Linked List)

### ✅ 개념

- 데이터를 저장하는 단위인 **노드(node)**로 구성
- 각 노드는 다음 노드의 주소를 가리키는 **링크 필드(link field)**를 포함
- 마지막 노드의 링크 필드는 `NULL`
- **동적 메모리 할당**을 통해 메모리를 필요할 때 확보하고 필요 없으면 해제

### ✅ 구현 핵심

```
typedef struct Node {
    char data;
    struct Node* next;
} Node;
```



self-referential structure: 구조체 내부에서 자기 참조
---

---
✅ 연결 리스트 장점

임의 위치에서 삽입/삭제가 빠름

배열처럼 미리 메모리 크기를 정하지 않아도 됨

메모리 낭비가 적음
---


🕹 실생활/게임 응용 예: Replay 기능

게임에서 버튼 조작 시마다 키 입력을 연결 리스트로 저장

Esc 키를 누르면 저장된 키값을 순서대로 출력

역순 출력을 위해 재귀 함수 사용
---


동적 메모리 관리 (Dynamic Memory Allocation)

실행 중 필요한 만큼 메모리를 확보하고, 불필요해지면 반환

malloc, calloc, free 함수 사용

예: 키 입력 시 동적 노드 생성


```
Node* newNode = (Node*)malloc(sizeof(Node));
newNode->data = inputChar;
newNode->next = NULL;
```

---


🧱 스택 (Stack)
✅ 개념

Last In, First Out (LIFO) 구조

삽입/삭제가 한 쪽 (top) 에서만 이루어짐

데이터 추가: push(), 데이터 제거: pop()
---


🧖 실생활 예: 찜질방 수건 더미

새로운 수건은 위에 놓이고

사용할 땐 위에서부터 꺼냄 → 스택 구조



---
🃏 게임 응용: 원카드(One Card) 게임

버리는 카드 더미: 같은 무늬/숫자 → push()

가져오는 카드 더미: 없을 경우 → pop()으로 가져감


---
✅ 스택에서 pop 구현 예시

```
char pop(StackNode** top) {
    if (*top == NULL) return -1;

    StackNode* temp = *top;
    char data = temp->data;
    *top = temp->next;
    free(temp);

    return data;
}
```


---
🔤 문자열 정렬 (Alphabetical Sorting)

텍스트 파일에서 컴퓨터 용어들을 읽고, 검색 전에 알파벳 순서로 정렬하기 위한 과정.
---

⚠️ 대문자와 소문자 문제

'A' = ASCII 65

'a' = ASCII 97

대소문자가 혼용된 문자열을 그대로 정렬하면 올바르지 않은 결과가 나올 수 있음
---


✅ 해결 방법: 비교 시 소문자로 변환

```
char upper_to_lower(char c) {
    if (c >= 'A' && c <= 'Z')
        return c + ('a' - 'A');
    return c;
}
```


✅ 정렬 로직 (Bubble Sort 예시)
```
void sort_strings(char* arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcasecmp(arr[j], arr[j + 1]) > 0) {
                char* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
```

strcasecmp()는 문자열을 소문자로 간주하여 비교 (비표준 함수, POSIX 시스템에 존재)


---
## 💾 연결 리스트 vs 배열 비교
| 항목     | 배열(Array)  | 연결 리스트(Linked List) |
| ------ | ---------- | ------------------- |
| 메모리 크기 | 고정         | 가변 (동적 할당)          |
| 삽입/삭제  | 느림 (이동 필요) | 빠름 (링크 변경만 필요)      |
| 접근 속도  | 빠름 (인덱스)   | 느림 (순차 접근 필요)       |
| 메모리 낭비 | 많을 수 있음    | 적음 (필요할 때만 할당)      |


---
## 📌 결론 및 활용 요약
| 자료구조   | 응용 사례                | 장점                 |
| ------ | -------------------- | ------------------ |
| 연결 리스트 | 게임 Replay / 입력 기록 저장 | 메모리 효율, 삽입/삭제 유리   |
| 스택     | 찜질방 수건 / 카드 버리는 더미   | LIFO 구조, 재귀적 처리 유리 |
| 문자열 정렬 | 용어 검색 전 정렬 / 사전 만들기  | 사용자 검색 속도 향상       |


