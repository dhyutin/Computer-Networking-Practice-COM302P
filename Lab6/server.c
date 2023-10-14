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
    int s_sock,new_sock;
    char msg[1024] ="Hello Client! Welcome!";
    struct sockaddr_in address;
    char buf[1024] = {0};
    int opt = 1;
    int addr_len = sizeof(address);

    address.sin_family=AF_INET;
    address.sin_port=htons(9009);
    address.sin_addr.s_addr=INADDR_ANY;

    if((s_sock=socket(AF_INET,SOCK_STREAM,0)) == 0)
    {
        perror("\nSocket Failed!\n");
        return -1;
    }

    if(setsockopt(s_sock,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&opt,sizeof(opt)))
    {
        perror("\nSocket Reuse Error!\n");
        return -1;
    }

    if(bind(s_sock,(struct sockaddr*)&address,sizeof(address)) < 0)
    {
        perror("\nBind Failire\n");
        return -1;
    }

    if(listen(s_sock,3) < 0)
    {
        perror("\nListen Failure!\n");
        return -1;
    }

    if((new_sock = accept(s_sock,(struct sockaddr*)&address,(socklen_t*)&addr_len)) < 0)
    {
        perror("\nAccept Failure!\n");
        return-1;
    }

    read(new_sock,buf,1024);
    printf("Message from Client: %s\n",buf);

    send(new_sock,msg,sizeof(msg),0);
    printf("Server Message Sent!!!\n");

    int count,nodes;
    struct node rt[20];
    int matrix[20][20];

    read(new_sock,&nodes,sizeof(nodes));
    printf("\nCalculating Routing Table!!!\n");

    for(int i=0;i<nodes;i++)
    {
        for(int j=0;j<nodes;j++)
        {
            read(new_sock,&matrix[i][j],sizeof(int));

            // Initialise the distance equal to cost matrix
            rt[i].dist[j]=matrix[i][j];
            rt[i].hop[j]=j;
        }
    }

    do
    {
        count = 0;
        for(int i=0;i<nodes;i++)
        for(int j=0;j<nodes;j++)
        for(int k=0;k<nodes;k++)
            if(rt[i].dist[j] > matrix[i][k] + rt[k].dist[j])
            {
                rt[i].dist[j] =  rt[i].dist[k] + rt[k].dist[j];
                rt[i].hop[j] = k;
                count++;
            }
    } while(count != 0);

    for(int i=0;i<nodes;i++)
        write(new_sock,&rt[i],sizeof(struct node));
    printf("\nDistance Vector Routing Table Sent!!!\n");

    return 0;
}
