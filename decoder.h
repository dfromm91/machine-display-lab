#pragma once
#include <cstdint>
#include <optional>
#include <vector>

inline constexpr unsigned speedFrame = 0x181;

inline std::optional<unsigned> decodeSpeed(unsigned id, const std::vector<std::uint8_t>& bytes)
{
    if (id != speedFrame || bytes.size() != 2) return std::nullopt;
    const unsigned tenths = bytes[0] | (static_cast<unsigned>(bytes[1]) << 8);
    if (tenths > 1200) return std::nullopt;
    return tenths;
}
