#include "Room.h"

Room::Room(int id)
    : start_(false),
      id_(id),
      players_(),
      birds_()
{
  taskStart_ = Timer::instance()->runAfter(std::bind(&Room::gameStart, this), kWaitTime_);
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
  birds_[playId] = player->getBirdType();
  MessageBuilder message(builder);
  message.add_type(Type_SelfInfo);
  message.add_id(playId);
  struct timeval tv;
  gettimeofday(&tv, nullptr);
  long int now = tv.tv_sec * kSecToUsec + tv.tv_usec;
  message.add_timeWaiting(kWaitTime_ - (now - initTime_) / (float)kSecToUsec);
  auto msg = message.Finish();
  builder.Finish(msg);

  player->sendmsg(builder.GetBufferPointer(), builder.GetSize());
  players_.insert(player);

  if (playId == kRoomLimit_)
  {
    printf("cancel task\n");
    Timer::instance()->cancel(taskStart_);
    gameStart();
  }
}

void Room::removePlayer(PlayerPtr player)
{
  players_.erase(player);
}

int Room::playerCount() const
{
  return players_.size();
}

bool Room::isStart() const
{
  return start_;
}

// tofix
void Room::gameStart()
{
  printf("room start\n");
  start_ = true;
  if (players_.size() == 0)
    return;
  flatbuffers::FlatBufferBuilder builder(1024);
  std::vector<flatbuffers::Offset<BirdInfo>> birdInfos;
  for (auto &bird : birds_)
  {
    birdInfos.push_back(CreateBirdInfo(builder, bird.first, bird.second));
  }
  auto birds = builder.CreateVector(birdInfos);
  MessageBuilder message(builder);
  message.add_type(Type_Start);
  message.add_birds(birds);
  message.add_seed(time(nullptr));
  auto msg = message.Finish();
  builder.Finish(msg);
  for (auto &player : players_)
  {
    player->sendmsg(builder.GetBufferPointer(), builder.GetSize());
  }
  Timer::instance()->runEvery(std::bind(&Room::turn, this), tick_);
}

void Room::turn()
{
  flatbuffers::FlatBufferBuilder builder(1024);
  auto taps = builder.CreateVector(taps_);
  MessageBuilder message(builder);
  message.add_type(Type_Turn);
  message.add_ids(taps);
  auto msg = message.Finish();
  builder.Finish(msg);
  for (auto &player : players_)
  {
    player->sendmsg(builder.GetBufferPointer(), builder.GetSize());
  }
  taps_.clear();
}
