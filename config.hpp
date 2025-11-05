//
// Created by neko on 11/2/25.
//

#ifndef RV64_CONFIG_HPP
#define RV64_CONFIG_HPP

#include <cstdint>
#include <string_view>
#include <string>
#include <vector>
#include "enum_helpers.hpp"

class ConfigParser {
public:
    enum class EMemoryRegionPermissions : std::uint64_t {
        None     = 0,
        Readable = 1 << 0,
        Writable = 1 << 1,
    };

    struct MemoryRegion {
        std::uint64_t start;
        std::size_t length;
        EMemoryRegionPermissions permissions;
    };

    struct LoadSection {
        std::string file;
        std::uint64_t address;
        std::size_t maxSize;
    };

    explicit ConfigParser(const std::string_view& configPath);
    const std::vector<MemoryRegion>& getMemoryRegions() const;
    const std::vector<LoadSection>& getLoadSections() const;

private:
    const std::string_view& m_configPath;
    std::vector<MemoryRegion> m_memoryRegions;
    std::vector<LoadSection> m_loadSections;

    static std::uint64_t parseHex(const std::string& str);
    static EMemoryRegionPermissions parsePermissions(const std::string& str);
};

#endif //RV64_CONFIG_HPP
