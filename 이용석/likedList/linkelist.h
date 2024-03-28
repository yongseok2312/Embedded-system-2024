
#ifndef linkelist.h
#define linkelist.h


typedef struct BOOK {
    char name[100]; // 책 제목
    int price;       // 책 가격
    struct BOOK* link;
    int num;         // 책 수량
    char author[100]; // 책 저자
    int ISBN;         // 책 번호
    char publisher[100]; // 출판사
} book;

// 책 노드 생성
book* createnode(int ISBN, char name[], char author[], char publisher[], int price, int num) {
    book* newnode = (book*)malloc(sizeof(book));
    if (newnode == NULL) {
        printf("메모리 할당 실패\n");
        exit(1);
    }
    strcpy(newnode->name, name);
    strcpy(newnode->author, author);
    strcpy(newnode->publisher, publisher);
    newnode->ISBN = ISBN;
    newnode->price = price;
    newnode->num = num;
    newnode->link = NULL;
    return newnode;
}

void menu();  // 메뉴
void add(book** head, int ISBN, char name[], char author[], char publisher[], int price, int num);
void data(book** head); // 모든 데이터 출력
void printdata(book** head);  // 원하는 데이터 출력
void search(book** head); // 검색
void deletebook(book** head); // 삭제
void returnbook(book** head);
void freebook(book** head); // 메모리 해제
void array(book** head);