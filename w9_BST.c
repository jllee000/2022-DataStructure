#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10


typedef struct Node {
  char data;
	struct Node* left;
	struct Node* right;
} NODE;

void initNode(NODE* node, char DATA);
void deleteNode(NODE** root, char DATA);
void insertNode(NODE** root, char DATA);
void findNode(NODE** root, char DATA);
NODE* searchNode(NODE* root, char DATA);
NODE* searchParent(NODE* root, char DATA);
void inorder_traversal(NODE* root); //need \n
void right_root_left_traversal(NODE* root); // \n
void printTree(NODE* root); //cant print root node data, need \n
NODE* get_min(NODE* root);
NODE* get_max(NODE* root);
int countNode(NODE* root);
int height(NODE* root); 

void clear(NODE* root); //need to set root pointer to NULL
int changeInt(char str[], int* idx);

void menu() {
  printf("2021313628 이재림_Binary search Tree\n");
  printf("=============menu==============\n");
  printf("+(데이터)   insertNode\n");
  printf("-(데이터)   deleteNode\n");
  printf("F(데이터)   findNode\n");
  printf("G(데이터)   get_right_child\n");
  printf("L(데이터)   get_left_child\n");
  printf("p          print\n");
  printf("I          inorder_traversal\n");
  printf("R          right_root_left_traversal\n");
  printf("N          get_Min\n");
  printf("X          get_Max\n");
  printf("H          height\n");
  printf("#          countNode\n");
  printf("C          clear\n");
  printf("Q          Quit\n");
  printf("===================================\n");
}
int main() {
	NODE* root = NULL;
  char request[MAX];
  menu();
  int cnt = 0;
  int go = 1;

  while (1){
    if (cnt == 0) 
      printf("현재 트리는 비어있습니다.\n");
    else {
      printf("\t%d", root->data);
      printTree(root);
    }
    printf("\n\t>>>: ");
    gets(request);
    
    int length = strlen(request);
    
    for (int i = 0; i<length; i++){
    
      if (request[i] == '+'){
        i++; // 부호 뒤에 있는 데이터를 사용할때, 숫자로 뽑기 위해 ++
        insertNode(&root, changeInt(request, &i));
        cnt ++;
      }
      else if (request[i] == '-'){
        i++;
        deleteNode(&root, changeInt(request, &i));
        cnt --;
      }
      else if (request[i] == 'F'){
				i++; 
        int findData = changeInt(request, &i);
        findNode(&root, findData);
			}
      
			else if (request[i] == 'P'){
				if (root == NULL){
					printf("\t현재 트리는 비어있습니다.\n");
				}
				else{
					printf("\t%d", root->data);
					printTree(root);
					printf("\n");
				}
			}
			else if (request[i] == 'I'){
				inorder_traversal(root);
				printf("\n");
			}
			else if (request[i] == 'R'){
				right_root_left_traversal(root);
				printf("\n");
			}
			
      else if (request[i] == 'G'){
				i++;
				NODE* rightnode = searchNode(root, changeInt(request, &i)); // 일단 해당 데이터의 노드 지정
				if (rightnode == NULL){ // 해당 데이터 노드가 없다면
					printf("\t해당 노드는 존재하지 않습니다.\n");
				}
				else{
					rightnode = rightnode->right; // 해당노드의 오른쪽으로 업데이트
					printf("\t%d\n", rightnode->data);
				}
			}
		  else if (request[i] == 'L'){
				i++;
				NODE* leftnode = searchNode(root, changeInt(request, &i));
				if (leftnode == NULL){
					printf("\t해당 노드는 존재하지 않습니다.\n");
				}
				else{
					leftnode = leftnode->left; // 해당노드의 왼쪽으로 업데이트
					printf("\t%d\n", leftnode->data); 
				}
			}
			else if (request[i] == 'N'){
				NODE* min = get_min(root);
				if (min == NULL){
					printf("\t최솟값이 존재하지 않습니다.\n");
				}
				else{
					printf("\t%d\n", min->data);
				}
			}
      else if (request[i] == 'X'){
				NODE* max = get_max(root);
				if (max == NULL){
					printf("\t최대값이 존재하지 않습니다.\n");
				}
				else{
					printf("\t%d\n", max->data);
				}
			}  
			
			else if (request[i] == 'H'){
				printf("\t%d\n", height(root));
			}
			else if (request[i] == '#'){
				printf("\t%d개입니다.\n", countNode(root));
			}

			else if (request[i] == 'C'){
        printf("\t트리를 초기화합니다.\n");
				clear(root);
				root = NULL;
			}
      else if (request[i] == 'Q') {
        int go = 0;
        break;
      }
      else
        break;
    }

  }
  return 0;
}



void insertNode(NODE** root, char DATA) { // 추가
	NODE* newnode = (NODE*)malloc(sizeof(NODE));
  newnode->left = NULL;
	newnode->right = NULL;
	newnode->data = DATA;

	if (*root == NULL) {
		*root = newnode;
		return;
	}
	NODE* cur = *root;
	NODE* parent = NULL;
	while (cur != NULL) {
		if (cur->data > DATA) {
			parent = cur;
			cur = cur->left;
		}
		else if (cur->data < DATA) {
			parent = cur;
			cur = cur->right;
		}
		else {
			printf("\t중복된 데이터가 존재합니다.\n");
			return;
		}
	}
	if (parent->data > DATA)
		parent->left = newnode;
	else
		parent->right = newnode;
}

void deleteNode(NODE** root, char DATA) { // 트리의 루트의 주소를 가리킴
	NODE* cur = searchNode(*root, DATA); 
	if (cur == NULL) {
		printf("NO DATA\n");
		return;
	}
	NODE* parent = searchParent(*root, DATA);
	NODE* goUp;
	NODE* theUp;

  if (cur->left == NULL && cur->right == NULL) {//해당 노드 밑에 비어있음
    if (cur == *root) {
      free(*root);
      return;
    }
    if (parent->left == cur) 
      parent->left = NULL; // 해당 노드가 왼쪽에 있으므로 삭제
    else
      parent->right = NULL; // 해당 노드가 오른쪽에 있으므로 삭제
    free(cur);
    
  }
  else if (cur->right == NULL) { // 해당 노드보다 큰 것은 없음
    if (cur == *root){
      NODE* temp = *root;
      *root = (*root)->left;
      free(temp);
      return;
    }
		goUp = cur->left;        
		if (parent->left == cur)
			parent->left = goUp;
		else
			parent->right = goUp;
		free(cur);
  }
  else if (cur->left == NULL) { // 해당 노드보다 작은 것은 없음
    if (cur == *root){
      NODE* temp = *root;
      *root = (*root)->right;
      free(temp);
      return;
    }
		goUp = cur->right;
		if (parent->left == cur)
			parent->left = goUp;
		else
			parent->right = goUp;
		free(cur);
  }
  else if (cur->left != NULL && cur->right == NULL ) {// 해당 노드 밑에 요소들 있을 때
    goUp = cur->right;
		theUp = NULL; // 원래 goUp 노드 저장 노드
		while (goUp->left != NULL) {
			theUp = goUp;
			goUp = goUp->left;
		}
		if (goUp->right == NULL) {
			if (theUp == NULL) {
				cur->data = goUp->data;
				cur->right = NULL;
				free(goUp);
			}
			else {
				cur->data = goUp->data;
				theUp->left = NULL;
				free(goUp);
			}
		}
		else {
			if (theUp == NULL) {
				cur->data = goUp->data;
				cur->right = goUp->right;
				free(goUp);
			}
			else {
				cur->data = goUp->data;
				theUp->left = goUp->right;
				free(goUp);
			}
		}
  }
  else 
    return;
}

void findNode(NODE** root, char DATA) {
  NODE* node = searchNode(*root, DATA);
		if (node == NULL){ // 해당 노드를 검색했을 때 없다면
			printf("\t해당 데이터는 존재하지 않습니다.\n");
		}
		else{ // 해당 노드가 존재한다면, 위치 찾아주기
			int data = node->data;
      printf("\tROOT ");
			NODE* cur = *root; // 처음부터
			while (data != cur->data){ // 데이터로 비교 (크면 오른쪽, 작으면 왼쪽)
				if (cur->data < data){ //해당 데이터가 지금 데이터보다 크면, 오른쪽으로 가야함
					printf("& RIGHT");
					cur = cur->right;
				}
				else{ //해당 데이터가 지금 데이터보다 작으면, 왼쪽으로 가야함
					printf("& LEFT");
					cur = cur->left;
				}
			}
			printf("\n");
		}
  
}

NODE* searchNode(NODE* root, char DATA) { // 해당 데이터 검색
  //트리의 시작과 비교값 반환
	NODE* cur = root; // 맨 첫 노드를 cur로 지정
	while (cur != NULL) { // 마지막
		if (cur->data == DATA) {
			return cur;
		}
		else if (cur->data > DATA)
			cur = cur->left;
		else
			cur = cur->right;
	}

	return NULL;
}

NODE* searchParent(NODE* root, char DATA) { // 위에있는 부모노드 검색
	NODE* cur = root;
	NODE* parent = NULL;
	while (cur != NULL) {
		if (cur->data == DATA) {
			return parent;
		}
		else if (cur->data > DATA) {
			parent = cur;
			cur = cur->left;
		}
		else {
			parent = cur;
			cur = cur->right;
		}
	}
	return NULL;
}

void inorder_traversal(NODE* root) { // 트리 순서대로 출력
	if (root != NULL) {
		inorder_traversal(root->left);
		printf("%d ", root->data);
		inorder_traversal(root->right);
	}
}

void right_root_left_traversal(NODE* root) { // 반대 순서로 출력
  if (root == NULL)
    return;
	else { // root 가 비어있지 않다면
		right_root_left_traversal(root->right); // 제일 오른쪽으로 커서 옮겨서 
		printf("%d ", root->data); // 출력
		right_root_left_traversal(root->left); // 
	}
}




NODE* get_min(NODE* root) {
	if (root == NULL)
		return NULL;
	NODE* cur = root;
	while (cur->left != NULL) {
		cur = cur->left;
	}
	return cur;
}

NODE* get_max(NODE* root) {
	if (root == NULL)
		return NULL;
	NODE* cur = root;
	while (cur->right != NULL) {
		cur = cur->right;
	}
	return cur;
}

int countNode(NODE* root) {
	if (root == NULL)
		return 0;
	return 1 + countNode(root->left) + countNode(root->right);
}

int height(NODE* root) {
	if (root == NULL)
		return 0;
	int left = height(root->left);
	int right = height(root->right);
	if (left > right)
		return left + 1;
	else
		return right + 1;
}



  
void printTree(NODE* root) {
	if (root == NULL)
		return;
	if (root->right == NULL && root->left == NULL)
		return;
  printf("(");
	if (root->left != NULL)
		printf("%d", root->left->data);
	printTree(root->left);
	printf(",");
	if (root->right != NULL)
		printf("%d", root->right->data);
	printTree(root->right);
	printf(")");
}
  

void clear (NODE* root){ //초기화
  if (root != NULL){
    clear(root->left);
    clear(root->right); 
    free(root); //할당 해제
  }
  return;
}

int changeInt(char str[], int* idx){ // request에서 문자열 받은걸 숫자로 변환
    int x = 0;
    while (str[*idx] >= '0' && str[*idx] <= '9'){
        x *= 10;
        x += str[*idx] - 48; // 문자를 숫자로 변환
        (*idx)++; // 뒤에 내용이 숫자가 끝날 때까지
    }
    (*idx)--;
    return x;
}