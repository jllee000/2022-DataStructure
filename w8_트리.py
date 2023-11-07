#트리
#2021313628 이재림 

class Node:
    def __init__(self, data):
        self.data = data
        self.left = None  # 자손 연결
        self.right = None  # 형제 연결


class Tree:
    def __init__(self):
        self.root = None
        self.count = 0
        self.level = 0
        self.degree = 0

    def insert_child(self, parent, item):
        node = Node(item) # 추가할 노드 생성

        if parent.left is None: # 자손노드가 없다면
            parent.left = node # 그 왼쪽부터 바로 추가

        else:
            cur = parent.left # 왼쪽에 자손노드가 이미 있다면
            while cur.right is not None: # 자리가 비어있는 곳까지 형제 탐색
                cur = cur.right # 계속 비어있는 곳까지 업데이트
            cur.right = node # 비어있는 노드에 추가

        self.count += 1 # 개수 증가

    def insert_sibling(self, sib, item):
        node = Node(item) # 추가할 노드 생성
        cur = sib # 해당 노드 먼저 cur로 지정
        while cur.right is not None: # cur 중심으로 형제들 자리중 빈 곳 찾기
            cur = cur.right # 계속 업데이트
        cur.right = node

        self.count += 1 # 개수 증가

    def print_tree(self, node1, node2):
        cur = node2.left 
        if node1 is node2: # 트리의 첫 루트일 때
            print(node1.data, end='')

        if node1.left is None: # 트리가 비어있음
            print()
            return
        print("(", end='')

        while cur is not None: # 자손노드가 있을 때
            print(cur.data, end='')
            if cur.left is not None: # 밑에 또 자손이 있을 때 안에 괄호로 묶어서 출력
                self.print_tree(node1, cur) # 다시 반복호출
            if cur.right is not None: # 형제노드가 있을 때 옆에 또 출력
                print(",", end='')
            cur = cur.right

        print(")", end='')
        if node1 is node2: 
            print()

    def search_node(self, node, item): # 해당데이터를 가진 노드 검색
        if node is None: 
            return
        if node.data == item:
            return node

        cur = self.search_node(node.left, item)
        if cur is not None:
            return cur
        cur = self.search_node(node.right, item)
        if cur is not None:
            return cur

        return None

    def get_parent_bt(self, root, node):
        if root is None: # 루트x, 트리자체가 정의되지않음
            return None
        if root.left == node or root.right == node: # 해당 노드가 루트의 자손
            return root
        cur = self.get_parent_bt(root.left, node) # 
        if cur is not None:
            return cur
        cur = self.get_parent_bt(root.right, node)
        if cur is not None:
            return cur
        return None



    def is_leftchild(self, parent, node):
        if parent.left is node:
            return True
        else:
            return False

    def is_rightchild(self, parent, node):
        if parent.right is node:
            return True
        else:
            return False

    def get_parent(self, root, node): # 부모노드 출력
        if self.get_parent_bt(root, node) is None:
            return None

        cur = node
        while not self.is_leftchild(self.get_parent_bt(root, cur), cur):
            cur = self.get_parent_bt(root, cur)
        return self.get_parent_bt(root, cur)

    def get_child(self, parent): # 자식노드들 출력
        if parent.left is None:
            print("자식노드가 존재하지 않습니다.")
            return

        cur = parent.left # 부모노드의 젤 왼쪽 자손을 cur로 지정 
        while cur is not None: 
            print(cur.data, end='') # 끝날때까지 출력
            cur = cur.right # 부모노드들의 다른 자식들 탐색 & 업데이트
        print()

    def get_sibling(self, root, node): # 형제노드들 출력
        cur = self.get_parent(root, node) # 해당 노드의 부모노드 먼저 지정
        if cur is None: # 부모노드가 없다면, 해당 노드 자체가 루트임
            print("{} 는 루트 노드입니다.".format(node.data))
            return
        cur = cur.left # 부모노드의 자손들을 탐색
        while cur is not None: # 끝날때까지 반복
            if cur.data != node.data:
                print(cur.data, end='')
            cur = cur.right
        print()

    def level_of_node(self, root, node): # 해당 노드의 레벨
        level = 0
        cur = node
        while cur is not root:
            cur = self.get_parent(root, cur)
            level += 1
        return level

    def level_of_tree(self, root, node): # 트리 자체의 레벨
        if node is not None:
            self.level_of_tree(root, node.left)
            self.level_of_tree(root, node.right)
            if self.level_of_node(root, node) > self.level:
                self.level = self.level_of_node(root, node)
        return

    def delete_node(self, root, node): 
        if node.left is not None:
            print("이 노드는 부모노드로 삭제할 수 없습니다.")
            return

        parent = self.get_parent_bt(root, node)

        if node.right is None:
            if self.is_leftchild(parent, node):
                parent.left = None
            else:
                parent.right = None

        else:
            child = node.right
            if self.is_leftchild(parent, node):
                parent.left = child
            else:
                parent.right = child

    def get_ancestors(self, node): # 조상 노드들 출력
        if self.root is node:
            print("NO ANCESTORS")
            return
        cur = node
        while cur is not self.root:
            cur = self.get_parent(self.root, cur)
            print(cur.data, end='')
        print()

    def get_descendants(self, node): # 자손 노드들 출력
        temp = node.data
        node.data = ''
        self.print_tree(node, node)
        node.data = temp

    def degree_of_node(self, node):
        degree = 0
        cur = node.left
        while cur is not None:
            degree += 1
            cur = cur.right
        return degree

    def degree_of_tree(self, root):
        if root is not None:
            self.degree_of_tree(root.left)
            self.degree_of_tree(root.right)
            if self.degree_of_node(root) > self.degree:
                self.degree = self.degree_of_node(root)
        return

    def count_child(self, node): # 자손 노드들 개수
        if node is None:
            return -1
        elif node.left == 0:
            return 0
        else:
            num = 0
            cur = node.left
            while cur is not None:
                cur = cur.right
                num += 1
            return num



def joinPrepare_tree(root):
    if root is not None:
        newnode = Node(root.data)
        newnode.left = joinPrepare_tree(root.left)
        newnode.right = joinPrepare_tree(root.right)
        return newnode
    return None


def join_trees(newroot, root1, root2):
    node1 = joinPrepare_tree(root1)
    node2 = joinPrepare_tree(root2)
    newroot.left = node1
    node1.right = node2
    return newroot


trees = []
idx = -1
print("2021313628 이재림_Tree")
print("=============menu==============")
print("+^루트데이터           create Tree")
print("+부모데이터(추가데이터)  insert")
print("=형제데이터(추가데이터) insert_sibling")
print("S(형제데이터)          get_sibling")
print("P(자식데이터)          get_parent")
print("C(부모데이터)          get_child")
print("A(자손데이터)          get_ancestors")
print("D(조상데이터)          get_desvendants")
print("L(데이터)             level_of_Node")
print("L                    level_of_Tree")
print("G(데이터)             degree_of_Node")
print("G                    degree_of_Tree")
print("T                    print_Tree")
print("#                    count_Node")
print("J                    join_Trees")
print("K                    clear_Tree")
print("Q                    Quit")
print("===================================\n")

is_binary = int(input("일반트리(0), 이진트리(1) >>"))

while True:
    request = input(">>>: ")
    request += ' '
    if request[0] == 'Q':
        break
    i = 0
    while i < len(request):
        #추가
        if request[i] == '+':
            if request[i + 1] == '^': # 첫 트리(루트) 생성
                root = Node(request[i + 2])
                tree = Tree() # 함수 사용 가능
                tree.root = root
                trees.append(tree)
                idx = len(trees) - 1
                i += 2
            elif request[i + 2] == '(': # 기존 트리에 자식으로 추가
                node = trees[idx].search_node(trees[idx].root, request[i + 1])
                if node is None:
                    print("%c 는 트리에 존재하지 않다." %(request[i + 1]))
                else:
                    i += 3
                    while request[i] != ')':
                        if is_binary == 1 and trees[idx].count_child(node) == 2:
                            print("이진트리이므로, 더이상 들어갈 수 없습니다.(2/2)")
                            break
                        trees[idx].insert_child(node, request[i])
                        i += 1
                while request[i] != ')':
                    i += 1
        # 출력        
        elif request[i] == 'T':
            if idx == -1:
                print("아직 트리가 존재하지 않습니다.")
            else:
                trees[idx].print_tree(trees[idx].root, trees[idx].root)
        # 삭제
        elif request[i] == '-':
            node = trees[idx].search_node(trees[idx].root, request[i + 1])
            if node is None:
                print("%c 는 트리%d에 존재하지 않습니다." %(request[i + 1], idx))
            else:
                trees[idx].delete_node(trees[idx].root, node)
            i += 1
        # 형제노드로 추가
        elif request[i] == '=':
            node = trees[idx].search_node(trees[idx].root, request[i + 1])
            if node is None:
                print("%c 는 트리%d에 존재하지 않습니다." %(request[i + 1], idx))
            else:
                i += 3
                while request[i] != ')':
                    if is_binary == 1 and trees[idx].count_child(trees[idx].get_parent(trees[idx].root,node)) == 2:
                        print("이진트리이므로, 더이상 들어갈 수 없습니다.(2/2)")
                        break
                    trees[idx].insert_sibling(node, request[i])
                    i += 1
            while request[i] != ')':
                i += 1
        # 부모노드 출력
        elif request[i] == 'P':
            # P괄호 다음에 들어있는 데이터를 가진 노드를 먼저 찾기
            
            # 찾은 해당 노드의 부모 노드 찾기
            parent = trees[idx].get_parent(trees[idx].root, trees[idx].search_node(trees[idx].root, request[i+2]))
            if parent is None:
                print("ERROR")
            else:
                print(parent.data)
            i += 3
        # 자식노드 출력
        elif request[i] == 'C':
            if trees[idx].search_node(trees[idx].root, request[i + 2]) is None:
                print("%c 는 트리%d에 존재하지 않습니다." %(request[i + 2], idx))
            else:
                trees[idx].get_child(trees[idx].search_node(trees[idx].root, request[i + 2]))
            i += 3
        # 형제노드 출력
        elif request[i] == 'S':
            node = trees[idx].search_node(trees[idx].root, request[i+2])
            if node is None:
                print("%c 는 트리%d에 존재하지 않습니다." %(request[i+2], idx))
            else:
                trees[idx].get_sibling(trees[idx].root, node)
            i += 3
        # 조상노드 출력
        elif request[i] == 'A':
            node = trees[idx].search_node(trees[idx].root, request[i+2])
            if node is None:
                print("%c 는 트리%d에 존재하지 않습니다." %(request[i+2], idx))
            else:
                trees[idx].get_ancestors(node)
            i += 3
        # 자손노드 출력
        elif request[i] == 'D':
            node = trees[idx].search_node(trees[idx].root, request[i+2])
            if node is None:
                print("%c 는 트리%d에 존재하지 않습니다." %(request[i+2], idx))
            else:
                trees[idx].get_descendants(node)
            i += 3
        # 레벨 출력
        elif request[i] == 'L':
            if request[i+1] == '(':
                node = trees[idx].search_node(trees[idx].root, request[i+2])
                if node is None:
                    print("%c 는 트리%d에 존재하지 않습니다." %(request[i+2], idx))
                else:
                    print("LEVEL OF NODE {} IS {}".format(request[i+2], trees[idx].level_of_node(trees[idx].root, node)))
                i += 3
            else:
                trees[idx].level_of_tree(trees[idx].root, trees[idx].root)
                print("LEVEL OF TREE {} IS {}".format(idx, trees[idx].level))
        # degree 출력
        elif request[i] == 'G':
            if request[i+1] == '(':
                node = trees[idx].search_node(trees[idx].root, request[i+2])
                if node is None:
                    print("%c 는 트리%d에 존재하지 않습니다." %(request[i+2], idx))
                else:
                    print("DEGREE OF NODE {} IS {}".format(request[i+2], trees[idx].degree_of_node(node)))
                i += 3
            else:
                trees[idx].degree_of_tree(trees[idx].root)
                print("DEGREE OF TREE {} IS {}".format(idx, trees[idx].degree))
        # 노드 개수 출력
        elif request[i] == '#':
            if request[i+1] == '(':
                node = trees[idx].search_node(trees[idx].root, request[i+2])
                if node is None:
                    print("%c 는 트리%d에 존재하지 않습니다." %(request[i+2], idx))
                else:
                    print("NODE {} HAS {} CHILD NODE".format(idx, trees[idx].count_child(node)))
                i += 3
            else:
                print("TREE {} HAS {} NODE".format(idx, trees[idx].count))
        # 트리들 합함
        elif request[i] == 'J':
            idx1 = -1 # 일단 생성
            idx2 = -1 # 일단 생성
            cnt1 = 0
            cnt2 = 0
            for j in range(len(trees)): # 트리들 개수
                if trees[j].root.data == request[i+3]:
                    idx1 = j
                    cnt1 = trees[j].count
                elif trees[j].root.data == request[i+4]:
                    idx2 = j
                    cnt2 = trees[j].count
            if idx1 == -1 or idx2 == -1:
                print("ERROR")
            else:
                newtree = Tree()
                newroot = Node(request[i+2])
                newtree.root = newroot
                join_trees(newroot, trees[idx1].root, trees[idx2].root)
                newtree.count = cnt1 + cnt2 + 1
                trees.append(newtree)
                idx = len(trees) - 1
            i += 5
        # 트리 초기화
        elif request[i] == 'K':
            if idx == -1:
                print("트리가 애초에 존재하지 않습니다.")
            else:
                print("트리를 초기화합니다.")
                trees.pop(idx)
                idx -= 1
        i += 1
