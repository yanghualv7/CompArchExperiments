#include "4-sum_compilation.h"

int main()
{
    int sum[5];
    printf("Please enter 5 numbers (use enter once for each number): ");
    for(int i=0;i<5;i++)
    {
        scanf("%d",&sum[i]);
    }

    int sum_val = Sum(sum); 
    printf("sum = %d\n",sum_val);
    if(sum_val > 50)
        printf("The average value is greater than 10");
    else
        printf("The average value is less than 10");

    system("pause");
    return 0; 
}