#pragma once

class Timeline;
class UnloadStationBroker;
class UnloadStation;

class Truck {
public:
  Truck(Timeline *timeline, UnloadStationBroker *broker, int number);
  Truck(const Truck &) = delete;
  Truck &operator=(const Truck &) = delete;
  ~Truck();

private:
  void StartMining();
  void SelectUnloadStationAndStartMovingThere();
  void TryUnloading(UnloadStation *station);
  void StartDrivingToHarvestingSite();

  Timeline *timeline_;
  UnloadStationBroker *broker_;
  int truck_number_;
};
