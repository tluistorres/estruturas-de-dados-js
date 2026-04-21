#include<stdio.h>
int main()
{
    int a=5;
    int b=2+a++;
    printf("%d %d",b++,a);
    return 0;   
}
