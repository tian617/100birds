#ifndef TANK_NET_CONNECTION_H
#define TANK_NET_CONNECTION_H

#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <functional>
#include <memory>
#include <string>

class Connection : public std::enable_shared_from_this<Connection>
{

public:
  typedef std::function<void(const char *data)> MessageCallback;
  typedef std::function<void()> CloseCallback;

  explicit Connection(struct event_base *base, evutil_socket_t fd);

  void setCallbacks(MessageCallback msgCb, CloseCallback closeCb);

  const MessageCallback &msgcb();

  void close() const;

  void send(const char *data, int len) const;

  void send(const char *data) const;

  void send(const std::string &data) const;

  std::string name() const;

  std::weak_ptr<const Connection> getWeak() const;

private:
  void setName(int fd);

  CloseCallback closeCb_;
  MessageCallback msgCb_;
  struct bufferevent *bev_;
  std::string name_;
};

typedef std::weak_ptr<const Connection> ConnectionWeak;

#endif
