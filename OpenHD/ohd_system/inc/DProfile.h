#ifndef PROFILE_H
#define PROFILE_H

#include <string>
#include <cstdint>

#include "DPlatform.h"

#include "json.hpp"

#include "openhd-platform.hpp"
#include "openhd-discoverable.hpp"

/**
 * Discover the profile we are running on and write it to json.
 */
class DProfile: public OHD::IDiscoverable {
public:
    DProfile(PlatformType platform_type, BoardType board_type, CarrierType carrier_type, int camera_count);
    
    virtual ~DProfile() = default;

    void discover() override;

    nlohmann::json generate_manifest() override;

    static std::string generate_unit_id();

    [[nodiscard]] bool is_air() const {
        return m_camera_count != 0;
    }

    std::string unit_id() {
        return m_unit_id;
    }

private:
    const PlatformType m_platform_type;
    const BoardType m_board_type;
    const CarrierType m_carrier_type;

    int m_camera_count = 0;
    std::string m_unit_id;
};

#endif
