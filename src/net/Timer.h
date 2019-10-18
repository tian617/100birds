#ifndef TANK_NET_TIMER_H
#define TANK_NET_TIMER_H

#include <event2/event.h>
#include <functional>

typedef std::function<void()> ExpiredCallback;
class Timer
{
public:
  explicit Timer(struct event_base * base);

  int runEvery(ExpiredCallback cb, float second);

  int runAfter(ExpiredCallback cb, float second);

  void cancel(int taskId);

private:
  int setCb(ExpiredCallback cb, float second,bool once);

  struct event_base *base_;
};

#endif