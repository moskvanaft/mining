#include "timeline.h"
#include "truck.h"
#include "unload_station.h"

int main() {
  Timeline timeline;
  RoundRobinUnloadStationManager broker(1);
  std::deque<Truck> trucks;
  for (int i = 0; i < 20; ++i) {
    trucks.emplace_back(&timeline, &broker, i);
  }
  timeline.RunFor(72 * 60);
  return 0;
}
