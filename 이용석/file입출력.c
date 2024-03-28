/*
	File: file입출력.c

	Created: 24-03-13
	Author: 이용석
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

    printf("아이디: \n");
    scanf("%s", id);
    printf("비밀번호: \n");
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
            printf("비밀번호가 틀렸습니다\n");
        }
    }
    else {
        printf("입력된 id가 존재하지 않습니다\n");
        return;
    }
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
