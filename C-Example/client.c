#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 


#define BUFFER_SIZE 256

void DieWithError(char *message);

int main(int argc, char *argv[]) {
  int clientSock, portNo;
  socklen_t clilen;
  char buffer[BUFFER_SIZE];
  struct sockaddr_in serv_addr;
  int connectStatus, closeStatus;

  if (argc < 2) {
    fprintf(stderr,"ERROR, no port provided\n");
    exit(1);
  }


  clientSock = socket(PF_INET, SOCK_STREAM, 0);
  if(clientSock < 0)
  {
    DieWithError("socket() failed\n");
  }

  bzero((char *) &serv_addr, sizeof(serv_addr));

  portNo = atoi(argv[1]);
  serv_addr.sin_family = AF_INET; /* Internet adderss family */
  serv_addr.sin_port = htons(portNo); /* Local port */
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */

  connectStatus = connect(clientSock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

  if(connectStatus < 0) {
    DieWithError("connect() Failed");
  }

  
  send(clientSock, "Hello from C TCP Client\n", 23 , 0);

  recv(clientSock, buffer, BUFFER_SIZE,0);
  fprintf(stdout, "%s\n", buffer);


  closeStatus = close(clientSock);

  return 0;
}


void DieWithError(char *message)
{
  fprintf(stderr, "%s", message);
  exit(1);
}
