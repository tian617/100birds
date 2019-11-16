#ifndef TANK_PLAYER_H
#define TANK_PLAYER_H

#include <memory>
#include <string>
#include "src/base/Connection.h"
#include "flatbuffers/message_generated.h"

class Player
{
public:
  Player(const Connection *connect)
      : conn_(connect),
        id_(-1),
        roomId_(-1),
        tap_(false)
  {
  }

  Player(const Connection *conn, BirdType type);

  long roomId() const
  {
    return roomId_;
  }

  uint8_t id() const
  {
    return id_;
  }

  void setRoomId(long id)
  {
    roomId_ = id;
  }

  void setId(uint8_t id)
  {
    id_ = id;
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

  void sendmsg(const void *msg, size_t len) const
  {
    conn_->send(msg, len);
  }

  BirdType getBirdType() const
  {
    return type_;
  }

private:
  const Connection *conn_;

  uint8_t id_;
  long roomId_;
  bool tap_;
  BirdType type_;
};

#endif