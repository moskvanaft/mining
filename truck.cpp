#include "truck.h"

#include "timeline.h"
#include "unload_station.h"

#include <iostream>

constexpr int kDefaultPriority = 0;
constexpr int kStartUnloadingPriority = 1;
constexpr int kEndUnloadingPriority = 2;

Truck::Truck(Timeline *timeline, UnloadStationBroker *broker, int number)
    : timeline_(timeline), broker_(broker), truck_number_(number) {
  timeline_->AddEvent(0, kDefaultPriority, [this]() { StartMining(); });
}

Truck::~Truck() {}

void Truck::StartMining() {
  timeline_->AddEventAtRandomTime(60, 300, kDefaultPriority, [this]() {
    SelectUnloadStationAndStartMovingThere();
  });
  std::cout << "Truck " << truck_number_ << " started mining" << std::endl;
}

void Truck::SelectUnloadStationAndStartMovingThere() {
  auto station = broker_->GetStation();
  timeline_->AddEvent(30, kDefaultPriority,
                      [this, station]() { TryUnloading(station); });
  std::cout << "Truck " << truck_number_
            << " finished mining and started driving to station "
            << station->GetNumber() << std::endl;
}

void Truck::TryUnloading(UnloadStation *station) {
  if (station->TryUse()) {
    timeline_->AddEvent(5, kStartUnloadingPriority, [this, station]() {
      StartDrivingToHarvestingSite();
      station->Release();
    });
    std::cout << "Truck " << truck_number_ << " started unloading at station "
              << station->GetNumber() << std::endl;
  } else {
    station->WakeupWhenAvailable([this, station] { TryUnloading(station); });
    std::cout << "Truck " << truck_number_ << " began waiting at station "
              << station->GetNumber() << std::endl;
  }
}

void Truck::StartDrivingToHarvestingSite() {
  timeline_->AddEvent(30, kEndUnloadingPriority, [this]() { StartMining(); });
  std::cout << "Truck " << truck_number_ << " started driving to mining site "
            << std::endl;
}
