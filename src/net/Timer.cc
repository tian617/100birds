#include "Timer.h"
#include <assert.h>
#include <vector>
#include <queue>
#include <utility>

namespace detail
{
class Callbacks
{
  typedef std::pair<ExpiredCallback, struct event *> Func;

public:
  Callbacks() : funcs_(), availableIdxs_() {}

  int addCb(ExpiredCallback cb, struct event *ev)
  {
    Func func(cb, ev);
    int funcIdx;
    if (!availableIdxs_.empty())
    {
      funcIdx = availableIdxs_.front();
      funcs_[funcIdx] = std::move(func);
      availableIdxs_.pop();
    }
    else
    {
      funcs_.push_back(std::move(func));
      funcIdx = funcs_.size() - 1;
    }
    return funcIdx;
  }

  void delCb(int idx)
  {
    event_free(funcs_[idx].second);
    // the element will deleting next cb set
    availableIdxs_.push(idx);
  }

  int nextIdx() const
  {
    return availableIdxs_.empty() ? funcs_.size() : availableIdxs_.front();
  }

  void invoke(int idx) const
  {
    funcs_[idx].first();
  }

private:
  std::vector<Func> funcs_;
  std::queue<int> availableIdxs_;
} timerFuncs;
} // namespace detail

void timerCb(evutil_socket_t fd, short what, void *idx)
{
  detail::timerFuncs.invoke(*reinterpret_cast<int *>(idx));
}

Timer::Timer(struct event_base *base)
    : base_(base)
{
}

int Timer::setCb(ExpiredCallback cb, float second, bool once)
{
  struct timeval tv = {(int)second, (second - (int)second) * 1000000};
  int idx = detail::timerFuncs.nextIdx();
  struct event *ev = event_new(base_, -1, once ? 0 : EV_PERSIST, timerCb, &idx);
  int ret = detail::timerFuncs.addCb(cb, ev);
  assert(idx == ret);

  evtimer_add(ev, &tv);
  return idx;
}

int Timer::runEvery(ExpiredCallback cb, float second)
{
  return setCb(cb, second, false);
}

int Timer::runAfter(ExpiredCallback cb, float second)
{
  return setCb(cb, second, true);
}

void Timer::cancel(int taskId)
{
  detail::timerFuncs.delCb(taskId);
}
