#include "Server.h"
#include <functional>

using std::placeholders::_1;

Server::Server(const std::string &ip, int port)
    : net_(new NetworkManager(ip, port)),
      room_()
{
  net_->setConnectionCallback(std::bind(&Server::onConnect,this,_1));
}

void Server::onConnect(const Connection *conn)
{
  conn->send("OK");
  room_->addPlayer(Player(conn));
}

// 在房间有指定人数时，构造一条生成tank的命令
// int main()
// {
//   NetworkManager net("127.0.0.1", 7777);
//   BattleRoom room(1);
//   net.setConnectionCallback([&](const Connection *conn) {
//     room.addPlayer(Player(conn));
//   });

//   net.setMessageCallback([&](const Connection *conn, const char *data) {
//     printf("--");
//     room.addCommand(data);
//   });

//   net.start();
// }