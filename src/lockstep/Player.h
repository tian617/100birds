#ifndef TANK_PLAYER_H
#define TANK_PLAYER_H

#include <memory>
#include <string>
#include "src/base/Connection.h"

class Player
{
public:
  Player(const Connection *connect)
      : conn_(connect),
        playerInRoomId_(-1),
        roomId_(-1),
        tap_(false)
  {
  }

  long roomId() const
  {
    return roomId_;
  }

  int playerInRoomId() const
  {
    return playerInRoomId_;
  }

  void setRoomId(long id)
  {
    roomId_ = id;
  }

  void setPlayerInRoomId(int id)
  {
    playerInRoomId_ = id;
  }

  void setTap(bool tap)
  {
    tap_ = tap;
  }

  bool connected() const
  {
    return conn_->alive();
  }

  void sendmsg(const std::string &msg) const
  {
    conn_->send(msg);
  }

private:
  const Connection *conn_;
  int playerInRoomId_;
  long roomId_;
  bool tap_;
};

#endif