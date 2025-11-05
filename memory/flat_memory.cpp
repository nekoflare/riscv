//
// Created by neko on 11/4/25.
//

#include "flat_memory.hpp"

#include <cstring>

flat_memory::flat_memory(size_t size)
    : mem_(size) {}

bool flat_memory::read(address addr, std::span<std::byte> out) noexcept {
    if (addr + out.size() > mem_.size())
        return false;
    std::memcpy(out.data(), mem_.data() + addr, out.size());
    return true;
}

bool flat_memory::write(address addr, std::span<const std::byte> in) noexcept {
    if (addr + in.size() > mem_.size())
        return false;
    std::memcpy(mem_.data() + addr, in.data(), in.size());
    return true;
}

size_t flat_memory::size() const noexcept {
    return mem_.size();
}

std::byte* flat_memory::data() noexcept {
    return mem_.data();
}

const std::byte* flat_memory::data() const noexcept {
    return mem_.data();
}
