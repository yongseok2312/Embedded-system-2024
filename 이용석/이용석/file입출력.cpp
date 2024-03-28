/*
	File: file�����.c

	Created: 24-03-13
	Author: �̿뼮
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 100

void error_handling(char* message);

void main() {
    int fd;
    char buf[BUF_SIZE];
    char id[BUF_SIZE], pass[BUF_SIZE];
    char str[] = "Yongseok";

    printf("���̵�: \n");
    scanf("%s", id);
    printf("��й�ȣ: \n");
    scanf("%s", pass);

    if (strcmp(id, "a") == 0) {
        if (strcmp(pass, "b") == 0) {
            fd = open("myinfo.txt", O_RDONLY);
            if (fd == -1) {
                error_handling("open() error!");
            }
            else {
                printf("\n");
            }

            if (read(fd, buf, sizeof(buf)) == -1)
                error_handling("read() error");
            printf("%s", buf);
            close(fd);
        }
        else {
            printf("��й�ȣ�� Ʋ�Ƚ��ϴ�\n");
        }
    }
    else {
        printf("�Էµ� id�� �������� �ʽ��ϴ�\n");
        return;
    }
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
