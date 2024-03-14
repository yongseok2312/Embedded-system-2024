# Embedded-system-2024
IoT  개발자 임베디드시스템 학습리포지토리

## 기본명령어(C) - 기존 pc같이 사용하면 안된다. 순서에 맞추어서 사용
- ls : 현재 목록, ls -a : 숨겨져 있는 파일 확인, ls -l: 상세하게 보여줌, ls .etc: 환경 파일 등을 보여주는 디렉토리
- pwd : 기본위치
- mkdir Work: 새로운 work 디렉터리 생성
- rm -fr Work: Work 디렉터리 삭제
- cd work: work에 들어감, cd ..: 상위 폴더로 빠져나감
- nano /etc/nanorc
- sudo nano /etc/nanorc: 관리자 권한
    - set autoindent //주석 제거
    - set linenumbers //주석 제거
    - set tabsize 2 // 주석제거 및 사이즈 크기 바꿈
- sudo shutdown now
- mv : 이동 및 수정
- cp : 복사
- gcc -o 실행파일 source파일 : 실행파일 제작    //gcc실행파일 제작
- ./실행파일 : 실행 파일 실행
- %d: 정수 출력
- %f: 실수 출력
- sizeof(크기)
- %c: 문자 출력
- %s: 문자열 출력
- define : 매크로
- pirntf:출력
- scanf: 받는 
- malloc free




### day01
- 라즈베리파이 설치

### day02
- sudo apt update
- sudo apt upgrade -y
- clear 
- 환경설정 편집기: 코드 작업 할때 사용하는 프로그램(nano)


### day03
    - vnc viewer 설치
    - vncserver-virtual 
    - enum 열거형
       ``` python
        #이부분은 주석입니다 C언어
        #include <stdio.h>
            void main(){
                enum season {SPRING, SUMMER, FALL, WINTER} s;
                s= SPRING;
                printf("%d\n",s);
                }
        ```
### day04
- malloc free
- curr 순환
- node 전위 삽입/ 후위 삽입