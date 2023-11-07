#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10

typedef struct Node{
  int data;
  struct Node* left;
  struct Node* right;
}NODE;


void insertNode(NODE** root, int DATA);
void deleteNode(NODE** root, int DATA, int* len);
void printTree(NODE* root);
NODE* findNode(NODE** root, int DATA);
NODE* searchNode(NODE* root, int DATA);
NODE* searchParent(NODE* root, int DATA);
void inorder_traversal(NODE* root);
void rightrootleft_traversal(NODE* root);
NODE* getMin(NODE* root);
NODE* getMax(NODE* root);
int height(NODE* root);
NODE* balanceAgain(NODE** root);
void clear (NODE* root);


void menu(){
  printf("2021313628 이재림_AVLtree\n\n");
  printf("주의 사항1 : 명령 입력시, 반드시 하나의 명령 key만 적용하시오.\n");
  printf("주의 사항2 : P키를 통해서, 트리를 계속적으로 확인할 수 있습니다.\n"); 
  printf("주의 사항3 : 프로그램 종료 원할 시, Q를 입력하시오.\n\n");
  printf("================menu===============\n");
  printf("+          insertNode\n");
  printf("-          deleteNode\n");
  printf("#          countNode\n");
  printf("T          heightTree\n");
  printf("I          inorder_traversal_traversal\n");
  printf("R          rightrootleft_traversal\n");
  printf("N          getMin\n");
  printf("X          getMac\n");
  printf("P          printTree\n");
  printf("C          clear\n");
  printf("F(data)    findNode\n");
  printf("H(data)    heightNode\n");
  printf("G(data)    get_rightChild\n");
  printf("L(data)    get_leftChild\n");
  printf("=======================================\n");
}

int main() {
  menu();
  NODE* root = NULL; // 노드 가리티는 루트 생성

  char request[MAX];
  int go = 1;
  int len = 0;
  while(go) {
   
    int x = 0; // 받은 데이터를 int로 바꿔주기
    printf("\n\t>>>");
    gets(request);
    int length = strlen(request);
    int i = 1;
    while (request[i] >= '0' && request[i] <= '9') {
      x *= 10;
      x += request[i] - 48;
      i ++; 
    }
    for (int i = 0; i < length; i++) {
      switch(request[i]) {
        case '+' : {
          printf("\t%d를 삽입합니다.\n", x);
          insertNode(&root, x);
          len ++;
          root = balanceAgain(&root); // 조정
          break;
        }
        case '-' : {
          printf("\t%d를 삭제합니다.\n", x);
          if (root == NULL) {
            printf("\t트리가 비어있습니다.\n");
            break;
          }
          deleteNode(&root, x, &len);
          len --;
          root = balanceAgain(&root); // 조정
          break;
        }
        case '#' : {
          printf("\t노드는 %d개입니다.", len);
          break;
        }
        case 'T' : {
          int h = height(root);
          printf("\theight : %d", h);
          break;
        }
        case 'I' : {
          printf("\t데이터 나열합니다.\n\t");
          inorder_traversal(root);
          break;
        }
        case 'R' : {
          printf("\t데이터 나열합니다.\n\t");
          rightrootleft_traversal(root);
          break;
        }
        case 'N' : {
          NODE* min = getMin(root);
          printf("\t최솟값 : %d", min->data);
          break;
        }
        case 'X' : {
          NODE* max = getMax(root);
          printf("\t최대값 : %d", max->data);
          break;
        }

        case 'F' : {
          printf("\t위치를 탐색합니다.\n");
          findNode(&root, x);
          break;
        }

        case 'G': {
				  NODE* rightnode = searchNode(root, x); // 일단 해당 데이터의 노드 지정
				  if (rightnode == NULL){ // 해당 데이터 노드가 없다면
					  printf("\t해당 노드는 존재하지 않습니다.\n");
            break;
				  }
          else if (rightnode->right == NULL) {
            printf("\trightNode를 찾을 수 없습니다.\n");
            break;
          }
				  else {
					  rightnode = rightnode->right; // 해당노드의 오른쪽으로 업데이트
					  printf("\t데이터 : %d\n", rightnode->data);
				  }
          break;
			  }
        case 'L': {
				  NODE* leftnode = searchNode(root, x);
				  if (leftnode == NULL){
					printf("\t해당 노드는 존재하지 않습니다.\n");
				  }
          else if (leftnode->left == NULL) {
            printf("\tleftNode를 찾을 수 없습니다.\n");
            break;
          }
				  else{
					  leftnode = leftnode->left; // 해당노드의 왼쪽으로 업데이트
					  printf("\t데이터 : %d\n", leftnode->data); 
				  }
          break;
			  }     
        
        case 'P' : {
          if (root == NULL)
            printf("\t아직 루트가 비어있습니다.\n");
          else {
            printf("\n\t%d", root->data);
            printTree(root); 
          }
          printf("\n");
          break;
          }
        case 'C' : {
          clear(root);
          break;
        }

        case 'Q' : {
          printf("\t종료합니다.");
          go = 0;
          break;
        }
      }
    }
  }
  return 0;
}


void insertNode(NODE** root, int DATA) {
  NODE* newNode = malloc(sizeof(NODE));
  newNode->right = NULL;
  newNode->left = NULL;
  newNode->data = DATA;
  
  if (*root == NULL) { // 루트가 가리키는 것이 없음
    printf("\t루트에 데이터를 삽입합니다.\n");
    *root = newNode; // 루트가 가리키는 것을 새노드로
    return;
  }  
  // 루트에 이미 값이 있는 경우, 넣어야 하는 곳 찾기
  NODE* cur = *root;
  NODE* parent = NULL;
  while (cur != NULL) {
		if (cur->data < DATA) { // 지금 위치의 데이터보다 삽입할 것이 더 큼
			parent = cur; // 저장
			cur = cur->right; // 오른쪽으로 가기
		}
		else if (cur->data > DATA) { // 지금 위치보다 삽입할 것이 더 작음
			parent = cur; // 저장
			cur = cur->left; // 왼쪽으로 가기
		}
		else {
			printf("\t중복된 데이터가 존재합니다.\n");
			return;
		}
	}
  //대소에 따라서 해당 위치에 노드 집어넣기!
	if (parent->data > DATA)
		parent->left = newNode; 
	else
		parent->right = newNode;
}

void printTree(NODE* root) {
  if (root == NULL)
		return; // 질문)) 이거 빼고 안빼고의 차이가 무엇일지,,이거 따라 오류가 남
	if (root->right == NULL && root->left == NULL) // 루트 밑에 비어있음
		return;
  // 출력을 시작
	printf("(");
	if (root->left != NULL) // 왼쪽
		printf("%d", root->left->data); 
	printTree(root->left);
	printf(",");
	if (root->right != NULL) // 오른쪽
		printf("%d", root->right->data);
	printTree(root->right);
	printf(")");
}

NODE* findNode(NODE** root, int DATA)  { 
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

NODE* searchNode(NODE* root, int DATA) { // 해당 데이터 검색
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

NODE* searchParent(NODE* root, int DATA) { // 위에있는 부모노드 검색
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


void deleteNode(NODE** root, int DATA, int *len) { // 트리의 루트의 주소를 가리킴
	NODE* cur = searchNode(*root, DATA); 
	if (cur == NULL) { // 해당 값의 노드를 찾을 수 없음
    printf("해당 노드를 찾을 수 없습니다.\n");
    *len = *len + 1; // 이 경우는 main 함수에서 len줄어들면 안되므로!
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

NODE* getMin(NODE* root) {
	if (root == NULL)
		return NULL;
	NODE* cur = root;
	while (cur->left != NULL) {
		cur = cur->left;
	}
	return cur;
}

NODE* getMax(NODE* root) {
	if (root == NULL)
		return NULL;
	NODE* cur = root;
	while (cur->right != NULL) {
		cur = cur->right;
	}
	return cur;
}


void inorder_traversal(NODE* root) {
	if (root != NULL) {
		inorder_traversal(root->left); // 왼쪽부터 출력을 시작
		printf("%d ", root->data);
		inorder_traversal(root->right);
	}
}

void rightrootleft_traversal(NODE* root) {
	if (root != NULL) {
		rightrootleft_traversal(root->right); // 오른쪽부터 출력
		printf("%d ", root->data);
		rightrootleft_traversal(root->left);
	}
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

    
int balancing_factor(NODE* node){
  return height(node->left) - height(node->right);
}


NODE* LLrotate(NODE* root){
	NODE* a = root->left; //new root
	NODE* b = a->right;
	a->right = root;
	root->left = b;
	return a;
}

NODE* RRrotate(NODE* root){
	NODE* a = root->right;
	NODE* b = a->left;
	a->left = root;
	root->right = b;
	return a;
}
    
NODE* LRrotate(NODE* root){ //RR -> LL
	root->left = RRrotate(root->left);
	return LLrotate(root);
}

NODE* RLrotate(NODE* root){ //LL -> RR
	root->right = LLrotate(root->right);
	return RRrotate(root);
}
    
NODE* balanceAgain(NODE** root){
	if (balancing_factor(*root) >= 2){
		if (balancing_factor((*root)->left) >= 1){
			*root = LLrotate(*root);
		}
		else{
			*root = LRrotate(*root);
		}
	}

	else if (balancing_factor(*root) <= -2){
		if (balancing_factor((*root)->right) <= -1){
			*root = RRrotate(*root);
		}
		else{
			*root = RLrotate(*root);
		}
	}
	return *root;
}

void clear (NODE* root){
  if (root != NULL){
    clear(root->left);
    clear(root->right);
    free(root);
  }
  return;
}