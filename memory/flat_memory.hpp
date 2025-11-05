//
// Created by neko on 11/4/25.
//

#ifndef RV64_FLAT_MEMORY_HPP
#define RV64_FLAT_MEMORY_HPP

#include <cstddef>
#include <span>
#include <vector>
#include "base_memory.hpp"

class flat_memory final : public base_memory {
public:
    explicit flat_memory(size_t size);

    [[nodiscard]] bool read(address addr, std::span<std::byte> out) noexcept override;
    [[nodiscard]] bool write(address addr, std::span<const std::byte> in) noexcept override;

    [[nodiscard]] size_t size() const noexcept;
    [[nodiscard]] std::byte* data() noexcept;
    [[nodiscard]] const std::byte* data() const noexcept;

private:
    std::vector<std::byte> mem_;
};

#endif //RV64_FLAT_MEMORY_HPP
