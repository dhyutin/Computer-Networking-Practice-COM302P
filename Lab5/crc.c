#include <stdio.h>
#include <conio.h>
#include <string.h>

int main()
{
    char data[100], key[20], temp[20], q[100], r[20], key1[20];
    int keylen, datalen, i, j;
    
    printf("Enter Data: "); //dividend
    gets(data);
    printf("\nEnter Key :"); //divisor
    gets(key);
    
    keylen = strlen(key);
    datalen = strlen(data);
    strcpy(key1, key);
    
    for(i = 0; i < keylen-1; i++) //keylen-1 bits of 0's append at the end
    {
        data[datalen+i] = '0'; 
    }
    
    for(i = 0; i < keylen; i++) //first keylen bits required for xor 
    {
        temp[i] = data[i];
    }
    
    for(i = 0; i < datalen; i++) 
    {
		q[i]=temp[0];
		
		if(q[i]=='0')//not enough sufficient bits -> need to xor by 0's
		{
		    for(j = 0; j < keylen; j++)
        		 key[j] = '0';
		}
		 
        else //xor by divisor
        {
            for(j = 0; j < keylen; j++)
        		 key[j] = key1[j];
        }
		
		for(j = keylen-1; j > 0; j--) //xor function
		{
			if(temp[j] == key[j])
			 r[j-1]='0'; 
			else
			 r[j-1]='1';
		}
		
		r[keylen-1] = data[i+keylen]; //next bit needs to be bought for division
		strcpy(temp, r); //remainder is the new dividend for next xor func
	}
    
    strcpy(r,temp); //last step temp is now the remainder
    
	printf("\nQuotient is ");
	for(i = 0; i < datalen; i++)
	 printf("%c",q[i]);
	 
	printf("\nRemainder is ");
	for(i = 0; i < keylen-1; i++)
	 printf("%c",r[i]);
	 
	printf("\nFinal data is: ");
	for(i = 0; i < datalen; i++) //dividend
	 printf("%c",data[i]); 
	 
	for(i = 0; i < keylen-1; i++) //remaining remainder added at the end.
	 printf("%c",r[i]);
	 
	printf("\n");
	for(i = 0; i < keylen-1; i++)
    	data[i+datalen] = r[i];
    
    
    return 0;
}
