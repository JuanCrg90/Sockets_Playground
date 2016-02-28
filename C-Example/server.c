#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void DieWithError(char *message);

int main(int argc, char *argv[]) {
  int serverSock, clientSock, portNo;
  socklen_t clilen;
  struct sockaddr_in serv_addr, cli_addr;
  int closeStatus;

  if (argc < 2) {
    fprintf(stderr,"ERROR, no port provided\n");
    exit(1);
  }
  serverSock = socket(PF_INET, SOCK_STREAM, 0);
  if(serverSock < 0)
  {
    DieWithError("socket() failed\n");
  }

  bzero((char *) &serv_addr, sizeof(serv_addr));

  portNo = atoi(argv[1]);
  serv_addr.sin_family = AF_INET; /* Internet adderss family */
  serv_addr.sin_port = htons(portNo); /* Local port */
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */

  if( bind(serverSock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
  {
    DieWithError("bind() failed\n");
  }

  if( listen(serverSock, 5) < 0 )
  {
    DieWithError("listen() failed\n");
  }

  while(1)
  {
    clilen = sizeof(cli_addr);

    clientSock = accept(serverSock, (struct sockaddr *) &cli_addr, &clilen);

    if(clientSock < 0) 
    {
      DieWithError("accept() failed\n");
      break;
    }
    else {
      fprintf(stdout, "connected");
    }

   send(clientSock, "Hello TCP", 10 , 0);

  }

  closeStatus = close(serverSock);

  return 0;
}


void DieWithError(char *message)
{
  fprintf(stderr, "%s", message);
  exit(1);
}
