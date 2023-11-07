#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>

#define MAX 50

int length = 0;
int position = -1;

void menu() {
  
  printf("===============menu=================\n");
  printf("insert : +\n");
  printf("delete : -\n");
  printf("traverse_front : <\n");
  printf("traverse_rear : >\n");
  printf("prev : P\n");
  printf("next : N\n");
  printf("get_data : @\n");
  printf("replace : =\n");
  printf("empty : E\n");
  printf("move : M\n");
  printf("move backward one : MP\n");
  printf("move forward one : MN\n");
  printf("display array : L\n");
  printf("uppercase : U\n");
  printf("lowercase : D\n");
  printf("view menu : V\n");
  printf("\n\n===============================\n");
  printf("===SOME WARNINGS TO KEEP IN MIND===\n");
  printf("* Q should be used ALONE.\n");
  printf("* SPACING between COMMANDS.\n");
  printf("* ONLY 1 data per 1 command.\n");
  printf("\n\n===============================\n");
}

void insert(char array[], char data) {
	position++;
	length = strlen(array);
	for (int i = length; i >= position; i--) {
		array[i] = array[i - 1];
	}
	array[position] = data;
}

void replace(char arr[], char data) 
{
	arr[position] = data;
}
void change_part(char array[], int index, char data) {
	array[index - 48] = data;
	position = index - 48;
}

void delete(char arr[]) {
  arr[position] = NULL;
}

void empty(char array[]) {
	for (int i = 0; i < length; i++) {
		array[i] = NULL;
	}
	position = -1;
}

void print(char array[]) 
{
	length = strlen(array);
	if (length == 0) printf("This array is empty");
	else 
  {
		printf("\t    array : [");
		for (int i = 0; i < length-1; i++)	printf(" %c,", array[i]);
		printf(" %c ]\n",array[length-1]);
  }
}
void get_data(char arr[])
{
  printf("\ncurrent data : %c\n", arr[position]);
}

void traverse_front(char array[]) {
	position = 0;
}
void traverse_rear(char array[]) {
	position = length - 1;
}
void next(char array[]) {
	if (position == length - 1);
	else position++;
}
void prev(char array[]) {
	if (position == 0);
	else position--;
}


void move(char arr[], int index) {
	char temp;
	if (position > index) 
  {
	  temp = arr[0];
	  for(int i = 1 ; i < length ; i++)
	  {
		  arr[i-1] = arr[i] ;
	  }
	  arr[length-1] = temp ;
  }
	else if (position < index) 
  {  
	  temp = arr[length-1];
	  for(int i = length-1 ; i > 0 ; i--)
	  {
		  arr[i] = arr[i-1] ; 
	  }
	  arr[0] = temp ;
  }
  else
    position = index;

}
void show(char arr[])
{
  if (length == 0) 
    printf("\n\t This array is empty");
	else 
  {
    printf("");
		for (int i = 0; i < length; i++) 
    {
			if ((i == position || (position == -1 && length != 0))) 
        printf(" (%c)", arr[i]);
			else 
        printf(" %c", arr[i]);
		}
	}
}
void uppercase(char arr[])
{
  int data;
  data = arr[position];
  char UP;
  if((data >= 97) && (data <= 122))
  {
    UP = data - 32;
    arr[position] = UP;
  }
}

void lowercase(char arr[])
{
  char data;
  data = arr[position];
  char LOW;
  if((data >= 65) && (data <= 90))
  {
    LOW = data + 32;
    arr[position] = LOW;
  }
}

//main function
int main() {
  printf("2021313628 이재림_4주차과제\n\n");
	char alpha[MAX] = { 0 }; //문자 배열 공간을 준비
	menu(); //메뉴 출력
	while (1) {

		char request[MAX] = { 0 }; // 사용자 요청받을 문자열

		length = strlen(alpha); 
		show(alpha);
		printf("\n>>> ");
		gets(request); //사용자 요청 받음
		char length = strlen(request);
    if (request[0] == 'Q')
    {
			printf("\n--------The end--------\n");
			break;
    }

		for (int i = 0; i < length; i++) {
			switch (request[i]) {
			case '+': //삽입
        insert(alpha, request[i + 1]);
        i++;
        break;
			case '-': //현재 위치의 문자 삭제
	      delete(alpha);
        break;
			case '=': //현재 위치 문자를 다른 문자로 대체
				replace(alpha, request[i+1]);
        i++;
        break;
			case 'E': //배열 전체 지우기
				empty(alpha);
				break;
			case '@': //현재 위치의 문자 출력
        get_data(alpha);
				break;

			case 'L': //배열 전체 보이기
				print(alpha);
				break;
			case '<': //맨 앞으로 커서 움직이기
				traverse_front(alpha);
				break;
			case '>': //맨 뒤로 커서 움직이기
				traverse_rear(alpha);
				break;
			case 'N': //오른쪽으로 커서 움직이기
				next(alpha);
				break;
			case 'P': //왼쪽으로 커서 움직이기
				prev(alpha);
				break;
      case 'U' : //현재 위치의 문자 대문자화
        uppercase(alpha);
        break;
      case 'D' : //현재 위치의 문자 소문자화
        lowercase(alpha);
        break;
      case 'V' : //메뉴 보이기
        printf("메뉴를 출력합니다.\n");
        menu();
        break;
			case 'M': //배열 전체를 당기기
        if (request[i + 1] == 'N') //오른쪽
					move(alpha, position + 1);
				else if (request[i + 1] == 'P') //왼쪽
					move(alpha, position - 1);
				i++;
				break;
         
			default:
				break;
			}
		}
	}
	return 0;
}//main()