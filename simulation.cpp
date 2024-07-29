#include "timeline.h"
#include "truck.h"
#include "unload_station.h"

#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>

static int readArgValueOrExit() {
  size_t pos;
  std::string s = optarg;
  int val = std::stoi(s, &pos);
  if (pos != s.size()) {
    std::cerr << "Wrong value " << s << std::endl;
    std::exit(1);
  }
  return val;
}

int main(int argc, char *argv[]) {
  int num_trucks = 0;
  int num_stations = 0;
  int opt;
  while ((opt = getopt(argc, argv, "t:s:")) != -1) {
    switch (opt) {
    case 't':
      num_trucks = readArgValueOrExit();
      break;
    case 's':
      num_stations = readArgValueOrExit();
      break;
    case '?':
      printf("unknown option: %c\n", optopt);
      return 1;
    }
  }

  if (num_trucks <= 0 || num_stations <= 0) {
    std::cerr
        << "Usage: simulation -t <number of trucks> -s <number of stations>"
        << std::endl
        << "Example: simulation -t 30 -s 2" << std::endl;
    return 1;
  }

  Timeline timeline;
  RoundRobinUnloadStationManager broker(num_stations);
  std::deque<Truck> trucks;
  for (int i = 0; i < num_trucks; ++i) {
    trucks.emplace_back(&timeline, &broker, i);
  }
  timeline.RunFor(72 * 60);
  return 0;
}
