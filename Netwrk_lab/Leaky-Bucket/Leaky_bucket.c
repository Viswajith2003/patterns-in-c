#include<stdio.h>
void main()
{
    int bsize,bcontnt=0,packects,outrate;
    printf("Enter the size of bucket: ");
    scanf("%d",&bsize);
    printf("Enter the output rate: ");
    scanf("%d",&outrate);
    printf("Enter the no: of packets: ");
    scanf("%d",&packects);

    for(int i=0;i<=packects;i++)
    {
        int psize;
        printf("Enter the size of packet %d :",i+1);
        scanf("%d",&psize);
        if(psize>bsize-bcontnt)
        {
            printf("packet is droped due to the inefficiant space \n");
        }
        else{
            bcontnt+=psize;
            if(bcontnt<0)
            {
                bcontnt=0;
            }
            printf("Bucket content : (%d/%d)\n",bcontnt,bsize);
        }
        bcontnt-=outrate;
        if(bcontnt<0)
        {
            bcontnt=0;
        }
        printf("Bucket content after outgoing is : (%d/%d)\n",bcontnt,bsize);   
    }
    while (bcontnt!=0)
    {
        bcontnt-=outrate;
        if(bcontnt<0)
        {
                bcontnt=0;
        }
        printf("Bucket content after outgoing is : (%d/%d)\n",bcontnt,bsize); 
    }
    
}