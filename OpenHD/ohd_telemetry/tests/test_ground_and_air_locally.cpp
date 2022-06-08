//
// For testing, run the air and ground telemetry services side by side on the same machine locally.
//
#include <iostream>

#include "../src/OHDTelemetry.hpp"
#include "openhd-profile.hpp"
#include "openhd-platform.hpp"
#include <thread>
#include <memory>

int main() {
  std::cout<<"start\n";
  std::unique_ptr<OHDTelemetry> ohdTelemGround;
  std::unique_ptr<OHDTelemetry> ohdTelemAir;
  {
	OHDProfile profile{false, "XX"};
	OHDPlatform platform{};
	ohdTelemGround = std::make_unique<OHDTelemetry>(platform, profile);
  }
  {
	OHDProfile profile{true, "XX"};
	OHDPlatform platform{};
	ohdTelemAir = std::make_unique<OHDTelemetry>(platform, profile);
  }
  while (true) {
	std::this_thread::sleep_for(std::chrono::seconds(1));
	const auto gLog=ohdTelemGround->createDebug();
	const auto airLog=ohdTelemAir->createDebug();
  }
}
