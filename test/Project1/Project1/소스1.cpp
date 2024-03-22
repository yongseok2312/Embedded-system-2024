#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BOOK {
    char name[100]; // 책 제목
    int price;  // 책 가격
    struct BOOK* link;
    int num;    // 책 수량
    char author[100]; // 책 저자
    int ISBN; // 책 번호
} book;

//책 노드 생성
book* createnode(int ISBN, char name[], char author[], int price, int num) {
    book* newnode = (book*)malloc(sizeof(book));
    if (newnode == NULL) {
        printf("메모리 할당 실패\n");
        exit(1);
    }
    strcpy(newnode->name, name);
    strcpy(newnode->author, author);
    newnode->ISBN = ISBN;
    newnode->price = price;
    newnode->num = num;
    newnode->link = NULL;
    return newnode;
}

void menu();  //메뉴
void add(book** head, int ISBN, char name[], char author[], int price, int num);
//void search(book** head);

int main() {
    book* head = NULL;
    char name[100];
    int price, num, ISBN;
    int a;
    char input[100];  //받는숫자
    char author[100];

    while (1) {
        menu();
        int inputStatus = 0; // 숫자인지 문자인지판별
        while (inputStatus == 0) {
            printf("메뉴를 선택하세요: ");
            scanf("%s", input);

            if (sscanf(input, "%d", &a) == 1) {  //문자열을 [>
                inputStatus = 1;
            }
            else {
                printf("잘못된 입력입니다. 숫자를 입력하세요.\n");
            }
        }

        if (a == 1) {
            printf("책 번호 입력\n");
            scanf("%d", &ISBN);
            printf("책 이름을 입력\n");
            scanf("%s", name);
            printf("책 저자  입력\n");
            scanf("%s", author);
            printf("책 가격  입력\n");
            scanf("%d", &price);
            printf("책 수량을 입력\n");
            scanf("%d", &num);

            add(&head, ISBN, name, author, price, num);

        }
        else if (a == 2) {
            //search(&head);

        }
        else if (a == 3) {

        }
        else if (a == 4) {

        }
        else if (a == 0) {
            return 0;
        }
        else {
            printf("잘못된 입력입니다\n");
        }
    }
    free(head); // 메모리 해제
    return 0;
}

void menu() {
    printf("**** 메뉴 ****\n");
    printf("1. 도서구입(등록)\n");
    printf("2. 도서검색\n");
    printf("3. 도서삭제\n");
    printf("4. 도서출력\n");
    printf("0. 종료\n");
}
void add(book** head, int ISBN, char name[], char author[], int price, int num) {
    book* current = *head;
    // 책이 같은 경우 수량 증가
    while (current != NULL) {
        if (strcmp(current->name, name) == 0 && current->ISBN == ISBN) {
            current->num += num;
            printf("수량이 증가하였습니다.\n");
            printf("%s의 수량은 %d입니다.\n", name, current->num);
            return;
        }
        current = current->link;
    }

    //new book 노드 생성
    book* new_book = createnode(ISBN, name, author, price, num);

    if (*head == NULL) {
        *head = new_book;
    }
    else {
        book* temp = *head;
        while (temp->link != NULL) {
            temp = temp->link;
        }
        temp->link = new_book;
    }
    printf("책이 추가 되었습니다\n");
}

/*void search(book** head)
{
    book* current = *head;
    if (*head == NULL)
    {
        printf("등록된 책이 없습니다.");
        return;
    }
    else {
        //book* temp = *head;
        printf("***** list *****\n");
        while (current != NULL) {
            printf("%d %s %s %d %d\n", current->ISBN, current->name, current->author, current->price, current->num);
            current = current->link;

        }
        return;
    }
}*/

void search(book** head) {
    book* current = *head;
    if (*head == NULL) {
        printf("등록된 책이 없습니다.\n");
        return;
    }
    else {
        printf("찾고자하는 책의 제목을 입력하세요: ");
        char search_name[100];
        scanf("%s", search_name);

        while (current != NULL) {
            if (strcmp(current->name, search_name) == 0) {
                printf("찾으시는 책의 정보:\n");
                printf("ISBN: %d\n", current->ISBN);
                printf("제목: %s\n", current->name);
                printf("저자: %s\n", current->author);
                printf("가격: %d\n", current->price);
                printf("수량: %d\n", current->num);
                return;
            }
            current = current->link;
        }

        printf("찾으시는 책이 없습니다.\n");
        return;
    }
}