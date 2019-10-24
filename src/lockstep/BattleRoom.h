#ifndef TANK_BATTLEROOM_H
#define TANK_BATTLEROOM_H

#include <string>
#include <vector>
#include <unordered_map>
#include "src/base/Timer.h"
#include "Player.h"

class BattleRoom
{
  typedef long ID;

public:
  BattleRoom(int count)
      : count_(count)
  {
  }
  void addCommand(const std::string &msg);
  void addPlayer(const Player &player);
  void dealTurn();

private:
  int count_;
  std::vector<Player> players_;
  std::vector<std::string> commands_;
};

#endif
