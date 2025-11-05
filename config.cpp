//
// Created by neko on 11/2/25.
//

#include "config.hpp"

#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <fstream>

ConfigParser::ConfigParser(const std::string_view &configPath) : m_configPath(configPath) {
    std::ifstream file{std::string(configPath)};
    nlohmann::json j;
    file >> j;

    for (const auto& region : j["memory-regions"]) {
        MemoryRegion r{};
        r.start = parseHex(region["start"].get<std::string>());
        r.length = parseHex(region["length"].get<std::string>());
        r.permissions = parsePermissions(region["permissions"].get<std::string>());
        m_memoryRegions.push_back(r);
    }

    for (const auto& section : j["load-sections"]) {
        LoadSection s;
        s.file = section["file"].get<std::string>();
        s.address = parseHex(section["address"].get<std::string>());
        s.maxSize = parseHex(section["max-size"].get<std::string>());
        m_loadSections.push_back(s);
    }
}

const std::vector<ConfigParser::MemoryRegion>& ConfigParser::getMemoryRegions() const {
    return m_memoryRegions;
}

const std::vector<ConfigParser::LoadSection>& ConfigParser::getLoadSections() const {
    return m_loadSections;
}

std::uint64_t ConfigParser::parseHex(const std::string &str) {
    std::size_t idx = 0;
    return std::stoull(str, &idx, 0);
}

ConfigParser::EMemoryRegionPermissions ConfigParser::parsePermissions(const std::string &str) {
    auto  perms = EMemoryRegionPermissions::None;
    for (const char c : str) {
        if (c == 'r') perms |= EMemoryRegionPermissions::Readable;
        if (c == 'w') perms |= EMemoryRegionPermissions::Writable;
    }
    return perms;
}