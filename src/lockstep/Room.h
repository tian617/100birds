#ifndef TANK_BATTLEROOM_H
#define TANK_BATTLEROOM_H

#include <string>
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include <time.h>
#include "src/base/Timer.h"
#include "Player.h"
#include "flatbuffers/message_generated.h"

using namespace FlappyBird;
class Room
{
  typedef long ID;
  typedef std::shared_ptr<Player> PlayerPtr;

public:
  Room(int id);
  void addTap(uint8_t id);
  void addPlayer(PlayerPtr player);
  void removePlayer(PlayerPtr player);
  int playerCount() const;
  bool isStart() const;

private:
  const int kRoomLimit_ = 64;
  const float kWaitTime_ = 3.0f;
  const float tick_ = 1 / 30.0f;
  const int kSecToUsec = 1000 * 1000;

  void turn();
  void gameStart();

  bool start_;
  int id_;
  long int initTime_;
  int taskStart_;
  std::vector<uint8_t> taps_;
  std::unordered_set<PlayerPtr> players_;
  std::unordered_map<uint8_t,BirdType> birds_;
};

#endif
