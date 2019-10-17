#include "Connection.h"
#include <string.h>
#include <assert.h>

#define EvbufferHeadLength 2

namespace cb
{
void readCallback(struct bufferevent *bev, void *conn)
{
  printf("read\n");
  struct evbuffer *input = bufferevent_get_input(bev);
  size_t len = evbuffer_get_length(input);
  printf("data len:%ld\n",len);

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


  // fix use length
  int arraySize = n + EvbufferHeadLength + 1;
  char data[arraySize];
  evbuffer_remove(input, data, arraySize - 1);
  data[arraySize - 1] = '\0';
  Connection *connection = static_cast<Connection *>(conn);
  connection->msgcb()(data + EvbufferHeadLength);
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
    : bev_(NULL)
{
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

void Connection::close() const
{
  assert(closeCb_);
  closeCb_();
}