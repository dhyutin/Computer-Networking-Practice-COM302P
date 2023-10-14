#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main()
{
 int c_sock;
 int input[7];
 
 c_sock=socket(AF_INET,SOCK_DGRAM,0);
 
 struct sockaddr_in client,other;
 
 client.sin_family=AF_INET;
 client.sin_port=htons(9001);
 client.sin_addr.s_addr=INADDR_ANY;
 
 socklen_t ad;
 ad=sizeof(other);
 
 printf("\nEnter message ");
 scanf("%d",&input[0]);
 scanf("%d",&input[1]);
 scanf("%d",&input[2]);
 scanf("%d",&input[4]);
 
 input[6] = input[0]^input[2]^input[4];
 input[5] = input[0]^input[1]^input[4];
 input[3] = input[0]^input[1]^input[2];
 
 sendto(c_sock,input,sizeof(input),0,(struct sockaddr*)&client,sizeof(client));
 
 printf("client send: ");
 for(int i = 0; i < 7; i++)
    printf("%d",input[i]);
 
 //close(c_sock);
 return 0;
}
