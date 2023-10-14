#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int frames, window;
    
    printf(" Enter the number of frames to be sent : ");
    scanf("%d", &frames);
    printf("\n Enter the window size : ");
    scanf("%d", &window);
    
    int i = 0;
    
    while(i < frames)
    {
        int x = 0;
        
        for(int j = i+1; j <= i+window && j <= frames; j++)
            printf("Frame %d Sent \n", j);
            
        for(int j = i+1; j <= i+window && j <= frames; j++)
        {
            int ack = rand() % 10;
            
            if(ack > 2 && ack < 7)
            {
                printf("Acknowledgment for Frame %d Recieved \n",  j);
                x++;
            }
            else
            {
                printf("Frame Time Out.\n Discarding the present window size.");
                break;
            }
        }
        i += x;
    }

    return 0;
}
