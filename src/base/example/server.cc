#include "../NetworkManager.h"
#include "../Connection.h"
#include "../Timer.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std::placeholders;
typedef std::shared_ptr<Connection> ConnectionPtr;

int main()
{
  NetworkManager net("127.0.0.1", 7777);
  net.setConnectionCallback([](const Connection *conn) {
    std::cout << "new client" << conn->name() << "\n";
    ConnectionWeak cw = conn->getWeak();
    int taskId = Timer::instance()->runEvery([=]() {
      printf("task\n");
      if (!cw.expired())
      {
        cw.lock()->send(std::to_string(time(NULL)));
      }
      else
      {
        printf("skip task\n");
      }
    },
                                             0.1f);
    printf("taskid:%d\n", taskId);
  });

  net.setMessageCallback([](const Connection *conn, const char *data) {
    printf("data:%s\n", data);
    conn->send("hello");
  });
  net.start();
}