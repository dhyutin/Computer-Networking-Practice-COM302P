#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main()
{
 int s_sock, p, p1, p2, p4;
 int data[7], test[7];
 
 s_sock=socket(AF_INET,SOCK_DGRAM,0);
 
 struct sockaddr_in server, other;
 server.sin_family=AF_INET;
 server.sin_port=htons(9001);
 server.sin_addr.s_addr=INADDR_ANY;
 socklen_t add;
 
 bind(s_sock,(struct sockaddr*)&server,sizeof(server));
 add=sizeof(other);
 
 recvfrom(s_sock,data,sizeof(data),0,(struct sockaddr*)&other,&add);
 
 printf("Recieved msg: ");
 for(int i = 0; i < 7; i++)
    printf("%d",data[i]);
  
 printf("\nEnter data for testing :");
 for(int i = 0; i < 7; i++)
    scanf("%d", &test[i]);
   
 p1 = test[0]^test[2]^test[4]^test[6];
 p2 = test[0]^test[1]^test[4]^test[5];
 p4 = test[0]^test[1]^test[2]^test[3];
 
 p = (4*p4) + (2*p2) + p1;
 
 if(p == 0)
    printf("No error in message.");
 else
 {
    printf("\nError in position %d ",p);
    printf("\nCorrect Data is : ");
    test[7-p] = (test[7-p] == 0) ? 1 : 0;
    for(int i = 0; i < 7; i++)
       printf("%d", test[i]);
 }
    
 //close(s_sock);
 return 0;
}
