#include <arpa/inet.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <string>

int main()
{
  const char *ip = "127.0.0.1";
  struct sockaddr_in sin, localAdrr;
  memset(&sin, 0, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_port = htons(7777);
  sin.sin_addr.s_addr = inet_addr(ip);
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  assert(connect(fd, reinterpret_cast<struct sockaddr *>(&sin), sizeof(sin)) != -1);

  socklen_t len = sizeof(localAdrr);
  getsockname(fd, (sockaddr *)&localAdrr, &len);
  printf("local port:%d\n", ntohs(localAdrr.sin_port));

  const char *msg = "abcdefghijklm";
  char buf[1024], data[1024];
  memset(buf, 0, sizeof(buf));
  int16_t n = strlen(msg);

  ::memcpy(buf, &n, 2);
  ::memcpy(buf + 2, msg, n);

  while (true)
  {
    write(fd, buf, n + 2);

    ::memset(data, 0, 1024);
    int nread = read(fd, data, 1024);
    data[nread] = '\0';
    printf("nread:%d,msg:%s\n", nread, data + 2);

    ::memset(data, 0, 1024);
    nread = read(fd, data, 1024);
    data[nread] = '\0';
    printf("nread:%d,msg:%s\n", nread, data + 2);

    sleep(1);
  }

  return 0;
}