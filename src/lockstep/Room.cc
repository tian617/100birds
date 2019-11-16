#include "Room.h"

// Room::Room()
//     : curWaitBeginRoomId(1),
//       rooms_(),
//       roomCommands_(),
//       roomPlayersCount_()
// {
// }

Room::Room(int id)
    : id_(id),
      players_(),
      birds_()
{
  Timer::instance()->runAfter(std::bind(&Room::gameStart, this), kWaitTime_);
  struct timeval tv;
  gettimeofday(&tv, nullptr);
  initTime_ = tv.tv_sec * kSecToUsec + tv.tv_usec;
}

void Room::addTap(uint8_t id)
{
  taps_.push_back(id);
}

void Room::addPlayer(PlayerPtr player)
{
  flatbuffers::FlatBufferBuilder builder(1024);
  int playId = players_.size();
  auto info = CreateBirdInfo(builder, playId, player->getBirdType());
  birds_.push_back(std::move(info));
  builder.Clear();
  MessageBuilder message(builder);
  message.add_id(playId);
  struct timeval tv;
  gettimeofday(&tv, nullptr);
  long int now = tv.tv_sec * kSecToUsec + tv.tv_usec;
  message.add_timeWaiting(kWaitTime_ - (now - initTime_) / (float)kSecToUsec);
  message.Finish();
  player->sendmsg(builder.GetBufferPointer(), builder.GetSize());
  players_.insert(player);
}

void Room::removePlayer(PlayerPtr player)
{
  players_.erase(player);
}

int Room::playerCount() const
{
  return players_.size();
}

void Room::gameStart()
{
  if (players_.size() == 0)
    return;
  flatbuffers::FlatBufferBuilder builder(1024);
  MessageBuilder message(builder);
  message.add_type(Type_Start);
  message.add_birds(builder.CreateVector(birds_));
  message.Finish();
  for (auto &player : players_)
  {
    player->sendmsg(builder.GetBufferPointer(), builder.GetSize());
  }
  Timer::instance()->runEvery(std::bind(&Room::turn, this), tick_);
}

void Room::turn()
{
  flatbuffers::FlatBufferBuilder builder(1024);
  MessageBuilder message(builder);
  message.add_ids(builder.CreateVector(taps_));
  message.Finish();
  for (auto &player : players_)
  {
    player->sendmsg(builder.GetBufferPointer(), builder.GetSize());
  }
  taps_.clear();
}
