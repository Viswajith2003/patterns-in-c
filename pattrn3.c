#include<stdio.h>

void main()
{
    int i,j,n;
    printf("Enter the limit: ");
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=i ;j++)
        {
            printf("%d ",j);
        }
        printf("\n");
    }
}


//Output
// 1 
// 1 2 
// 1 2 3 
// 1 2 3 4 
// 1 2 3 4 5 

//H.W
// 1 2 3 4 5
// 1 2 3 4
// 1 2 3
// 1 2
// 1