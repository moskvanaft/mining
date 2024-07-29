#pragma once

#include "broker.h"
#include "timeline.h"

#include <memory>
#include <queue>

class UnloadStation {
public:
  using Callback = std::function<void()>;

  UnloadStation(int number);
  ~UnloadStation();

  bool TryUse();
  void Release();
  void WakeupWhenAvailable(Callback callback);

  int GetNumber() const { return number_; }

private:
  int number_;
  bool available_;
  std::queue<Callback> waiters_;
};

class RoundRobinUnloadStationManager : public UnloadStationBroker {
public:
  RoundRobinUnloadStationManager(unsigned int count);
  ~RoundRobinUnloadStationManager();

  UnloadStation *GetStation() override;

private:
  std::vector<UnloadStation> stations;
  size_t pos;
};
