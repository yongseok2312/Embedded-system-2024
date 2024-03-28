/*
	File: linkedList.c

	Created: 24-03-27
	Author: �̿뼮
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct BOOK {
    char name[100]; // å ����
    int price;       // å ����
    struct BOOK* link;
    int num;         // å ����
    char author[100]; // å ����
    int ISBN;         // å ��ȣ
    char publisher[100]; // ���ǻ�
} book;

// å ��� ����
book* createnode(int ISBN, char name[], char author[], char publisher[], int price, int num) {
    book* newnode = (book*)malloc(sizeof(book));
    if (newnode == NULL) {
        printf("�޸� �Ҵ� ����\n");
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

void menu();  // �޴�
void add(book** head, int ISBN, char name[], char author[], char publisher[], int price, int num);
void data(book** head); // ��� ������ ���
void printdata(book** head);  // ���ϴ� ������ ���
void search(book** head); // �˻�
void deletebook(book** head); // ����
void returnbook(book** head);
void freebook(book** head); // �޸� ����
void array(book** head);

int main() {
    book* head = NULL;
    char name[100];
    int price, num, ISBN;
    char input[100];  // �޴� ���ڿ�
    char author[100];
    char publisher[100];

    while (1) {
        printf("\n");
        menu();
        int inputStatus = 0; // �������� �������� �Ǻ�
        while (inputStatus == 0) {
            printf("�޴��� �����ϼ���: ");
            scanf("%s", input);
            printf("\n");

            if (sscanf(input, "%s", input) == 1) {  // ���ڿ��� ���ڷ� ��ȯ
                inputStatus = 1;
            }
            else {
                printf("�߸��� �Է��Դϴ�. ���ڸ� �Է��ϼ���.\n");
            }
        }
        if (strcmp(input, "add") == 0) {
            printf("å ��ȣ �Է��ϼ���.\n");
            scanf("%d", &ISBN);
            printf("å �̸��� �Է��ϼ���.\n");
            scanf("%s", name);
            printf("å ����  �Է��ϼ���.\n");
            scanf("%s", author);
            printf("å ���ǻ� �Է��ϼ���.\n");
            scanf("%s", publisher);
            printf("å ����  �Է��ϼ���.\n");
            scanf("%d", &price);
            printf("å ������ �Է��ϼ���.\n");
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
            printf("�߸��� �Է��Դϴ�\n");
        }
    }
    freebook(&head);
    return 0;
}

void menu() {
    printf("**** �޴� ****\n");
    printf("add - ��������(���)\n");
    printf("search - �����˻�\n");
    printf("delete - ��������\n");
    printf("print - �������\n");
    printf("return - �����ݳ�\n");
    printf("exit - ����\n");
}

void add(book** head, int ISBN, char name[], char author[], char publisher[], int price, int num) {
    book* current = *head;

    // å�� ���� ��� ���� ����
    while (current != NULL) {
        if (strcmp(current->name, name) == 0 && current->ISBN == ISBN) {
            current->num += num;
            printf("������ �����Ͽ����ϴ�.\n");
            printf("%s�� ������ %d�Դϴ�.\n", name, current->num);
            return;
        }
        else if (current->ISBN == ISBN) { // ISBN��ȣ�� ������
            book* temp = current;
            *head = current->link;
            free(current);
            printf("�ߺ��� ��ȣ�Դϴ�\n");
            return;
        }
        current = current->link;
    }

    // new book ��� ����
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
    printf("å�� �߰� �Ǿ����ϴ�\n");
}

void data(book** head) {
    book* current = *head;
    if (*head == NULL) {
        printf("��ϵ� å�� �����ϴ�.\n");
        return;
    }
    else {
        printf("******************************** list *******************************\n");
        printf("-ISBN-     -å����-   -����-     -���ǻ�-   -����-     -����-\n");
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
        printf("��ϵ� å�� �����ϴ�.\n");
        return;
    }
    else {
        char _data[100];
        printf("å�� ������ �Է��ϼ���\n");
        printf("å�� �뿩�Ͻ÷��� �����̳� å�� ��ȣ�� �Է��ϼ���\n");
        scanf("%s", _data);
        while (current != NULL) {
            if (strcmp(current->name, _data) == 0) {
                printf("%s�� ���� �ִ� å�� %d���Դϴ�.\n", current->name, current->num);
                char ans[10];
                printf("å�� �뿩�Ͻðڽ��ϱ�?(yes or no)\n");
                scanf("%s", ans);
                if (strcmp(ans, "yes") == 0) {
                    if (current->num <= 0) {
                        printf("���� å�� ���� ���� �� �����ϴ�\n");
                        return;
                    }
                    else {
                        current->num -= 1;
                        printf("å�� �뿩�Ͽ����ϴ�\n");
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
        printf("ã���ô� å�� �����ϴ�.\n");
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
    printf("ã�����ϴ� å�� ������ �Է��ϼ���: \n");
    char data[100];
    scanf("%s", data);

    while (current != NULL) {
        if (strcmp(current->name, data) == 0) {
            printf("ã���ô� å�� ����:\n");
            printf("ISBN: %d\n", current->ISBN);
            printf("����: %s\n", current->name);
            printf("����: %s\n", current->author);
            printf("���ǻ�: %s\n", current->publisher);
            printf("����: %d\n", current->price);
            printf("����: %d\n", current->num);
            return;
        }
        current = current->link;
    }
    printf("ã���ô� å�� �����ϴ�.\n");
    return;
}

void deletebook(book** head) {
    book* current = *head;
    char data1[100];
    printf("�����Ͻ� å�� ������ ��������.\n");
    scanf("%s", data1);

    while (current != NULL) {
        if (strcmp(current->name, data1) == 0) {
            book* temp = current;
            *head = current->link;
            free(temp);
            printf("å�� �����Ǿ����ϴ�.\n");
            return;
        }
        current = current->link;
    }
    printf("�ش��ϴ� å�� �����ϴ�!\n");
    return;
}

void returnbook(book** head) {
    book* current = *head;
    char plus[100];
    printf("�ݳ��Ͻ� å�� ������ �ۼ��Ͻÿ�\n");
    scanf("%s", plus);

    while (current != NULL) {
        if (strcmp(current->name, plus) == 0) {
            current->num += 1;
            printf("å�� �ݳ��Ǿ����ϴ�\n");
            return;
        }
        current = current->link;
    }
    printf("�츮 å�� �ƴմϴ�!\n");
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
