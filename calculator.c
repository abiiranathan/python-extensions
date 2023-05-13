#include <stdio.h>

typedef struct {
    int (*add)(int, int);
    int (*subtract)(int, int);
    int (*mul)(int, int);
    int (*div)(int, int);
    int (*mod)(int, int);
} Calculator;

// Function to add 2 numbers
int add(int a, int b) {
    return a + b;
}

// Function to subtract 2 numbers
int subtract(int a, int b) {
    return a - b;
}

// Function to multiply 2 numbers
int multiply(int a, int b) {
    return a * b;
}

// Function to divide 2 numbers. b must not be zero
int divide(int a, int b) {
    return a / b;
}

// Function to find modulo between 2 numbers
int modulo(int a, int b) {
    return a % b;
}

int main(void) {
    // Create calculator object
    Calculator calc;

    // Assign the function pointers
    calc.add = add;
    calc.subtract = subtract;
    calc.mul = multiply;
    calc.div = divide;
    calc.mod = modulo;

    int a = 10, b = 2, result;
    result = calc.add(a, b);
    printf("Addition: %d\n", result);

    result = calc.mod(a, b);
    printf("Mod: %d\n", result);

    result = calc.subtract(a, b);
    printf("Sub: %d\n", result);

    result = calc.mul(a, b);
    printf("Mul: %d\n", result);

    result = calc.div(a, b);
    printf("Div: %d\n", result);
}