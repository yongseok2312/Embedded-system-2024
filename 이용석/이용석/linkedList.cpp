/*
	File: linkedList.c

	Created: 24-03-27
	Author: 이용석
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

int main() {
    book* head = NULL;
    char name[100];
    int price, num, ISBN;
    char input[100];  // 받는 문자열
    char author[100];
    char publisher[100];

    while (1) {
        printf("\n");
        menu();
        int inputStatus = 0; // 숫자인지 문자인지 판별
        while (inputStatus == 0) {
            printf("메뉴를 선택하세요: ");
            scanf("%s", input);
            printf("\n");

            if (sscanf(input, "%s", input) == 1) {  // 문자열을 문자로 변환
                inputStatus = 1;
            }
            else {
                printf("잘못된 입력입니다. 문자를 입력하세요.\n");
            }
        }
        if (strcmp(input, "add") == 0) {
            printf("책 번호 입력하세요.\n");
            scanf("%d", &ISBN);
            printf("책 이름을 입력하세요.\n");
            scanf("%s", name);
            printf("책 저자  입력하세요.\n");
            scanf("%s", author);
            printf("책 출판사 입력하세요.\n");
            scanf("%s", publisher);
            printf("책 가격  입력하세요.\n");
            scanf("%d", &price);
            printf("책 수량을 입력하세요.\n");
            scanf("%d", &num);
            add(&head, ISBN, name, author, publisher, price, num);
        }
        else if (strcmp(input, "search") == 0) {
            array(&head);
            data(&head);
            search(&head);
        }
        else if (strcmp(input, "delete") == 0) {
            array(&head);
            data(&head);
            deletebook(&head);
        }
        else if (strcmp(input, "print") == 0) {
            printdata(&head);
        }
        else if (strcmp(input, "return") == 0) {
            returnbook(&head);
        }
        else if (strcmp(input, "exit") == 0) {
            return 0;
        }
        else {
            printf("잘못된 입력입니다\n");
        }
    }
    freebook(&head);
    return 0;
}

void menu() {
    printf("**** 메뉴 ****\n");
    printf("add - 도서구입(등록)\n");
    printf("search - 도서검색\n");
    printf("delete - 도서삭제\n");
    printf("print - 도서출력\n");
    printf("return - 도서반납\n");
    printf("exit - 종료\n");
}

void add(book** head, int ISBN, char name[], char author[], char publisher[], int price, int num) {
    book* current = *head;

    // 책이 같은 경우 수량 증가
    while (current != NULL) {
        if (strcmp(current->name, name) == 0 && current->ISBN == ISBN) {
            current->num += num;
            printf("수량이 증가하였습니다.\n");
            printf("%s의 수량은 %d입니다.\n", name, current->num);
            return;
        }
        else if (current->ISBN == ISBN) { // ISBN번호만 같을시
            book* temp = current;
            *head = current->link;
            free(current);
            printf("중복된 번호입니다\n");
            return;
        }
        current = current->link;
    }

    // new book 노드 생성
    book* new_book = createnode(ISBN, name, author, publisher, price, num);

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

void data(book** head) {
    book* current = *head;
    if (*head == NULL) {
        printf("등록된 책이 없습니다.\n");
        return;
    }
    else {
        printf("******************************** list *******************************\n");
        printf("-ISBN-     -책제목-   -저자-     -출판사-   -가격-     -수량-\n");
        while (current != NULL) {
            printf("%-10d %-10s %-10s %-10s %-10d %-10d \n", current->ISBN, current->name, current->author, current->publisher, current->price, current->num);
            current = current->link;
        }
        return;
    }
}


void search(book** head) {
    book* current = *head;
    if (*head == NULL) {
        printf("등록된 책이 없습니다.\n");
        return;
    }
    else {
        char _data[100];
        printf("책의 정보를 입력하세요\n");
        printf("책을 대여하시려면 제목이나 책의 번호를 입력하세요\n");
        scanf("%s", _data);
        while (current != NULL) {
            if (strcmp(current->name, _data) == 0) {
                printf("%s의 남아 있는 책은 %d권입니다.\n", current->name, current->num);
                char ans[10];
                printf("책을 대여하시겠습니까?(yes or no)\n");
                scanf("%s", ans);
                if (strcmp(ans, "yes") == 0) {
                    if (current->num <= 0) {
                        printf("현재 책이 없어 빌릴 수 없습니다\n");
                        return;
                    }
                    else {
                        current->num -= 1;
                        printf("책을 대여하였습니다\n");
                        return;
                    }
                }
                else {
                    return;
                }
            }
            else if (strcmp(current->author, _data) == 0) {
                printf("%-10d %-10s %-10s %-10s %-10d %-10d \n", current->ISBN, current->name,
                    current->author, current->publisher, current->price, current->num);
            }
            else if (strcmp(current->publisher, _data) == 0) {
                printf("%-10d %-10s %-10s %-10s %-10d %-10d \n", current->ISBN, current->name,
                    current->author, current->publisher, current->price, current->num);
            }
            current = current->link;
        }
        printf("찾으시는 책이 없습니다.\n");
        return;
    }
}

void freebook(book** head) {
    book* current = *head;
    while (current != NULL) {
        book* temp = current;
        current = current->link;
        free(temp);
    }
    *head = NULL;
}

void printdata(book** head) {
    book* current = *head;
    printf("찾고자하는 책의 제목을 입력하세요: \n");
    char data[100];
    scanf("%s", data);

    while (current != NULL) {
        if (strcmp(current->name, data) == 0) {
            printf("찾으시는 책의 정보:\n");
            printf("ISBN: %d\n", current->ISBN);
            printf("제목: %s\n", current->name);
            printf("저자: %s\n", current->author);
            printf("출판사: %s\n", current->publisher);
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
    printf("삭제하실 책의 제목을 적으세요.\n");
    scanf("%s", data1);

    while (current != NULL) {
        if (strcmp(current->name, data1) == 0) {
            book* temp = current;
            *head = current->link;
            free(temp);
            printf("책이 삭제되었습니다.\n");
            return;
        }
        current = current->link;
    }
    printf("해당하는 책이 없습니다!\n");
    return;
}

void returnbook(book** head) {
    book* current = *head;
    char plus[100];
    printf("반납하실 책의 제목을 작성하시오\n");
    scanf("%s", plus);

    while (current != NULL) {
        if (strcmp(current->name, plus) == 0) {
            current->num += 1;
            printf("책이 반납되었습니다\n");
            return;
        }
        current = current->link;
    }
    printf("우리 책이 아닙니다!\n");
    return;
}

void array(book** head) {
    if (*head == NULL || (*head)->link == NULL) {
        return;
    }

    book* current = *head;
    book* prev = NULL;
    book* temp;
    bool isSorted = false;

    while (!isSorted) {
        isSorted = true;
        current = *head;
        prev = NULL;

        while (current->link != NULL) {
            if (current->ISBN > current->link->ISBN) {
                temp = current->link;
                current->link = temp->link;
                temp->link = current;

                if (prev == NULL) {
                    *head = temp;
                }
                else {
                    prev->link = temp;
                }
                prev = temp;
                isSorted = false;
            }
            else {
                prev = current;
                current = current->link;
            }
        }
    }
}
