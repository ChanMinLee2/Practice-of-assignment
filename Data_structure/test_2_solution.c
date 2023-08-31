#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student 
{
    char name[20];
    char gender[5];
    char address[50];
    char department[20];
    char grade[10];
    char height[10];
    char weight[10];
    struct Student *next; // 다음 구조체
};
struct Student *headnode; // headnode 선언

void process_create() {
    headnode = (struct Student*)calloc(1, sizeof(struct Student)); // 배열 할당을 위한 headnode 설정
    headnode -> next = NULL;
}

void process_print() {
    struct Student *current = headnode; // 현재 구조체를 가리키는 포인터
    while (current -> next != NULL) {
        printf("%s ", current -> next -> name);
        printf("%s ", current -> next -> gender);
        printf("%s ", current -> next -> address);  
        printf("%s ", current -> next -> department);  
        printf("%s ", current -> next -> grade);  
        printf("%s ", current -> next -> height);  
        printf("%s\n", current -> next -> weight);
        current = current -> next;
    }
}

void swap(char *a, char *b) { // 정렬을 위한 바구기 TODO:이건 피드백 봐야긋다
    char *temp;
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}

void process_load(char filename[]) {
    FILE *listFp = fopen(filename, "r+t"); // 파일 열기
    char c[512];
    struct Student *current;
    current = headnode;
    while (fgets(c, 512, listFp) != NULL) { // 정보 입력받기 
        struct  Student *temp = (struct Student*)calloc(1, sizeof(struct Student));
        sscanf(c, "%s%s%s%s%s%s%s", temp->name, temp->gender, temp -> address, temp -> department, temp -> grade, temp -> height, temp -> weight);
        temp -> next = NULL;
        while (current -> next != NULL) {
            current = current -> next;
        }
        current -> next = temp;
    }
    // For sorting array
    current = headnode -> next; // 현재 구조체를 가리키는 포인터
    struct Student *compare;
    while ((current -> next) != NULL) {
        compare = current -> next; // 비교할 구조체 포인터
        while (compare -> next != NULL) {
            if (strcmp(current -> name, compare -> name) > 0) {// 뒤의 것이 작으면 뒤로 보내기
                swap(current -> name, compare -> name); // 데이터 바꾸기 (주소 X)
                swap(current -> gender, compare -> gender);
                swap(current -> address, compare -> address);
                swap(current -> department, compare -> department);
                swap(current -> grade, compare -> grade);
                swap(current -> height, compare -> height);
                swap(current -> weight, compare -> weight);
            }
            compare = compare -> next;
        }
        current = current -> next;
    }
    fclose(listFp);
}

void process_insert(char name[], char gender[], char address[], char department[], char grade[], char height[], char weight[]) {
    struct Student *current = headnode;
    struct  Student *temp = (struct Student*)calloc(1, sizeof(struct Student)); // 새로 추가할 구조체 포인터 만들기
    sscanf(name, "%s", temp -> name);
    sscanf(gender, "%s", temp -> gender);
    sscanf(address, "%s", temp -> address);
    sscanf(department, "%s", temp -> department);
    sscanf(grade, "%s", temp -> grade);
    sscanf(height, "%s", temp -> height);
    sscanf(weight, "%s", temp -> weight);
    temp -> next = NULL;
    while (current -> next != NULL) {
        if (strcmp(current -> next -> name, name) > 0) {
            temp -> next = current -> next; // 다음 링크만 다시 설정하기
            current -> next = temp;
            return;
        }
        current = current -> next;
    }
    current -> next = temp;
}

void process_search(char name[]) {
    struct Student *current = headnode;
    while (current -> next != NULL) {
        if (strcmp(current -> next -> name, name) == 0) {// 찾아서 출력
            printf("%s ", current -> next -> name);
            printf("%s ", current -> next -> gender);
            printf("%s ", current -> next -> address);
            printf("%s ", current -> next -> department);
            printf("%s ", current -> next -> grade);
            printf("%s ", current -> next -> height);
            printf("%s\n", current -> next -> weight);
            return;
        }
        current = current -> next;
    }
    printf("%s를 찾지 못했습니다. \n", name); // 예외처리
}

void process_delete(char name[]) {
    struct Student *current = headnode;
    while (current -> next != NULL) {
        if (strcmp(current -> next -> name, name) == 0) {
            current -> next = current -> next -> next; // 링크를 다음의 링크로 바꾸기
            return;
        }
        current  = current -> next;
    }
    printf("%s를 찾지 못했습니다. \n", name); // 예외처리
}

int main()
{
    FILE *fp = fopen("input.txt", "r+t");
    char input[512];
    char tok1[32], tok2[32], tok3[32], tok4[32], tok5[32], tok6[32], tok7[32], tok8[32], tok9[32];
    while (fgets(input, 512, fp) != NULL) {
        sscanf(input, "%s%s%s%s%s%s%s%s%s", tok1, tok2, tok3, tok4, tok5, tok6, tok7, tok8, tok9);
        if (strcmp(tok1, "CREATE") == 0) {
            process_create();
            printf(" %s is done =======================================\n\n", tok1);
        }
        else if (strcmp(tok1, "LOAD") == 0) {
            process_load(tok2);
            printf(" %s is done =======================================\n\n", tok1);
        }
        else if (strcmp(tok1, "PRINT") == 0) {
            process_print();
            printf(" %s is done =======================================\n\n", tok1);
        }
        else if (strcmp(tok1, "INSERT") == 0) {
            process_insert(tok2, tok3, tok4, tok5, tok6, tok7, tok8);
            printf(" %s is done =======================================\n\n", tok1);
        }
        else if (strcmp(tok1, "SEARCH") == 0) {
            process_search(tok2);
            printf(" %s is done =======================================\n\n", tok1);
        }
        else if (strcmp(tok1, "DELETE") == 0) {
            process_delete(tok2);
            printf(" %s is done =======================================\n\n", tok1);
        }
        else {
            printf("%s is not a keyword \n", tok1);
        }
    }
    fclose(fp);
}