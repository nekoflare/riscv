//
// Created by neko on 11/5/25.
//

#include "flat_test_memory.hpp"

#include <cstring>
#include <iostream>
#include <ostream>

flat_test_memory::flat_test_memory(size_t size)
    : mem_(size) {}

bool flat_test_memory::read(address addr, std::span<std::byte> out) noexcept {
    if (addr + out.size() > mem_.size())
        return false;
    std::memcpy(out.data(), mem_.data() + addr, out.size());
    return true;
}

bool flat_test_memory::write(address addr, std::span<const std::byte> in) noexcept {
    if (in.size() == 1 && addr == 0x1000000000) {
        // uart
        std::cout << *(char*)in.data();
        return true;
    }

    if (addr + in.size() > mem_.size())
        return false;

    std::memcpy(mem_.data() + addr, in.data(), in.size());
    return true;
}

size_t flat_test_memory::size() const noexcept {
    return mem_.size();
}

std::byte* flat_test_memory::data() noexcept {
    return mem_.data();
}

const std::byte* flat_test_memory::data() const noexcept {
    return mem_.data();
}
