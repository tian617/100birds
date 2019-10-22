#ifndef TANK_BATTLEROOM_H
#define TANK_BATTLEROOM_H

#include <string>
#include <vector>
#include <unordered_map>
#include "base/Timer.h"
#include "Player.h"

class BattleRoom
{
  typedef long ID;

public:
  void addCommand(const std::string& msg);
  void addPlayer(const Player& player);
  void dealTurn();
private:
  std::vector<Player> players_;
  std::vector<std::string> commands_;
};

#endif
