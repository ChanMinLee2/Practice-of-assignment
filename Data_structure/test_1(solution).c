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
};
struct Student *arrayStudent;
int countOfArray = 0;

void process_create() {
    arrayStudent = calloc(100, sizeof(struct Student));
}

void process_print() {
    for (int i = 0; i < countOfArray; i++) {
        printf("%s ", arrayStudent[i].name);
        printf("%s ", arrayStudent[i].gender);
        printf("%s ", arrayStudent[i].address);  
        printf("%s ", arrayStudent[i].department);  
        printf("%s ", arrayStudent[i].grade);  
        printf("%s ", arrayStudent[i].height);  
        printf("%s\n", arrayStudent[i].weight);
    }
}

void process_load(char filename[]) {
    FILE *listFp = fopen(filename, "r+t");
    char c;
    while ((c = fgetc(listFp)) != EOF) { // count a number of line
        if (c == '\n')
            countOfArray++;
    }
    countOfArray++;
    rewind(listFp);
    for (int i = 0; i < countOfArray; i++) { // input info into
        fscanf(listFp, "%s", arrayStudent[i].name);
        fscanf(listFp, "%s", arrayStudent[i].gender);
        fscanf(listFp, "%s", arrayStudent[i].address);
        fscanf(listFp, "%s", arrayStudent[i].department);
        fscanf(listFp, "%s", arrayStudent[i].grade);
        fscanf(listFp, "%s", arrayStudent[i].height);
        fscanf(listFp, "%s", arrayStudent[i].weight);
    }
    struct Student temp; // For sorting array
    for(int i = 0; i < countOfArray - 1; i++){
        for(int j = i+1; j < countOfArray; j++){
            if(strcmp(arrayStudent[i].name, arrayStudent[j].name) > 0){ // Bubble sort
                temp = arrayStudent[i]; // swap
                arrayStudent[i] = arrayStudent[j];
                arrayStudent[j] = temp;
            }
        }
    }
    fclose(listFp);
}

void process_insert(char name[], char gender[], char address[], char department[], char grade[], char height[], char weight[]) {
    int i = 0;
    for (i = 0; i < countOfArray - 1; i++) {
        if (strcmp(arrayStudent[i].name, name) > 0) { // Find name in array
            for (int j = countOfArray - 1; j >= i; j--) { // Element move back one step
                arrayStudent[j+1] = arrayStudent[j];
            }
            sscanf(name, "%s", arrayStudent[i].name);
            sscanf(gender, "%s", arrayStudent[i].gender);
            sscanf(address, "%s", arrayStudent[i].address);
            sscanf(department, "%s", arrayStudent[i].department);
            sscanf(grade, "%s", arrayStudent[i].grade);
            sscanf(height, "%s", arrayStudent[i].height);
            sscanf(weight, "%s", arrayStudent[i].weight);
            break;
        }
    }
    if (i == countOfArray - 1) { // Exception handling when insert at index of countOfArray
        sscanf(name, "%s", arrayStudent[i].name);
        sscanf(gender, "%s", arrayStudent[i].gender);
        sscanf(address, "%s", arrayStudent[i].address);
        sscanf(department, "%s", arrayStudent[i].department);
        sscanf(grade, "%s", arrayStudent[i].grade);
        sscanf(height, "%s", arrayStudent[i].height);
        sscanf(weight, "%s", arrayStudent[i].weight);
    }
    countOfArray++; // Plus one from count because of inserting
}

void process_search(char name[]) {
    for (int i = 0; i < countOfArray - 1; i++) {
        if (strcmp(arrayStudent[i].name, name) == 0) { // find name
            printf("%s ", arrayStudent[i].name);
            printf("%s ", arrayStudent[i].gender);
            printf("%s ", arrayStudent[i].address);  
            printf("%s ", arrayStudent[i].department);  
            printf("%s ", arrayStudent[i].grade);  
            printf("%s ", arrayStudent[i].height);  
            printf("%s\n", arrayStudent[i].weight);
            return;
        }
    }
    printf("%s를 찾지 못했습니다. \n", name); // If it didn't find name in array
}

void process_delete(char name[]) {
    for (int i = 0; i < countOfArray - 1; i++) {
        if (strcmp(arrayStudent[i].name, name) == 0) { // find name
            for (int j = i; j < countOfArray - 1; j++) { // Element move front one step
                arrayStudent[j] = arrayStudent[j+1];
            }
            countOfArray--; // Minus one from count because of deleting
            return;
        }
    }
    printf("%s를 찾지 못했습니다. \n", name); // If it didn't find name in array
}

int main() {

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
