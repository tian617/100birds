#include "Server.h"
#include <functional>
#include <cstring>
#include <assert.h>

using namespace std::placeholders;

Server::Server(const std::string &ip, int port)
    : net_(new NetworkManager(ip, port)),
      curWaitingRoom_(1),
      rooms_()
{
  net_->setConnectionCallback(std::bind(&Server::onConnect, this, _1));
  net_->setMessageCallback(std::bind(&Server::onMessage, this, _1, _2));
  net_->setDisConnectCallback(std::bind(&Server::onDisConnect,this,_1));
  rooms_[curWaitingRoom_] = std::make_unique<Room>(curWaitingRoom_);
}

// connect meaes click play button
void Server::onConnect(const Connection *conn)
{
  printf("new client:%s\n", conn->name().c_str());
  std::shared_ptr<Player> player = std::make_shared<Player>(conn);
  players_[conn] = player;
}

void Server::onMessage(const Connection *conn, const char *data)
{
  printf("msg:%s\n", data);
  auto message = GetMessage(data);
  switch (message->type())
  {
  case Type_Play:
    printf("%d\n", message->id());
    players_[conn]->setBirdType(message->birdType());
    playMsg(players_[conn]);
    break;
  case Type_Tap:
    tapMsg(players_[conn], message->id());
    break;
  case Type_Heartbeat:
    printf("heartbeat\n");
    break;
  }
}

void Server::onDisConnect(const Connection *conn)
{
  printf("close:%s\n", conn->name().c_str());
  removePlayerInRoom(players_[conn]->roomId(), players_[conn]);
}

void Server::removePlayerInRoom(long roomId, const std::shared_ptr<Player> &player)
{
  if (roomId < 0)
    return;
  rooms_[roomId]->removePlayer(player);
  if (rooms_[roomId]->playerCount() == 0)
  {
    rooms_.erase(roomId);
  }
}

void Server::playMsg(std::shared_ptr<Player> player)
{
  printf("play\n");
  if (rooms_[curWaitingRoom_]->isStart())
  {
    printf("create new room\n");
    curWaitingRoom_++;
    rooms_[curWaitingRoom_] = std::make_unique<Room>(curWaitingRoom_);
  }
  if (player->roomId() > 0)
  {
    removePlayerInRoom(player->roomId(), player);
  }
  player->setRoomId(curWaitingRoom_);
  rooms_[curWaitingRoom_]->addPlayer(player);
}

void Server::tapMsg(std::shared_ptr<Player> player, uint8_t id)
{
  printf("id:%d,tap\n", id);
  rooms_[player->roomId()]->addTap(id);
}

void Server::heartbeatMsg(std::shared_ptr<Player> player)
{
  // todo
}

void Server::run() const
{
  printf("server run...\n");
  net_->start();
}