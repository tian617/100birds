#ifndef TANK_NET_NETWORKMANAGER_H
#define TANK_NET_NETWORKMANAGER_H

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
  typedef std::function<void(const Connection* conn)> ConnectionCallback;
  typedef std::function<void(const Connection* conn, const char *data)> MessageCallback;

  explicit NetworkManager(std::string ip, int port);

  void setConnectionCallback(ConnectionCallback &&cb);

  void setMessageCallback(MessageCallback &&cb);

  void start() const;

private:
  struct event_base *base_;
  std::set<ConnectionPtr> connects_;
};

#endif
