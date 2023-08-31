#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_COUNT 100
#define DIFFERENT 1
#define SAME 0

struct Student {
    char name[20];
    char gender[5];
    char address[50];
    char department[20];
    char grade[10];
    char height[10];
    char weight[10]; 
};

struct Set {
    struct Student *student; // data
    int cardinality; // cardinality
};

struct Map {
    char *string; // key
    struct Set set; //value
};

void setInit(struct Set *mySet, int size) {
    mySet -> student = (struct Student*)malloc(size * sizeof(struct Student));
    mySet -> cardinality = 0;
}

void set_print(struct Set *mySet) {
    for (int i = 0; i < mySet -> cardinality; i++) {
        printf("%s ", mySet -> student[i].name);
        printf("%s ", mySet -> student[i].gender);
        printf("%s ", mySet -> student[i].address);  
        printf("%s ", mySet -> student[i].department);  
        printf("%s ", mySet -> student[i].grade);  
        printf("%s ", mySet -> student[i].height);  
        printf("%s\n", mySet -> student[i].weight);
    }
}

int check_Same_student(struct Student first, struct Student second) { // check two student has same value.(name, gender, address, department, grade, height, weight)
    if (strcmp(first.name, second.name) == 0 && strcmp(first.address, second.address) == 0 && strcmp(first.gender, second.gender) == 0 && strcmp(first.department, second.department) == 0 && strcmp(first.grade, second.grade) == 0 && strcmp(first.height, second.height) == 0 && strcmp(first.weight, second.weight) == 0) {
        return 1; // true
    }
    return 0; // false
}

void set_load(struct Set *mySet) {
    FILE *listFp = fopen("list.txt", "r+t");
    char c[512];
    int i = 0, STATUS;
    while (fgets(c, 512, listFp) != NULL) { // 정보 입력받기 
        int j = 0;
        struct Student temp;

        STATUS = DIFFERENT; //  In order to check that set has same student 
        sscanf(c, "%s%s%s%s%s%s%s", temp.name, temp.gender, temp.address, temp.department, temp.grade, temp.height, temp.weight);
        for (; j < mySet -> cardinality; j++) {
            if (check_Same_student(*(mySet -> student), temp)) { // If student is same, don't add
                STATUS = SAME;
                break; // for overwrite
            }
            else if (strcmp(mySet -> student[j].name, temp.name) > 0) {
                for (int k = mySet -> cardinality - 1; k >= j; k--) {
                    mySet -> student[k + 1] = mySet -> student[k];
                }   
                break;
            }
        }
        mySet -> student[j] = temp;
        i++;
        if (STATUS == DIFFERENT) {    
            mySet -> cardinality++;
        }
    }
    fclose(listFp);
}

char* Q1(struct Set *mySet, char *name) {
    printf("%s가 사는 곳은 어디인가?\n", name);

    for (int i = 0; i < mySet -> cardinality; i++) { // Find name in set and return 
        if (strcmp(mySet -> student[i].name, name) == 0) {
            return mySet -> student[i].address;
        }
    }
    return "찾지 못했습니다.";
}

int Q2(struct Set *mySet, char *name) {
    printf("%s보다 성적이 좋은 사람은 몇명인가?\n", name);
    int count = 0, i; // i is name's index
    for (i = 0; i < mySet -> cardinality; i++) { // find name in set
        if (strcmp(mySet -> student[i].name, name) == 0) {
            break;
        }
    }
    if (i == mySet -> cardinality) { // If can't find name in set
        return -1;
    }
    for (int j = 0; j < mySet -> cardinality; j++) { // Compare name with student in set
        if (mySet -> student[j].grade > mySet -> student[i].grade) {
            count++;
        }
    }
    return count;
}

char* Q3(struct Set mySet) {
    printf("가장 학생이 많은 학과는 무슨 과인가?\n");
    struct Map myMap[MAX_COUNT];
    for (int i = 0; i < MAX_COUNT; i++) {  // Allocate dynamic memory of student
        setInit(&myMap[i].set, 1);
    }
    
    int index = 0; // element count of array map
    // count
    if (mySet.cardinality <= 0) { // If set is empty
        return "집합이 비어있습니다.";
    }
    
    for (int i = 0; i < MAX_COUNT; i++) { // initialize cardinality to 0
        myMap[i].set.cardinality = 0;
    }
    
    myMap[0].string = mySet.student[0].department; // count a number of each major
    for (int i = 0; i < mySet.cardinality; i++) { // mySet's index
        for (int j = 0; j <= index; j++) { // myMap's index
            if (j == index) { // Doesn't find major in map. So, Create new.
                myMap[j].string = mySet.student[i].department;
                myMap[j].set.cardinality++;
                index++;
                break;
            }
            else if (strcmp(myMap[j].string, mySet.student[i].department) == 0) { // If it find in map, count++;
                myMap[j].set.cardinality++;
                break;
            }
        }
    }
    // Find major that is most in set
    int findIndex = 0;
    for (int i = 1; i < index; i++) {
        if (myMap[findIndex].set.cardinality < myMap[i].set.cardinality){
            findIndex = i;
        }
    }
    // Deallocate dynamic memory
    char *string = myMap[findIndex].string;
    for (int i = 0; i < MAX_COUNT; i++) {
        free(myMap[i].set.student);
    }
    return string;
}

void print_one_of_map(struct Map *myMap, int index) {
    for (int i = 0; i < myMap[index].set.cardinality; i++) {
        printf("%s ", myMap[index].set.student[i].name);
        printf("%s ", myMap[index].set.student[i].gender);
        printf("%s ", myMap[index].set.student[i].address);  
        printf("%s ", myMap[index].set.student[i].department);  
        printf("%s ", myMap[index].set.student[i].grade);  
        printf("%s ", myMap[index].set.student[i].height);  
        printf("%s\n", myMap[index].set.student[i].weight);
    }
}

void Q4(struct Set mySet) {
    printf("가장 많이 거주하는 지역 순서\n");
    struct Map myMap[MAX_COUNT];
    for (int i = 0; i < MAX_COUNT; i++) { // Allocate dynamic memory of student
        setInit(&myMap[i].set, MAX_COUNT);
    }
    
    int index = 0; // element count of array map
    // count
    if (mySet.cardinality <= 0) { // If set is empty
        printf("집합이 비어있습니다.\n");
        return;
    }
    
    for (int i = 0; i < MAX_COUNT; i++) { // initialize cardinality to 0
        myMap[i].set.cardinality = 0;
    }
    
    myMap[0].string = mySet.student[0].address; // count a number of each address
    for (int i = 0; i < mySet.cardinality; i++) { // mySet's index
        for (int j = 0; j <= index; j++) { // myMap's index
            if (j == index) { // Doesn't find address in map. So, Create new.
                myMap[j].string = mySet.student[i].address;
                myMap[j].set.student[myMap[j].set.cardinality] = mySet.student[i]; // Store student's info in set of map
                myMap[j].set.cardinality++; // add 1 to cardinality of set of map
                index++; 
                break;
            }
            else if (strcmp(myMap[j].string, mySet.student[i].address) == 0) { // If it find in map, count++ and store set;
                myMap[j].set.student[myMap[j].set.cardinality] = mySet.student[i];
                myMap[j].set.cardinality++;
                break;
            }
        }
    }
    // Find major that is most in set
    int ascending[index], temp; // ascending is array consisting of index of map
    for (int i = 0; i < index; i++) {
        ascending[i] = i;
    }
    
    for(int i = 0; i < index - 1; i++){ // sorting index with a order of ascending cardinality
        for(int j = i+1; j < index; j++){
            if(myMap[ascending[i]].set.cardinality < myMap[ascending[j]].set.cardinality){
                temp = ascending[i]; // swap
                ascending[i] = ascending[j];
                ascending[j] = temp;
            }
        }
    }
    // print
    for (int i = 0; i < index; i++) {
        print_one_of_map(myMap, ascending[i]);
    }
    
    for (int i = 0; i < MAX_COUNT; i++) { // Deallocate memory
        free(myMap[i].set.student);
    }
}

void Q5(struct Map **myMap, struct Set *mySet) {
    // Set of Map already have unique name because of body of set_load function, So, Only make map
    *myMap = (struct Map*)malloc(mySet -> cardinality * sizeof(struct Map));
    // count
    if (mySet -> cardinality <= 0) { // If set is empty
        printf("집합이 비어있습니다.\n");
        return;
    }
    
    for (int i = 0; i < mySet -> cardinality; i++) { // initialize student to NULL. for loop statement
        (*myMap)[i].set.student = NULL;
    }
    
    // Mapping name and student info
    for (int i = 0; i < mySet -> cardinality; i++) {
        for (int j = 0; j < i; j++) {
            if (strcmp((*myMap)[j].string, mySet -> student[i].name) == 0) {
                printf("이름이 중복되어 Key값으로 사용할 수 없습니다.\n");
                return;
            }
        }
        (*myMap)[i].string = mySet -> student[i].name;
        (*myMap)[i].set.student = mySet -> student + i;
    }
}

int main() {

    struct Set mySet;
    struct Map *myMap;
    setInit(&mySet, MAX_COUNT);
    set_load(&mySet);

    // print
    printf("이름순으로 정렬 \n");
    set_print(&mySet);

    // Question 1
    printf("\nQ1 : \n");
    char *name = "김문희";
    printf("%s의 사는 곳은 %s입니다.\n", name, Q1(&mySet, name));

    // // Question 2
    name = "천하은";
    printf("\nQ2 : \n");
    printf("%s보다 성적이 좋은 사람은 %d명입니다.\n", name, Q2(&mySet, name));

    // // Question 3
    printf("\nQ3 : \n");
    printf("가장 많은 학과 : %s\n", Q3(mySet));

    // // Question 4
    printf("\nQ4 : \n");
    Q4(mySet);

    // // Question 5
    printf("\nQ5 : \n");
    struct Set *temp;
    Q5(&myMap, &mySet);
    // 만약 동명이인이 있어 이름이 중복되면 Key값이 unique하지 않아 ID로 사용이 불가능합니다.


    if (mySet.student != NULL) { // Decallocat heap memory
        free(mySet.student);
    }

    if (myMap != NULL) { // Decallocat heap memory
        free(myMap);
    }
    return 0;
}