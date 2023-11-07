
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 10


typedef struct Queue {
  char arr[MAX];
  int head;
  int tail;
  int len;
}QUEUE;


void menu() {
  printf("자료구조 큐 과제_이재림_2021313628\n");
  printf("=================menu==================\n");
  printf("+(element)     EnQueue\n");
  printf("-              DeQueue\n");
  printf("P              Peek\n");
  printf("H              Head\n");
  printf("T              Tail\n");
  printf("F              Is_full\n");
  printf("E              Is_empty\n");
  printf("#              Count element\n");
  printf("?(element)     Is_member\n");
  printf("=(element)     Replace element\n");
  printf("C              Clear Queue\n");
  printf("L              Print Queue\n");
  printf("U              Uppercase\n");
  printf("D              Lowercase\n");
  printf("V              View menu\n");
  printf("Q              Quit\n");
  printf("WARNING TO KEEP IN MIND\n");
  printf("*Only 1 element per 1 command\n");
  printf("========================================\n\n");
}

void enQueue(QUEUE* Queue, char data) {
  int length = Queue->tail - Queue->head;
  int first = Queue->head;
  int last = Queue->tail;
  int i = last;
  if (length == 0) {// 비어있으면
    Queue->arr[0] = data;
  }
  else if ((length == MAX)) {
    printf("\t\t배열이 꽉차서 추가가 안됩니다.");
    Queue->len--;
    Queue->tail--;
  }
  else if (Queue->tail == MAX - 1){
    for (int i = 0; i < Queue->len; i++){
      Queue->arr[Queue->head+i] = Queue->arr[Queue->head+i+1];
    }
    Queue->arr[Queue->tail] = data;
    Queue->tail = Queue->tail - Queue->head - 1;
    Queue->head = -1;
    
    
  }
  else 
    Queue->arr[last+1] = data;
  Queue->len ++;
  Queue->tail ++;
    
 
}

void deQueue(QUEUE* Queue) {
  int first = Queue->head+1;
  int length = Queue->tail - Queue->head;
  if (length == 0)
    printf("\t\t삭제할 요소가 없습니다.\n");
  else {
    printf("\t\t%c를 삭제합니다.\n", Queue->arr[first]);
    Queue->arr[first] = NULL;
    Queue->head ++;
  }
  Queue->len --;
}

void peek(QUEUE* Queue) {
  int length = Queue->len;
  int first = Queue->head+1;
  printf("\t\tpeek: %c", Queue->arr[first]);
}

void head(QUEUE* Queue) {
  printf("\t\t현재 head 위치: %d", Queue->head);
}

void tail(QUEUE* Queue) {
  printf("\t\t현재 tail 위치: %d", Queue->tail);
}

void Is_full(QUEUE* Queue) {
  int length = Queue->tail - Queue->head;
  if (length == MAX) {
    printf("\t\tTRUE: Array is Full (%d/%d)", length, MAX);
  }
  else 
    printf("\t\tFALSE: 큐에 공간이 남아있습니다. (%d/%d)", length, MAX);
}

void Is_empty(QUEUE* Queue) {
  int length = Queue->tail - Queue->head;
  if (length == 0) {
    printf("\t\tTRUE: 현재 큐는 비어있습니다");
  }
  else
    printf("\t\tFALSE: 현재 큐는 비어있지 않습니다. (%d/%d)", length, MAX);
}

void Is_member(QUEUE* Queue, char DATA) {
  int first = Queue->head+1;
  int length = Queue->tail - Queue->head;
  int result = 0;
  for (int i = 0; i < Queue->tail+1; i++) {
    if (Queue->arr[i] == DATA) 
      printf("\t\tTRUE: 해당 데이터 <%c>가 존재합니다.\n", DATA);
      result = 1;
  }
  if (result == 0)
    printf("\t\tFALSE: 큐에 해당 데이터가 없습니다.\n");
    
}


void count(QUEUE* Queue) {
  int first = Queue->head;
  int last = Queue->tail;
  int length = last-first;
  printf("\t\t현재 큐 요소 개수: %d개\t", length);
}

void replace(QUEUE* Queue, char DATA) {
  int first = Queue->head+1;
  Queue->arr[first] = DATA;
}

void print(QUEUE* Queue) {
  int length = Queue->tail- Queue->head;
  int last = Queue->tail;
  if (length == 0)
    printf("\tThe array is empty");
  else{
    printf("\t\tarray: [");
    int i = Queue->head;
    while (i != last){
      printf("%c ", Queue->arr[i+1]);
      i++;
    }
    printf("]");
  }
}

void uppercase(QUEUE* Queue) {
  int first = Queue->head+1;
  char UP = Queue->arr[first];
  UP = UP-32;
  Queue->arr[first] = UP;
}

void lowercase(QUEUE* Queue) {
  int first = Queue->head+1;
  char DOWN = Queue->arr[first];
  DOWN = DOWN+32;
  Queue->arr[first] = DOWN;
}

void clear(QUEUE* Queue) {
  int length = Queue->tail- Queue->head;
  for (int i=0; i < length; i++)
  {
    deQueue(Queue);
  }
  
}




int main() {
  menu();
  QUEUE s1;
  int go = 1;
  s1.head = -1;
  s1.len = 0;
  s1.tail = -1;
  int result;

  while(go){
    char request[MAX];
    print(&s1);
    printf("\n\t>>>");
    gets(request);
    int size = strlen(request);
  

    for (int i = 0; i < size; i++) {
      switch(request[i]) {
        case '+' :
          if ((isalpha(request[i+1])) != 0)
            enQueue(&s1, request[i+1]);
          i++;
          break;
        case '-' :
          deQueue(&s1);
          break;
        case 'P' :
          peek(&s1);
          break;
         case 'H' :
          head(&s1);
          break;
         case 'T' :
          tail(&s1);
          break;
        case 'F' :
          Is_full(&s1);
          break;
        case 'E' :
          Is_empty(&s1);
          break;
        case '#' :
          count(&s1);
          break;
        case '=' :
          if ((isalpha(request[i+1])) != 0)
            replace(&s1, request[i+1]);
          i++;
          break;
        case '?' :
          if ((isalpha(request[i+1])) != 0)
            Is_member(&s1, request[i+1]);
          i++;
          break;
        case 'L' :
          printf("\t\t현재 큐를 출력합니다.\n");
          break;
        case 'U' :
          uppercase(&s1);
          break;
        case 'D' :
          lowercase(&s1);
          break;
        case 'C' :
          clear(&s1);
          printf("\t\t배열을 초기화하였습니다.");
          break;
        case 'Q' :
          printf("\t프로그램을 종료합니다.\n");
          go = 0;
          break;
        case 'V' : 
          menu();
          break;
        default :
          break;
        
      }
    }
  }
}  