#pragma once

class UnloadStation;

class UnloadStationBroker {
public:
  virtual UnloadStation *GetStation() = 0;
};
