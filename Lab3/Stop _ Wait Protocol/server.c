#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include <arpa/inet.h>

// Define data packers
typedef struct packet{
    char data[100];
}packet;

// create data frame
typedef struct data_frame{
    int frame_type; // 0 = ack; 1 = sequence
    int seq_no;
    int ack;
    packet pack;
}frame;


int main()
{
    int sock;
    struct sockaddr_in serverAddr, newAddr;
    char buf[100];
    socklen_t addr_size;
    
    int frame_no = 0;
    
    frame send;
    frame recv;
    
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9009);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    
    bind(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    addr_size = sizeof(newAddr);
    
    while (1)
    {
        int recv_size = recvfrom(sock, &recv, sizeof(recv), 0, (struct sockaddr*)&newAddr, &addr_size);
        printf("%d", recv_size);
        
        if (recv_size > 0 && recv.frame_type == 1 && recv.seq_no == frame_no)
        {
            printf("Received Frame : %s\n", recv.pack.data);
            
            send.seq_no = 0;
            send.frame_type = 0;
            send.ack = recv.seq_no + 1;
            
            sendto(sock, &send, sizeof(frame), 0,(struct sockaddr*)&newAddr, addr_size);
            
            printf("Acknowledgement Sent\n");
        }
        else
        {
            printf("Frame Not Received\n");
        }
        frame_no = frame_no + 1;
    }
    
    //close(sock);
    return 0;
}


