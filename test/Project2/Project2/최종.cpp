#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
void add(book** head, int ISBN, char name[], char author[], int price, int num);//�߰�
void data(book** head); // ������ ��ü ����
void printdata(book** head);    // ������ ���
void deletebook(book** head); // ������ ����
void borrow(book** head); // �뿩
void returnbook(book** head); //�ݳ�
void freebook(book** head); // �޸� ����

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
            printf("�߸��� �Է��Դϴ�\n");
        }
    }
    //free(head); // �޸� ����
    freebook(&head);
    return 0;
}

void menu() {
    printf("**** �޴� ****\n");
    printf("1. ��������(���)\n");
    printf("2. �����˻�\n");
    printf("3. ��������\n");
    printf("4. �������\n");
    printf("5. �����ݳ�\n");
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

void data(book** head)
{
    book* current = *head;
    if (*head == NULL)
    {
        printf("��ϵ� å�� �����ϴ�.\n");
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
       // printf("��ϵ� å�� �����ϴ�.\n");
        return;
    }
    else
    {   
        char _data[100];
        printf("å�� ������ �Է��ϼ���\n");
        scanf("%s",_data);
        while (current != NULL)
        {
            if (current->ISBN == atoi(_data) || current->name == _data)
            {
                printf("ã���ô� å�� �ֽ��ϴ�!!\n");
                return;
            }
            current = current->link;
        }
    }
    printf("ã���ô� å�� �����ϴ�.\n");
    return;
}

void printdata(book** head) {
    book* current = *head;
    printf("ã�����ϴ� å�� ���� �Ǵ� ISBN�� �Է��ϼ���: \n");
    char data[100];
    scanf("%s", data);
    int search_number = atoi(data); // atoi ������ ��ȯ

    while (current != NULL) {
        if (strcmp(current->name, data) == 0 || current->ISBN == search_number)
        {
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

void deletebook(book** head) {
    book* current = *head;
    char data1[100];
    int num2;
    printf("�����Ͻ� å�� ���� �Ǵ� ISBN�� ��������!\n");
    scanf("%s", data1);
    int num1 = atoi(data1);
    printf("å�� ������ ��������\n");
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
                printf("å�� �����Ǿ����ϴ�.\n");
                return;
            }
            else
            {
                current->num -= num2;
                printf("å�� ������ �����Ͽ����ϴ�.\n");
                return;
            }
        }
        current = current->link;
    }
    printf("�ش��ϴ� å�� �����ϴ�!\n");
}

void borrow(book** head)
{
    char ans[10];
    book* current = *head;
    printf("å�� �뿩�Ͻðڽ��ϱ�?(ture or false)\n");
    scanf("%s", ans);
    if (strcmp(ans,"true") == 0)
    {
        char data[100];
        printf("�뿩�� å�� ���� �� ISBN�� ������!\n");
        scanf("%s", data);
        int data2 = atoi(data);
        while (current != NULL)
        {
            if (strcmp(current->name, data) == 0 || current->ISBN == data2)
            {
                printf("%d %s �� ���� �ִ� å�� ���� %d�Դϴ�.\n", current->ISBN, current->name, current->num);
                if (current->num <= 0)
                {
                    printf("���� å�� ���� ������ �����ϴ�!\n");
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
        printf("ã���ô� å�� �����ϴ�!\n");
    }
    else {
            return;
    }
}

void returnbook(book** head)
{
    book* current = *head;
    char plus[100];
     printf("�ݳ��Ͻ� å�� �����̳� ISBN�� �ۼ��Ͻÿ�\n");
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
        printf("�츮 å�� �ƴմϴ�!\n");
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