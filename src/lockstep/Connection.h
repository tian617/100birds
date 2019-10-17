#ifndef TANK_LOCKSTEP_CONNECTION
#define TANK_LOCKSTEP_CONNECTION

#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <functional>
#include <memory>

class Connection
{

public:
  typedef std::function<void(const char *data)> MessageCallback;
  typedef std::function<void()> CloseCallback;

  explicit Connection(struct event_base *base, evutil_socket_t fd);

  void setCallbacks(MessageCallback msgCb, CloseCallback closeCb);

  const MessageCallback &msgcb();

  void close() const;

private:
  CloseCallback closeCb_;
  MessageCallback msgCb_;
  struct bufferevent *bev_;
};

#endif
