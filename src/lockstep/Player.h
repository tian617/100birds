#ifndef TANK_PLAYER_H
#define TANK_PLAYER_H

#include <memory>
#include <string>
#include "base/Connection.h"

class Player
{
public:
  Player(const Connection* connect)
      : conn_(connect)
  {
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
  const Connection* conn_;
};

#endif