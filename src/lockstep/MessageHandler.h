#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "flatbuffers/message_generated.h"
#include <functional>
#include "src/base/NetworkManager.h"
#include "src/base/Connection.h"
#include "src/base/Timer.h"
#include "src/lockstep/Room.h"
#include <string>
#include <memory>
#include <unordered_map>
#include "Player.h"

using namespace FlappyBird;
class MessageHandler
{
  typedef std::function<void(std::shared_ptr<Player> player, BirdType birdType)> PlayCallback;
  typedef std::function<void(std::shared_ptr<Player> player, uint8_t id)> TapCallback;
  typedef std::function<void(std::shared_ptr<Player> player)> HeartbeatCallback;

public:
  MessageHandler() {}
  void setPlayCallback(PlayCallback cb)
  {
    playCb_ = cb;
  }

  void setTapCallback(TapCallback cb)
  {
    tapCb_ = cb;
  }

  void setHeartbeatCallback(HeartbeatCallback cb)
  {
    heartbeatCb_ = cb;
  }

  void handle(std::shared_ptr<Player> player, const char *data)
  {
    flatbuffers::FlatBufferBuilder builder(1024);
    auto message = GetMessage(data);
    switch (message->type())
    {
    case Type_Play:
      playCb_(player, message->birdType());
      break;
    case Type_Tap:
      tapCb_(player, message->id());
      break;
    case Type_Heartbeat:
      heartbeatCb_(player);
      break;
    }
  }

private:
  PlayCallback playCb_;
  TapCallback tapCb_;
  HeartbeatCallback heartbeatCb_;
};

#endif