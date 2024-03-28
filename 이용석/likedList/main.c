#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "linkelist.h"

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