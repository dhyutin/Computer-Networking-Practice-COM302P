#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>


struct node
{
    unsigned int dist[20];
    unsigned int hop[20];
};

int main()
{
    int c_sock;
    char msg[1024] ="Hi! I am client!\n";
    struct sockaddr_in serv_addr;
    char buf[1024] = {0};

    if((c_sock=socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        printf("\nSocket creation error!\n");
        return -1;
    }

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(9009);
    serv_addr.sin_addr.s_addr=INADDR_ANY;

    if(connect(c_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
    {
        perror("\nConnection Failed!\n");
        return -1;
    }

    send(c_sock,msg,sizeof(msg),0);
    printf("Client Message Sent!!!\n");

    read(c_sock,buf,1024);
    printf("\nMessage from Server: %s\n",buf);


    int matrix[20][20];
    struct node rt[20];
    int nodes;

    printf("\nEnter the number of nodes: ");
    scanf(" %d",&nodes);
    write(c_sock,&nodes,sizeof(nodes));

    printf("\nEnter the cost matrix:\n");
    for(int i=0;i<nodes;i++)
    {
        for(int j=0;j<nodes;j++)
        {
            scanf(" %d",&matrix[i][j]);
            matrix[i][i]=0;
        }
    }

    for(int i=0;i<nodes;i++)
        for(int j=0;j<nodes;j++)
            write(c_sock,&matrix[i][j],sizeof(int));

    for(int i=0;i<nodes;i++)
        read(c_sock,&rt[i],sizeof(struct node));
    printf("\nDistance Vector Routing Table:");

    for(int i=0;i<nodes;i++)
    {
        printf("\n\nFor Router %d:",i+1);
            for(int j=0;j<nodes;j++)
                printf("\t\nDestination: %d ; Distance: %d ; Next Hop: %d",j+1,rt[i].dist[j],rt[i].hop[j]+1);
    }
    printf("\n");

    close(c_sock);
    return 0;
}

