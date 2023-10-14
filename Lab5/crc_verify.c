#include <stdio.h>
#include <conio.h>
#include <string.h>

int main()
{
    char data[100], key[20], temp[20], q[100], r[20], key1[20];
    int keylen, datalen, i, j;
    
    printf("Enter Recieved Data: ");
    gets(data);
    printf("\nEnter Key :");
    gets(key);
    
    keylen = strlen(key);
    datalen = strlen(data);
    strcpy(key1, key);
    
    for(i = 0; i < keylen; i++)
    {
        temp[i] = data[i];
    }
    
    for(i = 0; i < datalen-keylen+1; i++)  
    {
		q[i]=temp[0];
		
		if(q[i]=='0')
		{
		    for(j = 0; j < keylen; j++)
        		 key[j] = '0';    
		}
		 
        else
        {
            for(j = 0; j < keylen; j++)
        		 key[j] = key1[j];      
        }
		
		for(j = keylen-1; j > 0; j--) 
		{
			if(temp[j] == key[j])
			 r[j-1]='0'; 
			else
			 r[j-1]='1';
		}
		
		r[keylen-1] = data[i+keylen];  
		strcpy(temp, r);
	}
    
    strcpy(r,temp);
	 
	printf("\nRemainder is ");
	for(i = 0; i < keylen-1; i++)
	 	printf("%c",r[i]);
	
    return 0;
}
