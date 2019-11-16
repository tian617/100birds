#include "Connection.h"
#include <string.h>
#include <assert.h>
#include <arpa/inet.h>

#define EvbufferHeadLength 2

namespace cb
{
void readCallback(struct bufferevent *bev, void *conn)
{
  struct evbuffer *input = bufferevent_get_input(bev);

  while (true)
  {
    size_t len = evbuffer_get_length(input);

    if (len < EvbufferHeadLength)
    {
      return;
    }
    char header[EvbufferHeadLength];
    evbuffer_copyout(input, header, EvbufferHeadLength);
    int16_t n;
    ::memcpy(&n, header, EvbufferHeadLength);
    if (len - EvbufferHeadLength < n)
    {
      return;
    }

    int arraySize = n + EvbufferHeadLength + 1;
    char data[arraySize];
    evbuffer_remove(input, data, arraySize - 1);
    data[arraySize - 1] = '\0';
    Connection *connection = static_cast<Connection *>(conn);
    connection->msgcb()(data + EvbufferHeadLength);
  }
}

void eventCallback(struct bufferevent *bev, short events, void *conn)
{
  if (events & BEV_EVENT_ERROR)
    perror("Error from bufferevent");
  if (events & (BEV_EVENT_EOF | BEV_EVENT_ERROR))
  {
    bufferevent_free(bev);
    Connection *connection = static_cast<Connection *>(conn);
    connection->close();
  }
}
} // namespace cb

typedef Connection::MessageCallback MessageCallback;
Connection::Connection(struct event_base *base, evutil_socket_t fd)
    : bev_(NULL),
      alive_(true)
{
  setName(fd);
  bev_ = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
  bufferevent_setcb(bev_, cb::readCallback, NULL, cb::eventCallback, this);
  bufferevent_enable(bev_, EV_READ);
}

void Connection::setCallbacks(MessageCallback msgCb, CloseCallback closeCb)
{
  closeCb_ = closeCb;
  msgCb_ = msgCb;
}

const MessageCallback &Connection::msgcb()
{
  assert(msgCb_);
  return msgCb_;
}

void Connection::close()
{
  assert(closeCb_);
  closeCb_();
  alive_ = false;
}

void Connection::send(const void *data, int len) const
{
  struct evbuffer *evbuf = evbuffer_new();
  evbuffer_add(evbuf, &len, EvbufferHeadLength);
  evbuffer_add(evbuf, data, len);
  bufferevent_write_buffer(bev_, evbuf);
}

void Connection::send(const char *data) const
{
  send(data, strlen(data));
}

void Connection::send(const std::string &data) const
{
  send(data.c_str());
}

std::string Connection::name() const
{
  return name_;
}

std::weak_ptr<const Connection> Connection::getWeak() const
{
  return shared_from_this();
}

void Connection::setName(int fd)
{
  struct sockaddr_in sin;
  socklen_t len = sizeof(sin);
  getpeername(fd, reinterpret_cast<sockaddr *>(&sin), &len);
  name_ = std::string(inet_ntoa(sin.sin_addr)) + ":" + std::to_string(ntohs(sin.sin_port));
}

bool Connection::alive() const
{
  return alive_;
}