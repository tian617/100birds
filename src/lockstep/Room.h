#ifndef TANK_BATTLEROOM_H
#define TANK_BATTLEROOM_H

#include <string>
#include <vector>
#include <unordered_map>
#include "src/base/Timer.h"
#include "Player.h"

class Room
{
  typedef long ID;
  typedef std::shared_ptr<Player> PlayerPtr;

public:
  Room();
  void addCommand(PlayerPtr player, const char *data);
  void addPlayer(PlayerPtr player);

private:
  const int kRoomLimit = 64;
  const float kWaitTime = 10.0f;
  const float tick_ = 1 / 30.0f;

  void beginGame();
  void dealTurn(long roomId);
  void checkPrevious(long roomId);

  long curWaitBeginRoomId;
  std::unordered_map<long, std::vector<PlayerPtr>> rooms_;
  std::unordered_map<long, std::string> roomCommands_;
  // when player add to other room, not delete from previous room, but reduce room count
  std::unordered_map<long,int> roomPlayersCount_; 
};

#endif
