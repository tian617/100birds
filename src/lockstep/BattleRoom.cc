#include "BattleRoom.h"

void BattleRoom::addCommand(const std::string &msg)
{
  commands_.push_back(std::move(msg));
}

void BattleRoom::addPlayer(const Player &player)
{
  players_.push_back(player);
}

void BattleRoom::dealTurn()
{
  std::vector<int> delPlayerIdxs;
  for (int i = 0; i < commands_.size(); i++)
  {
    for (int j = 0; j < players_.size(); j++)
    {
      if (players_[j].connected())
      {
        players_[j].sendmsg(commands_[i]);
      }
      else
      {
        delPlayerIdxs.push_back(i);
      }
    }

    for (int i = delPlayerIdxs.size() - 1; i >= 0; i--)
    {
      players_.erase(players_.begin() + i);
    }
  }
}