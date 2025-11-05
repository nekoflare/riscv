//
// Created by neko on 11/4/25.
//

#ifndef RV64_STATE_HPP
#define RV64_STATE_HPP
#include <cstdint>
#include <cstring>

constexpr uint64_t X_ZERO = 0;
constexpr uint64_t X_RA   = 1;
constexpr uint64_t X_SP   = 2;
constexpr uint64_t X_GP   = 3;
constexpr uint64_t X_TP   = 4;
constexpr uint64_t X_T0   = 5;
constexpr uint64_t X_T1   = 6;
constexpr uint64_t X_T2   = 7;
constexpr uint64_t X_S0   = 8;
constexpr uint64_t X_S1   = 9;
constexpr uint64_t X_A0   = 10;
constexpr uint64_t X_A1   = 11;
constexpr uint64_t X_A2   = 12;
constexpr uint64_t X_A3   = 13;
constexpr uint64_t X_A4   = 14;
constexpr uint64_t X_A5   = 15;
constexpr uint64_t X_A6   = 16;
constexpr uint64_t X_A7   = 17;
constexpr uint64_t X_S2   = 18;
constexpr uint64_t X_S3   = 19;
constexpr uint64_t X_S4   = 20;
constexpr uint64_t X_S5   = 21;
constexpr uint64_t X_S6   = 22;
constexpr uint64_t X_S7   = 23;
constexpr uint64_t X_S8   = 24;
constexpr uint64_t X_S9   = 25;
constexpr uint64_t X_S10  = 26;
constexpr uint64_t X_S11  = 27;
constexpr uint64_t X_T3   = 28;
constexpr uint64_t X_T4   = 29;
constexpr uint64_t X_T5   = 30;
constexpr uint64_t X_T6   = 31;

struct Registers {
    uint64_t regs[32] = {};
    uint64_t pc;

    [[nodiscard]] uint64_t operator[](const std::size_t index) const noexcept {
        return index == 0 ? 0 : regs[index];
    }

    uint64_t& operator[](const std::size_t index) noexcept {
        static uint64_t dummy_zero = 0;

        if (index != X_ZERO)
            return regs[index];

        dummy_zero = 0;
        return dummy_zero;
    }

    auto& ip() { return pc; };
};

#endif //RV64_STATE_HPP
