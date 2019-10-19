#ifndef TANK_NET_TIMER_H
#define TANK_NET_TIMER_H

#include <event2/event.h>
#include <functional>
#include <memory>

typedef std::function<void()> ExpiredCallback;
class Timer
{

public:
  Timer(const Timer &) = delete;
  void operator=(const Timer &) = delete;
  static void init(struct event_base *base);

  static std::shared_ptr<Timer> instance();

  int runEvery(ExpiredCallback cb, float second);

  int runAfter(ExpiredCallback cb, float second);

  void cancel(int taskId);

private:
  explicit Timer(struct event_base *base);
  int setCb(ExpiredCallback cb, float second, bool once);

  struct event_base *base_;
  static std::shared_ptr<Timer> self_;

};

#endif