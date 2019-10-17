#ifndef TANK_LOCKSTEP_NETWORKMANAGER
#define TANK_LOCKSTEP_NETWORKMANAGER

#include <event2/event.h>
#include <event2/listener.h>
#include <functional>
#include <memory>
#include <string>
#include <set>
#include "Connection.h"

class NetworkManager
{

public:
  typedef std::shared_ptr<Connection> ConnectionPtr;
  typedef std::function<void(const ConnectionPtr &conn)> ConnectionCallback;
  typedef std::function<void(const ConnectionPtr &conn, const char *data)> MessageCallback;

  explicit NetworkManager(std::string ip, int port);

  void setConnectionCallback(ConnectionCallback &&cb);

  void setMessageCallback(MessageCallback &&cb);

  void run() const;

private:
  struct event_base *base_;
  std::set<ConnectionPtr> connects_;
};

#endif
