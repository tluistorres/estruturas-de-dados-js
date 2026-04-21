#include <stdio.h>

int main() {
    int balance = 3000;
    int withdraw = 3000;

    if (balance -= withdraw)
       printf("Transaction Successful");
    else
       printf("Insufficient Balance");

    return 0;
     
}
