#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#define timediff 0.8
struct datastruct
{
  int packetno;
  char buffer[100];
};
struct datastruct mystr;
int main()
{
    struct sockaddr_in server;
    int s,n,filevar;
    int tmp=0,i=0,k;
    char buff[100];
    FILE *fp;
    s=socket(AF_INET,SOCK_DGRAM,0);
    server.sin_family=AF_INET;
    server.sin_port=2000;
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
   // server.sin_addr.s_addr=inet_addr("10.42.0.42 ");
    bind(s,(struct sockaddr *)&server,sizeof(server));
    printf("\nServer ready,waiting for client....\n");
    n=sizeof(server);
    bzero(&mystr,sizeof(mystr));
    
    recvfrom(s,&mystr,sizeof(mystr),0,(struct sockaddr *) &server,&n);
    printf("server has got this file:%s\n",mystr.buffer);
    fp=fopen(mystr.buffer,"w+");
    
    
    while(1)
    {  
        
          recvfrom(s,&mystr,sizeof(mystr),0,(struct sockaddr *) &server,&n);
            
             
             if(mystr.packetno==-1)
               {
		 sendto(s,&mystr.packetno,4,0,(struct sockaddr *) &server,n);
				 while(1)
				 {
				   if(mystr.buffer[i]=='\0')	 
			           break;
			           fputc(mystr.buffer[i++],fp);
                        	}
                 // printf("%s",mystr.buffer);	
		          break;
	     }
                fseek(fp,(mystr.packetno-1)*100,SEEK_SET); 
		 fwrite(mystr.buffer,1,sizeof(mystr.buffer),fp);
			  
       
			     sendto(s,&mystr.packetno,4,0,(struct sockaddr *) &server,n); 
			   
			//  printf("%s",mystr.buffer);
             
             
           printf("\nServer has got packet no and sent this no:%d\n",mystr.packetno);
          
         

           bzero(&mystr,sizeof(mystr));
            system("sleep 1 "); // time difference

    }
    printf("bi***************************\n");
    fclose(fp);
    return 0;
}
/*
* first run server then client..
* how to run server..
$gcc gobkn_server.c -lpthread -o server
$./server
.
.
.
enjoy
*/
