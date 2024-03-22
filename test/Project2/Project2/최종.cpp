#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
void add(book** head, int ISBN, char name[], char author[], int price, int num);//추가
void data(book** head); // 데이터 전체 보기
void printdata(book** head);    // 데이터 출력
void deletebook(book** head); // 데이터 삭제
void borrow(book** head); // 대여
void returnbook(book** head); //반납
void freebook(book** head); // 메모리 해제

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
            data(&head);
            search(&head);
            borrow(&head);

        }
        else if (a == 3) {
            deletebook(&head);
        }
        else if (a == 4) {
            printdata(&head);
        }
        else if (a == 0) {
            return 0;
        }
        else if (a == 5) {
            returnbook(&head);
        }
        else {
            printf("잘못된 입력입니다\n");
        }
    }
    //free(head); // 메모리 해제
    freebook(&head);
    return 0;
}

void menu() {
    printf("**** 메뉴 ****\n");
    printf("1. 도서구입(등록)\n");
    printf("2. 도서검색\n");
    printf("3. 도서삭제\n");
    printf("4. 도서출력\n");
    printf("5. 도서반납\n");
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

void data(book** head)
{
    book* current = *head;
    if (*head == NULL)
    {
        printf("등록된 책이 없습니다.\n");
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
}

void search(book** head)
{
    book* current = *head;
    if (*head == NULL) {
       // printf("등록된 책이 없습니다.\n");
        return;
    }
    else
    {   
        char _data[100];
        printf("책의 정보를 입력하세요\n");
        scanf("%s",_data);
        while (current != NULL)
        {
            if (current->ISBN == atoi(_data) || current->name == _data)
            {
                printf("찾으시는 책이 있습니다!!\n");
                return;
            }
            current = current->link;
        }
    }
    printf("찾으시는 책이 없습니다.\n");
    return;
}

void printdata(book** head) {
    book* current = *head;
    printf("찾고자하는 책의 제목 또는 ISBN을 입력하세요: \n");
    char data[100];
    scanf("%s", data);
    int search_number = atoi(data); // atoi 정수로 변환

    while (current != NULL) {
        if (strcmp(current->name, data) == 0 || current->ISBN == search_number)
        {
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

void deletebook(book** head) {
    book* current = *head;
    char data1[100];
    int num2;
    printf("삭제하실 책의 제목 또는 ISBN을 적으세요!\n");
    scanf("%s", data1);
    int num1 = atoi(data1);
    printf("책의 수량을 적으세요\n");
    scanf("%d", &num2);
    
    while (current != NULL) 
    {
        if (strcmp(current->name, data1)==0 || current->ISBN == num1)
        {
            if (current->num <= num2)
            {
                book* temp = current;
                *head = current->link;
                free(temp);
                printf("책이 삭제되었습니다.\n");
                return;
            }
            else
            {
                current->num -= num2;
                printf("책의 수량이 감소하였습니다.\n");
                return;
            }
        }
        current = current->link;
    }
    printf("해당하는 책이 없습니다!\n");
}

void borrow(book** head)
{
    char ans[10];
    book* current = *head;
    printf("책을 대여하시겠습니까?(ture or false)\n");
    scanf("%s", ans);
    if (strcmp(ans,"true") == 0)
    {
        char data[100];
        printf("대여할 책의 제목 및 ISBN을 쓰세요!\n");
        scanf("%s", data);
        int data2 = atoi(data);
        while (current != NULL)
        {
            if (strcmp(current->name, data) == 0 || current->ISBN == data2)
            {
                printf("%d %s 의 남아 있는 책의 수는 %d입니다.\n", current->ISBN, current->name, current->num);
                if (current->num <= 0)
                {
                    printf("현재 책이 없어 빌릴수 없습니다!\n");
                    return;
                }
                else
                {
                    current->num -= 1;
                    return;
                }
            }
            current = current->link;
        }
        printf("찾으시는 책이 없습니다!\n");
    }
    else {
            return;
    }
}

void returnbook(book** head)
{
    book* current = *head;
    char plus[100];
     printf("반납하실 책의 제목이나 ISBN을 작성하시오\n");
        scanf("%s", plus);
        int plus2 = atoi(plus);
        while (current != NULL)
        {
            if (strcmp(current->name, plus) == 0 || current->ISBN == plus2)
            {
                current->num += 1;
                return;
            }
            current = current->link;
        }
        printf("우리 책이 아닙니다!\n");
 }

void freebook(book** head)
{
    book* current = *head;
    while (current != NULL)
    {
        book* temp = current;
        current = current->link;
        free(temp);
    }
    *head = NULL;
}