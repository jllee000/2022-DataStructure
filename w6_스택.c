#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 10


typedef struct Stack {
  char arr[MAX];
  int len;
}STACK;

int top;

void menu() {
  printf("자료구조 스택 과제_이재림_2021313628\n");
  printf("=================menu==================\n");
  printf("+(element)     Push\n");
  printf("-              Pop\n");
  printf("P              Peek\n");
  printf("F              Is_full\n");
  printf("#              Count element\n");
  printf("T              Top data\n");
  printf("?(element)     Is_member\n");
  printf("=(element)     Replace element\n");
  printf("C              Clear stack\n");
  printf("L              Print stack\n");
  printf("U              Uppercase\n");
  printf("D              Lowercase\n");
  printf("V              view menu\n");
  printf("Q              Quit\n");
  printf("WARNING TO KEEP IN MIND\n");
  printf("*Only 1 element per 1 command\n");
  printf("========================================\n\n");
}

void push(STACK* stack, char data) {
  int curr = stack->len;
  if (curr == 0)
    stack->arr[0] = data;
  else 
    stack->arr[curr] = data;
  stack->len ++;
}

void pop(STACK* stack) {
  int top = stack->len-1;
  printf("\t%c를 삭제합니다.\n", stack->arr[top]);
  stack->arr[top] = NULL;
  stack->len --;
}
void clear(STACK* stack) {
  int length = stack->len;
  while(length != 0) {
    stack->arr[length-1] = NULL;
    length--;  
  }
  stack->len = 0;
  printf("\t스택이 모두 초기화되었습니다.\n");
}
void count(STACK* stack) {
  printf("\tdata 개수: %d개", stack->len);
}
void print(STACK* stack) {
  int length = stack->len;
	if (length == 0) 
    printf("\tThis array is empty");
	else {
    printf("\t    array : [");
		for (int i = 0; i < length-1; i++)	
      printf(" %c,", stack->arr[i]);
		printf(" %c ]\n",stack->arr[length-1]);
  }
}


void printStack(STACK* stack) {
  int length = stack->len;
	if (length == 0) 
    printf("\tThis array is empty");
	else {
    printf("\t스택을 출력합니다.\n");
    printf("\t    => [");
		for (int i = 0; i < length-1; i++)	
      printf(" %c,", stack->arr[i]);
		printf(" %c ]\n",stack->arr[length-1]);
  }
}
void peek(STACK* stack) {
  int top = stack->len-1;
  if (stack->len == 0)
    printf("\tThere is no element.");
  else
    printf("\tTOP Data : %c", stack->arr[top] );
}
void uppercase(STACK* stack) {
  int top = stack->len-1;
  char UP = stack->arr[top];
  UP = UP-32;
  stack->arr[top] = UP;
}

void lowercase(STACK* stack) {
  int top = stack->len-1;
  char DOWN = stack->arr[top];
  DOWN = DOWN+32;
  stack->arr[top] = DOWN;
}

void topData(STACK* stack) {
  int top = stack->len-1;
  printf("\n\tTopdata 출력: %c\n", stack->arr[top]);
}

void isMember(STACK* stack,char DATA) {
  int num = 0;
  int no = 0;
  int length = stack->len;
	while (num != length) {
		if (stack->arr[length-num-1] == DATA) {
			printf("\n\tdata[%d] : %c", stack->len-num-1, DATA);
      no = 1;
		}
    num++; //반복
	}
	printf("\n");
	if (no == 0) printf("\n\tdata <%c> 가 stack 내에 존재하지 않습니다\n", DATA);
}

void isFull(STACK* stack) {
  int length = stack->len;
  if (length == MAX) {
    printf("\t스택이 가득 차있습니다.\n\t10/10;");
  }
  else {
    printf("\t스택에 공간이 남아있습니다.\n");
    printf("\t%d / 10", length);
  }
    
  
}
void replace(STACK* stack, char DATA) {
  int top = stack->len-1;
  stack->arr[top] = DATA;
}
int is_empty(STACK* stack) {
	if (stack->len==0) return 1;
	else return 0;
}

int main() {
  menu();
  STACK s1;
  int go = 1;
  s1.len = 0;
  int result;

  while(go){
    char request[MAX];
    print(&s1);
    printf("\n\t>>>");
    gets(request);
    int size = strlen(request);
    int top = s1.len-1;

    for (int i = 0; i < size; i++) {
      switch(request[i]) {
        case '+' :
          if ((isalpha(request[i+1])) != 0)
            push(&s1, request[i+1]);
          i++;
          break;
        case '-' :
          pop(&s1);
          break;
        case '#' :
          count(&s1);
          break;
        case '?' :
          if ((isalpha(request[i+1])) != 0)
            isMember(&s1, request[i+1]);
          break;
        case '=' :
          replace(&s1, request[i+1]);
          break;
        case 'P' :
          peek(&s1);
          break;
        case 'E' :
          result = is_empty(&s1);
				  if (result == 1) 
            printf("\n\tStack is empty\n");
				  else printf("\n\tStack is not empty\n");
          break;
        case 'C' :
          clear(&s1);
          break;
        case 'F' :
          isFull(&s1);
          break;
        case 'U' :
          uppercase(&s1);
          break;
        case 'D' :
          lowercase(&s1);
          break;
        case 'T' :
          topData(&s1);
          break;
        case 'L' :
          printStack(&s1);
          break;
        case 'Q' :
          printf("프로그램을 종료합니다.\n");
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