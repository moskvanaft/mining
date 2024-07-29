#include "timeline.h"

#include <iostream>

Timeline::Timeline() {}

Timeline::~Timeline() {}

void Timeline::AddEvent(unsigned int minutes_after_now, int priority,
                        Callback callback) {
  queue_.push(Event{
    .time_ = current_time_ + minutes_after_now,
    .priority_ = priority,
    callback_ : callback
  });
}

void Timeline::AddEventAtRandomTime(unsigned int minutes_after_now_min,
                                    unsigned int minutes_after_now_max,
                                    int priority, Callback callback) {
  int minutes =
      std::rand() % (minutes_after_now_max - minutes_after_now_min + 1) +
      minutes_after_now_min;
  AddEvent(minutes, priority, std::move(callback));
}

void Timeline::RunFor(unsigned int minutes) {
  while (current_time_ < minutes && !queue_.empty()) {
    auto event = std::move(queue_.top());
    queue_.pop();
    current_time_ = event.time_;
    std::cout << "Minute " << current_time_ << ':' << std::endl;
    event.callback_();
  }
}
