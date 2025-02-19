// function mySum
// precondition: a and b are integers
// postcondition: returns the sum of a and b
int mySum(int a, int b) {
    return a + b;
}

// function myDivision
// precondition: a and b are integers
// postcondition: 0 a and b if b != 0, otherwise returns -1
int myDivision(int a, int b, int *result, int *remainder) {
    if (b == 0) {
        return -1;
    }
    *result = a / b;
    *remainder = a % b;
    return 0;
}
