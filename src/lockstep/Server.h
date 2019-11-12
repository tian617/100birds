#ifndef SRC_LOCKSTEP_SERVER_H
#define SRC_LOCKSTEP_SERVER_H

#include "src/base/NetworkManager.h"
#include "src/base/Connection.h"
#include "src/base/Timer.h"
#include "src/lockstep/Room.h"
#include <string>
#include <memory>
#include <unordered_map>

class Server
{
public:
  Server(const std::string &ip, int port);
  void run() const;

private:
  void onConnect(const Connection *conn);
  void onMessage(const Connection *conn, const char *data);
  
  std::unique_ptr<NetworkManager> net_;
  std::unique_ptr<Room> room_;
  std::unordered_map<const Connection*,std::shared_ptr<Player>> players_;
};

#endif
