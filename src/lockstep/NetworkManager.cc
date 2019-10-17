#include "NetworkManager.h"
#include <arpa/inet.h>
#include <assert.h>
#include <string.h>

using std::placeholders::_1;
typedef NetworkManager::ConnectionPtr ConnectionPtr;
typedef NetworkManager::MessageCallback MessageCallback;
typedef std::function<void(const ConnectionPtr &conn)> AddCallback;
typedef std::function<void(const ConnectionPtr &conn)> CloseCallback;

namespace detail
{
struct CallBack
{
  AddCallback addCb_;
  CloseCallback closeCb_;
  MessageCallback messageCb_;

  void msgHandler(const ConnectionPtr &conn, const char *data)
  {
    messageCb_(conn, data);
  }

} cb;
} // namespace detail

void acceptCallback(struct evconnlistener *listener,
                    evutil_socket_t fd, struct sockaddr *address, int socklen,
                    void *ctx)
{
  struct event_base *base = evconnlistener_get_base(listener);
  assert(base);
  ConnectionPtr conn(new Connection(base, fd));
  conn->setCallbacks(std::bind(&detail::CallBack::msgHandler, &detail::cb, conn, _1),
                     [=]() { detail::cb.closeCb_(conn); });
  detail::cb.addCb_(conn);
}

void acceptErrorCallback(struct evconnlistener *listener, void *ctx)
{
  struct event_base *base = evconnlistener_get_base(listener);
  int err = EVUTIL_SOCKET_ERROR();
  fprintf(stderr, "Got an error %d (%s) on the listener. Shutting down.\n",
          err, evutil_socket_error_to_string(err));
  event_base_loopexit(base, NULL);
}

NetworkManager::NetworkManager(std::string ip, int port)
    : base_(event_base_new()),
      connects_()
{
  struct sockaddr_in sin;
  memset(&sin, 0, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  inet_ntop(AF_INET, &sin.sin_addr, const_cast<char *>(ip.c_str()), ip.length());

  struct evconnlistener *listener = evconnlistener_new_bind(base_, acceptCallback, this,
                                                            LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE, -1,
                                                            reinterpret_cast<sockaddr *>(&sin), sizeof(sin));
  evconnlistener_set_error_cb(listener, acceptErrorCallback);
  
  detail::cb.closeCb_ = [&](const ConnectionPtr &conn) { connects_.erase(conn); };
}

void NetworkManager::setConnectionCallback(ConnectionCallback &&cb)
{
  detail::cb.addCb_ = [&, cb](const ConnectionPtr &conn) {
    connects_.insert(conn);
    cb(conn);
  };
}

void NetworkManager::setMessageCallback(MessageCallback &&cb)
{
  detail::cb.messageCb_ = std::move(cb);
}

void NetworkManager::run() const
{
  event_base_dispatch(base_);
}
