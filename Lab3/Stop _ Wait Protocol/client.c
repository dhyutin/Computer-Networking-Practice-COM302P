#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

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
    struct sockaddr_in serverAddr;
    char buf[100];
    socklen_t addr_size;
    
    int frame_no = 0;
    frame send;
    frame recv;
    
    int ack_recv = 1;
    //ipv4 , udpm, Internet protocol
    sock = socket(AF_INET, SOCK_DGRAM, 0);
	
    //allocate memory to the port(local host , port 9009)
    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9009);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    int check = 1;
    while(check)
    {
        if ( ack_recv == 1)
        {
            send.seq_no = frame_no;
            send.frame_type = 1;
            send.ack = 0;
            
            printf("Enter Data : ");
            scanf("%s", buf);
            strcpy(send.pack.data, buf);
            
            sendto(sock, &send, sizeof(send), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
            printf("Frame Sent\n");
        }
        
        int addr_size = sizeof(serverAddr);
        
        int recv_size = recvfrom(sock, &recv, sizeof(recv),0 ,(struct sockaddr*)&serverAddr, &addr_size);
        
        if (recv_size > 0 && recv.seq_no == 0 && recv.ack == frame_no + 1)
        {
            printf("Acknowledgement Received\n");
            ack_recv = 1;
        }
        else
        {
            printf("Acknowledgement Not Received\n");
            ack_recv = 0;
        }
        frame_no = frame_no + 1;
        
        printf("Send another frame?(0/1)\n");
        scanf("%d",&check);
    }
    printf("End of Communication\n");
    
    //close(sock);
    return 0;
}
