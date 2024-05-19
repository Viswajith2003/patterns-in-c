#include <stdio.h>

int sum(int number){
    
    int f_no,l_no,total;
    l_no=number%10;
    
    while(number >=10)
    {
        number=number/10;
    }
    f_no=number;
    
    total=f_no+l_no;
    return total;
}

void main()
{
    int number,res;
    printf("Enter the number: ");
    scanf("%d",&number);
    res=sum(number);
    
    printf("The sum is: %d",res);
}