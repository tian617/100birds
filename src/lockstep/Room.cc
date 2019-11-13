#include "Room.h"

Room::Room()
    : curWaitBeginRoomId(1),
      rooms_(),
      roomCommands_(),
      roomPlayersCount_()
{
}

void Room::addPlayer(PlayerPtr player)
{
  // means replay
  if (player->roomId() > 0)
  {
    checkPrevious(player->roomId());
  }

  if (rooms_[curWaitBeginRoomId].size() == 0)
  {
    roomCommands_[curWaitBeginRoomId] = std::string("taps:");
    roomCommands_[curWaitBeginRoomId].reserve(1024);
    // roomPlayersCount_[curWaitBeginRoomId] = 0;
    Timer::instance()->runAfter(std::bind(&Room::beginGame, this), kWaitTime_);
  }
  roomPlayersCount_[curWaitBeginRoomId]++;

  // single thread not need lock
  player->setRoomId(curWaitBeginRoomId);
  rooms_[curWaitBeginRoomId].push_back(player);
  player->setPlayerInRoomId(rooms_[curWaitBeginRoomId].size());
  player->sendmsg("self:" + std::to_string(rooms_[curWaitBeginRoomId].size()));
  std::string newPlayerBroadcast = "new:" + std::to_string(player->playerInRoomId()) + "," + "type";
  for (auto &roomPlayer : rooms_[curWaitBeginRoomId])
  {
    if (player->playerInRoomId() == roomPlayer->playerInRoomId())
    {
      continue;
    }
    roomPlayer->sendmsg(newPlayerBroadcast);
  }
}

void Room::beginGame()
{
  printf("begin\n");
  for (auto &player : rooms_[curWaitBeginRoomId])
  {
    printf("send\n");
    player->sendmsg("other:start");
  }
  // Timer::instance()->runEvery(std::bind(&Room::dealTurn, this, curWaitBeginRoomId), tick_);
  curWaitBeginRoomId++;
}

void Room::addCommand(PlayerPtr player, const char *data)
{
  printf("log msg:%s\n", data);
  std::string command = roomCommands_[curWaitBeginRoomId];
  command.insert(command.size(), data);
  command.insert(command.size(), ",");
}

void Room::dealTurn(long roomId)
{
  for (auto &player : rooms_[roomId])
  {
    player->sendmsg(roomCommands_[roomId]);
  }
  roomCommands_[roomId].clear();
  roomCommands_[roomId].insert(0, "taps:");
}

void Room::checkPrevious(long roomId)
{
  if (--roomPlayersCount_[roomId] == 0)
  {
    rooms_.erase(roomId);
    roomCommands_.erase(roomId);
    roomPlayersCount_.erase(roomId);
  }
}
