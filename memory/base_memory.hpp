//
// Created by neko on 11/4/25.
//

#ifndef RV64_BASE_MEMORY_HPP
#define RV64_BASE_MEMORY_HPP

#include <cstddef>
#include <cstdint>
#include <span>
#include <optional>

class base_memory {
public:
    using address = std::uintptr_t;
    virtual ~base_memory() = default;

    [[nodiscard]] virtual bool read(address addr, std::span<std::byte> out) noexcept = 0;
    [[nodiscard]] virtual bool write(address addr, std::span<const std::byte> in) noexcept = 0;

    template<typename T>
    [[nodiscard]] std::optional<T> read_value(address addr) noexcept {
        T v{};
        auto buf = std::span(reinterpret_cast<std::byte*>(&v), sizeof(T));
        if (!read(addr, buf)) return std::nullopt;
        return v;
    }

    template<typename T>
    [[nodiscard]] bool write_value(address addr, const T &v) noexcept {
        auto buf = std::span(reinterpret_cast<const std::byte*>(&v), sizeof(T));
        return write(addr, buf);
    }
};


#endif //RV64_BASE_MEMORY_HPP
