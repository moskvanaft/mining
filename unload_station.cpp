#include "unload_station.h"

UnloadStation::UnloadStation(int number) : number_(number), available_(true) {}

UnloadStation::~UnloadStation() {}

bool UnloadStation::TryUse() {
  if (available_) {
    available_ = false;
    return true;
  } else {
    return false;
  }
}

void UnloadStation::Release() {
  available_ = true;
  while (available_ && !waiters_.empty()) {
    waiters_.front()();
    // timeline_.AddEvent(0, std::move(waiters_.front()));
    waiters_.pop();
  }
}

void UnloadStation::WakeupWhenAvailable(Callback callback) {
  waiters_.push(std::move(callback));
}

RoundRobinUnloadStationManager::RoundRobinUnloadStationManager(
    unsigned int count) {
  stations.reserve(count);
  for (unsigned int i = 0; i < count; ++i) {
    stations.emplace_back(i);
  }
}

RoundRobinUnloadStationManager::~RoundRobinUnloadStationManager() {}

UnloadStation *RoundRobinUnloadStationManager::GetStation() {
  return &stations[(pos++) % stations.size()];
}
