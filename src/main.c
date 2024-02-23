#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 3012

#pragma pack(push, 1)
struct Addr
{
  uint32_t addr;
  uint16_t port;
};
#pragma pack(pop)

int main()
{
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
  {
    perror("socket() failed");
    return 1;
  }
  struct sockaddr_in serverAddr = {};
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddr.sin_port = htons(PORT);

  const int enable = 1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
  {
    perror("setsockopt(SO_REUSEADDR) failed");
    return 1;
  }

  struct linger optval;

  optval.l_onoff = 1;
  optval.l_linger = 3;

  if (setsockopt(sockfd, SOL_SOCKET, SO_LINGER, (char *)&optval, sizeof(optval)) < 0)
  {
    perror("setsockopt(SO_LINGER) failed");
    return 1;
  }

  if (bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
  {
    perror("bind() failed");
    return 1;
  }

  if (listen(sockfd, 5) == -1)
  {
    perror("listen() failed");
    return 1;
  }

  while (1)
  {
    struct sockaddr_in clientAddr = {};
    socklen_t clientAddrSize = sizeof(clientAddr);
    int clientSockfd = accept(sockfd, (struct sockaddr *)&clientAddr, &clientAddrSize);
    if (clientSockfd == -1)
    {
      perror("accept() failed");
      continue;
    }

    struct Addr addr = {clientAddr.sin_addr.s_addr, clientAddr.sin_port};

    struct in_addr paddr;
    paddr.s_addr = addr.addr;

    printf("%s:%hu\n", inet_ntoa(paddr), htons(addr.port));

    if (write(clientSockfd, &addr, sizeof(addr)) < 0)
    {
      perror("write failed");
    }

    // prevent from passing packet with FIN
    char buffer[] = "END";
    if (write(clientSockfd, buffer, sizeof(buffer)) < 0)
    {
      perror("write failed");
    }

    close(clientSockfd);
  }
  return 0;
}