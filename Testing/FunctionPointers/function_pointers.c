#include <stdio.h>

int add(int a, int b){
    return a + b;
}

int substract(int a, int b){
    return a - b;
}

int multiply(int a, int b){
    return a * b;
}

int divide(int a, int b){
    return a / b;
}

int main(){
    int ((**ftpr)(int, int));

    ftpr = (int ((**)(int, int)))malloc(sizeof(int (*)(int, int)) * 4);
    0[ftpr] = add;
    1[ftpr] = substract;
    2[ftpr] = multiply;
    3[ftpr] = divide;

    printf("%d", 0[ftpr](10,5));

    return 0;
}