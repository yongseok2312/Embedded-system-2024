#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BOOK {
    char name[100]; // å ����
    int price;  // å ����
    struct BOOK* link;
    int num;    // å ����
    char author[100]; // å ����
    int ISBN; // å ��ȣ
} book;

//å ��� ����
book* createnode(int ISBN, char name[], char author[], int price, int num) {
    book* newnode = (book*)malloc(sizeof(book));
    if (newnode == NULL) {
        printf("�޸� �Ҵ� ����\n");
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

void menu();  //�޴�
void add(book** head, int ISBN, char name[], char author[], int price, int num);
//void search(book** head);

int main() {
    book* head = NULL;
    char name[100];
    int price, num, ISBN;
    int a;
    char input[100];  //�޴¼���
    char author[100];

    while (1) {
        menu();
        int inputStatus = 0; // �������� ���������Ǻ�
        while (inputStatus == 0) {
            printf("�޴��� �����ϼ���: ");
            scanf("%s", input);

            if (sscanf(input, "%d", &a) == 1) {  //���ڿ��� [>
                inputStatus = 1;
            }
            else {
                printf("�߸��� �Է��Դϴ�. ���ڸ� �Է��ϼ���.\n");
            }
        }

        if (a == 1) {
            printf("å ��ȣ �Է�\n");
            scanf("%d", &ISBN);
            printf("å �̸��� �Է�\n");
            scanf("%s", name);
            printf("å ����  �Է�\n");
            scanf("%s", author);
            printf("å ����  �Է�\n");
            scanf("%d", &price);
            printf("å ������ �Է�\n");
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
            printf("�߸��� �Է��Դϴ�\n");
        }
    }
    free(head); // �޸� ����
    return 0;
}

void menu() {
    printf("**** �޴� ****\n");
    printf("1. ��������(���)\n");
    printf("2. �����˻�\n");
    printf("3. ��������\n");
    printf("4. �������\n");
    printf("0. ����\n");
}
void add(book** head, int ISBN, char name[], char author[], int price, int num) {
    book* current = *head;
    // å�� ���� ��� ���� ����
    while (current != NULL) {
        if (strcmp(current->name, name) == 0 && current->ISBN == ISBN) {
            current->num += num;
            printf("������ �����Ͽ����ϴ�.\n");
            printf("%s�� ������ %d�Դϴ�.\n", name, current->num);
            return;
        }
        current = current->link;
    }

    //new book ��� ����
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
    printf("å�� �߰� �Ǿ����ϴ�\n");
}

/*void search(book** head)
{
    book* current = *head;
    if (*head == NULL)
    {
        printf("��ϵ� å�� �����ϴ�.");
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
        printf("��ϵ� å�� �����ϴ�.\n");
        return;
    }
    else {
        printf("ã�����ϴ� å�� ������ �Է��ϼ���: ");
        char search_name[100];
        scanf("%s", search_name);

        while (current != NULL) {
            if (strcmp(current->name, search_name) == 0) {
                printf("ã���ô� å�� ����:\n");
                printf("ISBN: %d\n", current->ISBN);
                printf("����: %s\n", current->name);
                printf("����: %s\n", current->author);
                printf("����: %d\n", current->price);
                printf("����: %d\n", current->num);
                return;
            }
            current = current->link;
        }

        printf("ã���ô� å�� �����ϴ�.\n");
        return;
    }
}