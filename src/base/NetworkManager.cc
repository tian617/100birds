#include "NetworkManager.h"
#include "Timer.h"
#include <arpa/inet.h>
#include <assert.h>
#include <string.h>
#include <signal.h>

using std::placeholders::_1;
typedef NetworkManager::MessageCallback MessageCallback;
typedef std::function<void(const ConnectionPtr &conn)> AddCallback;

typedef std::weak_ptr<Connection> ConnectionWeakPtr;
typedef std::function<void(const ConnectionWeakPtr& connPtr)> CloseCallback;

namespace detail
{
struct CallBack
{
  AddCallback addCb_;
  CloseCallback closeCb_;
  MessageCallback messageCb_;

  void msgHandler(const Connection* conn, const char *data)
  {
     messageCb_(conn, data);
  }
} cb;
} // namespace detail

void acceptCallback(struct evconnlistener *listener,
                    evutil_socket_t fd, struct sockaddr *address, int socklen,
                    void *ctx)
{
  signal(SIGPIPE,SIG_IGN); // avoid exist when twice close conn
  struct event_base *base = evconnlistener_get_base(listener);
  assert(base);
  ConnectionPtr conn(new Connection(base, fd));
  ConnectionWeakPtr cwp=conn;
  Connection *c=conn.get();
  conn->setCallbacks(std::bind(&detail::CallBack::msgHandler, &detail::cb, c, _1),
                     [=]() { detail::cb.closeCb_(cwp); });
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
  Timer::init(base_);
  
  struct sockaddr_in sin;
  memset(&sin, 0, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  inet_ntop(AF_INET, &sin.sin_addr, const_cast<char *>(ip.c_str()), ip.length());

  struct evconnlistener *listener = evconnlistener_new_bind(base_, acceptCallback, this,
                                                            LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE, -1,
                                                            reinterpret_cast<sockaddr *>(&sin), sizeof(sin));
  evconnlistener_set_error_cb(listener, acceptErrorCallback);

  detail::cb.closeCb_ = [&](const ConnectionWeakPtr& conn) {
    printf("close client: %s\n", conn.lock()->name().c_str());
    connects_.erase(conn.lock());
  };
}

void NetworkManager::setConnectionCallback(ConnectionCallback &&cb)
{
  detail::cb.addCb_ = [&, cb](const ConnectionPtr &conn) {
    connects_.insert(conn);
    cb(conn.get());
  };
}

void NetworkManager::setMessageCallback(MessageCallback &&cb)
{
  detail::cb.messageCb_ = std::move(cb);
}

void NetworkManager::start() const
{
  event_base_dispatch(base_);
}
