#자료구조 5주차 과제

def menu() :
    print("자료구조 5주차_이재림(9조)_2021313628")
    print("\n\t");
    print("====================================================")
    print("\n	    	    FUNCTION")
    print("\n ****CAPITALIZE all the COMMANDSs")
    print(" ****Do not use space bar")
    print("----------------------------------------------------")
    print(" + (data)		addBefore\t")
    print(" T+ (data)	addTail\t")
    print(" N+ (data)	addNext\t")
    print(" =  (data)	replace data\t")
    print(" -  (data)	delete\t")
    print(" G		get present data\t")
    print(" L		print all data\t")
    print(" E		is empty\t")
    print(" C		be empty\t")
    print(" #		all data count\t")
    print(" ? (data)		this data is member\t")
    print(" <		traverse_front\t")
    print(" >		traverse_rear\t")
    print(" N		go to next index\t")
    print(" P		go to previous index\t")
    print(" U		UpperCase\t")
    print(" D		LowerCase\t")
    print(" V		viewMenu\t")
    print(" (index)		go to (numberth) index\t")
    print("----------------------------------------------------\t")
    print(" Q			quit\t")
    print("====================================================")

class Node:
    def __init__(self,data):
        self.data=data
        self.next =None

class LinkedList:
    def __init__(self):
        new = Node(None)
        self.head=new # 헤드는 곧 new 노드로 지정
        self.len=0
        self.pos=self.head # 아직은 헤드 가리킴
#-----------------------------------------------------------------------

def addTail(self,DATA):
    new=Node(DATA)
    if self.pos==self.head or self.pos.next==None: # 지금 커서가 비어있거나, 지금 커서가 마지막노드
        new.next=None # 새 노드를 마지막 끝에 연결
        self.pos.next=new # 리스트의 커서가 가리키는 노드에 새 노드 연결
        self.pos=new # 지금 새 노드에 커서 가리킴
        self.len+=1 # 리스트 개수 증가
    elif(self.pos.next!=None): # 지금 커서위치가 앞뒤로 노드들 사이에 끼어있다면
        last=list.head 
        while last.next != None: # 마지막 노드 찾기
            last=last.next
        self.pos=last # 지금 커서를 마지막 노드로 지정
        
        new.next=None # 마찬가지로 새 노드를 마지막에 연결
        self.pos.next=new # 원래 마지막 노드에 새 노드 연결
        self.pos=new
        self.len+=1

def addNext(self,DATA): # 지금 커서의 뒤로 추가
    new=Node(DATA)
    if self.pos==self.head or self.pos.next==None: # 지금 커서가 비어있거나, 지금 커서가 마지막노드
        addTail(self, DATA)
    else: # 지금 커서 위치 뒤로 끼어들어갈 때
        new.next=self.pos.next 
        self.pos.next=new
        self.pos=new # 커서 위치
        self.len+=1 # 리스트 개수 증
        
    

def addBefore(self,DATA): # 지금 커서의 앞으로 추가
    new=Node(DATA)
    before=self.head
    while before.next != self.pos: # 지금 커서의 노드를 만나기 전까지
        before=before.next
    new.next=self.pos # 지금 커서의 노드를 새노드 뒤에 연결
    before.next=new # 지금 커서 앞의 노드 뒤로 새 노드가 추가
    self.pos=new
    self.len+=1 

def is_empty(self):
    if self.len==0:
        return True
    else :return False

def reverse(self):
    if is_empty(self)==True:return
    first=self.head.next
    last=self.pos
    while last.next !=None:
        last=last.next
    for i in range(int(self.len/2)):
        first.data,last.data=last.data,first.data
        first=first.next
        before=self.head
        while before.next!=last:
            before=before.next
        last=before
    while self.pos.next !=None:
        self.pos=self.pos.next
        
def delete(self):
    if is_empty(self)==True:
        return
    before=self.head 
    while before.next!=self.pos: # 현재 커서 앞의 노드까지
        before=before.next
    if self.pos.next==None:#마지막
        before.next=None
        if self.len==1:
            self.pos=self.head
            self.pos.next=None
        else:
            self.pos=self.head.next
    else:
        delete=self.pos
        before.next=self.pos.next
        self.pos=self.pos.next
        delete=None
    self.len-=1

def empty(self):
    while self.len!=0:
        delete(self)

def datacount(self):
    print("data 개수 : ",self.len)



def is_member(self,DATA):
    if is_empty(self)==True:
        print("Not Found")
        return
    crnt =self.head.next
    i=1
    k=0
    while crnt!=None:
        if crnt.data==DATA :
            print("이 데이터는 존재합니다.")
            print(DATA,"위치 : ",i)
            self.pos=crnt
            k=1
        i+=1
        crnt=crnt.next
    if k==0 :
        print("Not Found")
        return
    

def getdata(self):
    if is_empty(self)==True:return
    print("current data : ",self.pos.data)

def gonext(self):
    if is_empty(self)==True or self.pos.next==None :return
    self.pos=self.pos.next

def goback(self):
    if is_empty(self)==True or self.head.next==self.pos :return
    before=self.head
    while before.next!=self.pos:
        before=before.next
    before.next=self.pos
    self.pos=before


def traverse_front(self):
    if is_empty(self)==True:return
    else :self.pos=self.head.next
    
def traverse_rear(self):
    if is_empty(self)==True:return
    else:
        crnt=self.head.next
        while crnt.next != None:
            crnt=crnt.next
        crnt.next=None
        self.pos=crnt
    
def goindex(self,index):
    if is_empty(self)==True: #리스트가 비어있다면
        return
    else :
        move=self.head
        for i in range(index):
            move=move.next
        self.pos=move

def replace(self,DATA):
    if is_empty(self)==True: #리스트가 비어있다면
        return
    self.pos.data=DATA

def printf(self):
    if is_empty(self)==True:
        print("This list is empty")
        return
    pnt=self.head.next
    while pnt != None:
        if pnt==self.pos:print('(',pnt.data,')',end=' ')
        else : print(pnt.data,end=' ')
        pnt=pnt.next
    print()

def printL(self):
    if is_empty(self)==True:
        print("This list is empty")
        return
    pnt=self.head.next
    while pnt != None:
        print(pnt.data,end=' ')
        pnt=pnt.next
    print()

def uppercase(self):
    num = ord(self.pos.data)
    num -= 32
    self.pos.data = chr(num)
    
def lowercase(self):
    num = ord(self.pos.data)
    num += 32
    self.pos.data = chr(num)    

#main
list=LinkedList() # 연결리스트 정의
menu()

while True:
    printf(list)
    order=input("\n>>> ")
    if order[0]=='Q':
        print("프로그램을 종료합니다.\n")
        break
    num=0
    size = len(order)
    i=0
    while i<size: 
        if '0' <= order[i] <= '9': # 숫자 입력일때
            index= int(order[i])
            goindex(list,index)
        elif order[i]=='<':
            traverse_front(list)
        elif order[i]=='>':
            traverse_rear(list)
        elif order[i]=='N':
            gonext(list)
        elif order[i]=='P':
            goback(list)
        elif order[i]=='+': 
            if list.len == 0: # 일단 첫 생성 리스트라면 데이터 끝에 삽입
                addTail(list, order[i+1])
            else : # 이미 리스트에 요소가 있다면, 현재 커서 앞에 삽입
                addBefore(list,order[i+1])
            i+=1
        elif order[i]=='T' and order[i+1]=='+' : #T+입력했다면, 전체 리스트 뒤에 삽입
            addTail(list, order[i+2])
            i+=2
        elif order[i]=='N' and order[i+1]=='+' :
            addNext(list, order[i+2])
            i+=2
        elif order[i]=='-':
            delete(list)
        elif order[i]=='G':
            getdata(list)
        elif order[i]=='=':
            replace(list,order[i+1])
            i+=1
        elif order[i]=='L':
            printL(list)
        elif order[i]=='#':
            datacount(list)
        elif order[i]=='C':
            empty(list)
        elif order[i]=='E':
            print(is_empty(list))
        elif order[i]=='?':
            is_member(list,order[i+1])
            i+=1
        elif order[i]=='U':
            uppercase(list)
        elif order[i]=='D':
            lowercase(list)
        elif order[i]=='V':
            print("메뉴를 출력합니다.\n")
            menu()
        i+=1
