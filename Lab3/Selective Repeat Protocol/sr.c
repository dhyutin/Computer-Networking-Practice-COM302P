#include<stdio.h>
#include <stdlib.h>
#include<time.h>

int sent(int j,int *arr,int *i)
{
	printf("Frame %d sent\n",j);
	int flag = rand()%10; // flag gives us random values.
            
    if(flag)  //if flag != 0, the frame is accepted and acknowledgment is sent 
    {
        printf("Acknowledgment for Frame %d\n",j);
        return 1;
    }
    else  //The frame is not accepted.
    { 
        arr[*i] = j;
        (*i)++;
        return 0;
    }
}

int nak_print(int *arr,int i)
{
	int j;
	for(j=0;j<i;j++)
	{
		printf("Frame %d Not Received. This frames will be retransmitted.\n",arr[j]);
	}
}

int main()
{
	int nf,N,j,i,l;
	int* ptr;
    srand(time(NULL));
    
    printf("Enter the number of frames : ");
    scanf("%d",&nf);
    printf("Enter the Window Size : ");
    scanf("%d",&N);
    
    
    int nextw[N],nak[N],k=0;
    int frames[nf];
 
    for (i = 0; i < N; ++i) //entering the series of frame numbers
	{
        nextw[i]=i;
    }
    i = 0;  
    k=N;
    
    while(i<nf) //running loop till we send all the frames
    {
        int x=0,temp;
        
        l=0;
        for(j=0;j<N && i <= nf;j++) //running a loop to print the frames that are sent to the receiver.
        {
            if(i < nf)
            {
                temp = sent(nextw[j],nak,&l);
                i=i+temp; 
                if(temp == 1)
                {
                	nextw[j] = k; 
                // 	printf("\nK = %d",k);
    				k++;           	
    			} 
            }
        		
        }
        nak_print(nak,l);
        
        printf("i = %d\n\n",i);
        
    }
    return 0;
}
