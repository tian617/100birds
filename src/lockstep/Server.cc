#include "src/base/NetworkManager.h"
#include "src/base/Connection.h"
#include "src/base/Timer.h"
#include "BattleRoom.h"
#include "Player.h"

// 在房间有指定人数时，构造一条生成tank的命令
int main()
{
  NetworkManager net("127.0.0.1", 7777);
  BattleRoom room(2);
  net.setConnectionCallback([&](const Connection *conn) {
    room.addPlayer(Player(conn));
  });

  net.setMessageCallback([&](const Connection *conn, const char *data) {
    printf("--");
    room.addCommand(data);
  });

  net.start();
}