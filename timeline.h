#pragma once

#include <functional>
#include <queue>

// Time represents simulated time in minutes, i.e. number of minutes since
// initial time of simulation.
using Time = unsigned int;

using Callback = std::function<void()>;

class Timeline {
public:
  Timeline();
  ~Timeline();
  void AddEvent(unsigned int minutes_after_now, int priority,
                Callback callback);
  void AddEventAtRandomTime(unsigned int minutes_after_now_min,
                            unsigned int minutes_after_now_max, int priority,
                            Callback callback);
  void RunFor(unsigned int minutes);

private:
  struct Event {
    Time time_;
    int priority_;
    Callback callback_;
  };
  struct Cmp {
    bool operator()(const Event &a, const Event &b) const {
      return a.time_ > b.time_ ||
             (a.time_ == b.time_ && a.priority_ < b.priority_);
    }
  };
  std::priority_queue<Event, std::vector<Event>, Cmp> queue_;
  Time current_time_;
};
