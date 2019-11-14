#include "Server.h"
#include <functional>
#include <cstring>
#include <assert.h>

using namespace std::placeholders;

Server::Server(const std::string &ip, int port)
    : net_(new NetworkManager(ip, port)),
      room_(new Room())
{
  net_->setConnectionCallback(std::bind(&Server::onConnect, this, _1));
  net_->setMessageCallback(std::bind(&Server::onMessage, this, _1, _2));
}

// connect meaes click play button
void Server::onConnect(const Connection *conn)
{
  printf("new client:%s\n", conn->name().c_str());
  std::shared_ptr<Player> player = std::make_shared<Player>(conn);
  player->sendmsg("OK");
  room_->addPlayer(player);
  players_[conn] = player;
}

void Server::onMessage(const Connection *conn, const char *data)
{
  const char *p = strchr(data, ':');
  if (p == nullptr) // play or heartbeat
  {
    if (strcmp(data, "play") == 0)
    {
      // play button
      room_->addPlayer(players_[conn]);
    }
    else if (strcmp(data, "heartbeat") == 0)
    {
      // heartbeat msg
    }
  }
  else
  {
    assert(strncmp(data, "tap", 3) == 0);
    room_->addCommand(players_[conn], data + 4);
  }
}

void Server::run() const
{
  printf("server run...\n");
  net_->start();
}