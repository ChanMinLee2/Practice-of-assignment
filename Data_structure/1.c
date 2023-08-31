#include <stdio.h>

int main() {
    char formula[100];   // declare a character array to store the input formula
    int i = 0;           // initialize a counter variable to keep track of the formula length
    char num1[20];       // declare a character array to store the first number
    char num2[20];       // declare a character array to store the second number
    char op;             // declare a character variable to store the operator
    int is_decimal = 0;  // initialize a flag variable to keep track of decimal point

    printf("Enter a formula: ");

    // read the input formula character by character until the newline character is encountered
    while ((formula[i] = getchar()) != '\n') 
    {
        if (formula[i] != ' ') 
        {
            i++;
        }
    }


    formula[i] = '\0';   // terminate the formula string with a null character

    i = 0;

    // parse the formula string to separate the first number, operator, and second number
    while (formula[i] >= '0' && formula[i] <= '9' || formula[i] == '.') {
        if (formula[i] == '.') {
            num1[i] = formula[i];
            is_decimal = 1;
        } else {
            if (is_decimal) {
                num1[i+1] = formula[i];
            } else {
                num1[i] = formula[i];
            }
        }
        i++;
    }
    num1[i] = '\0';
    op = formula[i];
    i++;

    int j = 0;
    is_decimal = 0;
    while (formula[i] >= '0' && formula[i] <= '9' || formula[i] == '.') {
        if (formula[i] == '.') {
            num2[j] = formula[i];
            is_decimal = 1;
        } else {
            if (is_decimal) {
                num2[j+1] = formula[i];
            } else {
                num2[j] = formula[i];
            }
        }
        i++;
        j++;
    }
    num2[j] = '\0';

    printf("Number 1: %s\n", num1);
    printf("Operator: %c\n", op);
    printf("Number 2: %s\n", num2);

    return 0;
}
