#include "base/NetworkManager.h"
#include "base/Connection.h"
#include "base/Timer.h"
#include "BattleRoom.h"
#include "Player.h"

int main()
{
  NetworkManager net("127.0.0.1", 7777);
  BattleRoom room;
  net.setConnectionCallback([&](const Connection *conn) {
    room.addPlayer(Player(conn));
  });

  net.setMessageCallback([&](const Connection *conn, const char *data) {
    room.addCommand(data);
  });

  Timer::instance()->runEvery([&]() {
    room.dealTurn();
  },
                              0.1f);

  net.start();
}