#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 10 
//MAX는 최대용량임
typedef struct Node {
	char data;
  struct Node* before;
	struct Node* next;
}NODE;
typedef struct Deque {
	NODE* front; // 첫 노드를 가리키는 포인터
	NODE* rear; // 현재 위치의 노드 가리키는 포인터
  int len; //노드의 길이
}DEQUE;



void menu() 
{
  printf("2021313628 이재림\n");
  printf("Our group decided to differentiate the input forms of ADD function\n");
  printf("PLEASE READ OUR MENU CAREFULLY!\n");
  printf("====================menu=======================\n");
  printf("============<<<<<deque program>>>>>============\n\n");
  printf("F+(data)    addFront(deque, data)\n"); 
  printf("R+(data)    addRear(deque, data)\n"); 
  printf("DF          deleteFront\n");
  printf("DR          deleteRear\n"); 
  printf("L           printList\n");
  printf("GF          getFront\n");
  printf("GR          getRear\n");
  printf("O           is_full\n");
  printf("E           is_empty(deque) Bool형태로 출력\n");
  printf("I           clear the deque(init)\n");
  printf("***반드시 '+' 앞에 알파벳 key를 입력하여 기능을 명시해주세요.***\n");
  printf("    ***첫 데이터 삽입시 R+를 이용하여 삽입하시오.***\n");
  
}


void addRear(DEQUE* deque, char DATA) {
	NODE* newNode = malloc(sizeof(NODE)); // 노드 새로 생성
  newNode->before = deque->rear;
	newNode->data = DATA; // 새 노드에 데이터 저장
	newNode->next = NULL; // 새 노드 next연결 끝으로
	deque->rear->next = newNode; // 원래 마지막 노드 next를 새노드로 
  deque->rear = newNode;
  
  deque->len ++;
}
void addFront(DEQUE* deque, char DATA) {// 지금 커서의 앞에 삽입
  NODE* newNode = malloc(sizeof(NODE));
  newNode->next=deque->front->next; // 원래 맨앞에 있던 노드를 새노드 뒤로 연결
  deque->front->next = newNode; // front 포인터는 이젠 새 노드로 가리킴
  newNode->data = DATA; // 새노드 데이터 삽입

  deque->len ++;
};

void deleteRear(DEQUE* deque) {

  NODE* delNode = deque->rear; //맨처음 노드 삭제 지정
  printf("\trear 위치에서 데이터 <%c>를 삭제합니다.", delNode->data);
  NODE* beforeNode = delNode->before;
  beforeNode->next = NULL;
  deque->rear->next= beforeNode;
  deque->rear = beforeNode;
  
  deque->len--;
  free(delNode);
}

void deleteFront(DEQUE* deque) {
  NODE* delNode = deque->front->next; //맨처음 노드 삭제 지정
  printf("\tfront 위치에서 데이터 <%c>를 삭제합니다.\n", delNode->data);
  NODE* nextNode = delNode->next;
  deque->front->next = nextNode;
  nextNode->before = deque->front;
  
  deque->len--;
  free(delNode);
}

void printL(DEQUE* deque) {
	NODE* crnt = deque->front->next;
	printf("\n\tarray: [");
	if (crnt == NULL) // front뒤에 아무것도 없다면
    printf("This deque is empty");
	else while (crnt != NULL) {
		printf("%c ", crnt->data);
		crnt = crnt->next;
	}
  printf("]");
}

void getFront(DEQUE* deque) {
  NODE* frontNode = deque->front->next;
  printf("\tfront data 출력: %c\n", frontNode->data);
  
}


void getRear(DEQUE* deque) {
  NODE* rearNode = deque->rear;
  printf("\trear data 출력: %c\n", rearNode->data);
  
}

void is_Full(DEQUE* deque) {
  if (deque->len == MAX)  // 지정된 최대용량 MAX와 비교
    printf("TRUE: The array is full\n");
  else
    printf("FALSE: The array is nor full(%d/%d)\n", deque->len, MAX);
}

void is_empty(DEQUE* deque) {
  if (deque->len == 0) 
    printf("TRUE: The array is empty\n");
  else
    printf("FALSE: The array is not empty(%d/%d)\n", deque->len, MAX);
}

void init(DEQUE* deque) {
  printf("덱을 초기화합니다.\n");
  NODE* temp = NULL;
	while (deque->front->next != NULL) {
		temp = deque->front;
		deque->front = temp->next;
		free(temp);
	}
	free(deque->front);
}




int main() {
  NODE* newNode = malloc(sizeof(NODE)); // 노드 생성
	DEQUE* deque = malloc(sizeof(DEQUE)); // 선언
	deque->front = newNode; // front는 이 newNode임
	deque->front->data = NULL; // 정보 x
	deque->front->next = NULL; // 정보 x
	deque->rear = deque->front; // 현재 위치 포인터는 헤드로

  int len = 0;
	int go = 1;
  menu();

	while (go) {
		printL(deque); // 리스트 상황 보여줌
		char request[30] = { 0 }; // 사용자 입력
		printf("\n\t>>> ");
		gets(request);
		int num = 0; // 
    int k = deque->len;
    int size = strlen(request);
    for (int i = 0; i < size; i++) {
      switch (request[i]) {
        
			case 'F':
				if (request[i + 1] == '+') {
          if ((isalpha(request[i+2])) != 0)
            addFront(deque, request[i+2]);
        }
        i++;
        i++;
				break;
      
			case 'R':
				if (request[i + 1] == '+') {
          if ((isalpha(request[i+2])) != 0)
            addRear(deque, request[i+2]);
        }
        i++;
        i++;
				break;
      case 'D':
				if (request[i + 1] == 'F') {
          deleteFront(deque);
        }
        else if (request[i + 1] == 'R') {
          deleteRear(deque);
        }
				break;
      case 'G':
				if (request[i + 1] == 'F') {
          getFront(deque);
        }
        else if (request[i + 1] == 'R') {
          getRear(deque);
        }
				break;
      case 'O': 
        is_Full(deque);
        break;
      case 'E':
        is_empty(deque);
        break;
      case 'I':
        init(deque);
        printf("덱을 초기화하여 자동 종료합니다.");
        go = 0;
        break;   
      case 'L':
        printf("\t리스트 상태를 출력합니다."); 
        break;
			case 'Q':
				printf("\n\t프로그램을 강제 종료합니다.\n\n");
				go = 0;
				break;
			default:
				break;
		  }
	  }
  }
    
		

	return 0;
}