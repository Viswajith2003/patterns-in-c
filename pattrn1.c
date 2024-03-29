    
#include<stdio.h>
 
void main()
{
    int i,j,n;
    printf("Enter the limit: ");
    scanf("%d",&n);
    printf("The sequence is: ");
    printf("\n");
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=i;j++)
        {
            printf(" *");
        }
        printf("\n");
    }
}


// #include<stdio.h>

// void main()
// {
//     int i,j,n;
//     printf("Enter the limit: ");
//     scanf("%d",&n);
//     for(i=1;i<=n;i++)
//     {
//         for(j=1;j<=i;j++)
//         {
//             printf(" # ");
//         }
//         printf("\n");
//     }
// }


//Output
// *
// * *
// * * *
// * * * *
// * * * * *