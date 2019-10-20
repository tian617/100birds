#include "Timer.h"
#include <assert.h>
#include <vector>
#include <queue>
#include <memory>
#include <utility>

namespace detail
{
class Callbacks
{
  typedef std::pair<ExpiredCallback, struct event *> Func;

public:
  Callbacks() : funcs_(), availableIdxs_() {}

  void addCb(ExpiredCallback cb, struct event *ev,int idx)
  {
    Func func(cb, ev);
    if(idx<funcs_.size())
    {
      funcs_[idx]=std::move(func);
    }
    else
    {
      funcs_.push_back(std::move(func));     
    }
  }

  void delCb(int idx)
  {
    event_free(funcs_[idx].second);
    // the element will deleting next cb set
    availableIdxs_.push(idx);
  }

  int* nextIdx()
  {
    if(availableIdxs_.empty())
    {
      idxs_.emplace_back(new int(idxs_.size()));
      return idxs_.back().get();
    }
    else
    {
      int idx=availableIdxs_.front();
      availableIdxs_.pop();
      return idxs_[idx].get();
    }
  }

  void invoke(int idx) const
  {
    funcs_[idx].first();
  }

private:
  std::vector<Func> funcs_;
  std::queue<int> availableIdxs_;
  std::vector<std::unique_ptr<int>> idxs_;  // save alloc int of index
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

  struct timeval tv = {(long)second, (long)((second - (int)second) * 1000000)};
  int *idx = detail::timerFuncs.nextIdx();
  struct event *ev = event_new(base_, -1, once ? 0 : EV_PERSIST, timerCb, idx);
  detail::timerFuncs.addCb(cb, ev,*idx);
  evtimer_add(ev, &tv);
  return *idx;
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

std::shared_ptr<Timer> Timer::self_;
void Timer::init(struct event_base *base)
{
  self_ = std::shared_ptr<Timer>(new Timer(base));
  printf("init timer\n");
}

std::shared_ptr<Timer> Timer::instance()
{
  return Timer::self_;
}
