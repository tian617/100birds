#ifndef SRC_LOCKSTEP_SERVER_H
#define SRC_LOCKSTEP_SERVER_H

#include "src/base/NetworkManager.h"
#include "src/base/Connection.h"
#include "src/base/Timer.h"
#include "Room.h"
#include <set>
#include <string>

class Server
{
public:
  Server(const std::string &ip, int port);

private:
  void onConnect(const Connection *conn);

  std::unique_ptr<NetworkManager> net_;
  std::unique_ptr<Room> room_;
};

#endif
