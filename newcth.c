#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include <arpa/inet.h>

#define PORT "3490" // the port client will be connecting to
#define MAXDATASIZE 255 // max number of bytes we can get at once



int main(int argc, char *argv[])
{
int sockfd, numbytes;
char buf[MAXDATASIZE];
struct addrinfo hints, *servinfo, *p;
int rv;
char s[INET6_ADDRSTRLEN];
char buffer[256];

if (argc !=2) {
fprintf(stderr,"usage: client hostname\n");
exit(1);
}


memset(&hints, 0, sizeof hints);

hints.ai_family = AF_UNSPEC;
hints.ai_socktype = SOCK_STREAM;



if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0) {
fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
return 1;
}


// loop through all the results and connect to the first we can
for(p = servinfo; p != NULL; p = p->ai_next) {

if ((sockfd = socket(p->ai_family, p->ai_socktype,p->ai_protocol)) == -1) {
perror("client: socket");
continue;
}







if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
close(sockfd);
perror("client: connect");
continue;
}

break;
}



if (p == NULL) {
fprintf(stderr, "client: failed to connect\n");
return 2;
}







              










freeaddrinfo(servinfo); // all done with this structure

  while(1)    {

 while(recv(sockfd,buffer,255,0) < 0 );


if(atoi(buffer)== -1){
                  printf("felicitation vous avez gangner l'enchere\n");
                     goto fin;}

                 if(atoi(buffer)== -2){
                  printf("vous éte elimeiner\n");
                     goto fin;}

                     if(atoi(buffer)>0){

                        printf("prix de l'echre = : %s\n",buffer);

        bzero(buffer,256);

        fgets(buffer,255,stdin);
        numbytes = send(sockfd,buffer,strlen(buffer),0);

        if (numbytes< 0) {
             printf("ERROR writing to socket");
                  break;}
}
            bzero(buffer,256);

 }

fin :
           close(sockfd); return 0; }





