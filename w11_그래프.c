#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct Node {
  char data; // 데이터
  struct Node *edge_next; // 무방향 연결
  int edge_cnt; // 간선들 개수
  int visited; // 1과 0으로 비교
} NODE;
typedef struct Graph {
  NODE *vertex[MAX]; // 그래프를 배열화
  int vertex_cnt;    // 정점들 개수
  int crr; // 현재
} G;

void menu() {
  printf("2021313628 이재림_Graph\n\n");
  printf("주의 사항1 : 명령 입력시, 반드시 하나의 명령 key만 적용하시오.\n");
  printf("주의 사항2 : 반드시 시작전에 G키로 그래프를 생성하시오.\n");
  printf("주의 사항3 : 프로그램 종료 원할 시, Q를 입력하시오.\n\n");
  printf("================menu===============\n");
  printf("G                            create\n");
  printf("+                            insertVertex_vertex\n");
  printf("-                            delete_vertex\n");
  printf("C                            isConnected\n");
  printf("N                            isEmpty\n");
  printf("L                            print\n");
  printf("E(vertex1, vertex2)          addEdge\n");
  printf("V(vertex)                    degree_of_vertex\n");
  printf("A(vertex)                    adjacent\n");
  printf("P(vertex1, vertex2)          path_exist\n");
  printf("D(vertex1, vertex2)          delete_edge\n");
  printf("R(vertex1, vertex2)          rename_vertex\n");
  printf("X                            num_of_vertex\n");
  printf("H                            num_of_edge\n");
  printf("K                            clear\n");
  printf("Q                            quit\n");
  printf("=======================================\n");
}

void create(G *graph);
void insertVertex(G *graph, char DATA);
void deleteVertex (G *graph, NODE *vertex);
void delete_edge(NODE *vertex, NODE *vertex2);
void reset_visited(G *graph);
NODE *search(G *graph, char DATA);
void visited(G *graph, NODE *node);
void print(G *graph);
void num_of_vertex(G *graph);
void degree_of_vertex(NODE *vertex);
void is_empty(G *graph);
void adjacent(NODE *vertex);
void path_existed(G *graph, NODE *start, NODE *end);
void is_connected(G *graph);
void num_of_edge(G *graph);
int edge_exist(NODE *vertex, NODE *vertex2);
void addEdge(NODE *vertex1, NODE *vertex2);
void rename_vertex(G *graph, NODE *vertex, char data);
void clear(G *graph);

void create(G *graph) {  // 그래프 생성
  graph->crr = 0;        // 현재 위치
  graph->vertex_cnt = 0; // 아직 정점 0개
}

void insertVertex(G *graph, char DATA) {
  int now = graph->crr;
  NODE *newvertex = malloc(sizeof(NODE)); // 정점을 동적할당
  newvertex->data = DATA;
  newvertex->edge_cnt = 0;
  newvertex->edge_next = NULL;    // 그다음 연결은 아직 없음
  graph->vertex[now] = newvertex; // 배열요소에 집어넣기

  graph->crr++;        // 위치 증가
  graph->vertex_cnt++; // 정점개수도 증가
}

void deleteVertex (G *graph, NODE *vertex) { // 정점 삭제
  // 연결먼저 끊기
  for (int i = 0; i < MAX; i++) {
    if (edge_exist(vertex, graph->vertex[i]) == 1) // 연결 있는지 확인
      delete_edge(vertex, graph->vertex[i]); // 연결 끊기 (반복문으로 모든 연결 i번째)
    if (i == graph->vertex_cnt - 1) 
      break;
  }
  for (int i = 0; i < MAX; i++) {
    if (graph->vertex[i]->data == vertex->data) { 
      NODE *tmp = graph->vertex[i];
      for (int j = i; j < graph->vertex_cnt; j++)
        graph->vertex[j] = graph->vertex[j + 1];
      free(tmp); // free 삭제함
      break;
    }
    if (i == graph->vertex_cnt - 1)
      break;
  }
  graph->vertex_cnt--; // 정점개수 감소함
  graph->crr--; // 현재도 감소
}

void delete_edge(NODE *vertex1, NODE *vertex2) { // 정점1과 정점2 연결 삭제
  // 정점1부터 연결 삭제
  if (vertex1->edge_cnt == 1) { // 정점1의 연결이 하나라면 (= 정점2만 연결되었다면)
    vertex1->edge_next = NULL; // 그냥 연결 끊어버리기 NULL로
  } 
  else if (vertex1->edge_next->data == vertex2->data) { 
    NODE *edge = vertex1->edge_next;
    vertex1->edge_next = edge->edge_next;
    free(edge);
  } 
  else { // 정점1 밑에 정점2말고도 다른 연결들이 있다면
    NODE *first = vertex1->edge_next;
    while (first != NULL) {
      if (first->edge_next->data = vertex2->data) { // 다음이 바로 정점2이면
        if (first->edge_next == NULL) { // 정점2 연결 뒤에 아무것도 없다면
          NODE *next = first->edge_next; 
          free(next); 
          first->edge_next = NULL;
        } 
        else { // 맨 끝 아니면
          NODE *edge_next = first->edge_next;
          first->edge_next = edge_next->edge_next; // 그다음다음의 노드를 연결지어줌
          free(edge_next); // 해당 정점은 free
        }
      }
      first = first->edge_next; // 다음이 정점2이기 전까진 옆으로 이동 반복
    }
  }
  // 정점2에서도 연결 끊기 (위와 같은 방식임)
  if (vertex2->edge_cnt == 1) {
    vertex2->edge_next = NULL;
  } else if (vertex2->edge_next->data == vertex1->data) {
    NODE *edge = vertex2->edge_next;
    vertex2->edge_next = edge->edge_next;
    free(edge);
  } else {
    NODE *edge = vertex2->edge_next;
    while (edge != NULL) {
      if (edge->edge_next->data = vertex1->data) { //다음꺼가 해당 vertex면
        if (edge->edge_next == NULL) {            //맨끝
          NODE *edge_next = edge->edge_next;
          free(edge_next);
          edge->edge_next = NULL;
        } else { //맨 끝 아니면
          NODE *edge_next = edge->edge_next;
          edge->edge_next = edge_next->edge_next;
          free(edge_next);
        }
      }
      edge = edge->edge_next;
    }
  }
  vertex1->edge_cnt--;
  vertex2->edge_cnt--;
}



void reset_visited(G *graph) {
  for (int i = 0; i < MAX; i++) { // 정점들끝까지 돌면서
    graph->vertex[i]->visited = 0;
    if (i == graph->vertex_cnt - 1)
      break; // 현재 정점들개수까지 만나면 끝내기
  }
}

NODE* search(G *graph, char DATA) { // 정점찾기 (있으면 노드 반환, 없으면 NULL반환)
  if (graph->vertex_cnt == 0)
    return NULL; // 아직 없음
  for (int i = 0; i < MAX; i++) { // 첫 정점부터 차례로 비교하기
    if (graph->vertex[i]->data == DATA)
      return graph->vertex[i];
    if (i == graph->vertex_cnt - 1)
      break;
  }
  return NULL;
}

void visited(G *graph, NODE *node) {
  if (node->visited == 1) // 방문했음
    return;
  node->visited = 1;            // 방문안되었다면 방문 표시시키기
  NODE *edge = node->edge_next; // 그다음 정점 연결
  while (edge != NULL) {        // 그 뒤 정점들 다 방문
    visited(graph, search(graph, edge->data)); //그다음 노드의 정점 찾아서 방문
    edge = edge->edge_next;
  }
}

void print(G *graph) { // 출력
  int cnt = 0;
  printf("(");
  while (cnt != graph->vertex_cnt) {
    printf("%c", graph->vertex[cnt]->data);
    if (graph->vertex[cnt]->edge_cnt != 0) {
      NODE *edge = graph->vertex[cnt]->edge_next;
      printf("(");
      while (edge != NULL) {
        printf("%c", edge->data);
        if (edge->edge_next != NULL) {
          printf(",");
        }
        edge = edge->edge_next;
      }
      printf(")");
    }
    if (cnt != graph->vertex_cnt - 1) {
      printf(",");
    }
    cnt++;
  }
  printf(")");
}

void num_of_vertex(G *graph) { // 정점 개수들
  printf("\n\n\t정점개수 : %d\n", graph->vertex_cnt);
}

void degree_of_vertex(NODE *vertex) { // 차수
  printf("\n\n\t정점 %c의 차수 : %d\n", vertex->data, vertex->edge_cnt); 
}

void is_empty(G *graph) { // 비어있는지
  if (graph->vertex_cnt == 0)
    printf("\n\n\tThis graph is empty\n");
  else
    printf("\n\n\tThis graph is not empty\n");
}

void adjacent(NODE *vertex) { // 이웃
  if (vertex->edge_cnt == 0)
    printf("\n\n\t{%c} does not have adjacent vertex\n", vertex->data);
  else {
    NODE *edge = vertex->edge_next;
    printf("\n\n\t{%c}'s adjacent vertex : {", vertex->data);
    while (edge != NULL) {
      printf("%c", edge->data);
      if (edge->edge_next != NULL) {
        printf(",");
      }
      edge = edge->edge_next;
    }
    printf("}\n");
  }
}

void path_existed(G *graph, NODE *start, NODE *end) { // 경로가 가능?
  reset_visited(graph);
  visited(graph, start);
  for (int i = 0; i < MAX; i++) {
    if (graph->vertex[i]->data == end->data) {
      if (graph->vertex[i]->visited == 0) {
        printf("\n\n\t{%c} and {%c} is not connected\n", start->data,
               end->data);
        return;
      } else {
        printf("\n\n\t{%c} and {%c} is connected\n", start->data, end->data);
        return;
      }
    }
    if (i == graph->vertex_cnt - 1)
      break;
  }
}

void is_connected(G *graph) { // 연결?
  reset_visited(graph);
  visited(graph, graph->vertex[0]);
  for (int i = 0; i < MAX; i++) {
    if (graph->vertex[i]->visited == 0) {
      printf("\n\n\tThis graph is not connected\n");
      return;
    }
    if (i == graph->vertex_cnt - 1)
      break;
  }
  printf("\n\n\tThis graph is connected\n");
}

void num_of_edge(G *graph) {
  int edge = 0;
  for (int i = 0; i < MAX; i++) {
    edge += graph->vertex[i]->edge_cnt;
    if (i == graph->vertex_cnt - 1)
      break;
  }
  printf("\n\n\tnumber of edge : %d\n", edge / 2);
}

int edge_exist(NODE *vertex, NODE *vertex2) {
  if (vertex->edge_cnt == 0)
    return 0;
  else {
    NODE *edge = vertex->edge_next;
    while (edge != NULL) {
      if (edge->data == vertex2->data)
        return 1;
      edge = edge->edge_next;
    }
  }
  return 0;
}

void addEdge(NODE *vertex1, NODE *vertex2) {
  // 정점1 밑에 추가
  NODE *temp2 = malloc(sizeof(NODE)); 
  temp2->data = vertex2->data; // 정점2 값 저장
  if (vertex1->edge_cnt == 0) { // 정점1 연결에 다른 것이 없다면
    vertex1->edge_next = temp2; // 정점1에 정점2 바로 연결 
  } 
  else { // 정점1에 다른 정점들 연결되어 있다면
    NODE *first1 = vertex1->edge_next; // 정점 연결 시작부터 끝까지 순회한 뒤 마지막에 연결
    while (first1->edge_next != NULL) {
      first1 = first1->edge_next; // 제일 끝 위치 찾기 & 지정
    }
    first1->edge_next = temp2; // 정점2 연결
  }
  // 정점2 밑에 추가
  NODE *temp1 = malloc(sizeof(NODE));
  temp1->data = vertex1->data; // 정점1 값 저장
  if (vertex2->edge_cnt == 0) { // 정점2 밑에 다른 연결 없으면 
    vertex2->edge_next = temp1; // 바로 연결함
  } 
  else { // 다른 연결들 있으면
    NODE *first2 = vertex2->edge_next;
    while (first2->edge_next != NULL) { // 위와 같이 반복함
      first2 = first2->edge_next;
    }
    first2->edge_next = temp1;
  }
  
  temp1->edge_next = NULL; // 끝은 NULL 비우기
  temp2->edge_next = NULL; // 끝은 NULL 비우기
  vertex1->edge_cnt++; // 간선 증가
  vertex2->edge_cnt++; // 간선 증가
}




void rename_vertex(G *graph, NODE *vertex, char DATA) { // 정점 이름을 DATA로 바꾸기
  if (vertex->edge_cnt != 0) { // edge 있으면
    for (int i = 0; i < MAX; i++) {
      NODE *edge = graph->vertex[i]->edge_next;
      while (edge != NULL) {
        if (edge->data == vertex->data) {
          edge->data = DATA;
        }
        edge = edge->edge_next;
      }
      if (i == graph->vertex_cnt - 1)
        break;
    }
  }
  vertex->data = DATA;
}



void clear(G *graph) { // 초기화
  while (graph->vertex_cnt != 0) {
    deleteVertex (graph, graph->vertex[0]);
  }
}

int main() {
  G *graph = malloc(sizeof(G));

  menu();
  int create_int = 0;
  int go = 1;
  while (go) {
    NODE *vertex1 = malloc(sizeof(NODE));
    NODE *vertex2 = malloc(sizeof(NODE));
    printf("\n\t");
    if (create_int == 0)
      printf("아직 그래프가 생성되지 않았습니다. G키로 생성해주세요.\n");
    else
      print(graph);
    char request[30] = {0};
    printf("\n\t>>> ");
    gets(request);
    
    for (int i = 0; i < strlen(request); i++) {
      switch (request[i]) {
      case 'G':
        if (create_int == 0) {
          printf("\t그래프를 생성합니다..\n");
          create(graph);
          create_int = 1;
        } else {
          printf("\n\n\t그래프는 이미 생성되어있습니다.\n");
        }
        break;
        
      case 'L':
        printf("\t그래프를 출력합니다.\n");
        break;
        
      case '+': // 정점 생성
        if (create_int == 0 || request[i + 1] == '\0')
          break;
        vertex1 = search(graph, request[i + 1]);
        if (vertex1 != NULL)
          printf("\n\n\t%c 정점은 이미 존재합니다.\n", request[i + 1]);
        else
          insertVertex(graph, request[i + 1]);
        i += 2;
        break;
        
      case '-': // 정점 삭제
        if (create_int == 0 || request[i + 1] == '\0')
          break;
        else if (graph->vertex_cnt == 0)
          break;
        vertex1 = search(graph, request[i + 1]);
        if (vertex1 == NULL)
          printf("\n\n\t이 정점은 존재하지 않습니다.\n");
        else
          deleteVertex(graph, vertex1);
        i += 2;
        break;
        
      case 'V': // degree
        if (create_int == 0 || request[i + 1] == '\0')
          break;
        else if (graph->vertex_cnt == 0)
          break;
        vertex1 = search(graph, request[i + 1]);
        if (vertex1 == NULL)
          printf("\n\n\t이 정점은 존재하지 않습니다.\n");
        else
          degree_of_vertex(vertex1);
        i += 2;
        break;
        
      case 'A': // adjacent
        if (create_int == 0 || request[i + 1] == '\0')
          break;
        else if (graph->vertex_cnt == 0)
          break;
        vertex1 = search(graph, request[i + 1]);
        if (vertex1 == NULL)
          printf("\n\n\t이 정점은 존재하지 않습니다.\n");
        else
          adjacent(vertex1);
        i += 2;
        break;
        
      case 'R': // rename
        if (create_int == 0 || request[i + 1] == '\0' || request[i + 2] == '\0')
          break;
        else if (graph->vertex_cnt == 0)
          break;
        vertex1 = search(graph, request[i + 1]); // 정점1 찾아서 반환
        vertex2 = search(graph, request[i + 2]); // 정점2가 있다면 찾아서 반환
        if (vertex1 == NULL)
          printf("\n\n\t%c 정점이 그래프에 존재하지 않습니다.\n", request[i + 1]);
        else if (vertex2 != NULL) // 정점 2 반환이 NULL이어야지 바꿀 수 있음
          printf("\n\n\t%c 정점은 이미 존재하므로 이름을 바꿀 수 없습니다.\n", request[i + 2]);
        else // 바꿀 수 있는 상황
          rename_vertex(graph, vertex1, request[i + 2]);
        i += 3;
        break;
        
    
        
      case 'P': // path_exist
        if (create_int == 0 || request[i + 1] == '\0' || request[i + 2] == '\0')
          break;
        else if (graph->vertex_cnt == 0)
          printf("아직 그래프가 생성되지 않았습니다.\n");
          break;
        vertex1 = search(graph, request[i + 1]);
        vertex2 = search(graph, request[i + 2]);
        if (vertex1 == NULL && vertex2 == NULL)
          printf("\n\n\t정점%c 와 정점%c은 모두 그래프에 없습니다.\n", vertex1->data,
                 vertex2->data);
        else if (vertex1 == NULL)
          printf("\n\n\t정점%c은 그래프에 존재하지 않습니다.\n", request[i + 1]);
        else if (vertex2 == NULL)
          printf("\n\n\t정점%c은 그래프에 존재하지 않습니다.\n", request[i + 2]);
        else
          path_existed(graph, vertex1, vertex2);
        i += 3;
        break;

        
      case 'E':
        if (create_int == 0 || request[i + 1] == '\0' || request[i + 2] == '\0')
          break;
        else if (graph->vertex_cnt == 0)
          break;
        vertex1 = search(graph, request[i + 1]);
        vertex2 = search(graph, request[i + 2]);
        if (vertex1 == NULL && vertex2 == NULL)
          printf("\n\n\t정점%c and 정점%c는 모두 그래프에 존재하지 않습니다.\n", vertex1->data,
                 vertex2->data);
        else if (vertex1 == NULL)
          printf("\n\n\t정점%c은 그래프에 존재하지 않습니다.\n", request[i + 1]);
        else if (vertex2 == NULL)
          printf("\n\n\t정점%c은 그래프에 존재하지 않습니다.\n", request[i + 2]);
        else {
          if (edge_exist(vertex1, vertex2) == 1)
            printf("\n\n\t정점%c와 정점%c은 이미 연결되어 있습니다.\n", vertex1->data,
                   vertex2->data);
          else
            addEdge(vertex1, vertex2);
        }
        i += 3;
        break;
        
      case 'D':
        if (create_int == 0 || request[i + 1] == '\0' || request[i + 2] == '\0')
          break;
        else if (graph->vertex_cnt == 0)
          break;
        vertex1 = search(graph, request[i + 1]);
        vertex2 = search(graph, request[i + 2]);
        if (vertex1 == NULL && vertex2 == NULL)
          printf("\n\n\t정점%c은 정점%c 모두 그래프에 존재하지 않습니다.\n", vertex1->data,
                 vertex2->data);
        else if (vertex1 == NULL)
          printf("\n\n\t정점%c은 그래프에 존재하지 않습니다.\n", request[i + 1]);
        else if (vertex2 == NULL)
          printf("\n\n\t정점%c은 그래프에 존재하지 않습니다.\n", request[i + 2]);
        else {
          if (edge_exist(vertex1, vertex2) == 0)
            printf("\n\n\t정점%c와 정점%c은 이미 연결되어 있습니다.\n",
                   vertex1->data, vertex2->data);
          else
            delete_edge(vertex1, vertex2);
        }
        i += 3;
        break;
        

      case 'X':
        if (create_int == 0)
          break;
        else if (graph->vertex_cnt == 0)
          break;
        if (request[i + 1] == '\0')
          num_of_vertex(graph);
        i++;
        break;
        
      case 'N':
        if (create_int == 0)
          break;
        else if (graph->vertex_cnt == 0)
          break;
        if (request[i + 1] == '\0')
          is_empty(graph);
        i++;
        break;
        
      case 'C':
        if (create_int == 0)
          break;
        else if (graph->vertex_cnt == 0)
          break;
        if (request[i + 1] == '\0')
          is_connected(graph);
        i++;
        break;
      case 'H':
        if (create_int == 0)
          break;
        else if (graph->vertex_cnt == 0)
          break;
        if (request[i + 1] == '\0')
          num_of_edge(graph);
        break;
      case 'K':
        if (create_int == 0)
          break;
        else if (graph->vertex_cnt == 0)
          break;
        if (request[i + 1] == '\0')
          clear(graph);
        i++;
        break;
      case 'Q':
        printf("\n\n\t프로그램을 종료합니다.\n");
        go = 0;
        break;
      default:
        break;
      } 
    }  

  }
  return 0;
}