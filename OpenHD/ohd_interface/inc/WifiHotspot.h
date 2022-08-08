//
// Created by consti10 on 17.05.22.
//

#ifndef OPENHD_OPENHD_OHD_INTERFACE_SRC_WIFIHOTSPOT_H_
#define OPENHD_OPENHD_OHD_INTERFACE_SRC_WIFIHOTSPOT_H_

#include <vector>
#include <string>
#include "openhd-wifi.hpp"

/**
 * Wifi hotspot refers to creating a WiFi Access point on the device we are running on.
 * External clients like QOpenHD running on a tablet can then connect to the hotspot.
 * Note that video and telemetry has to be forwarded to clients connected to the wifi hotspot.
 * For that, you can register a callback here.
 * NOTE: Needs
 * hostapd and isc-dhcp-server
 */
class WifiHotspot {
 public:
  /**
   * Utility for starting, stopping WIFI AP (Hotspot) and forwarding the client connect/disconnect events.
   */
  explicit WifiHotspot(WiFiCard wifiCard);
  /**
   * initialize and start the hotspot.
   */
  void start();
  // since starting the wifi hotspot can be quite a long operation, this calls start() in a new thread.
  // TODO stop safe in regards to concurrency.
  void start_async();
  void stop_async();
  /**
   * stop,de-init and cleanup hotspot.
   */
  void stop();
 private:
  // Ip addresses of all connected clients.
  // A client might dynamically connect or disconnect from the AP at run time,
  // In this case the apropriate callbacks have to be called.
  std::vector<std::string> connectedClientsIps;
  const WiFiCard wifiCard;
  bool started=false;
  std::unique_ptr<std::thread> _start_async_thread= nullptr;
  std::unique_ptr<std::thread> _stop_async_thread= nullptr;
};

#endif //OPENHD_OPENHD_OHD_INTERFACE_SRC_WIFIHOTSPOT_H_
